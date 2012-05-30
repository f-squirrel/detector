#include "source.h"
#include "image_processor.h"
#include "opencv_display.h"
#include "cascade_face_detector.h"
#include "source_factory.h"
#include <boost/program_options.hpp>

using namespace detector;
namespace po = boost::program_options;

int main(int argc, char* argv[]) {
	try {
		//	TODO: add possibility to use cmd line options:
		//	--image		"path"
		//	--video		"path"
		//	--camera	"device_id"
		//	--cascade	"path"

		po::options_description desc("Allowed options");
		desc.add_options()
			("help", "produce help message")
			("source",		po::value<int>(),			"set source type")
			("path",		po::value<std::string>(),	"set path to image or video or id for camera")
			("cascade",		po::value<std::string>(),	"set path to cascade");

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);

		if (vm.count("help")) {
			std::cout << desc << "\n";
			return 1;
		}

		SourceFactory factory;
 		source_ptr_t source = factory.create("imagesource", "d:\\Projects\\openCV\\detector\\detector\\data\\lena.jpg");

		//source_ptr_t source(new ImageSource("d:\\Projects\\openCV\\detector\\detector\\data\\lena.jpg"));
		//source_ptr_t source(new FrameSource("d:\\Projects\\openCV\\detector\\detector\\data\\browser.flv"));
		//source_ptr_t source(new FrameSource(200)) ;
		display_ptr_t display(new OpenCVDisplay("Frame window"));
		object_detector_ptr_t object_detector(new CascadeFaceDetector(
			"d:\\Projects\\openCV\\detector\\detector\\data\\haarcascade_frontalface_alt.xml")
			);
		ImageProcessor img_processor(source, display, object_detector);
		img_processor.run();
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	return 0;
}