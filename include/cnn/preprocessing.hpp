#ifndef PREPOCESSING_H
#define PREPOCESSING_H
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <functional>
#include <armadillo>
#include <map>

namespace AIX{
    namespace CNN{

         enum class ImageChannel{
            RED,
            GREEN,
            BLUE
        };


        std::function<cv::Mat*(const cv::Mat*)> get_image_size_transform(size_t size_x,size_t size_y);
       
        /**
         * Given an input BGR image in formt cv::Mat, transfers it into thre arma::mat images 
         */        
        std::map<ImageChannel,arma::mat*> get_normalized_rgb_image_transform(const cv::Mat*);
        arma::mat* get_normalized_rgb_image_transform_gray(const cv::Mat*);
    }
}
#endif