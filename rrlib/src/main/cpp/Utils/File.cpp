#include <rrlib/Utils/File.h>

std::string rr::utils::LoadFile(std::string path){
    std::ifstream fFile(path);
    std::string sFile((std::istreambuf_iterator<char>(fFile)), (std::istreambuf_iterator<char>()));
    return sFile;
}
