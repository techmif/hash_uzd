#include "hashLib.h"
#include "functionCalls.h"

void hashTest() {
	int end = 5;
	while (true) {
		cout << "Pasirinkite norima hasho testavimo funkcija irasant skaiciu nuo 1 iki " << end << ".\n";
		cout << "------------------------------------------------------------------------\n";
		cout << "1 - HEX isvedimo ilgis\n";
		cout << "2 - Deterministiskumas\n";
		cout << "3 - Konstitucija\n";
		cout << "4 - Poru generavimas\n";
		cout << end << " - Baigti darba\n";
		cout << "------------------------------------------------------------------------\n";
		int menuPasirinkimas = ivestiesPatikrinimas(1, end, end);


		if (menuPasirinkimas == end) { cout << "\nTestavimas baigesi, griztama i pagrindini meniu\n\n\n"; break; }

		switch (menuPasirinkimas) {
		case 1:
			outputLengthTest();
			break;
		case 2:
			deterministicTest();
			break;
		case 3:
			konstitucijaTest();
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

void outputLengthTest() {
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

void konstitucijaTest() {
	const std::string fileName = "konstitucija.txt";
	std::ifstream duom(fileName, std::ios::binary);
	if (!duom) {
		cout << "'konstitucija.txt' failas nerastas.\n\n";
		return;
	}

	// Nuskaityti visa faila i buferi VIENĄ kartą
	std::ostringstream raw;
	raw << duom.rdbuf();
	std::string content = raw.str();
	duom.close();

	if (content.empty()) {
		cout << "Failas tuscias.\n";
		return;
	}

	// Suskaiciuoti eiluciu kieki
	size_t totalLines = 0;
	{
		std::istringstream iss(content);
		std::string tmp;
		while (std::getline(iss, tmp)) ++totalLines;
	}
	if (totalLines == 0) {
		cout << "Eiluciu nerasta.\n";
		return;
	}

	cout << "Bendras eiluciu skaicius faile: " << totalLines << "\n";
	cout << "Vykdomas eksponentinis skaitymo testas (1,2,4,...)\n";

	const int iterations = 20;

	for (size_t linesToRead = 1; linesToRead <= totalLines; linesToRead <<= 1) {
		size_t target = std::min(linesToRead, totalLines);

		sec totalTime{ 0.0 }; // accumulate as seconds (sec = std::chrono::duration<double>)
		for (int it = 0; it < iterations; ++it) {
			std::istringstream iss(content);
			std::string line;
			size_t count = 0;
			volatile size_t sink = 0; // keep loop work observable

			auto start = hrClock::now();
			while (count < target && std::getline(iss, line)) {
				sink += line.size();
				++count;
			}
			auto end = hrClock::now();
			totalTime += (end - start); // (end-start) is a duration; added directly
		}

		double avgSec = (totalTime / iterations).count();

		// Fixed formatting similar to your snippet
		std::ios::fmtflags oldFlags = cout.flags();
		auto oldPrec = cout.precision();
		cout << std::fixed << std::setprecision(8);

		cout << "Lines: " << std::left << std::setw(10) << target
			<< " in: " << avgSec << " sec\n";

		cout.flags(oldFlags);
		cout.precision(oldPrec);

		if (target == totalLines) break;
	}

	cout << "\n";
}