#include "hashLib.h"
#include "functionCalls.h"


uint64_t chaoticPrimeMixer(const std::string& input) {
    static const std::vector<uint64_t> primes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29
    };

    uint64_t state = 0x84222325ULL; // arbitrary seed

    for (size_t i = 0; i < input.size(); i++) {
        uint64_t c = static_cast<unsigned char>(input[i]);
        uint64_t val = (c * primes[i % primes.size()]) ^ (i * 2654435761u);
        state = (state ^ val) * 6364136223846793005ULL + 1;
    }

    // final mixing
    state ^= (state >> 33);
    state *= 0xff51afd7ed558ccdULL;
    state ^= (state >> 29);
    state *= 0xc4ceb9fe1a85ec53ULL;
    state ^= (state >> 32);

    return state;
}

void hashManual (){
	string input;
	cout << "Iveskite teksta kuri norite hashuoti: \n";
    cin >> input;
	

    uint64_t decimal_value = chaoticPrimeMixer(input);
    cout << "\nDecimal: " << decimal_value << "\n";


    std::stringstream ss;
    ss << std::hex << decimal_value;
    std::string res(ss.str());
    std::cout << "Hexdecimal: "<< res << "\n";
}

void hashFile (){
	std::stringstream buffer;
	std::ifstream duom(fileNameGetter());
	if (!duom) {
		throw std::runtime_error("\nFailas nerastas.\n\n");
		return;
	}
	buffer << duom.rdbuf();
	duom.close();


	string input = buffer.str();
	uint64_t decimal_value = chaoticPrimeMixer(input);
    cout << "\nDecimal: " << decimal_value << "\n";


    std::stringstream ss;
    ss << std::hex << decimal_value;
    std::string res(ss.str());
    std::cout << "Hexdecimal: " << res << "\n";
}

void hashTest (){
    cout << "Placeholder" << endl;
}