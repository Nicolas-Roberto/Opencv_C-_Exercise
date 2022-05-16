#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main()
{
    Mat img(512,512, CV_8UC3, Scalar(100,20,50));

    circle(img, Point(256,256), 166, Scalar(200,34,240),FILLED);
    rectangle(img, Point(120, 210), Point(400,300), Scalar(100,20,50), 3);
    line(img, Point(130,296), Point(382,296), Scalar(100,20,50), 4);

    putText(img,"Texto Aqui", Point(125, 205), FONT_HERSHEY_SCRIPT_COMPLEX, 0.75, Scalar(200,34.240), 6);

    imshow("image", img);
    //imshow("image Resize", imgResize);

    waitKey(0);


    return 0;
}