#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H
#include "source.h"
#include "image_display.h"
#include "object_detector.h"

namespace detector {
	
	typedef std::shared_ptr<Source> source_ptr_t;
	typedef std::shared_ptr<ImageDisplay> display_ptr_t;
	typedef std::shared_ptr<ObjectDetector> object_detector_ptr_t;
	
	class ImageProcessor {
	public:
		explicit ImageProcessor( source_ptr_t src, display_ptr_t display, object_detector_ptr_t detector_ptr );
		virtual ~ImageProcessor();
	
		virtual void run();
	
	private:
		source_ptr_t m_source_ptr;
		display_ptr_t m_display_ptr;
		object_detector_ptr_t m_object_detector_ptr;
	};
}
#endif	//IMAGE_PROCESSOR_H