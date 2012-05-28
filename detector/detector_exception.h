#ifndef DETECTOR_EXCEPTION_H
#define DETECTOR_EXCEPTION_H
#include <stdexcept>

class DetectorRuntimeException : public std::runtime_error {
public:
	explicit DetectorRuntimeException(const std::string& message) : std::runtime_error(message) {}
	explicit DetectorRuntimeException(const char* message) : std::runtime_error(message) {}
};
#endif	//DETECTOR_EXCEPTION_H