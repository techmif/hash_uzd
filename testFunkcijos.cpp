#include "hashLib.h"
#include "functionCalls.h"

void hashTest() {
	int end = 6;
	while (true) {
		cout << "Pasirinkite norima hasho testavimo funkcija irasant skaiciu nuo 1 iki " << end << ".\n";
		cout << "------------------------------------------------------------------------\n";
		cout << "1 - HEX isvedimo ilgis\n";
		cout << "2 - Deterministiskumas\n";
		cout << "3 - Konstitucija\n";
		cout << "4 - Kolizija\n";
		cout << "5 - Poru generavimas\n";
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
			pairGenerator();
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

void pairGenerator() {
    // Select length
    cout << "\nPasirinkite poru eiluciu ilgi:\n";
    cout << "1 - 10\n2 - 100\n3 - 500\n4 - 1000\n";
    int choice = ivestiesPatikrinimas(1, 4);
    int length = (choice == 1 ? 10 : choice == 2 ? 100 : choice == 3 ? 500 : 1000);

    const size_t PAIRS = 100'000;
    std::string fileName = "pairs_" + std::to_string(length) + ".txt";
    cout << "Failo pavadinimas: " << fileName << "\n";

    std::ofstream out(fileName, std::ios::binary);
    if (!out) {
        cout << "Nepavyko sukurti failo.\n";
        return;
    }

    // Random generator
    static const char charset[] =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";
    const size_t charsetSize = sizeof(charset) - 1;

    std::random_device rd;
    std::mt19937_64 rng(rd());
    std::uniform_int_distribution<size_t> dist(0, charsetSize - 1);

    auto makeRandom = [&](int len) {
        std::string s;
        s.resize(static_cast<size_t>(len));
        for (int i = 0; i < len; ++i) {
            s[static_cast<size_t>(i)] = charset[dist(rng)];
        }
        return s;
    };

    cout << "Generuojamos poros (" << PAIRS << ")...\n";
    auto start = hrClock::now();

    for (size_t i = 0; i < PAIRS; ++i) {
        std::string a = makeRandom(length);
        std::string b = makeRandom(length);
        out << a << '\t' << b << '\n';
    }
    out.close();

    auto end = hrClock::now();
    sec dur = end - start;
    cout << "Generavimas baigtas per: " << std::fixed << std::setprecision(6) << dur.count() << " s\n\n";
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