#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;


/*
*ref: http://opencv.itseez.com/doc/tutorials/objdetect/cascade_classifier/cascade_classifier.html
*30/Aug/2012
*
* runs a cascade on an image
* args:
*  Mat image - The image to run cascade on
*  cc_path - The cascade classifier xml path
* returns:
*  list of faces, i think faces[].{x,y,width,height}...
*/
std::vector<Rect> detect(Mat image,string cc_path){
    CascadeClassifier cascade;
    if( !cascade.load( cc_path ) ){ 
        cout << "Error loading cascade classifier: " << cc_path;
    }
    std::vector<Rect> faces;
    Mat frame_gray;
    cvtColor( image, frame_gray, CV_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    //-- Detect faces
    cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
    cout << "Detected :" << faces.size() << " Objects";
    return faces; 
}

/*
* Draw circlers around detected faces
*/
Mat circlefaces(Mat image, std::vector<Rect> faces){
    Mat ret;
    memcpy(image,ret,sizeof(image));
    //Mat ret;
    //ret=image;
    for( int i = 0; i < faces.size(); i++ ){
        Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
        ellipse( ret, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
    }
    return ret;
}

/*
*ref: http://nashruddin.com/opencv-examples-for-operation-on-images.html/4/
*31/Aug/2012
*
*Save detected faces to sperate files
*/
void extractfaces(Mat image, std::vector<Rect> faces){
}

void usage(){
    cout << "usage: cascade_circles image_file cascade_classifier_xml_file";
}

int main(int argc, char** argv) {
    string image_path = argv[1];
    string cascade_path = argv[2];
    //if (!image_path || !cascade_path) usage();
    cv::Mat image = cv::imread(image_path);
    std::vector<Rect> faces = detect(image, cascade_path);
    Mat output_image = circlefaces(image,faces);
    cv::imshow("Big Society, for XL people!",image);
    cv::imshow("Big Society, for circles people!",output_image);
    cvWaitKey(0);
    return (EXIT_SUCCESS);
}
