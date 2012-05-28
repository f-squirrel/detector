#ifndef SOURCE_FACTORY_H
#define SOURCE_FACTORY_H

#include <memory>
#include "source.h"
#include <string>

namespace detector {
	
	class SourceFactory {
	public:
		explicit SourceFactory();
	
		std::shared_ptr<Source> create(const std::string& source_id, const std::string& source_file) const;
	private:
	};
}

#endif	//SOURCE_FACTORY_H