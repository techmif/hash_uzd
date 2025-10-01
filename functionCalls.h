#ifndef FUNCTIONSCALLS_H
#define FUNCTIONSCALLS_H


//Funkciju prototipai

//main.cpp
// tuščias

//hash.cpp
uint64_t chaoticPrimeMixer(const std::string& input, uint64_t salt = 0);

//hashFunctions.cpp
void hashManual();
void hashFile();
void hashFileLAS();

//testFunkcijos.cpp
void hashTest();
void outputLengthTest();
void deterministicTest();
void konstitucijaTest();
void collisionTest();
void avalancheTest();
void saltTest();

//generators.cpp
void pairGenerator();
void similarPairGenerator();

//ivestisPatikrinimas.cpp
int ivestiesPatikrinimas(const int nuo, const int iki);
int ivestiesPatikrinimas(const int nuo, const int iki, const int sustabdymoSalyga);

//fileNameGetter.cpp
std::string fileNameGetter();

//hexConverter.cpp
std::string decimalToHex(uint64_t num);


#endif