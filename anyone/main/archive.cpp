#include "archive.h"

namespace anyone {

UniquePtr<Archive> create_archive(const String& uri)
{
    return nx::fs::create_archive(uri);
}

// BuiltinArchive::BuiltinArchive() { }
// BuiltinArchive::~BuiltinArchive() { }

} // namespace anyone