#include "source_factory.h"
#include <memory>

namespace detector {
	
	const std::string image_source = "image";
	const std::string frame_source = "video";
	const std::string camera_source = "camera";

	
	source_factory::source_factory() {}
	
	std::shared_ptr<source> source_factory::create(const std::string& source_id, const std::string& source_file) const {
		if (source_id == image_source) {
			return std::shared_ptr<source>( new Imagesource( source_file ) );
		}
		else if (source_id == frame_source) {
			return std::shared_ptr<source>( new Framesource( source_file ) );
		}
		else if (source_id == camera_source) {
			int device_id = atoi(source_file.c_str());
			return std::shared_ptr<source>( new Framesource( device_id ) );
		}
		else {
			throw detector_runtime_exception("Unknown source type: " + source_id);
		}
		std::shared_ptr<source> src(new Imagesource( source_file ));
		return src;
	}
}
