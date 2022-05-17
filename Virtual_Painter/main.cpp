#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat img;
vector<vector<int>> newPoints;

// from hmin,hmax,smin,smax,vmin,vmax
// to hmin, smin, vmin, hmax, smax, vmax
vector<vector<int>> myColors {{0,194,44,88,255,197}};
vector<Scalar> myColorsValue{{0,255,0}};

// find object contourns and return one point //
Point getContourns(Mat imgDilate)
{
    vector<vector<Point>> contourns;
    vector<Vec4i> hierarchy;
    Point myPoint(0, 0);

    findContours(imgDilate, contourns, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    //drawContours(img, contourns,-1, Scalar(255,0,255), 2);

    for(int i=0; i<contourns.size(); i++)
    {
        vector<vector<Point>> conPoly(contourns.size());
        vector<Rect> boundRect(contourns.size());
        string objectType;
        int area = contourArea(contourns[i]);
        //cout<<area<< endl;
        if(area > 1000)
        {
            float peri = arcLength(contourns[i], true);
            approxPolyDP(contourns[i], conPoly[i], 0.02*peri, true);
            //cout<<conPoly[i].size()<<endl;
            
            boundRect[i] = boundingRect(conPoly[i]);
            myPoint.x = boundRect[i].x + boundRect[i].width / 2;
            myPoint.y = boundRect[i].y;

            drawContours(img, conPoly, i, Scalar(255,0,255), 2);
            
        }
    }
    return myPoint;
}

// find object color //
vector<vector<int>> findColor()
{
    Mat imgHSV;
    cvtColor(img, imgHSV, COLOR_BGR2HSV);

    for(int i=0; i<myColors.size(); i++)
    {
        Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
        Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
        
        Mat mask;
        inRange(imgHSV, lower, upper, mask);
        
        //show windows with each one mask
        //imshow(to_string(i), mask);

        Point myPoint = getContourns(mask);
        if(myPoint.x != 0 && myPoint.y != 0)
        {
            newPoints.push_back({myPoint.x, myPoint.y, i});
        }
    }
    return newPoints;

}

// draw image //
void drawOnCanvas(vector<vector<int>> myPoints, vector<Scalar> myColorsValue)
{
    for(int i=0; i<myPoints.size(); i++)
    {
        circle(img, Point(newPoints[i][0], newPoints[i][1]), 10, myColorsValue[newPoints[i][2]], FILLED);
    }
}

int main()
{
    // in cap(x) you select your webcam, 0 is default cam, 2 is my droidcam
    VideoCapture cap(2);
    

    while(true)
    {
        cap.read(img);
        newPoints = findColor();
        drawOnCanvas(newPoints, myColorsValue);

        imshow("image", img);
        waitKey(1);
    }

    return 0;
}