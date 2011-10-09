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
        for (x,y) in cv.GoodFeaturesToTrack(img, eig_image, temp_image, 10000, 0.04, 1.0, useHarris = True):
		ret.append((x,y))
	return ret;

#Takes file names
def paintFeatures(inp,out):
	scaleMat = cv.CreateMat(300, 300, cv.CV_8UC3)
	img = cv.LoadImageM(inp,cv.CV_LOAD_IMAGE_GRAYSCALE);
	#cv.Resize(img,scaleMat);
	

	gf=goodFeatures(img);
	omg =  cv.LoadImageM(inp,1);
	cv.Resize(omg,scaleMat);
	for (x,y) in gf:
		#print "x",int(x),"y",y
		#print omg
		cv.Circle(omg,(int(x),int(y)),5,(00,255,00))
	cv.SaveImage(out, omg)

	
def main():
	global rgb_img;
	paintFeatures("distance-image.pgm","distance-image.features.png")
	paintFeatures("rgb-image.ppm","rgb-image.features.png")
	paintFeatures("distance-image.laplacian.png","distance-image.laplacian.features.png")
	paintFeatures("rgb-image.laplacian.png","rgb-image.laplacian.features.png")
	

if __name__=='__main__': main()

