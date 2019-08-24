#ifndef ACTIVATIONS_H
#define ACTIVATIONS_H

namespace AIX{
    class IActivation{
        public:
           virtual double f(const double&) = 0; 
           virtual double df(const double&) = 0; 
           virtual ~IActivation(){};
    };

    class Sigmoid:public IActivation{
        private:
            const double c;
        
        public:
           Sigmoid()=delete;
           Sigmoid(double c);
           double f(const double&) override; 
           double df(const double&) override; 
    };

    class HyperbolicTangent:public IActivation{
        private:
            const double c;
        
        public:
           HyperbolicTangent()=delete;
           HyperbolicTangent(double c);
           double f(const double&) override; 
           double df(const double&) override; 
    };

    class Exponential:public IActivation{
        private:
            const double c;
        
        public:
           Exponential()=delete;
           Exponential(double c);
           double f(const double&) override; 
           double df(const double&) override; 
    };

    class ReLU:public IActivation{
    private:
        const double leak;
        const double slope;
    
    public:
        ReLU()=delete;
        ReLU(double leak_,double slope_);
        double f(const double&) override; 
        double df(const double&) override; 
};
}
#endif