#ifndef OBJECT_DETECTOR_H
#define OBJECT_DETECTOR_H

#include <boost/noncopyable.hpp>
#include <opencv2/opencv.hpp>

namespace detector {
	
	class ObjectDetector : boost::noncopyable {
	public:
		explicit ObjectDetector() {}
		virtual ~ObjectDetector() = 0 {}
	
		virtual void detect(cv::Mat& source_image) = 0;
		virtual bool is_ready() const = 0;
	};
}
#endif	//OBJECT_DETECTOR_H