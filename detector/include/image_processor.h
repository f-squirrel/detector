#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H
#include "source.h"
#include "image_display.h"
#include "object_detector.h"
//#include "concurrent_queue.h"
#include <ppl.h>
#include <concurrent_queue.h>
using namespace Concurrency;

namespace detector {
	
	typedef std::shared_ptr<source> source_ptr_t;
	typedef std::shared_ptr<image_display> display_ptr_t;
	typedef std::shared_ptr<object_detector> object_detector_ptr_t;
	
	class image_processor {
	public:
		explicit image_processor( source_ptr_t src, display_ptr_t display, object_detector_ptr_t detector_ptr );
		virtual ~image_processor();
	
		virtual void run();
	
	private:
		virtual void single_threaded_run();
		virtual void multi_threaded_run();
		virtual void source_worker();
		virtual void detector_worker();
		virtual void display_worker();
		virtual void source_detector_combined_worker();

		virtual void display_worker_v2();
		source_ptr_t				m_source_ptr;
		display_ptr_t				m_display_ptr;
		object_detector_ptr_t		m_object_detector_ptr;
		const char					m_escape_char;
		detector::concurrent_queue<cv::Mat>	m_source_to_detector_queue;
		detector::concurrent_queue<cv::Mat>	m_detector_to_display_queue;
		//concurrent_queue<cv::Mat> queue;

		bool m_main_thread_finished;
		bool m_display_thread_finished;
		cv::Mat m_image_to_display;
	};
}
#endif	//IMAGE_PROCESSOR_H