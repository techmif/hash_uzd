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

/*
// 256-bit variant: derive four 64-bit lanes with diversified seeds and cross-mixing.
Hash256 chaoticPrimeMixer256(const std::string& input, uint64_t salt) {
    static const uint64_t primes[16] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};
    // Initialize four internal states with different constants + salt diffusion
    uint64_t s0 = 0x84222325ULL ^ (salt * 0x9E3779B97F4A7C15ULL);
    uint64_t s1 = 0x9E3779B97F4A7C15ULL ^ (salt + 0xC2B2AE3D27D4EB4FULL);
    uint64_t s2 = 0xC4ceb9fe1a85ec53ULL ^ (salt * 0xFF51AFD7ED558CCDULL);
    uint64_t s3 = 0x94D049BB133111EBULL ^ (salt + 0xD6E8FEB86659FD93ULL);

    for (size_t i = 0; i < input.size(); ++i) {
        uint64_t c = static_cast<unsigned char>(input[i]);
        uint64_t mix = (c + ((uint64_t)i << 16)) ^ (salt >> (i & 15));
        uint64_t p = primes[i & 15];

        // Each lane gets a differently transformed contribution
        s0 ^= (mix * p) + (s3 >> 7);
        s0 *= 0x9E3779B185EBCA87ULL; s0 = (s0 << 17) | (s0 >> (64-17));

        s1 ^= (mix * (p + 3)) + (s0 >> 11);
        s1 *= 0xC2B2AE3D27D4EB4FULL; s1 = (s1 << 29) | (s1 >> (64-29));

        s2 ^= (mix * (p + 5)) + (s1 >> 13);
        s2 *= 0x165667B19E3779F9ULL; s2 = (s2 << 31) | (s2 >> (64-31));

        s3 ^= (mix * (p + 7)) + (s2 >> 19);
        s3 *= 0x94D049BB133111EBULL; s3 = (s3 << 41) | (s3 >> (64-41));
    }

    // Inject length & salt into each lane differently
    uint64_t len = (uint64_t)input.size();
    s0 ^= len * 0xA24BAED4963EE407ULL ^ (salt << 17);
    s1 ^= len * 0x9E6C63D0676A9A99ULL ^ (salt << 23);
    s2 ^= len * 0xD6E8FEB86659FD93ULL ^ (salt << 31);
    s3 ^= len * 0xFF51AFD7ED558CCDULL ^ (salt << 37);

    // Final cross-lane avalanche: mix all lanes together
    auto fmix = [](uint64_t x){
        x ^= x >> 33; x *= 0xff51afd7ed558ccdULL;
        x ^= x >> 29; x *= 0xc4ceb9fe1a85ec53ULL;
        x ^= x >> 32; return x;
    };

    // Blend lanes
    uint64_t t0 = fmix(s0 ^ (s1 >> 3) ^ (s2 << 7));
    uint64_t t1 = fmix(s1 ^ (s2 >> 5) ^ (s3 << 11));
    uint64_t t2 = fmix(s2 ^ (s3 >> 7) ^ (s0 << 13));
    uint64_t t3 = fmix(s3 ^ (s0 >> 11) ^ (s1 << 17));

    // Final diffusion between t's
    t0 ^= t2 >> 19; t1 ^= t3 >> 23; t2 ^= t0 >> 29; t3 ^= t1 >> 31;
    t0 = fmix(t0); t1 = fmix(t1); t2 = fmix(t2); t3 = fmix(t3);

    return Hash256{t0,t1,t2,t3};
}

std::string hash256ToHex(const Hash256& h, bool uppercase) {
    std::ostringstream oss;
    if (uppercase) oss.setf(std::ios::uppercase);
    oss << std::hex << std::setw(16) << std::setfill('0') << h.a
        << std::setw(16) << std::setfill('0') << h.b
        << std::setw(16) << std::setfill('0') << h.c
        << std::setw(16) << std::setfill('0') << h.d;
    return oss.str();
}
*/