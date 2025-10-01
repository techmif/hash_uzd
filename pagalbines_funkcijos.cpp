#include "pagalbines_funkcijos.hpp"

void nuskaitytimp3(vector<int> &nuskaityti_binary_duomenys){
    ifstream in("irasas.mp3", ios::binary); //uzdedu binary input output flag, kad nuskaitomo failo nereiketu uzkoduoti i utf8. radau info https://cplusplus.com/doc/tutorial/files/
    if(!in){
        cout<<"Failas nerastas"<<endl;
        return;
    }
    else 
    {
        //cout<<"nuskaitoma is failo.";
        for(char byte; in.get(byte);)
        {
            if(byte != '\0') nuskaityti_binary_duomenys.push_back((unsigned char)byte); //nors duomenys nuskaitomi binary, kai char irasome i int vektoriu, jis konvertuojamas i desimtaine sistema
            //if (nuskaityti_binary_duomenys.size() % 50000 == 0) cout<<"."; //skaitant ilgesni faila rodys kad vyksta procesas
        }
    }
    in.close();
}

void KonvertCharIx10 (string input, vector<int> &konvertuota_ivestis){
    char simbolis;
    for(int i=0; i<=input.length(); i++)
    {
        simbolis = input[i]; //null patampa 0, o 0 yra 48
        //cout<< simbolis << " ";
        //cout<< (int)simbolis << " ";
        konvertuota_ivestis.push_back((int)simbolis);
    }
}

int Sumax10(vector<int> &konvertuota_ivestis){ //apskaiciuosime visu ivestu simboliu desimtaine suma, kuria naudosime kreipiantis i mp3 suskirstyta veiktoriu
    int suma = 0;
    for(int i=0; i<konvertuota_ivestis.size(); i++){
        suma += konvertuota_ivestis[i];
        if (suma<0) suma *= -1; //kad nepasidarytu neigiama suma (lengviau bus sitaip)
    }
    return suma;
}

void failo_pasirinkimas_ir_nuskaitymas(int &pasirinkimas, vector<string> &txtsarasas, string &input){
    cout<<"Pasirinkite faila, is kurio norite nuskaityti duomenis: "<<endl;
    txtfailai(".",txtsarasas);
    int i;
    for(i=0; i<txtsarasas.size(); i++)
    {
        cout<<i+1<<" - "<<txtsarasas[i]<<endl;
    }
    cout<<"Pasirinkite ivesdami skaiciu: ";
    int temp;
    cin>>temp;

    ifstream fr(txtsarasas[temp-1]);
    if (fr) {
        string line;
        while (getline(fr, line)) {
            input += line;
            input += '\n';
        }
    }
    //cout<<input.size()<<endl;
    fr.close();
}

void clearData(string &input, string &hash, string &salt, int &suma, vector<int> &konvertuota_ivestis, vector<int> &konvertuota_druskyte){
    input.clear();
    hash.clear();
    salt.clear();
    suma=0;
    konvertuota_ivestis.clear();
    konvertuota_druskyte.clear();
}

string read_first_n_lines(const string &filepath, int n) { //gpt parase patogesne funkcija nei as. Bet as ja modikavau nemazai
    string lines;
    if (n <= 0) return lines;
    ifstream in(filepath);
    if (!in) {
        std::cerr << "Nepavyko atidaryti failo: " << filepath << endl;
        return lines;
    }
    string line;
    int count = 0;
    while (count < n && std::getline(in, line)) {
        lines += line;
        ++count;
    }
    in.close();
    return lines;
}
