#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//IMAGE
void image()
{
    Mat img = imread("Resources/img.jpg");
    imshow("image", img);
    waitKey(0);
}

//Video
void video()
{
   VideoCapture cap("Resources/video.mp4");
   Mat img;

   while(true)
   {
       cap.read(img);
       imshow("Image", img);
       waitKey(1);
   }
}

//webca,
void webcam()
{
   VideoCapture cap(0);
   Mat img;

   while(true)
   {
       cap.read(img);
       imshow("Image", img);
       waitKey(1);
   }
}

int main()
{
    //image();
    //video();
    webcam();
    return 0;
}