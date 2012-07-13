#ifndef source_FACTORY_H
#define source_FACTORY_H

#include <memory>
#include "source.h"
#include <string>

namespace detector {
	
	class source_factory {
	public:
		explicit source_factory();
	
		std::shared_ptr<source> create(const std::string& source_id, const std::string& source_file) const;
	private:
	};
}

#endif	//source_FACTORY_H
