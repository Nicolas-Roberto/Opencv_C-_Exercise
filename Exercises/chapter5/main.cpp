#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

float w=250, h=350;

int main()
{
    Mat img = imread("Resources/cards.jpg");
    Mat imgWarp, matrix;

    //112,220  289,189   154,482  352,440
    Point2f src[4] = {{112,220},{154,482},{289,189},{352,440}};
    Point2f dst[4] = {{0.0f,0.0f},{0.0f,h},{w,0.0f},{w,h}};
 
    matrix = getPerspectiveTransform(src, dst);
    warpPerspective(img, imgWarp, matrix, Point(w, h));

    Point2f dst2[4] = {{0.0f,25},{0.0f,h+25},{w+15,-25},{w+15,h-25}};
    matrix = getPerspectiveTransform(dst, dst2);
    Mat imgWarp2;
    warpPerspective(imgWarp, imgWarp2, matrix, Point(w, h));

    for(int i=0; i<4; i++)
    {
        circle(img, src[i], 10, Scalar(0,0,255), FILLED);
    }

    imshow("image", img);
    imshow("image Warp", imgWarp);
    imshow("image Warp2", imgWarp2);

    waitKey(0);


    return 0;
}