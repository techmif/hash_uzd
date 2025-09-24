#include "lib.hpp"

void hashFunkcija(vector<int> &nuskaityti_binary_duomenys, vector<int> &konvertuota_ivestis, int suma, string &hash, vector<int> &konvertuota_druskyte){
    int skyriu_sk = nuskaityti_binary_duomenys.size() / 32; //dalinu ne is 64 todel, kad kiekvienas sombolis uzims 2 baitus 16 sistemoje
    int pradinis_skyrius = suma;
    if (pradinis_skyrius > skyriu_sk) pradinis_skyrius -= skyriu_sk; //darau antra rata, jei zodis ivestas per ilgas
    //cout<<"Pradinis skyrius: "<<pradinis_skyrius<<endl; //turi buti = suma
    for(int i=0; i<32; i++)
    {
        hash += desimtaine_i_16(konvertuota_ivestis[i] ^ nuskaityti_binary_duomenys[pradinis_skyrius * 32 + i] ^ konvertuota_druskyte[i]);
    }
    int i=0;
    while (hash.length()<64) 
    {
        hash += desimtaine_i_16(konvertuota_ivestis[i] ^ nuskaityti_binary_duomenys[pradinis_skyrius * (32 + i)] ^ konvertuota_druskyte[i]); //pradedam kaskart is skirtingo skyriaus
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
        for(char byte; in.get(byte);)
        {
            if(byte != '\0') nuskaityti_binary_duomenys.push_back((unsigned char)byte); //nors duomenys nuskaitomi binary, kai char irasome i int vektoriu, jis konvertuojamas i desimtaine sistema
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

void failo_nuskaitymas(int &pasirinkimas, vector<string> &txtsarasas, string &input){
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
    cout<<input.size()<<endl;
    fr.close();
}

int main (){
    vector<int> nuskaityti_binary_duomenys; //jie saugomi desimtainiu formatu, pavadinti taip tik del nuskaitymo budo
    vector<int> konvertuota_ivestis; //vartotojo ivedamas string ir paverstas i desimtaini vektoriu
    vector<int> konvertuota_druskyte;
    string hash;
    string salt;
    int suma;
    string input;

    cout<<"Kaip norėsite vykdyti programą?: "<<endl;
    cout<<"1 - slaptazodzio ivedimas ranka." <<endl;
    cout<<"2 - nuskaitymas is failo." <<endl;
    cout<<"3 - testavimas." <<endl;
    cout<<"Pasirinkite ivesdami skaiciu: ";
    string temp;
    cin>>temp;

    if (temp=="1"){
        cout << "Iveskite zodi, kuri norite uzkoduoti: " <<endl;
        cin >> input;
    }

    else if(temp=="2"){
        vector<string> txtsarasas;
        int failo_pasirinkimas;
        failo_nuskaitymas(failo_pasirinkimas, txtsarasas, input);
    }

    else if(temp=="3"){

    }
    else return 0;

    //pagrindinis ciklas
    salt = druskyte(input);
    KonvertCharIx10(input, konvertuota_ivestis);
    KonvertCharIx10(salt, konvertuota_druskyte);
    suma = Sumax10(konvertuota_ivestis);
    nuskaitytimp3(nuskaityti_binary_duomenys);
    hashFunkcija(nuskaityti_binary_duomenys, konvertuota_ivestis, suma, hash, konvertuota_druskyte);

    cout<<"Koki rezultata norite matyti?"<<endl;
    cout<<"1 - tik sugeneruota hash"<<endl;
    cout<<"2 - sugeneruotus hash ir salt"<<endl;
    temp.clear();
    cin>>temp;
    if(temp=="1"){
        cout<<"Sugeneruotas hash: "<<hash<<endl;
    }
    else {
        cout<<"Sugeneruotas hash: "<<hash<<endl;
        cout<<"Sugeneruotas salt: "<<salt<<endl;
    }

    //testavimui naudotos eilutes
    //cout<<"Visu simboliu desimtaine suma: "<<suma<<endl;
    //cout<<"Vektoriaus dydis: "<<nuskaityti_binary_duomenys.size()<<endl; //turi buti 102295
    //cout<<"Vektoriaus dydis: "<<konvertuota_ivestis.size()<<endl;

    //hash debugginimui (kad tikrai butu 64 simboliai)
    /*
    for(int i=1; i<=hash.length(); i++) 
    {
        cout<< hash[i-1];
        if(i%8==0) cout<<endl;
    }
    */

    return 0;
}


//problemos:
//siuo metu gaunasi kad ivedus nedidelius zodzius, labai nemazas sansas gauti beveik ta pati hash 123________ ir pvz 222________ turi tas pacias desimtainiu reiksmiu sumas
//hashas nesigauna visada 64 simboliu ilgio. Kartais gaunasi maziau