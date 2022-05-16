#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main()
{
    Mat img = imread("Resources/img.jpg");
    Mat imgResize, imgCrop;

    cout << img.size << endl;
    resize(img, imgResize, Size(), 0.5, 0.5);
    cout << imgResize.size << endl;


    Rect roi(150, 150, 300, 250);
    imgCrop = img(roi);

    imshow("image", img);
    imshow("image Resize", imgResize);
    imshow("image Crop", imgCrop);

    waitKey(0);


    return 0;
}