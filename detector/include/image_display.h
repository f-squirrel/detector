#ifndef IMAGE_DISPLAY_H	
#define IMAGE_DISPLAY_H
#include <boost/noncopyable.hpp>
#include <opencv2/opencv.hpp>

namespace detector {

	class image_display : boost::noncopyable {
	public:
		explicit image_display() {}
		virtual ~image_display() = 0 {};
	
		virtual void display(cv::Mat& image) = 0;
	};
}

#endif	//IMAGE_DISPLAY_H