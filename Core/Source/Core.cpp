#include <iostream>
#include <future>
#include <chrono>
#include <opencv2/opencv.hpp>

#include "Manager/LoaderManager.h"

#define _RESIZE_RATIO 16

cv::Mat resizeImageWithMinPooling(const cv::Mat& input, int resizeRatio)
{


	return cv::Mat();
}

int main() {
	cv::Mat image = cv::imread("path/to/image.jpg", cv::IMREAD_COLOR);

	if (image.empty()) {
		std::cerr << "Error: Could not open or find the image!" << std::endl;
		return -1;
	}
	

	cv::Mat resizedImage = resizeImageWithMinPooling(image, _RESIZE_RATIO);
}
