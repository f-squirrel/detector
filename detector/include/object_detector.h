#ifndef OBJECT_DETECTOR_H
#define OBJECT_DETECTOR_H

#include <boost/noncopyable.hpp>
#include <opencv2/opencv.hpp>

namespace detector {
	
	class object_detector : boost::noncopyable {
	public:
		explicit object_detector() {}
		virtual ~object_detector() = 0 {}
	
		virtual void detect(cv::Mat source_image) = 0;
		virtual bool is_ready() = 0;
	};
}
#endif	//OBJECT_DETECTOR_H