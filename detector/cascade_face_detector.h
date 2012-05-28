#ifndef CASCADE_FACE_DETECTOR_H
#define CASCADE_FACE_DETECTOR_H


#include "object_detector.h"
#include <opencv2/opencv.hpp>

namespace detector {
	
	class CascadeFaceDetector : public ObjectDetector {
	public:
		explicit CascadeFaceDetector(const std::string& cascade_file_name);
		~CascadeFaceDetector();
		virtual void detect(cv::Mat& source_image);
		virtual bool is_ready() { return !m_cascade.empty(); }
	private:
		cv::CascadeClassifier m_cascade;
	};
	
}
#endif // CASCADE_FACE_DETECTOR_H
