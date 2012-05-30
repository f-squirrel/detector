#ifndef OPENCV_DISPLAY_H
#define OPENCV_DISPLAY_H

#include "image_display.h"

namespace detector{

	class OpenCVDisplay : public ImageDisplay {
	public:
		explicit OpenCVDisplay( const std::string& window_name );
	
		virtual void display( cv::Mat& image );
	
	private:
		const std::string m_window_name;
	};
}
#endif	//OPENCV_DISPLAY_H