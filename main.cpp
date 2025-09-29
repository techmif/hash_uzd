#include "lib.hpp"
#include <iomanip>

void hashFunkcija(vector<int> &nuskaityti_binary_duomenys, vector<int> &konvertuota_ivestis, int suma, string &hash, vector<int> &konvertuota_druskyte){
    int skyriu_sk = nuskaityti_binary_duomenys.size() / 32; //dalinu ne is 64 todel, kad kiekvienas sombolis uzims 2 baitus 16 sistemoje
    int pradinis_skyrius = suma;
    while (pradinis_skyrius > skyriu_sk) pradinis_skyrius -= skyriu_sk; //darau antra rata, jei zodis ivestas per ilgas
    //cout<<"Pradinis skyrius: "<<pradinis_skyrius<<endl; //turi buti = suma
    for(int i=0; i<32; i++)
    {
        hash += desimtaine_i_16(konvertuota_ivestis[i] ^ nuskaityti_binary_duomenys[pradinis_skyrius * 32 + i] ^ konvertuota_druskyte[i]);
    }
    //cout<<"pirmas ciklas sekmingas"<<endl;
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

void kolizijuanalize() { //parase chatgpt, nes as buvau sugalvojes prastesni metoda.
    // This function analyzes collisions in hash outputs from files "output1.txt" to "output4.txt"
    // If a collision is found, it prints the file name, line numbers, and contents of both collided lines
    ofstream analize("analize.txt");
    int total_collisions = 0;
    for (int i = 0; i < 4; i++) {
        cout<<"analizuojamas "<<i+1<<" failas"<<endl;
        std::ifstream in("output" + std::to_string(i + 1) + ".txt");
        if (!in) {
            std::cout << "Nepavyko atidaryti failo: output" << std::to_string(i + 1) << ".txt" << std::endl;
            continue;
        }

        std::unordered_map<std::string, std::vector<std::pair<int, std::string>>> hash_lines;
        std::string line;
        int line_number = 0;
        while (std::getline(in, line)) {
            line_number++;
            std::istringstream iss(line);
            std::string password, hash;
            iss >> password >> hash;
            if (hash.length() == 64) {
                hash_lines[hash].emplace_back(line_number, line);
            }
        }
        in.close();

        for (const auto& pair : hash_lines) {
            // Use a set to check for unique lines
            std::unordered_set<std::string> unique_lines; 
            for (const auto& item : pair.second) {
                unique_lines.insert(item.second);
            }
            if (unique_lines.size() > 1) {
                total_collisions++;
                analize << "Kolizija faile output" << std::to_string(i + 1) << ".txt:" << std::endl;
                for (const auto& item : pair.second) {
                    analize << "Eilute: " << item.first << " | Turinys: " << item.second << std::endl;
                }
                analize << std::endl;
            }
        }
    }
    analize.close();
    cout<<"analize baigta"<<endl;
    cout<<"Is viso koliziju: "<<total_collisions<<endl;
}

void simboliuanalize() { //parase ai. PROMPT: create a function that would calculate the amount of times a symbol is repeated based on it's position in the hash. For example "in the 1st file, there were a total of x unique symbols in position 1, the highest repetition rate is x%, there were x unrepeated symbols."
    ofstream out("simboliu_analize.txt");
    cout<<"analizuojami simboliai kiekviename faile"<<endl;
    for (int fileIdx = 0; fileIdx < 4; ++fileIdx) {
        std::ifstream in("output" + std::to_string(fileIdx + 1) + ".txt");
        if (!in) {
            out << "Nepavyko atidaryti failo: output" << std::to_string(fileIdx + 1) << ".txt" << std::endl;
            continue;
        }

        // For each position in hash, count symbol occurrences
        std::vector<std::unordered_map<char, int>> position_counts(64);
    // For each position in hash, count bit statistics for the 4 bits of the hex digit
    // bit_counts[pos][bit_index].first = zeros count, .second = ones count
    // use vector<vector<pair>> so operator[] is available without relying on <array>
    std::vector<std::vector<std::pair<int,int>>> bit_counts(64, std::vector<std::pair<int,int>>(4, {0,0}));
        std::string line;
        while (std::getline(in, line)) {
            std::istringstream iss(line);
            std::string password, hash;
            iss >> password >> hash;
            if (hash.length() == 64) {
                for (int i = 0; i < 64; ++i) {
                    char c = hash[i];
                    // normalize to lowercase for consistent hex counting
                    c = std::tolower(static_cast<unsigned char>(c));
                    // validate hex char
                    bool is_hex = (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f');
                    if (!is_hex) continue; // skip unknown chars
                    position_counts[i][c]++;
                    // convert hex char to its 4-bit value
                    int value = (c >= '0' && c <= '9') ? (c - '0') : (10 + (c - 'a'));
                    for (int bit = 0; bit < 4; ++bit) {
                        if (value & (1 << (3 - bit))) {
                            bit_counts[i][bit].second++; // ones
                        } else {
                            bit_counts[i][bit].first++; // zeros
                        }
                    }
                }
            }
        }
        in.close();

        out << "Failas output" << std::to_string(fileIdx + 1) << ".txt analizė:" << std::endl;
    // Accumulators for per-file averages
    double sum_unique = 0.0;
    double sum_max_rates = 0.0;
    double sum_min_rates = 0.0;
    double sum_unrepeated = 0.0;
    // accumulate bit percentages (b0..b3) across positions
    double sum_bit_pct[4] = {0.0, 0.0, 0.0, 0.0};

        for (int pos = 0; pos < 64; ++pos) {
            int total = 0;
            int max_count = 0;
            int unrepeated = 0;
            int min_count = INT_MAX; // for finding min repetition among seen symbols
            for (const auto& pair : position_counts[pos]) {
                total++;
                if (pair.second > max_count) max_count = pair.second;
                if (pair.second == 1) unrepeated++;
                if (pair.second < min_count) min_count = pair.second;
            }
            if (min_count == INT_MAX) min_count = 0; // no symbols seen at this pos

            int sum = 0;
            for (const auto& pair : position_counts[pos]) sum += pair.second;
            double max_rate = sum ? (double)max_count / sum * 100.0 : 0.0;
            double min_rate = 0.0;
            if (sum && min_count > 0) min_rate = (double)min_count / sum * 100.0;

            // Bit-level percentages for the 4 bits (bit 0 is MSB of the hex digit)
            std::ostringstream bits_ss;
            double bit_pct[4] = {0.0, 0.0, 0.0, 0.0};
            for (int bit = 0; bit < 4; ++bit) {
                int zeros = bit_counts[pos][bit].first;
                int ones = bit_counts[pos][bit].second;
                int bit_sum = zeros + ones;
                double ones_pct = bit_sum ? (double)ones / bit_sum * 100.0 : 0.0;
                bit_pct[bit] = ones_pct;
                sum_bit_pct[bit] += ones_pct;
                if (bit) bits_ss << ", ";
                bits_ss << "b" << bit << "=" << std::fixed << std::setprecision(2) << ones_pct << "%";
            }

            out << "Pozicija " << pos + 1 << ": Unikalių simbolių: " << total
                << ", Didžiausias pasikartojimo dažnis: " << max_rate << "%"
                << ", Mažiausias pasikartojimo dažnis: " << min_rate << "%"
                << ", Nepasikartojančių simbolių: " << unrepeated
                << ", Bitų pasiskirstymas (MSB..LSB): " << bits_ss.str() << std::endl;

            // accumulate for averages
            sum_unique += total;
            sum_max_rates += max_rate;
            sum_min_rates += min_rate;
            sum_unrepeated += unrepeated;
        }

        // Print per-file averages
        double avg_unique = sum_unique / 64.0;
        double avg_max_rate = sum_max_rates / 64.0;
        double avg_min_rate = sum_min_rates / 64.0;
        double avg_unrepeated = sum_unrepeated / 64.0;

        out << std::endl;
        out << "Vidurkiai failui output" << std::to_string(fileIdx + 1) << ":" << std::endl;
        out << "Avg Unikalių simbolių: " << std::fixed << std::setprecision(2) << avg_unique << std::endl;
        out << "Avg Didžiausias pasikartojimo dažnis (%): " << std::fixed << std::setprecision(2) << avg_max_rate << std::endl;
        out << "Avg Mažiausias pasikartojimo dažnis (%): " << std::fixed << std::setprecision(2) << avg_min_rate << std::endl;
        out << "Avg Nepasikartojančių simbolių: " << std::fixed << std::setprecision(2) << avg_unrepeated << std::endl;
        // Print average of bit percentages (b0..b3) across all 64 positions
        out << "Avg bitu pasiskirstymas (MSB..LSB) per faila: ";
        for (int bit = 0; bit < 4; ++bit) {
            double avg_bit = sum_bit_pct[bit] / 64.0;
            if (bit) out << ", ";
            out << "b" << bit << "=" << std::fixed << std::setprecision(2) << avg_bit << "%";
        }
        out << std::endl;
        out << std::endl;
        cout<<fileIdx+1<<" failas isanalizuotas"<<endl;
    }
    out.close();
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
        temp.clear();
        cout<<"Pasirinkite, kuri testa atliksite:"<<endl;
        cout<<"1 - 100 000 atsitiktiniu skirtingu dydziu string"<<endl;
        cout<<"2 - sugeneruoti 100 000 string, kurie skiriasi tik 1 simboliu tarpusavy"<<endl;
        cout<<"3 - konstitucijos testai"<<endl;
        cin>>temp;
        if(temp=="1"){
            string pobudis="random";
            int hash_dydziai[4] = {10,100,500,10000};
            nuskaitytimp3(nuskaityti_binary_duomenys);
            cout<<"kuriami 100 000 string, 10 simboliu dydzio."<<endl;
            for(int i=0;i<4;i++){
                ofstream out("output" + std::to_string(i+1) + ".txt");
                for(int j=0;j<100000;j++){
                    input = randSgen(pobudis,hash_dydziai[i]); //visiskai atsitiktiniu 10 skirtingu simboliu string.
                    salt = druskyte(input);
                    KonvertCharIx10(input, konvertuota_ivestis);
                    KonvertCharIx10(salt, konvertuota_druskyte);
                    suma = Sumax10(konvertuota_ivestis);
                    hashFunkcija(nuskaityti_binary_duomenys, konvertuota_ivestis, suma, hash, konvertuota_druskyte);
                    if(j%10000==0) cout<<".";
                    if(j==50000) cout<<(i+1)*25<<"%..";
                    out<<input<<" "<<hash<<endl;
                    clearData(input,hash,salt,suma,konvertuota_ivestis,konvertuota_druskyte); //isvalom kintamuosius
                }
                cout<<endl;
                out.close();
            }
            kolizijuanalize();
        }
        else if (temp=="2"){
            string pobudis="panasus";
            int hash_dydis[4] = {10,100,500,10000};
            nuskaitytimp3(nuskaityti_binary_duomenys);
            cout<<"kuriami 100 000 string, kurie skiriasi tik 1 simboliu tarpusavy."<<endl;
            for(int i=0;i<4;i++){
                ofstream out("output" + std::to_string(i+1) + ".txt");
                for(int j=0;j<100000;j++){
                    input = randSgen(pobudis,hash_dydis[i]); //visiskai atsitiktiniu 10 skirtingu simboliu string.
                    salt = druskyte(input);
                    KonvertCharIx10(input, konvertuota_ivestis);
                    KonvertCharIx10(salt, konvertuota_druskyte);
                    suma = Sumax10(konvertuota_ivestis);
                    hashFunkcija(nuskaityti_binary_duomenys, konvertuota_ivestis, suma, hash, konvertuota_druskyte);
                    if(j%10000==0) cout<<".";
                    if(j==50000) cout<<"pusiaukele..";
                    out<<input<<" "<<hash<<endl;
                    clearData(input,hash,salt,suma,konvertuota_ivestis,konvertuota_druskyte); //isvalom kintamuosius
                }
                cout<<endl;
                out.close();
            }
            kolizijuanalize();
            simboliuanalize();
        }
        else if(temp=="3"){

        }
        else return 0;
        return 0;
    }
    else return 0;

    //pagrindinis ciklas
    salt = druskyte(input);
    //cout<<"Druska sukurta sekmingai"<<endl;
    KonvertCharIx10(input, konvertuota_ivestis);
    //cout<<"1 konvertavimas sekmingas"<<endl;
    KonvertCharIx10(salt, konvertuota_druskyte);
    //cout<<"2 konvertavimas sekmingas"<<endl;
    suma = Sumax10(konvertuota_ivestis);
    //cout<<"suma sekminga"<<endl;
    nuskaitytimp3(nuskaityti_binary_duomenys);
    //cout<<"mp3 nuskaitymas sekmingas"<<endl;
    hashFunkcija(nuskaityti_binary_duomenys, konvertuota_ivestis, suma, hash, konvertuota_druskyte);
    //cout<<"hash padarytas sekmingai"<<endl;

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