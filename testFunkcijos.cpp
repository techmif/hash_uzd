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

	// Split into lines once (so later timing isolates ONLY hashing cost)
	std::vector<std::string> lines;
	lines.reserve(1024);
	{
		std::string current;
		std::istringstream iss(content);
		while (std::getline(iss, current)) {
			lines.push_back(current);
		}
	}
	if (lines.empty()) {
		cout << "Eiluciu nerasta.\n";
		return;
	}

	size_t totalLines = lines.size();
	cout << "Bendras eiluciu skaicius faile: " << totalLines << "\n";
	cout << "Vykdomas eksponentinis HASH testas (1,2,4,...)\n";

	const int iterations = 20;

	for (size_t batch = 1; batch <= totalLines; batch <<= 1) {
		size_t target = std::min(batch, totalLines);

		sec totalTime{ 0.0 };
		volatile uint64_t sink = 0; // prevents optimizer removing hashing loop

		for (int it = 0; it < iterations; ++it) {
			auto start = hrClock::now();
			for (size_t i = 0; i < target; ++i) {
				sink ^= chaoticPrimeMixer(lines[i]); // hash each line individually
			}
			auto end = hrClock::now();
			totalTime += (end - start);
		}

		double avgSec = (totalTime / iterations).count();

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