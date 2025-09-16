#include "lib.hpp"

void CharIBinary(string input){
    char simbolis;
    for(int i=0; i<=input.length(); i++)
    {
        simbolis = input[i];
        cout<< simbolis << " ";
        cout<< bitset<8>(simbolis) << " ";
    }
    cout<<endl;
}

void KonvertCharIAscii (string input){
    char simbolis;
    for(int i=0; i<=input.length(); i++)
    {
        simbolis = input[i];
        cout<< simbolis << " ";
        cout<< (int)simbolis << " ";
    }
    cout<<endl;
}

void nuskaitytimp3(vector<int> &nuskaityti_binary_duomenys){
    ifstream in("irasas.mp3", ios::binary); //uzdedu binary input output flag, kad nuskaitomo failo nereiketu uzkoduoti i utf8. radau info https://cplusplus.com/doc/tutorial/files/
    if(!in){
        cout<<"Failas nerastas"<<endl;
        return;
    }
    else 
    {
        cout<<"nuskaitoma is failo.";
        for(char byte; in.get(byte);){
            nuskaityti_binary_duomenys.push_back((unsigned char)byte);
        }
    }
    in.close();
}

int main (){
    vector<int> nuskaityti_binary_duomenys;

    /* cout << "Iveskite zodi, kuri norite uzkoduoti: " <<endl;
    string input;
    cin >> input;
    cout<< input<<endl;
    KonvertCharIAscii(input);
    CharIBinary(input); */
    nuskaitytimp3(nuskaityti_binary_duomenys);
    cout<<"Pirmi trys simboliai: "<< nuskaityti_binary_duomenys[2]<<" "<<nuskaityti_binary_duomenys[3]<<" "<<nuskaityti_binary_duomenys[4]<<endl;
    cout<<"Vektoriaus dydis: "<<nuskaityti_binary_duomenys.size()<<endl;
    return 0;
}
