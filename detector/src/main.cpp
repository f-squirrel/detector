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
			("help",		"produce help message")
			("sourcetype",	po::value<std::string>(),	"set source type [image | video | camera]")
			("sourcepath",	po::value<std::string>(),	"set path to image or video or id for camera")
			("cascadetype",	po::value<std::string>(),	"set cascade type [haar]")
			("cascadepath", po::value<std::string>(),	"set path tp cascade xml");

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);

		if (vm.count("help")) {
			std::cout << desc << "\n";
			return 1;
		}

		SourceFactory factory;
 		auto source = factory.create(vm["sourcetype"].as<std::string>(), vm["sourcepath"].as<std::string>());
		display_ptr_t display(new OpenCVDisplay("Frame window"));
		object_detector_ptr_t object_detector(new CascadeFaceDetector(vm["cascadepath"].as<std::string>(), false));
		ImageProcessor img_processor(source, display, object_detector);
		img_processor.run();
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}

	system("pause");
	return 0;
}