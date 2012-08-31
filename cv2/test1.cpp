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
    if (faces.size() == 0){ exit(1); }
    cout << "Detected :" << faces.size() << " Objects";
    return faces; 
}

/*
*ref: http://nashruddin.com/opencv-examples-for-operation-on-images.html/4/
*     http://nashruddin.com/OpenCV_Region_of_Interest_%28ROI%29
*     31/Aug/2012
*
*Save detected faces to sperate files
*/
void extractfaces(Mat image, std::vector<Rect> faces){
    for( int i = 0; i < faces.size(); i++ ){
        int x=faces[i].x;
        int y=faces[i].y;
        int w=faces[i].width;
        int h=faces[i].height;
        Rect roi(x,y,w,h);
        Mat image_roi = image(roi);
        //cv::Mat face = image(cv::Rect(0,0),cv::Rect(10,10));
        cv::imshow("face",image_roi);
        cvWaitKey(0);
        //Mat face = image(Range(x,y),Range(w,h));
        
        //IplImage ipl = image::IplImage();
        //cvSetImageROI(ipl, cvRect(faces[i].x, 15, 150, 250));   
    }

}

void usage(){
    cout << "extract_objects input_image cascade_classifier_path output_directory";
}

int main(int argc, char** argv) {
    string image_path = argv[1];
    string cascade_path = argv[2];
    string output_path = argv[3];
    //if (!image_path || !cascade_path) usage();
    cv::Mat image = cv::imread(image_path);
    std::vector<Rect> faces = detect(image, cascade_path);
    extractfaces(image,faces);
    cv::imshow(image_path,image);
    cvWaitKey(0);
    return (EXIT_SUCCESS);
}
