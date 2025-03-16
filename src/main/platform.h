#pragma once

#if defined(ANYONE_TARGET_LINUX)
	#include <opengl.h>
#endif

namespace anyone {

class OpenglLoader {
public:
	virtual ~OpenglLoader() {}
	virtual bool load_opengl() = 0;
};

}
