#!/usr/bin/python
#From the example recepies at 
#http://opencv.willowgarage.com/documentation/python/cookbook.html
import cv,pygame
##Resizing
def resize():
	img = cv.LoadImageM("dump/r-1318125164.123585-4056130639.ppm")
	out=cv.SaveImage("out.png", img)
	thumbnail = cv.CreateMat(img.rows / 10, img.cols / 10, cv.CV_8UC3)
	cv.Resize(img, thumbnail)
	out_resize=cv.SaveImage("out.resized.png",thumbnail)


#Laplacian
def laplacian():
	im = cv.LoadImageM("out.png", 1)
	dst = cv.CreateImage(cv.GetSize(im), cv.IPL_DEPTH_16S, 3)
	laplace = cv.Laplace(im, dst)
	cv.SaveImage("out.laplace.png", dst)
def goodFeatures():
	img = cv.LoadImageM("out.png",cv.CV_LOAD_IMAGE_GRAYSCALE);
	eig_image = cv.CreateMat(img.rows, img.cols, cv.CV_32FC1)
	temp_image = cv.CreateMat(img.rows, img.cols, cv.CV_32FC1)
	for (x,y) in cv.GoodFeaturesToTrack(img, eig_image, temp_image, 10, 0.04, 1.0, useHarris = True):
		print "good feature at", x,y
def toPygame():
	src = cv.LoadImage("out.png");
	src_rgb = cv.CreateMat(src.height, src.width, cv.CV_8UC3)
	cv.CvtColor(src, src_rgb, cv.CV_BGR2RGB)
	pg_img = pygame.image.frombuffer(src_rgb.tostring(), cv.GetSize(src_rgb), "RGB")
		

#resize();
#laplacian
goodFeatures();
#toPygame();
