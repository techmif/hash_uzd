#include "hashLib.h"
#include "functionCalls.h"

// Function to convert decimal to hexadecimal
std::string decimalToHex(long long num) {
    if (num == 0) return "0";

    const char hexDigits[] = "0123456789ABCDEF";
    std::string hex;

    bool negative = (num < 0);
    if (negative) num = -num;

    while (num > 0) {
        int remainder = num % 16;
        hex.push_back(hexDigits[remainder]);
        num /= 16;
    }

    if (negative) hex.push_back('-');

    std::reverse(hex.begin(), hex.end());
    return hex;
}