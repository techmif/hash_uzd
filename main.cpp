#include "lib.hpp"
#include "pagalbines_funkcijos.hpp"
#include "test_functions.hpp"
#include "hash_funkcija.hpp"

int main (){
    string input, hash, salt;

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
        failo_pasirinkimas_ir_nuskaitymas(failo_pasirinkimas, txtsarasas, input);
    }

    else if(temp=="3"){
        temp.clear();
        cout<<"Pasirinkite, kuri testa atliksite:"<<endl;
        cout<<"1 - 100 000 atsitiktiniu skirtingu dydziu string"<<endl;
        cout<<"2 - sugeneruoti 100 000 string, kurie skiriasi tik 1 simboliu tarpusavy"<<endl;
        cout<<"3 - konstitucijos testai"<<endl;
        cin>>temp;
        if(temp=="1"){
            testavimas1();
        }
        else if (temp=="2"){
            testavimas2();
        }
        else if(temp=="3"){
            testavimas3();
        }
        else return 0;
        return 0;
    }
    else return 0;

    hashFunkcija(input,hash,salt);

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

    return 0;
}
