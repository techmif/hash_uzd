#include "hashLib.h"
#include "functionCalls.h"

void hashTest() {
	int end = 5;
	while (true) {
		cout << "Pasirinkite norima hasho testavimo funkcija irasant skaiciu nuo 1 iki " << end << ".\n";
		cout << "------------------------------------------------------------------------\n";
		cout << "1 - HEX isvedimo ilgis\n";
		cout << "2 - Deterministiskumas\n";
		cout << "3 - File read with Line Amount Selection\n";
		cout << "4 - Poru generavimas\n";
		cout << end << " - Baigti darba\n";
		cout << "------------------------------------------------------------------------\n";
		int menuPasirinkimas = ivestiesPatikrinimas(1, end, end);


		if (menuPasirinkimas == end) { cout << "\nTestavimas baigesi, griztama i pagrindini meniu\n\n\n"; break; }

		switch (menuPasirinkimas) {
		case 1:
			outputLength();
			break;
		case 2:
			deterministicTest();
			break;
		case 3:
			hashFileLAS();
			break;
		case 4:
			cout << "\nPlaceholder text\n\n";
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

void deterministicTest() {
	string input = "The quick brown fox jumps over the lazy dog";
	uint64_t decimal_value = chaoticPrimeMixer(input);
	cout << "\nInput:-" << input << "-";
	cout << "\nDecimal: " << decimal_value;
	cout << "\nHexdecimal: " << decimalToHex(decimal_value) << "\n";

	input = "The quick brown fox jumps over the lazy dog.";
	decimal_value = chaoticPrimeMixer(input);
	cout << "\nInput:-" << input << "-";
	cout << "\nDecimal: " << decimal_value;
	cout << "\nHexdecimal: " << decimalToHex(decimal_value) << "\n";

	input = "The quick brown fox jumps over the lazy dog!";
	decimal_value = chaoticPrimeMixer(input);
	cout << "\nInput:-" << input << "-";
	cout << "\nDecimal: " << decimal_value;
	cout << "\nHexdecimal: " << decimalToHex(decimal_value) << "\n";

	input = "The quick brown fox jumps over the lazy dog?";
	decimal_value = chaoticPrimeMixer(input);
	cout << "\nInput:-" << input << "-";
	cout << "\nDecimal: " << decimal_value;
	cout << "\nHexdecimal: " << decimalToHex(decimal_value) << "\n";

	input = "The quick brown fox jumps over the lazy dog ";
	decimal_value = chaoticPrimeMixer(input);
	cout << "\nInput:-" << input << "-";
	cout << "\nDecimal: " << decimal_value;
	cout << "\nHexdecimal: " << decimalToHex(decimal_value) << "\n";

	input = "The quick brown fox jumps over the lazy dog  ";
	decimal_value = chaoticPrimeMixer(input);
	cout << "\nInput:-" << input << "-";
	cout << "\nDecimal: " << decimal_value;
	cout << "\nHexdecimal: " << decimalToHex(decimal_value) << "\n";

	input = "The quick brown fox jumps over the lazy dog   ";
	decimal_value = chaoticPrimeMixer(input);
	cout << "\nInput:-" << input << "-";
	cout << "\nDecimal: " << decimal_value;
	cout << "\nHexdecimal: " << decimalToHex(decimal_value) << "\n";

	input = "The quick brown fox jumps over the lazy dog    ";
	decimal_value = chaoticPrimeMixer(input);
	cout << "\nInput:-" << input <<"-";
	cout << "\nDecimal: " << decimal_value;
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
