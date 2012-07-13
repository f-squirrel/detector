#include "image_processor.h"
#include <boost/thread.hpp>
namespace detector {

	image_processor::image_processor(source_ptr_t src, display_ptr_t display, object_detector_ptr_t object_detector_ptr)
		: m_source_ptr(src), m_display_ptr(display), m_object_detector_ptr(object_detector_ptr), m_escape_char(27) {}

	image_processor::~image_processor () {}

	void image_processor::run() {
		multi_threaded_run();
	}

	void image_processor::single_threaded_run() {
		for (;;) {

			cv::Mat image;
			m_source_ptr->next(image);
			if ( image.empty() ) {
				break;
			}
			m_object_detector_ptr->detect(image);
			m_display_ptr->display(image);

			if ( cv::waitKey(2) == m_escape_char) {
				break;
			}
		}
	}

	void image_processor::multi_threaded_run() {
		try {
			boost::thread source_thread(&image_processor::source_worker, this);
			boost::thread detector_thread(&image_processor::detector_worker, this);
			boost::thread display_thread(&image_processor::display_worker, this);
			
			source_thread.join();
			detector_thread.join();
			display_thread.join();
		}
		catch( std::exception& e ) {
			std::cerr << e.what() <<std::endl;
		}
	}

	void image_processor::source_worker() {
		try {
			std::cout << "source_worker started" << std::endl;
			for(;;) {
				//cv::Mat check_image = m_source_to_detector_queue.wait_and_front();
				//m_source_to_detector_queue.wait_and_pop(check_image);
				//if( check_image.empty() ) {
				//	std::cout << "received empty image from display: stopping source"<< std::endl;
				//	return;
				//}
				cv::Mat image;
				m_source_ptr->next(image);
				m_source_to_detector_queue.push(image);
				if ( image.empty() ) {
					std::cout << "source returned empty image: stopping source"<< std::endl;
					return;
				}
			}
		}
		catch(std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
		cv::Mat empty_image;
		m_source_to_detector_queue.push(empty_image);
	}

	void image_processor::detector_worker() {
		std::cout << "detector_worker started" << std::endl;
		try {
			for(;;) {
				cv::Mat image = m_detector_to_display_queue.wait_and_front();
				m_detector_to_display_queue.wait_and_pop(image);
				m_object_detector_ptr->detect(image);
				m_detector_to_display_queue.push(image);
				if ( image.empty() ) {
					std::cout << "detector returned empty image: stopping source"<< std::endl;
					return;
				}
			}
		}
		catch(std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
		cv::Mat empty_image;
		m_detector_to_display_queue.push(empty_image);
	}

	void image_processor::display_worker() {
		std::cout << "display_worker started" << std::endl;
		try {
			for(;;) {
				cv::Mat image = m_detector_to_display_queue.wait_and_front();
				m_detector_to_display_queue.wait_and_pop(image);
				if ( image.empty() ) {
					std::cout << "detector returned empty image: stopping source"<< std::endl;
					return;
				}

				m_display_ptr->display(image);
				if ( cv::waitKey(2) == m_escape_char) {
					// we need to tell other therads to go down!
					cv::Mat empty_image;
					m_source_to_detector_queue.push(empty_image);
					return;
				}
			}
		}
		catch(std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
		cv::Mat empty_image;
		m_source_to_detector_queue.push(empty_image);
	}
}