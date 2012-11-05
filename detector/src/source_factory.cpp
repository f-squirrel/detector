#include "source_factory.h"
#include <memory>

namespace detector {
	
	const std::string image = "image";
	const std::string frame = "video";
	const std::string camera = "camera";
	
	std::shared_ptr<source> source_factory::create(const std::string& source_type, const std::string& source_file) {
		if (source_type == image) {
			return std::shared_ptr<source>( new image_source( source_file ) );
		}
		else if (source_type == frame) {
			return std::shared_ptr<source>( new frame_source( source_file ) );
		}
		else if (source_type == camera) {
			int device_id = atoi(source_file.c_str());
			return std::shared_ptr<source>( new frame_source( device_id ) );
		}
		else {
			throw detector_runtime_exception("Unknown source type: " + source_type);
		}
		std::shared_ptr<source> src(new image_source( source_file ));
		return src;
	}
}
