#ifndef _RR_UTILS_FILE_H
#define _RR_UTILS_FILE_H

#include <string>
#include <fstream>

namespace rr {
    namespace utils {
        std::string LoadFile(std::string path);
    }
}

#endif // _RR_UTILS_FILE_H