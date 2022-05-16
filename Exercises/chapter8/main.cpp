#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main()
{
    Mat img = imread("Resources/girl.jpg");
    Mat imgResize;

    CascadeClassifier faceCascade;
    faceCascade.load("Resources/haarcascade_frontalface_default.xml");

    if(faceCascade.empty()) cout << "XML file not loaded" << endl;

    vector<Rect> faces;

    faceCascade.detectMultiScale(img, faces, 1.1, 10);

    for(int i=0; i<faces.size(); i++)
    {
        rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255,0,255), 2);
    }

    imshow("image", img);
    

    waitKey(0);


    return 0;
}