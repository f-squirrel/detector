#ifndef CMDLINE_PARSER_H
#define CMDLINE_PARSER_H

#include <boost\noncopyable.hpp>
#include <boost/program_options.hpp>

class CmdOptions : boost::noncopyable {
public:
	CmdOptions(int argc, char* argv[]);
	virtual ~CmdOptions();

	bool is_help();
private:
	boost::program_options::options_description m_options_desc;
	boost::program_options::variables_map m_variables_map;
};
#endif	//CMDLINE_PARSER_H