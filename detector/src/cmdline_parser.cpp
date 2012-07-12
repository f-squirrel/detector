#include "cmdline_parser.h"

namespace po = boost::program_options;
const std::string help_option = "help";
CmdOptions::CmdOptions(int argc, char* argv[]) : m_options_desc("Allowed options") {
			m_options_desc.add_options()
			("help",		"produce help message")
			("source",		po::value<std::string>(),	"set source type")
			("path",		po::value<std::string>(),	"set path to image or video or id for camera")
			("cascade",		po::value<std::string>(),	"set path to cascade");

		po::store(po::parse_command_line(argc, argv, m_options_desc), m_variables_map);
		po::notify(m_variables_map);
}


bool CmdOptions::is_help() {
	return ( m_variables_map.count(help_option) != 0 );
}

CmdOptions::~CmdOptions() {}