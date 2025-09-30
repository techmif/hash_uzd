#ifndef FUNCTIONSCALLS_H
#define FUNCTIONSCALLS_H


//Funkciju prototipai

//main.cpp
// tuščias

//hash.cpp
uint64_t chaoticPrimeMixer(const std::string& input);

//hashFunctions.cpp
void hashManual();
void hashFile();

//testFunkcijos.cpp
void hashTest();
void outputLength();
void deterministicTest();
void hashFileLAS();

//ivestisPatikrinimas.cpp
int ivestiesPatikrinimas(const int nuo, const int iki);
int ivestiesPatikrinimas(const int nuo, const int iki, const int sustabdymoSalyga);

//fileNameGetter.cpp
std::string fileNameGetter();

//hexConverter.cpp
std::string decimalToHex(uint64_t num);


#endif