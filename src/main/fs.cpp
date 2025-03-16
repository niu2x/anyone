#include "type.h"
#include "platform.h"
#include <sstream>

namespace anyone {

String path_join(const String& p1, const String& p2)
{
    std::stringstream ss;
    auto pf = GET_PLATFORM_SUPPORT();
    char path_separator = pf->get_path_separator();
    if (p1.size() > 0 && *(p1.end() - 1) == path_separator) {
        ss << p1.substr(0, p1.size() - 1);
    } else {
        ss << p1;
    }

    ss << path_separator;
    ss << p2;

    return ss.str();
}

} // namespace anyone