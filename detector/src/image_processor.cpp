#include "image_processor.h"

namespace detector {

	ImageProcessor::ImageProcessor(source_ptr_t src, display_ptr_t display, object_detector_ptr_t object_detector_ptr)
		: m_source_ptr(src), m_display_ptr(display), m_object_detector_ptr(object_detector_ptr) {}

	ImageProcessor::~ImageProcessor () {}

	void ImageProcessor::run() {
		for (;;) {

			cv::Mat image;
			m_source_ptr->next(image);
			if ( image.empty() ) {
				break;
			}
			m_object_detector_ptr->detect(image);
			m_display_ptr->display(image);

			if ( cv::waitKey(1) == 27) {
				break;
			}

		}
	}
}