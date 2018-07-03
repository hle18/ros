// ---------------------------------------------------------------------
//// nir_imProc_maxentropy.cpp : Defines the entry point for the console application.
// Hanh Le. Last eddited: 6/26/2018
//---------------------------------------------------------------------

#include "stdafx.h"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

/// Global Variables
Mat1b src; Mat1b dst; Mat1b dst_bw;
char window_name[] = "Maximum entropy filtering";

/// Function headers
int display_caption(char* caption);

uchar maxentropie(const Mat1b& src, Mat1b& dst)
{
	// Histogram
	Mat1d hist(1, 256, 0.0);
	for (int r = 0; r<src.rows; ++r)
		for (int c = 0; c<src.cols; ++c)
			hist(src(r, c))++;

	// Normalize
	hist /= double(src.rows * src.cols);

	// Cumulative histogram
	Mat1d cumhist(1, 256, 0.0);
	float sum = 0;
	for (int i = 0; i < 256; ++i)
	{
		sum += hist(i);
		cumhist(i) = sum;
	}

	Mat1d hl(1, 256, 0.0);
	Mat1d hh(1, 256, 0.0);

	for (int t = 0; t < 256; ++t)
	{
		// low range entropy (entropy of white pixels)
		double cl = cumhist(t);
		if (cl > 0)
		{
			for (int i = 0; i <= t; ++i)
			{
				if (hist(i) > 0)
				{
					hl(t) = hl(t) - (hist(i) / cl) * log(hist(i) / cl);
				}
			}
		}

		// high range entropy (entropy of black pixels)
		double ch = 1.0 - cl;  // constraint cl + ch = 1
		if (ch > 0)
		{
			for (int i = t + 1; i < 256; ++i)
			{
				if (hist(i) > 0)
				{
					hh(t) = hh(t) - (hist(i) / ch) * log(hist(i) / ch);
				}
			}
		}
	}

	// Choose optimal threshold value
	Mat1d entropie(1, 256, 0.0);
	double h_max = hl(0) + hh(0);
	uchar threshold = 0;
	entropie(0) = h_max;

	for (int t = 1; t < 256; ++t)
	{
		entropie(t) = hl(t) + hh(t);
		if (entropie(t) > h_max)
		{
			h_max = entropie(t);
			threshold = uchar(t);
		}
	}

	//Binary output image
	dst = src > threshold;

	return threshold;
}

int main(int argc, char** argv)
{
	namedWindow(window_name, CV_WINDOW_KEEPRATIO);
	cv::resizeWindow(window_name, 600, 600);

	/// Load the source image
	src = imread("C:/Users/Photonics/OneDrive/Research/Surgical navigation/3d_Structured_Illumination/NIRtracking/img/bmp/nir0000.bmp", CV_LOAD_IMAGE_GRAYSCALE);

	/// Applying Gaussian blur	
	GaussianBlur(src, dst, Size(5, 5), 2, 2);

	/// Maximum Entropy Thresholding
	uchar th = maxentropie(dst, dst_bw);
	Mat bw = dst_bw;
	imshow("Original", dst);
	imshow("Result", bw);
	waitKey();

	return 0;
}

