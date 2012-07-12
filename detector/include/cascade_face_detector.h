#ifndef CASCADE_FACE_DETECTOR_H
#define CASCADE_FACE_DETECTOR_H


#include "object_detector.h"
#include <opencv2/opencv.hpp>

namespace detector {
	
	class CascadeFaceDetector : public ObjectDetector {
	public:
		explicit CascadeFaceDetector(const std::string& cascade_file_name, bool use_cpp_detect = true);
		~CascadeFaceDetector();
		virtual void detect(cv::Mat source_image);
		virtual bool is_ready() { return !m_cascade.empty(); }
	private:
		void c_detect(cv::Mat source_image);
		void cpp_detect(cv::Mat source_image);

		cv::CascadeClassifier	m_cascade;
		const std::string		m_cascade_file_name;
		bool					m_use_cpp_detect;
	};
	
}
#endif // CASCADE_FACE_DETECTOR_H
