#include "preprocessor/preprocessing.hpp"

namespace AIX{namespace CNN{
    
        std::function<cv::Mat*(const cv::Mat*)> get_image_size_transform(size_t size_x,size_t size_y){
            cv::Size dstsz(size_x,size_y);
            return [size_x,size_y,dstsz](const cv::Mat* input){
                cv::Mat* dst = new cv::Mat();
                cv::resize(*input,*dst,dstsz);
                return dst;
            };
        }


        std::map<ImageChannel,arma::mat*> get_normalized_rgb_image_transform(const cv::Mat* image){
                cv::Size sz = image->size();
                int h = sz.height;
                int w = sz.width;

                // cv::Mat grey;
                // cv::cvtColor(*image, grey, CV_RGB2GRAY);
                arma::mat* dest_r= new arma::mat(h,w);
                arma::mat* dest_g= new arma::mat(h,w);
                arma::mat* dest_b= new arma::mat(h,w);
                for(int i=0;i<h;++i){
                    for(int j=0;j<w;++j){
                        const cv::Point3_<uchar>* p = image->ptr< cv::Point3_<uchar> >(i,j);
                        //cv::Vec3b p = image->at<cv::Vec3b>(i,j);
                        (*dest_r)(i,j)=p->x/255.0-0.5;
                        (*dest_g)(i,j)=p->z/255.0-0.5;
                        (*dest_b)(i,j)=p->y/255.0-0.5;                        
                    }
                }

                return {{ImageChannel::RED, dest_r},{ImageChannel::GREEN,dest_g},{ImageChannel::BLUE,dest_b}};
                
        }    

        arma::mat* get_normalized_rgb_image_transform_gray(const cv::Mat* image){
                cv::Size sz = image->size();
                int h = sz.height;
                int w = sz.width;

                cv::Mat grey;
                cv::cvtColor(*image, grey, cv::COLOR_RGB2GRAY);
                arma::mat* dest= new arma::mat(h,w);
                
                for(int i=0;i<h;++i){
                    for(int j=0;j<w;++j){
                        
                        (*dest)(i,j)=(double)image->at<uchar>(i,j)/255.0-0.5;
                    }
                }

                return dest; 
        }        
                
    
}}