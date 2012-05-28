#include "cascade_face_detector.h"
#include "detector_exception.h"

namespace detector {

	CascadeFaceDetector::CascadeFaceDetector(const std::string& cascade_file_name) : m_cascade(cascade_file_name) {}

	CascadeFaceDetector::~CascadeFaceDetector() {}

	void CascadeFaceDetector::detect(cv::Mat& source_image) {
		if (!is_ready()) {
			throw DetectorRuntimeException("Detector is not ready: cascade is empty\n");
		}
		cv::Mat frame_gray;
		cv::cvtColor(source_image, frame_gray, CV_BGR2GRAY);
		cv::equalizeHist(frame_gray, frame_gray);

		std::vector<cv::Rect> faces;
		// detect faces
		m_cascade.detectMultiScale( frame_gray, faces, 1.1, 3, 0|CV_HAAR_SCALE_IMAGE, cv::Size(30, 30) );
		std::cout << "faces detected: " << faces.size() << std::endl;
		for( size_t i = 0; i < faces.size(); i++ ) {
			cv::rectangle(source_image, faces[i], cv::Scalar(255, 0, 0), 4);
		}
	}
}