#ifndef source_H
#define source_H
#include <boost/noncopyable.hpp>
#include <stdexcept>
#include <opencv2/opencv.hpp>
#include "detector_exception.h"

namespace detector {

	class source : boost::noncopyable {
	public:
		virtual ~source() = 0 {};
		virtual void next(cv::Mat& img) = 0;
		virtual bool is_ready() const = 0;
	};

	class Imagesource : public source {
	public:
		explicit Imagesource(const std::string& filename);
		virtual void next(cv::Mat& img);
		virtual bool is_ready() const { return !image.empty(); }
		
	private:
		cv::Mat image;
		bool is_first_show;
	};

	class Framesource : public source {
	public:
		explicit Framesource(const std::string& filename);
		explicit Framesource(int device_id);

		virtual void next(cv::Mat& img);
		virtual bool is_ready() const { return capture.isOpened(); }

	private:
		cv::VideoCapture capture;
	};

}
#endif	//source_H