#include "hashLib.h"
#include "functionCalls.h"

std::string decimalToHex(uint64_t num) {
    std::ostringstream oss;
    oss << std::hex << std::uppercase << num;
    return oss.str();
}