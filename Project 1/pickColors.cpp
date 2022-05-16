#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat imgHSV, mask;
int hmin=52, smin=0, vmin=55;
int hmax=104 ,smax=255, vmax=255;

VideoCapture cap(2);
Mat img;

int main()
{
    

    namedWindow("Trackbars", (630,200));
    createTrackbar("Hue min", "Trackbars", &hmin, 255);
    createTrackbar("Hue max", "Trackbars", &hmax, 255);
    createTrackbar("Sat min", "Trackbars", &smin, 255);
    createTrackbar("Sat max", "Trackbars", &smax, 255);
    createTrackbar("Val min", "Trackbars", &vmin, 255);
    createTrackbar("Val max", "Trackbars", &vmax, 255);


    
    while(true)
    {
        cap.read(img);
        
        cvtColor(img, imgHSV, COLOR_BGR2HSV);
        
        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);
        
        inRange(imgHSV, lower, upper, mask);
        cout << hmin << "," << hmax << "," << smin << "," << smax << "," << vmin << "," << vmax << endl;

        imshow("image", img);
        //imshow("image HSV", imgHSV);
        imshow("image mask", mask);

        waitKey(1);
    }
    

 
    return 0;
}