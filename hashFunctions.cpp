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

void hashFileLAS() {
	cout << "\n";
	cout << "\nIveskite kiek eiluciu norite nuskaityti is failo (0 - nuskaito visas eilutes): ";
	int linesToRead = ivestiesPatikrinimas(0, INT_MAX);

	std::stringstream buffer;
	std::string fileName = fileNameGetter();
	cout << "\nPasirinktas failas: " << fileName << "\n";
	std::ifstream duom(fileName);
	if (!duom) {
		throw std::runtime_error("\nFailas nerastas.\n\n");
		return;
	}
	buffer << duom.rdbuf();
	duom.close();

	string line;
	int processed = 0;

	if (linesToRead <= 0) {
		// 0 or negative -> read all lines
		while (std::getline(buffer, line)) {
			++processed;
			uint64_t h = chaoticPrimeMixer(line);
			std::cout << "Line " << std::left << std::setw(10) << processed
				<< " Decimal: " << std::left << std::setw(25) << h
				<< " Hex: " << std::left << std::setw(25) << decimalToHex(h) << "\n";
		}
	}
	else {
		while (processed < linesToRead && std::getline(buffer, line)) {
			++processed;
			uint64_t h = chaoticPrimeMixer(line);
			std::cout << "Line " << std::left << std::setw(10) << processed
				<< " Decimal: " << std::left << std::setw(25) << h
				<< " Hex: " << std::left << std::setw(25) << decimalToHex(h) << "\n";
		}
		if (processed < linesToRead) {
			std::cout << "\nFailas turi tik " << processed
				<< " eiluciu (prasete " << linesToRead << ").\n";
		}
	}
	std::cout << "\n";
}