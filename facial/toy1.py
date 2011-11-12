#!/usr/bin/python
#import cv,pygame,Image
import sys,os
from opencv.cv import *
from opencv.highgui import *
import Image
dist_img=""
rgb_img=""
out_img="inp1.out.jpg"
inp_img="./inp1.jpg"
window=""

def displayObject(image):
  cvNamedWindow("face", 1)
  cvShowImage("face", image)
  cvWaitKey(0)
  cvDestroyWindow("face")


def paintfaces(img,faces):
	global inp_img;
	global out_img;
	print faces
	return 0;

def findfaces(img):
	#displayObject(img);
	image_size=cvGetSize(img);
	grayscale = cvCreateImage(image_size, 8, 1)

	cvCvtColor(img, grayscale, CV_BGR2GRAY)

	storage = cvCreateMemStorage(0)
	cvClearMemStorage(storage)
	cvEqualizeHist(grayscale, grayscale)

	cascade = cvLoadHaarClassifierCascade('haarcascade_frontalface_alt.xml', cvSize(1,1))
	faces = cvHaarDetectObjects(grayscale, cascade, storage, 1.2, 2, 
                              CV_HAAR_DO_CANNY_PRUNING, cvSize(20,20))
	if faces:
        	print 'faces detected!'
		for i in faces:
			print i;
			cvRectangle(img, cvPoint( int(i.x), int(i.y)),
			cvPoint(int(i.x+i.width), int(i.y+i.height)),
			CV_RGB(0,255,0), 3, 8, 0)
		displayObject(img)
	return faces;
def parseArgs():
	print()

def main():
	global inp_img;
	print "started"
	parseArgs()
	img = cvLoadImage(inp_img);
	faces=findfaces(img)
	paintfaces(img,faces);
if __name__=='__main__':main()
