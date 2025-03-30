#pragma once

#include <nx/alias.h>
#include "base/type.h"

namespace anyone {

using Archive = nx::fs::Archive;
UniquePtr<Archive> create_archive(const String&);

// class BuiltinArchive: public nx::Archive {
// public:
// 	BuiltinArchive();
// 	~BuiltinArchive() ;
//     Vector<String> list_dir(const String& path) override;
//     UniquePtr<Read> open(const String& path) override;
// };

} // namespace anyone
