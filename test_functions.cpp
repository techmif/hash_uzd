#include "lib.hpp"
#include "pagalbines_funkcijos.hpp"
#include "hash_funkcija.hpp"

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
        // accumulate average repetition-per-position (percentage)
        double sum_avg_rates = 0.0;

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
            // average repetition rate per position: average symbol percentage = 100 / unique_symbols
            double avg_rate_pos = total ? (100.0 / (double)total) : 0.0;

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
                << ", Vidutinis pasikartojimo dažnis: " << std::fixed << std::setprecision(2) << avg_rate_pos << "%"
                << ", Nepasikartojančių simbolių: " << unrepeated
                << ", Bitų pasiskirstymas (MSB..LSB): " << bits_ss.str() << std::endl;

            // accumulate for averages
            sum_unique += total;
            sum_max_rates += max_rate;
            sum_min_rates += min_rate;
            sum_unrepeated += unrepeated;
            sum_avg_rates += avg_rate_pos;
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
        // Overall average repetition rate per position (average of per-position averages)
        double avg_of_pos_avgs = sum_avg_rates / 64.0;
        out << "Bendras simbolių pasikartojimo vidurkis pozicijoje (%): " << std::fixed << std::setprecision(2) << avg_of_pos_avgs << std::endl;
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

void testavimas1(){
    string input, hash, salt;
    vector<int> nuskaityti_binary_duomenys;
    vector<int> konvertuota_ivestis;
    vector<int> konvertuota_druskyte;
    int suma;
    string pobudis="random";
    int hash_dydziai[4] = {10,100,500,10000};

    cout<<"kuriami 100 000 string, 10/100/500/1000 simboliu dydzio."<<endl;
    for(int i=0;i<4;i++){
        ofstream out("output" + std::to_string(i+1) + ".txt");
        for(int j=0;j<100000;j++){
            input = randSgen(pobudis,hash_dydziai[i]); //visiskai atsitiktiniu 10 skirtingu simboliu string.
            hashFunkcija(input, hash, salt);
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

void testavimas2(){
    string input, hash, salt;
    vector<int> nuskaityti_binary_duomenys;
    vector<int> konvertuota_ivestis;
    vector<int> konvertuota_druskyte;
    int suma;
    string pobudis="panasus";
    int hash_dydis[4] = {10,100,500,10000};

    cout<<"kuriami 100 000 string, kurie skiriasi tik 1 simboliu tarpusavy."<<endl;
    for(int i=0;i<4;i++){
        ofstream out("output" + std::to_string(i+1) + ".txt");
        for(int j=0;j<100000;j++){
            input = randSgen(pobudis,hash_dydis[i]); //visiskai atsitiktiniu 10 skirtingu simboliu string.
            hashFunkcija(input, hash, salt);
            if(j%10000==0) cout<<".";
            if(j==50000) cout<<(i+1)*25<<"%..";
            out<<input<<" "<<hash<<endl;
            clearData(input,hash,salt,suma,konvertuota_ivestis,konvertuota_druskyte); //isvalom kintamuosius
        }
        cout<<endl;
        out.close();
    }
    kolizijuanalize();
    simboliuanalize();
}

void testavimas3(){
    string input, hash, salt;
    vector<int> nuskaityti_binary_duomenys;
    vector<int> konvertuota_ivestis;
    vector<int> konvertuota_druskyte;
    int suma;
    int eiluciu_sk[9]={1,2,4,8,16,32,64,128,256};

    for(int i=0;i<10;i++){
        timer_point t = startTimer();
        if(i<9){
            cout<<"Pradedamas "<<eiluciu_sk[i]<<" eiluciu nuskaitymas."<<endl;
            input = read_first_n_lines("konstitucija.txt", eiluciu_sk[i]);
            hashFunkcija(input, hash, salt);
        }
        else {
            cout<<"Pradedamas viso failo nuskaitymas."<<endl;
            input = read_first_n_lines("konstitucija.txt", INT_MAX); //viso failo nuskaitymas
            salt = druskyte(input);
            KonvertCharIx10(input, konvertuota_ivestis);
            KonvertCharIx10(salt, konvertuota_druskyte);
            suma = Sumax10(konvertuota_ivestis);
            hashFunkcija(input, hash, salt);
        }
        double laikas = stopTimerSec(t);
        cout<<"Nuskaitymas ir hash generavimas baigtas, užtrukta laiko: "<<fixed<<setprecision(6)<<laikas<<"s."<<endl;
        clearData(input,hash,salt,suma,konvertuota_ivestis,konvertuota_druskyte);
    }
}
