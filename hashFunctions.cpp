#include "hashLib.h"
#include "functionCalls.h"

void hashManual (){
    cout << "\n";


	string input;
	cout << "Iveskite teksta kuri norite hashuoti: \n";
    cin >> input;
	

    uint64_t decimal_value = chaoticPrimeMixer(input);
    cout << "\nDecimal: " << decimal_value << "\n";

    cout << "\nHexdecimal: "<< decimalToHex(decimal_value) << "\n";


    cout << "\n\n";
}

void hashFile (){
	cout << "\n";


	std::stringstream buffer;
	std::string fileName;
	fileName = fileNameGetter();
	cout << "\nPasirinktas failas: " << fileName << "\n";
	std::ifstream duom(fileName);
	if (!duom) {
		throw std::runtime_error("\nFailas nerastas.\n\n");
		return;
	}
	buffer << duom.rdbuf();
	duom.close();


	string input = buffer.str();
	uint64_t decimal_value = chaoticPrimeMixer(input);
    cout << "\nDecimal: " << decimal_value << "\n";

    cout << "\nHexdecimal: " << decimalToHex(decimal_value) << "\n";


    cout << "\n\n";
}