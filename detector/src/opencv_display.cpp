#include "opencv_display.h"

namespace detector {

openCV_display::openCV_display( const std::string& window_name ) : m_window_name(window_name) {
	cv::namedWindow(m_window_name, CV_WINDOW_KEEPRATIO);
}

void openCV_display::display( cv::Mat& image ) {
	cv::imshow(m_window_name, image);
}

void openCV_display::stop() {
	cv::destroyWindow(m_window_name);
}

}