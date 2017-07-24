#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\opencv.hpp>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
	CascadeClassifier face_cascade;
	CascadeClassifier smile_cascade;
	face_cascade.load("data/haarcascade_frontalface_alt.xml");
	smile_cascade.load("data/haarcascade_smile.xml");


	Mat srcImage;
	srcImage = imread("image.jpg");
	
	imshow("ss", srcImage);
	Mat dstImage = srcImage.clone();

	Mat grayImage;
	grayImage = imread("image.jpg");
	//grayImage.create(srcImage.size(), srcImage.type());
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);
	//imshow("gray", grayImage);
	equalizeHist(grayImage, grayImage);
	//imshow("hist", grayImage);


	Scalar color = CV_RGB(255, 0, 0);
	vector<Rect>rect;
	face_cascade.detectMultiScale(grayImage, rect, 1.1, 3, 0,Size(30,30),Size(3000,3000));
	

	for (int i = 0; i < rect.size(); i++)
	{
		
		Point center;
		int radius;
		center.x = cvRound((rect[i].x + rect[i].width * 0.5));
		center.y = cvRound((rect[i].y + rect[i].height * 0.5));

		radius = cvRound((rect[i].width + rect[i].height) * 0.25);
		circle(dstImage, center, radius, color[i % 7], 2);

		Mat faceRIO = dstImage;
		std::vector<Rect>smile;
		//smile_cascade.detectMultiScale(faceRIO, rect, 1.1, 3,0,Size(30,30));
		smile_cascade.detectMultiScale(faceRIO, smile, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30),Size(3000,3000));

		for (int j = 0; j < rect.size(); j++)
		{
			
			Rect rect((rect[i].x + smile[j].x)*0.55, (rect[i].y + smile[j].y)*1.58, smile[j].width, smile[j].height);
			rectangle(dstImage, rect, Scalar(0, 0, 255), 2, 10, 0);
		
		}

	}
	
	 imshow("smile",dstImage);
	 waitKey(0);
	 return 0;
	
}
