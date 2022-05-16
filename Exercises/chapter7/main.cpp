#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


void getContourns(Mat imgDilate, Mat img)
{
    vector<vector<Point>> contourns;
    vector<Vec4i> hierarchy;

    findContours(imgDilate, contourns, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    //drawContours(img, contourns,-1, Scalar(255,0,255), 2);

    for(int i=0; i<contourns.size(); i++)
    {
        vector<vector<Point>> conPoly(contourns.size());
        vector<Rect> boundRect(contourns.size());
        string objectType;
        int area = contourArea(contourns[i]);
        cout<<area<< endl;
        if(area > 1000)
        {
            float peri = arcLength(contourns[i], true);
            approxPolyDP(contourns[i], conPoly[i], 0.02*peri, true);
            cout<<conPoly[i].size()<<endl;
            
            boundRect[i] = boundingRect(conPoly[i]);

            int objCor = (int)conPoly[i].size();
            if(objCor == 3) objectType = "Tri";
            if(objCor == 4) 
            {
                float aspRatio = (float)boundRect[i].width/(float)boundRect[i].height;
                if(aspRatio > 0.95 && aspRatio < 1.05) { objectType = "Square"; }
                else { objectType = "Rect"; }
            }
            if(objCor > 4) objectType = "Circ";

            drawContours(img, conPoly, i, Scalar(255,0,255), 2);
            rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(50,255,50),2);
            putText(img, objectType, {boundRect[i].x, boundRect[i].y-3}, FONT_HERSHEY_COMPLEX_SMALL, 0.5, Scalar(50,255,50), 1);

        }
    }
}

int main()
{
    Mat img = imread("Resources/shapes.jpg");
    Mat imgGray, imgBlur, imgCanny, imgDilate, imgErode;

    //preprocessing
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(imgGray, imgBlur, Size(3,3), 3, 0);
    Canny(imgBlur, imgCanny, 25, 75);
    Mat karnel = getStructuringElement(MORPH_RECT, Size(5,5));
    dilate(imgCanny, imgDilate, karnel);

    getContourns(imgDilate, img);

    imshow("image", img);
    /*imshow("image Gray", imgGray);
    imshow("image Blur", imgBlur);
    imshow("image Canny", imgCanny);
    imshow("image Dilate", imgDilate);*/

    waitKey(0);


    return 0;
}