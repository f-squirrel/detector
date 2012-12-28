#ifndef CMDLINE_PARSER_H
#define CMDLINE_PARSER_H

#include <boost/noncopyable.hpp>
#include <boost/program_options.hpp>

namespace detector {

class detector_options : boost::noncopyable {
public:
	enum source_type {
		image,
		video,
		camera
	};
	detector_options(int argc, char* argv[]);
	virtual ~detector_options();

	bool is_help();

private:
	boost::program_options::options_description m_options_desc;
	boost::program_options::variables_map m_variables_map;
};

}
#endif	//CMDLINE_PARSER_H