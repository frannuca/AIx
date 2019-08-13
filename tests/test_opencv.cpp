#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <armadillo>
#include "preprocessing.hpp"

using namespace cv;

int main(int argc, char** argv )
{
    auto imagepath = "~/code/cpp/github/cnn/resources/lena_color.jpg";   

    Mat image;
    image = imread(imagepath, cv::IMREAD_COLOR );    

    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    Mat imageshrunk;
    cv::resize(image, imageshrunk,cv::Size(8,8));

    auto rgbmat =  cnn::preprocessing::get_normalized_rgb_image_transform(&imageshrunk);
    std::cout<<"RED"<<std::endl<<*rgbmat[cnn::preprocessing::ImageChannel::RED]<<std::endl;
    std::cout<<"GREEN"<<std::endl<<*rgbmat[cnn::preprocessing::ImageChannel::GREEN]<<std::endl;
    std::cout<<"BLUE"<<std::endl<<*rgbmat[cnn::preprocessing::ImageChannel::BLUE]<<std::endl;

    auto graymat =  cnn::preprocessing::get_normalized_rgb_image_transform_gray(&imageshrunk);
    std::cout<<"GRAYSCALE"<<std::endl<<*graymat<<std::endl;
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", imageshrunk);
    //imshow("Display Image", image);
    waitKey(0);

    return 0;
}