#include"source.h"
#include<string>
#include<sstream>

namespace detector {

	image_source::image_source(const std::string& filename) : is_first_show(true) {
		// due to defect of openCV: in release version imread cannot open file
#ifdef WIN32
		image = cvLoadImage(filename.c_str());
#elif
		image = cv::imread(filename);
#endif
		if ( !is_ready() ) {
			throw detector_runtime_exception("cannot open image: " + filename);
		}
	}

	void image_source::next(cv::Mat& img) {
		if (is_first_show) {
			is_first_show = false;
			img = image;
		}
		else {
			cv::Mat empty_image;
			img = empty_image;
		}
	}

	frame_source::frame_source(const std::string& filename) : capture(filename) {
		if (!is_ready()) {
			const std::string err_msg = "cannot open video: " + filename;
			throw detector_runtime_exception(err_msg);
		}
	}
	
	frame_source::frame_source(int device_id) : capture(device_id) {
		if (!is_ready()) {
			std::stringstream err_stream;
			err_stream << "cannot open camera with id: " << device_id << std::endl;
			throw detector_runtime_exception(err_stream.str());
		}
	}

	void frame_source::next(cv::Mat& img) {
		capture >> img;
	}

}