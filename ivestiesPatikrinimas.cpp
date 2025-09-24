#include "hashLib.h"
#include "functionCalls.h"

/** Lengvai naudojama pagalbine funkcija gaudanti neteisingas ivestis.*/
int ivestiesPatikrinimas(const int nuo, const int iki) {
	int input{};
	while (true) {
		try {
			cin >> input;
			if (input < nuo || input > iki) {
				cout << "\n\n!!!!Iveskite skaiciu nuo " << nuo << " iki " << iki << ".!!!!\n\n\n";
				continue;
			}
		}
		catch (...) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "\n\n!!!!Ivestis neteisinga. Bandykite isnaujo.!!!!\n\n\n";
			continue;
		}
		break;
	}
	return input;
}

/** Lengvai naudojama pagalbine funkcija gaudanti neteisingas ivestis su sustabdymo salyga.*/
int ivestiesPatikrinimas(const int nuo, const int iki, const int sustabdymoSalyga) {
	int input{};
	while (true) {
		try {
			cin >> input;
			if (input == sustabdymoSalyga) {
				return sustabdymoSalyga;
			}

			if (input < nuo || input > iki) {
				cout << "\n\n!!!!Iveskite skaiciu nuo " << nuo << " iki " << iki << ".!!!!\n\n\n";
				continue;
			}
		}
		catch (...) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "\n\n!!!!Ivestis neteisinga. Bandykite isnaujo.!!!!\n\n\n";
			continue;
		}
		break;
	}
	return input;
}