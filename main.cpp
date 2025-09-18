#include "lib.hpp"

void hashFunkcija(vector<int> &nuskaityti_binary_duomenys, vector<int> &konvertuota_ivestis, int suma, string &hash){
    int skyriu_sk = nuskaityti_binary_duomenys.size() / 32; //dalinu ne is 64 todel, kad kiekvienas sombolis uzims 2 baitus 16 sistemoje
    int pradinis_skyrius = suma;
    if (pradinis_skyrius > skyriu_sk) pradinis_skyrius -= skyriu_sk; //darau antra rata, jei zodis ivestas per ilgas
    //cout<<"Pradinis skyrius: "<<pradinis_skyrius<<endl; //turi buti = suma
    for(int i=0; i<32; i++)
    {
        hash += desimtaine_i_16(konvertuota_ivestis[i] ^ nuskaityti_binary_duomenys[pradinis_skyrius * 32 + i]);
    }
    int i=0;
    while (hash.length()<64) 
    {
        hash += desimtaine_i_16(konvertuota_ivestis[i] ^ nuskaityti_binary_duomenys[pradinis_skyrius * (32 + i)]); //pradedam kaskart is skirtingo skyriaus
        i++;
    }
    if(hash.length()>64) hash = hash.substr(0,64); //kad butu tik 64 simboliai
    //cout<<"Pirmi trys simboliai: "<< nuskaityti_binary_duomenys[pradinis_skyrius*32]<<" "<<nuskaityti_binary_duomenys[pradinis_skyrius*32+1]<<" "<<nuskaityti_binary_duomenys[pradinis_skyrius*32+2]<<endl;
}

void nuskaitytimp3(vector<int> &nuskaityti_binary_duomenys){
    ifstream in("irasas.mp3", ios::binary); //uzdedu binary input output flag, kad nuskaitomo failo nereiketu uzkoduoti i utf8. radau info https://cplusplus.com/doc/tutorial/files/
    if(!in){
        cout<<"Failas nerastas"<<endl;
        return;
    }
    else 
    {
        //cout<<"nuskaitoma is failo.";
        for(char byte; in.get(byte);){
            nuskaityti_binary_duomenys.push_back((unsigned char)byte); //nors duomenys nuskaitomi binary, kai char irasome i int vektoriu, jis konvertuojamas i desimtaine sistema
            //if (nuskaityti_binary_duomenys.size() % 50000 == 0) cout<<"."; //skaitant ilgesni faila rodys kad vyksta procesas
        }
        //cout<<endl<<"Nuskaityta sekmingai."<<endl;
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
    cout<<endl;
}

int Sumax10(vector<int> &konvertuota_ivestis){ //apskaiciuosime visu ivestu simboliu desimtaine suma, kuria naudosime kreipiantis i mp3 suskirstyta veiktoriu
    int suma = 0;
    for(int i=0; i<konvertuota_ivestis.size(); i++){
        suma += konvertuota_ivestis[i];
        if (suma<0) suma *= -1; //kad nepasidarytu neigiama suma (lengviau bus sitaip)
    }
    return suma;
}

int main (){
    vector<int> nuskaityti_binary_duomenys; //jie saugomi desimtainiu formatu, pavadinti taip tik del nuskaitymo budo
    vector<int> konvertuota_ivestis; //vartotojo ivedamas string ir paverstas i desimtaini vektoriu
    string hash;
    int suma;
    string input;

    while (true)
    {
        cout << "Iveskite zodi, kuri norite uzkoduoti: " <<endl;
        cin >> input;
        if(input.length()<=0) input.clear(); //kad butu ivestas bent vienas simbolis
        else if (input.length() < 32) //pridedama dalele druskos (siuo atveju visiems slaptazodziams vienoda), kad slaptazodis butu pilnesnis.
        {
            int kiekTruksta = 32 - input.length();
            string papildymas = "AsEsuMiFakultetoAntrakursisStud"; //31 simbolio uzpildymas
            for (int i=0; i<=kiekTruksta; i++) 
            {
                input += papildymas[i]; //uzpildau iki 32 simboliu, kad butu galima panaudoti visa mp3 faila
            }
            //cout<<input<<endl;
            break;
        }
        else if (input.length() >= 32)
        {
            input = input;
            break;
        }
    }

    KonvertCharIx10(input, konvertuota_ivestis);
    suma = Sumax10(konvertuota_ivestis);
    nuskaitytimp3(nuskaityti_binary_duomenys);
    hashFunkcija(nuskaityti_binary_duomenys, konvertuota_ivestis, suma, hash);
    cout<<"Sugeneruotas hash: "<<hash<<endl;

    //testavimui naudotos eilutes
    //cout<<"Visu simboliu desimtaine suma: "<<suma<<endl;
    //cout<<"Vektoriaus dydis: "<<nuskaityti_binary_duomenys.size()<<endl; //turi buti 102295
    //cout<<"Vektoriaus dydis: "<<konvertuota_ivestis.size()<<endl;

    //hash debugginimui (kad tikrai butu 64 simboliai)
    
    for(int i=1; i<=hash.length(); i++) 
    {
        cout<< hash[i-1];
        if(i%8==0) cout<<endl;
    } 
    
    return 0;
}


//problemos:
//siuo metu gaunasi kad ivedus nedidelius zodzius, labai nemazas sansas gauti beveik ta pati hash 123________ ir pvz 222________ turi tas pacias desimtainiu reiksmiu sumas
//hashas nesigauna visada 64 simboliu ilgio. Kartais gaunasi maziau