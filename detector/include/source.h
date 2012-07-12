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
		explicit ImageSource(const std::string& filename);
		virtual void next(cv::Mat& img);
		virtual bool is_ready() const { return !image.empty(); }
		
	private:
		cv::Mat image;
		bool is_first_show;
	};

	class FrameSource : public Source {
	public:
		explicit FrameSource(const std::string& filename);
		explicit FrameSource(int device_id);

		virtual void next(cv::Mat& img);
		virtual bool is_ready() const { return capture.isOpened(); }

	private:
		cv::VideoCapture capture;
	};

}
#endif	//SOURCE_H