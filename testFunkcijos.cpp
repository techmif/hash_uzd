#include "hashLib.h"
#include "functionCalls.h"

void hashTest() {
	int end = 4;
	while (true) {
		cout << "Pasirinkite norima hasho testavimo funkcija irasant skaiciu nuo 1 iki " << end << ".\n";
		cout << "------------------------------------------------------------------------\n";
		cout << "1 - File read with Line Amount Selection\n";
		cout << "2 - Failo nuskaitymas\n";
		cout << "3 - Poru generavimas\n";
		cout << end << " - Baigti darba\n";
		cout << "------------------------------------------------------------------------\n";
		int menuPasirinkimas = ivestiesPatikrinimas(1, end, end);


		if (menuPasirinkimas == end) { cout << "\nTestavimas baigesi, griztama i pagrindini meniu\n\n\n"; break; }

		switch (menuPasirinkimas) {
		case 1:
			outputLength();
			break;
		case 2:
			cout << "\nFunction not implemented yet.\n";
			break;
		case 3:
			hashFileLAS(5);
			break;
		default:
			cout << "\nKlaida pasirenkant meniu punkta. Bandykite is naujo.\n";
			break;
		}
	}
}

void outputLength() {
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
	cout << "Hex length:" << decimalToHex(decimal_value).size() << "\n";


	cout << "\n\n";
}

void hashFileLAS(int end) {
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

		std::string line;
		int i = 0;
		while (getline(buffer, line) || i == end) {
			string input = buffer.str();
			uint64_t decimal_value = chaoticPrimeMixer(input);

			cout << "\nLine " << i + 1 << ": " << line;

			cout << "\nDecimal: " << decimal_value << "\n";

			cout << "\nHexdecimal: " << decimalToHex(decimal_value) << "\n";
		}
	}
