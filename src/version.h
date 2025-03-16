#pragma once


namespace anyone {

struct SemanticVersion {
	int major;
	int minor;
	int patch;
};

SemanticVersion get_version();

}