#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <armadillo>
#include "preprocessor/preprocessing.hpp"

using namespace cv;
using namespace AIX;
int main(int argc, char** argv )
{
    auto imagepath = "../../resources/lena_color.jpg";   

    Mat image;
    image = imread(imagepath, cv::IMREAD_COLOR );    

    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    Mat imageshrunk;
    cv::resize(image, imageshrunk,cv::Size(8,8));

    auto rgbmat =  CNN::get_normalized_rgb_image_transform(&imageshrunk);
    std::cout<<"RED"<<std::endl<<*rgbmat[CNN::ImageChannel::RED]<<std::endl;
    std::cout<<"GREEN"<<std::endl<<*rgbmat[CNN::ImageChannel::GREEN]<<std::endl;
    std::cout<<"BLUE"<<std::endl<<*rgbmat[CNN::ImageChannel::BLUE]<<std::endl;

    auto graymat =  CNN::get_normalized_rgb_image_transform_gray(&imageshrunk);
    std::cout<<"GRAYSCALE"<<std::endl<<*graymat<<std::endl;
    //namedWindow("Display Image", WINDOW_AUTOSIZE );
    //imshow("Display Image", imageshrunk);
    //imshow("Display Image", image);
    //waitKey(0);

    std::cout<<"OK";
    return 0;
}