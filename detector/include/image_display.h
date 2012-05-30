#ifndef IMAGE_DISPLAY_H	
#define IMAGE_DISPLAY_H
#include <boost/noncopyable.hpp>
#include <opencv2/opencv.hpp>

namespace detector {

	class ImageDisplay : boost::noncopyable {
	public:
		explicit ImageDisplay() {}
		virtual ~ImageDisplay() = 0 {};
	
		virtual void display(cv::Mat& image) = 0;
	};
}

#endif	//IMAGE_DISPLAY_H