#include "opencv_display.h"

namespace detector {

	OpenCVDisplay::OpenCVDisplay( const std::string& window_name ) : m_window_name(window_name) {
		cv::namedWindow(m_window_name, CV_WINDOW_KEEPRATIO);
	}

	void OpenCVDisplay::display( cv::Mat& image ) {
		cv::imshow(m_window_name, image);
	}

}