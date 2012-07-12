#include"source.h"
#include<string>

namespace detector {

	ImageSource::ImageSource(const std::string& filename) : is_first_show(true) {
		image = cv::imread(filename);
		if ( !is_ready() ) {
			throw DetectorRuntimeException("cannot open " + filename);
		}
	}

	void ImageSource::next(cv::Mat& img) {
		if (is_first_show) {
			is_first_show = false;
			img = image;
		}
		else {
			cv::Mat empty_image;
			img = empty_image;
		}
	}

	FrameSource::FrameSource(const std::string& filename) : capture(filename) {
		if (!is_ready()) {
			const std::string err_msg = "cannot open " + filename;
			throw DetectorRuntimeException(err_msg);
		}
	}
	
	FrameSource::FrameSource(int device_id) : capture(device_id) {
		if (!is_ready()) {
			const std::string err_msg = "cannot open " + device_id;
			throw DetectorRuntimeException(err_msg);
		}
	}

	void FrameSource::next(cv::Mat& img) {
		capture >> img;
	}

}