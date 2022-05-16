#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;



int main()
{
    Mat img = imread("Resources/img.jpg");
    Mat imgGray, imgBlur, imgCanny, imgDilate, imgErode;

    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(img, imgBlur, Size(7,7), 5, 0);
    Canny(imgBlur, imgCanny, 25, 75);
    
    Mat karnel = getStructuringElement(MORPH_RECT, Size(5,5));
    dilate(imgCanny, imgDilate, karnel);
    erode(imgDilate, imgErode, karnel);

    imshow("image", img);
    imshow("image gray", imgGray);
    imshow("image blur", imgBlur);
    imshow("image Canny", imgCanny);
    imshow("image Dilate", imgDilate);
    imshow("image Erode", imgErode);

    waitKey(0);


    return 0;
}