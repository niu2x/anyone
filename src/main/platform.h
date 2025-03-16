#pragma once

namespace anyone {

class OpenglLoader {
public:
	virtual ~OpenglLoader() {}
	virtual bool load_opengl() = 0;
};

}


#include ""