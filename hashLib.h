#ifndef HASHLIB_H
#define HASHLIB_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <numeric>
#include <cstdint>
#include <algorithm>
#include <random>

namespace fs = std::filesystem;

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

using hrClock = std::chrono::high_resolution_clock;
using ms = std::chrono::milliseconds;
using sec = std::chrono::duration<double>;

#endif