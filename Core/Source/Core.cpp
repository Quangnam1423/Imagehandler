#include <iostream>
#include <future>
#include <chrono>
#include <opencv2/opencv.hpp>

#include "Manager/LoaderManager.h"

#define _RESIZE_RATIO 32

cv::Mat resizeImageWithMinPooling(const cv::Mat& input, int resizeRatio)
{
	int newRows = input.rows / resizeRatio;
	int newCols = input.cols / resizeRatio;
	cv::Mat output(newRows, newCols, input.type());

	for (int i = 0; i < newRows; i++)
	{
		for (int j = 0; j < newCols ; j++)
		{
			uchar minVal = 255;
			for (int ki = 0; ki < resizeRatio; ++ki) {
				for (int kj = 0; kj < resizeRatio; ++kj) {
					int y = i * resizeRatio + ki;
					int x = j * resizeRatio + kj;
					uchar val = input.at<uchar>(y, x);
					if (val < minVal) minVal = val;
				}
			}
			output.at<uchar>(i, j) = minVal;
		}
	}

	return output;
}

int main() {
	cv::Mat image = cv::imread("D:/ImageHandler/Core/Resources/Images/rawimage.bmp", cv::IMREAD_GRAYSCALE);
	if (image.empty()) {
		std::cerr << "Error: Could not open or find the image!" << std::endl;
		return -1;
	}

	cv::flip(image, image, 0);
	
	auto start = std::chrono::high_resolution_clock::now();
	cv::Mat resizedImage = resizeImageWithMinPooling(image, (int)_RESIZE_RATIO);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> duration = end - start;
	std::cout << "Resizing took " << duration.count() << " ms" << std::endl;
	cv::flip(image, image, 0);
	cv::imwrite("D:/ImageHandler/Core/Resources/Images/gray_raw_image.bmp", image);

	cv::flip(resizedImage, resizedImage, 0);
	cv::imwrite("D:/ImageHandler/Core/Resources/Images/resizedimage.bmp", resizedImage);

	cv::waitKey(0);
	return 0;
}
