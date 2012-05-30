#ifndef SOURCE_H
#define SOURCE_H
#include <boost/noncopyable.hpp>
#include <stdexcept>
#include <opencv2/opencv.hpp>
#include "detector_exception.h"

namespace detector {

	class Source : boost::noncopyable {
	public:
		virtual ~Source() = 0 {};
		virtual void next(cv::Mat& img) = 0;
		virtual bool is_ready() const = 0;
	};

	class ImageSource : public Source {
	public:
		explicit ImageSource(const std::string& filename) : is_first_show(true) {
			image = cv::imread(filename);
			if ( !is_ready() ) {
				throw DetectorRuntimeException("cannot open " + filename);
			}
		}
		virtual void next(cv::Mat& img) {
			if (is_first_show) {
				is_first_show = false;
				img = image;
			}
			else {
				cv::Mat empty_image;
				img = empty_image;
			}
		}
		virtual bool is_ready() const { return !image.empty(); }

	private:
		cv::Mat image;
		bool is_first_show;
	};

	class FrameSource : public Source {
	public:
		explicit FrameSource(const std::string& filename) : capture(filename) {
			if (!is_ready()) {
				const std::string err_msg = "cannot open " + filename;
				throw DetectorRuntimeException(err_msg);
			}
		}
		explicit FrameSource(const int device_id) : capture(device_id) {
			if (!is_ready()) {
				const std::string err_msg = "cannot open " + device_id;
				throw DetectorRuntimeException(err_msg);
			}
		}

		virtual void next(cv::Mat& img) {
			capture >> img;
		}
		virtual bool is_ready() const { return capture.isOpened(); }

	private:
		cv::VideoCapture capture;
	};

}
#endif	//SOURCE_H