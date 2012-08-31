#include <stdlib.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
int main(int argc, char** argv) {
    cv::Mat image = cv::imread("Big-Society.jpg");
    cv::imshow("img",image);
    cvWaitKey(0);
    cout << "Hi \n";
    return (EXIT_SUCCESS);
}
