#include "detector_options.h"
#include "detector_exception.h"

namespace detector {

namespace po = boost::program_options;

const std::string help = "help";
const std::string sourcetype = "sourcetype";
const std::string sourcepath = "sourcepath";
const std::string cascadetype = "cascadetype";
const std::string cascadepath = "cascadepath";


detector_options::detector_options(int argc, char* argv[]) : m_options_desc("Allowed options") {
	m_options_desc.add_options()
	(help.c_str(),			"produce help message")
	(sourcetype.c_str(),	po::value<std::string>(),	"set source type [image | video | camera]")
	(sourcepath.c_str(),	po::value<std::string>(),	"set path to image or video or id for camera")
	(cascadetype.c_str(),	po::value<std::string>(),	"set cascade type [haar]")
	(cascadepath.c_str(), po::value<std::string>(),	"set path tp cascade xml");

	po::store(po::parse_command_line(argc, argv, m_options_desc), m_variables_map);
	po::notify(m_variables_map);
}


bool detector_options::is_help() {
	return ( m_variables_map.count(help) != 0 );
}


detector_options::~detector_options() {}

}