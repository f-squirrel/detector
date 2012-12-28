#ifndef OPENCV_DISPLAY_H
#define OPENCV_DISPLAY_H

#include "image_display.h"

namespace detector{

class openCV_display : public image_display {
public:
	explicit openCV_display( const std::string& window_name );
	
	virtual void display( cv::Mat& image );
	virtual void stop();
	
private:
	const std::string m_window_name;
};

}
#endif	//OPENCV_DISPLAY_H