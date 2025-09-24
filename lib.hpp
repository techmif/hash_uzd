#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <fstream>
#include <random>

#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#endif

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
        if(desimtaine <0 ) desimtaine = (-1) * desimtaine; //jei ivedami lietuviški simboliai, jų reikšmė būna minusinė. Tai trikdo veiklai.
        liekana = desimtaine % 16;
        if (liekana < 10) simbolis = liekana + '0';
        else simbolis = liekana - 10 + 'A';
        hex = simbolis + hex;
        desimtaine /= 16;
    }
    return hex;
}

string druskyte (string input){
    //generavau sita koda siu ai pagalba. Ideja kodo pasakiau as, tik nelabai mokejau igyvendinti (random skaiciu bibliotekos as nelabai pazistu)
    std::seed_seq seed(input.begin(), input.end());
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(0, 15);
    string result;
    for (int i = 0; i < 64; ++i) {
        int val = dist(rng);
        result += "0123456789ABCDEF"[val];//"0123456789ABCDEF" is a string containing all hexadecimal digits. [val] selects one based on the random value.
    }
    return result;
}

void txtfailai(const string &path, vector<string> &fileList) // Funkcija rasiau praeitam semestre
{
    int i = 0;
    #ifdef _WIN32
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileA((path + "\\*.txt").c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        cout << "No .txt files found or error opening directory!" << endl;
        return;
    }
    do
    {
        fileList.push_back(findFileData.cFileName);
        i++;
    } while (FindNextFileA(hFind, &findFileData) != 0);

    FindClose(hFind);

#else
    //  Linux/macOS su dirent.h
    DIR *dir = opendir(path.c_str()); // linuxine versija netestuota
    if (dir == nullptr)
    {
        cout << "Error opening directory!" << endl;
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr)
    {
        string filename = entry->d_name;
        if (filename.size() > 4 && filename.substr(filename.size() - 4) == ".txt")
        {
            i++;
            fileList.push_back(filename);
        }
    }

    closedir(dir);
#endif
}