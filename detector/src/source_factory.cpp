#include "source_factory.h"
#include <memory>

namespace detector {
	
	const std::string image_source = "imagesource";
	const std::string frame_source = "framesource";
	
	SourceFactory::SourceFactory() {}
	
	std::shared_ptr<Source> SourceFactory::create(const std::string& source_id, const std::string& source_file) const {
		if (source_id == image_source) {
			return std::shared_ptr<Source>( new ImageSource( source_file ) );
		}
		else if (source_id == frame_source) {
			return std::shared_ptr<Source>( new FrameSource( source_file ) );
		}
		else {
			throw DetectorRuntimeException("Unknown source id: " +source_id);
		}
		std::shared_ptr<Source> src(new ImageSource( source_file ));
		return src;
	}
}
