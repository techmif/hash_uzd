#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <fstream>

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::bitset;
using std::ios;
using std::ifstream;
using std::vector;

string desimtaine_i_16(int desimtaine){
    string hex = "";
    int liekana;
    char simbolis;
    while(desimtaine != 0){
        liekana = desimtaine % 16;
        if (liekana < 10) simbolis = liekana + '0';
        else simbolis = liekana - 10 + 'A';
        hex = simbolis + hex;
        desimtaine /= 16;
    }
    return hex;
}
