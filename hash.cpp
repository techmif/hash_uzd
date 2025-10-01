#include "hashLib.h"
#include "functionCalls.h"


uint64_t chaoticPrimeMixer(const std::string& input, uint64_t salt) {
    static const uint64_t primes[10] = { 2,3,5,7,11,13,17,19,23,29 };
    uint64_t state = 0x84222325ULL ^ (salt * 0x9E3779B97F4A7C15ULL);

    for (size_t i = 0; i < input.size(); ++i) {
        uint64_t c = static_cast<unsigned char>(input[i]);
        uint64_t val = (c + ((uint64_t)i << 8)) * primes[i % 10] ^ (salt >> (i & 7));
        state ^= val;
        state *= 6364136223846793005ULL;
        state = (state << 27) | (state >> (64 - 27)); // rotation
    }

    state ^= (uint64_t)input.size() * 0xA24BAED4963EE407ULL;
    state ^= salt * 0x9E6C63D0676A9A99ULL;
    // final avalanche
    state ^= state >> 33; state *= 0xff51afd7ed558ccdULL;
    state ^= state >> 29; state *= 0xc4ceb9fe1a85ec53ULL;
    state ^= state >> 32;
    return state;
}