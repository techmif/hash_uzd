#include "hash_funkcija.hpp"

void hashFunkcija(string input, string &hash, string &salt){

    vector<int> nuskaityti_binary_duomenys;
    vector<int> konvertuota_ivestis;
    vector<int> konvertuota_druskyte;
    int suma;

    salt = druskyte(input);
    KonvertCharIx10(input, konvertuota_ivestis);
    KonvertCharIx10(salt, konvertuota_druskyte);
    suma = Sumax10(konvertuota_ivestis);
    nuskaitytimp3(nuskaityti_binary_duomenys);

    int skyriu_sk = nuskaityti_binary_duomenys.size() / 32;
    int pradinis_skyrius = suma;
    while (pradinis_skyrius > skyriu_sk) pradinis_skyrius -= skyriu_sk;

    //pati hash funkcija
    for(int i=0; i<32; i++)
    {
        hash += desimtaine_i_16(konvertuota_ivestis[i] ^ nuskaityti_binary_duomenys[pradinis_skyrius * 32 + i] ^ konvertuota_druskyte[i]);
    }
    int i=0;
    while (hash.length()<64) 
    {
        hash += desimtaine_i_16(konvertuota_ivestis[i] ^ nuskaityti_binary_duomenys[pradinis_skyrius * (32 + i)] ^ konvertuota_druskyte[i]);
    }
    if(hash.length()>64) hash = hash.substr(0,64);
}