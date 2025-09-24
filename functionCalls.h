#ifndef FUNCTIONSCALLS_H
#define FUNCTIONSCALLS_H

//Funkciju prototipai

//ivestisPatikrinimas.cpp
int ivestiesPatikrinimas(const int nuo, const int iki);
int ivestiesPatikrinimas(const int nuo, const int iki, const int sustabdymoSalyga);

//hashFunctions.cpp
uint64_t chaoticPrimeMixer(const std::string& input);
void hashManual();
void hashFile();
void hashTest();

//hexConverter.cpp
std::string decimalToHex(long long num);

#endif