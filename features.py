#!/usr/bin/python
import cv,pygame,Image
dist_img=""
rgb_img=""
out_img=""

window=""

def goodFeatures(img):
        eig_image = cv.CreateMat(img.rows, img.cols, cv.CV_32FC1)
        temp_image = cv.CreateMat(img.rows, img.cols, cv.CV_32FC1)
	ret=[]
        for (x,y) in cv.GoodFeaturesToTrack(img, eig_image, temp_image, 10, 0.04, 1.0, useHarris = True):
		ret.append((x,y))
	return ret;

#Takes file names
def paintFeatures(inp,out):
	img = cv.LoadImageM(inp,cv.CV_LOAD_IMAGE_GRAYSCALE);
	gf=goodFeatures(img);
	omg = cv.CreateImage(cv.GetSize(img), cv.IPL_DEPTH_16S, 3)
	for (x,y) in gf:
		#print "x",int(x),"y",y
		#print omg
		cv.Circle(omg,(int(x),int(y)),20,(00,255,00))
	cv.SaveImage(out, omg)

	
def init():
	global dist_img
	global rgb_img
	global out_img
	dist_img=cv.LoadImage("distance-image.pgm");
	rgb_img=cv.LoadImage("rgb-image.ppm");
	print rgb_img.width
def main():
	global rgb_img;
	init()
	paintFeatures("rgb-image.ppm","rgb-image.features.png")
#	gf=goodFeatures();
	


if __name__=='__main__': main()

