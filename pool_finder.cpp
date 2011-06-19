#include <iostream>
using namespace std;

#include <cv.h>
#include <highgui.h>
#include <cvblob.h>

using namespace cvb;

int main()
{
  IplImage *original = cvLoadImage("pool_vegas.png", 1);
  IplImage *processed = cvCreateImage(cvGetSize(original), 8, 3);
  IplImage *img = cvCreateImage(cvGetSize(original), 8, 3);

  cvPyrMeanShiftFiltering(original, processed, 70, 35, 0);
  cvCvtColor(processed, img, CV_RGB2HSV);

  IplImage *grey = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
  cvInRangeS(img,cvScalar(0,41,80),cvScalar(40,150,255),grey);

  cvErode(grey, grey, NULL, 1);
  cvDilate(grey, grey, NULL, 3);

  IplImage *labelImg = cvCreateImage(cvGetSize(grey),IPL_DEPTH_LABEL,1);

  CvBlobs blobs;
  unsigned int result = cvLabel(grey, labelImg, blobs);

  IplImage *imgOut = cvLoadImage("pool_vegas.png");
  cvRenderBlobs(labelImg, blobs, img, imgOut);

  cvNamedWindow("test", 1);
  cvShowImage("test", imgOut);
  cvWaitKey(0);
  cvDestroyWindow("test");

  cvReleaseImage(&imgOut);
  cvReleaseImage(&grey);
  cvReleaseImage(&labelImg);
  cvReleaseImage(&img);

  cvReleaseBlobs(blobs);

  return 0;
}
