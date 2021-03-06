#include "mlp/ffnn.hpp"
#include "concurrency/scheduler.hpp"
#include "utils.hpp"
namespace{
bool checknan(const arma::mat& a){
            double x = arma::accu(a);
            
            return x!=x;
};

bool checknan(const arma::vec& a){
            double x = arma::sum(a);
            return x!=x;
};

bool checknan(const std::vector<double>& gf){
    double x = std::accumulate(gf.begin(),gf.end(),0.0);
    return x != x;
}
}
namespace AIX{namespace MLP{

   
    FeedForwardNN::FeedForwardNN(){

    }
    void FeedForwardNN::init(){
        _bestError=1e9;
       for(auto&w :_Ws){            
            _Ws_best.push_back(w);
        }
    }
    void FeedForwardNN::withInputLayer(size_t number_of_inputs){
        _number_inputs = number_of_inputs;
    }

    void FeedForwardNN::withHiddenLayer(std::unique_ptr<Layer>  x){
        _layers.push_back(std::move(x));
    }

    void FeedForwardNN::withOutputLayer(std::unique_ptr<Layer>  x){
        _outputLayer = std::move(x);
    }
    

    void FeedForwardNN::withLossFunctions(std::function<double(const arma::vec&, const arma::vec&)> f, std::function<arma::vec(const arma::vec&, const arma::vec&)> df){
        _floss = f;
        _dfloss = df;
      
    }
    
    double FeedForwardNN::forward(const arma::vec& xin, const arma::vec& y) const {
        
        arma::vec x=xin;
        _input=xin;
        _input_1 = extendvector(xin);
        _output = y;
                
        for(size_t i=0;i <_layers.size();++i){
            x = _layers[i]->forward(x,_Ws[i],&y);            
        } 

        
        //compute loss:
         _loss = _floss(x,y);
         
        //compute derivative of the loss
        _dloss = _dfloss(x,y);
               
        return _loss;
        
    }

    arma::vec FeedForwardNN::operator()(const arma::vec& x) const{
        arma::vec s = x;
        for(size_t i=0;i <_layers.size();++i){
            s = (*_layers[i])(s,_Ws[i]);
        } 
        return s;
    }

    FeedForwardNN::~FeedForwardNN(){};

 
    double FeedForwardNN::train(const TrainingSet& trainingset, size_t niter, double tol) const{
                

        double totalerr=std::numeric_limits<double>::max();
        
        std::mt19937 gen(42);
        std::vector<int> rindex(trainingset.size());
        std::generate(rindex.begin(),rindex.end(),[n=0]() mutable{return n++;});
        

        int counter=niter;
        while(niter-- && totalerr > tol){
                totalerr = 0.0;
                std::shuffle(rindex.begin(),rindex.end(),gen);
         
                std::for_each(rindex.begin(),rindex.end(),
                                [&](const int& n){
                                        auto &x = trainingset[n];
                                        totalerr += forward(x.input.col(0),x.output.col(0));
                                        backward();
                                });

                update(totalerr);
                std::cout<<"Iteration "<<niter<<" Error="<<totalerr<<std::endl;   
        }
                                                                                         
        _Ws = _Ws_best;        
        return totalerr;
    }

    void FeedForwardNN::checkforbest(const double& totalerror) const{
        if(_bestError>=totalerror){
                _bestError = totalerror;
                _Ws_best.clear();

                for(auto xW:_Ws) _Ws_best.push_back(xW);
            }
    }
}}
