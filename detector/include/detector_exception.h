#ifndef DETECTOR_EXCEPTION_H
#define DETECTOR_EXCEPTION_H
#include <stdexcept>

namespace detector {

class detector_runtime_exception : public std::runtime_error {
public:
	explicit detector_runtime_exception(const std::string& message) : std::runtime_error(message) {}
	explicit detector_runtime_exception(const char* message) : std::runtime_error(message) {}
};

}
#endif	//DETECTOR_EXCEPTION_H