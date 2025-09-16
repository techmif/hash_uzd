#include "lib.hpp"

void KonvertCharIx10 (string input){
    char simbolis;
    for(int i=0; i<=input.length(); i++)
    {
        simbolis = input[i]; //null patampa 0, o 0 yra 48
        //cout<< simbolis << " ";
        //cout<< (int)simbolis << " ";
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
            nuskaityti_binary_duomenys.push_back((unsigned char)byte); //nors duomenys nuskaitomi binary, kai char irasome i int vektoriu, jis konvertuojamas i desimtaine sistema
            if (nuskaityti_binary_duomenys.size() % 90000 == 0) cout<<".";
        }
        cout<<endl<<"Nuskaityta sekmingai."<<endl;
    }
    in.close();
}

int main (){
    vector<int> nuskaityti_binary_duomenys;

    cout << "Iveskite zodi, kuri norite uzkoduoti: " <<endl;
    string input;
    cin >> input;
    cout<< input<<endl;
    KonvertCharIx10(input);
    nuskaitytimp3(nuskaityti_binary_duomenys);

    //testavimui naudotos eilutes
    //cout<<"Pirmi trys simboliai: "<< nuskaityti_binary_duomenys[2]<<" "<<nuskaityti_binary_duomenys[3]<<" "<<nuskaityti_binary_duomenys[4]<<endl;
    //cout<<"Vektoriaus dydis: "<<nuskaityti_binary_duomenys.size()<<endl; //turi buti 102295
    return 0;
}
