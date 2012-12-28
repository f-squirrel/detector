#ifndef source_FACTORY_H
#define source_FACTORY_H

#include <memory>
#include "source.h"
#include <string>

namespace detector {
	
class source_factory {
public:
	
	static std::unique_ptr<source> create(const std::string& source_type, const std::string& source_file);
private:
	explicit source_factory();
};

}

#endif	//source_FACTORY_H
