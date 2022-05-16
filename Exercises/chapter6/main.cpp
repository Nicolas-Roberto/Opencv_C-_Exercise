#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;
int hmin=0, smin=120, vmin=153;
int hmax=19 ,smax=240, vmax=255;

int main()
{
    Mat img = imread("Resources/lambo.png");
    Mat imgHSV, mask;

    cvtColor(img, imgHSV, COLOR_BGR2HSV);
    namedWindow("Trackbars", (630,200));
    createTrackbar("Hue min", "Trackbars", &hmin, 179);
    createTrackbar("Hue max", "Trackbars", &hmax, 179);
    createTrackbar("Sat min", "Trackbars", &smin, 179);
    createTrackbar("Sat max", "Trackbars", &smax, 179);
    createTrackbar("Val min", "Trackbars", &vmin, 179);
    createTrackbar("Val max", "Trackbars", &vmax, 179);


    
    while(true)
    {
        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);
        inRange(imgHSV, lower, upper, mask);

        imshow("image", img);
        imshow("image HSV", imgHSV);
        imshow("image mask", mask);

        waitKey(1);
    }
    

 
    return 0;
}