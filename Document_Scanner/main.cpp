#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// Process image for dilate image  //
Mat preProcessing(Mat img)
{
    Mat imgGray, imgCanny, imgBlur, imgDilate;
    
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(img, imgBlur, Size(7,7), 5, 0);
    Canny(imgBlur, imgCanny, 25, 75);
    Mat karnel = getStructuringElement(MORPH_RECT, Size(5,5));
    dilate(imgCanny, imgDilate, karnel);
    
    //erode(imgDilate, imgErode, karnel);    
    return imgDilate;
}

// find biggest object contourns and return points //
vector<Point> getContourns(Mat img, Mat imgDilate)
{
    vector<vector<Point>> contourns;
    vector<Vec4i> hierarchy;
    vector<Point> biggest;
    int maxArea=0;

    findContours(imgDilate, contourns, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    for(int i=0; i<contourns.size(); i++)
    {
        vector<vector<Point>> conPoly(contourns.size());
        vector<Rect> boundRect(contourns.size());
        string objectType;
        int area = contourArea(contourns[i]);

        if(area > 1000)
        {
            float peri = arcLength(contourns[i], true);
            approxPolyDP(contourns[i], conPoly[i], 0.02*peri, true);

            if(area > maxArea && conPoly[i].size() == 4)
            {
                //drawContours(img, conPoly, i, Scalar(255,0,255), 5);
                biggest = {conPoly[i][0], conPoly[i][1], conPoly[i][2], conPoly[i][3]};
                maxArea = area;
            } 
        }
    }
    return biggest;
}

// draw rectangle vertices //
void drawPoints(Mat img, vector<Point> points, Scalar color)
{
    for(int i=0; i<points.size(); i++)
    {
        circle(img, points[i], 10, color, FILLED);
        putText(img, to_string(i), points[i], FONT_HERSHEY_PLAIN, 4, color, 4);
    }
}

// sort the vertices of the rectangle //
vector<Point> reorder(vector<Point> points)
{
    vector<Point> newPoints;
    vector<int> sumPoints, subPoints;

    for(int i=0; i<points.size(); i++)
    {
        sumPoints.push_back(points[i].x + points[i].y);
        subPoints.push_back(points[i].x - points[i].y);
    }

    // index 0
    newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);
    // index 1
    newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);
    // index 2
    newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);
    // index 3
    newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);

    return newPoints;
}

// warp image //
Mat getWarp(Mat img, vector<Point> points, float w, float h)
{
    Mat imgWarp;
    Point2f src[4] = {points[0], points[1], points[2], points[3]};
    Point2f dst[4] = {{0.0f,0.0f},{w, 0.0f},{0.0f, h},{w,h}};
 
    Mat matrix = getPerspectiveTransform(src, dst);
    warpPerspective(img, imgWarp, matrix, Point(w, h));

    return imgWarp;
}

int main()
{
    //VideoCapture cap(2);
    Mat imgOriginal = imread("Resources/paper.jpg");
    resize(imgOriginal, imgOriginal, Size(420, 596), 0.5, 0.5);

    // Preprocessing: imgOriginal -> imgThre
    Mat imgThre = preProcessing(imgOriginal);

    // Get contourns - Biggest
    vector<Point> initialPoints = getContourns(imgOriginal ,imgThre);
    vector<Point> docPoints = reorder(initialPoints);
    //drawPoints(imgOriginal, docPoints, Scalar(0,255,0));

    // Warp
    float w = 420, h = 596;
    Mat imgWarp = getWarp(imgOriginal, docPoints, w, h);

    // Crop
    int cropVal = 5;
    Rect roi(cropVal, cropVal, w-(2*cropVal), h-(2*cropVal));
    Mat imgCrop = imgWarp(roi);

    imshow("image", imgOriginal);
    imshow("image Warp", imgWarp);
    imshow("image Scanner", imgCrop);
    waitKey(0);

    return 0;
}