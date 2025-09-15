#include "lib.hpp"

void KonvertCharIAscii (string input){
    char simbolis;
    for(int i=0; i<=input.length(); i++)
    {
        simbolis = input[i];
        cout<< simbolis << " ";
        cout<< (int)simbolis << " ";
    }
}

int main (){
    cout << "Iveskite zodi, kuri norite uzkoduoti: " <<endl;
    string input;
    cin >> input;
    cout<< input<<endl;
    KonvertCharIAscii(input);
    return 0;
}
