#include "hashLib.h"
#include "functionCalls.h"

void hashTest() {
	int end = 8;
	while (true) {
		cout << "Pasirinkite norima hasho testavimo funkcija irasant skaiciu nuo 1 iki " << end << ".\n";
		cout << "------------------------------------------------------------------------\n";
		cout << "1 - TEST - HEX isvedimo ilgis\n";
		cout << "2 - TEST - Deterministiskumas\n";
		cout << "3 - TEST - Konstitucija\n";
		cout << "4 - TEST - Kolizija\n";
		cout << "5 - TEST - Lavina\n";
		cout << "6 - TEST - Druskinimas\n";
		cout << "7 - GENS - Poru generavimas\n";
		cout << "8 - GENS - Panasi poru generavimas\n";
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
			collisionTest();
			break;
		case 5:
			avalancheTest();
			break;
		case 6:
			saltTest();
			break;
		case 7:
			pairGenerator();
			break;
		case 8:
			similarPairGenerator();
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
	
	input = "The quick brown fox jumps over the lazy dog";
	decimal_value = chaoticPrimeMixer(input);
	cout << "\nInput:-" << input << "-";
	cout << "\nDecimal: " << decimal_value;
	cout << "\nHexdecimal: " << decimalToHex(decimal_value) << "\n";

	input = "The quick brown fox jumps over the lazy dog.";
	decimal_value = chaoticPrimeMixer(input);
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

void collisionTest() {
    std::string fileName = fileNameGetter();

    std::ifstream in(fileName, std::ios::binary);
    if (!in) {
        cout << "Failas nerastas.\n\n";
        return;
    }

    size_t totalPairs = 0;
    size_t hashMatches = 0;
    size_t trueCollisions = 0;
    size_t identicalPairs = 0;

    std::string s1, s2;

    cout << "Skaitoma ir tikrinama...\n";
    auto start = hrClock::now();

    while (in >> s1 >> s2) {
        ++totalPairs;
        uint64_t h1 = chaoticPrimeMixer(s1);
        uint64_t h2 = chaoticPrimeMixer(s2);
        if (h1 == h2) {
            ++hashMatches;
            if (s1 == s2) {
                ++identicalPairs;          // same string => trivial
            } else {
                ++trueCollisions;          // different strings => real collision
            }
        }
    }
    auto end = hrClock::now();
    sec dur = end - start;

    if (totalPairs == 0) {
        cout << "Nerasta poru.\n\n";
        return;
    }

    double matchPct = (static_cast<double>(hashMatches) / totalPairs) * 100.0;
    double trueColPct = (static_cast<double>(trueCollisions) / totalPairs) * 100.0;

    cout << std::fixed << std::setprecision(8);
    cout << "\nRezultatai failui: " << fileName << "\n";
    cout << "Viso poru:                " << totalPairs << "\n";
    cout << "Hash sutapimu (viso):     " << hashMatches << " (" << matchPct << " %)\n";
    cout << "Is ju tikru koliziju:     " << trueCollisions << " (" << trueColPct << " %)\n";
    cout << "Is ju identisku (tas pats tekstas): " << identicalPairs << "\n";
    cout << "Tikrinimo trukme:         " << dur.count() << " s\n\n";
}

void avalancheTest() {
	std::string fileName = fileNameGetter();

	std::ifstream in(fileName, std::ios::binary);
	if (!in) {
		cout << "Failas nerastas.\n\n";
		return;
	}

	auto toHex64 = [](uint64_t v) {
		std::ostringstream oss;
		oss << std::hex << std::uppercase << std::setw(16) << std::setfill('0') << v;
		return oss.str();
		};

	auto popcount64 = [](uint64_t x) -> int {
#if defined(_MSC_VER) && defined(_M_X64)
		return static_cast<int>(__popcnt64(x));
#else
		return static_cast<int>(__builtin_popcountll(x));
#endif
		};

	size_t totalPairs = 0;

	double sumBitPct = 0.0;
	double minBitPct = std::numeric_limits<double>::infinity();
	double maxBitPct = 0.0;

	double sumHexPct = 0.0;
	double minHexPct = std::numeric_limits<double>::infinity();
	double maxHexPct = 0.0;

	std::string line;
	std::string a, b;

	auto start = hrClock::now();
	while (std::getline(in, line)) {
		if (line.empty()) continue;
		auto tabPos = line.find('\t');
		if (tabPos == std::string::npos) continue;
		a = line.substr(0, tabPos);
		b = line.substr(tabPos + 1);

		uint64_t h1 = chaoticPrimeMixer(a);
		uint64_t h2 = chaoticPrimeMixer(b);

		uint64_t diff = h1 ^ h2;
		int diffBits = popcount64(diff);
		double bitPct = (static_cast<double>(diffBits) / 64.0) * 100.0;

		std::string hx1 = toHex64(h1);
		std::string hx2 = toHex64(h2);
		int diffHexChars = 0;
		for (size_t i = 0; i < 16; ++i) {
			if (hx1[i] != hx2[i]) ++diffHexChars;
		}
		double hexPct = (static_cast<double>(diffHexChars) / 16.0) * 100.0;

		sumBitPct += bitPct;
		if (bitPct < minBitPct) minBitPct = bitPct;
		if (bitPct > maxBitPct) maxBitPct = bitPct;

		sumHexPct += hexPct;
		if (hexPct < minHexPct) minHexPct = hexPct;
		if (hexPct > maxHexPct) maxHexPct = hexPct;

		++totalPairs;
		if (totalPairs % 20000 == 0) {
			cout << "Apdorota: " << totalPairs << "\n";
		}
	}
	auto end = hrClock::now();
	sec dur = end - start;

	if (totalPairs == 0) {
		cout << "Poru nerasta failuose.\n";
		return;
	}

	double avgBitPct = sumBitPct / totalPairs;
	double avgHexPct = sumHexPct / totalPairs;

	cout << std::fixed << std::setprecision(6);
	cout << "\nAvalanche rezultatai (" << fileName << ")\n";
	cout << "Poru kiekis: " << totalPairs << "\n\n";
	cout << "Bit'u skirtumo % (per 64 bitus):\n"
		<< "  Min: " << minBitPct << "\n"
		<< "  Max: " << maxBitPct << "\n"
		<< "  Avg: " << avgBitPct << "\n\n";
	cout << "Hex simboliu skirtumo % (per 16 hex simboliu):\n"
		<< "  Min: " << minHexPct << "\n"
		<< "  Max: " << maxHexPct << "\n"
		<< "  Avg: " << avgHexPct << "\n\n";
	cout << "Testo trukme: " << dur.count() << " s\n\n";
}

void saltTest() {
	std::string input = "The quick brown fox jumps over the lazy dog";
	cout << "\nInput:-" << input << "-\n\n";
	cout << "Unsalted decimal: " << chaoticPrimeMixer(input) << "  Hex: " << decimalToHex(chaoticPrimeMixer(input)) << "\n\n";
	for (uint64_t salt = 0; salt <= 5; ++salt) {
		uint64_t decimal_value = chaoticPrimeMixer(input, salt);
		cout << "Salt: " << salt
			<< "  Decimal: " << std::left << std::setw(22) << decimal_value
			<< "  Hex: " << decimalToHex(decimal_value) << "\n";
	}
	cout << "\n\n";
}