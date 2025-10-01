#include "hashLib.h"
#include "functionCalls.h"

std::string decimalToHex(uint64_t num) {
    std::ostringstream oss;
    oss << std::hex << std::uppercase
        << std::setw(16) << std::setfill('0')
        << num;
    return oss.str();
}