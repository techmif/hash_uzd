#include "hashLib.h"
#include "functionCalls.h"

int ivestiesPatikrinimas(const int nuo, const int iki) {
	int input{};
	while (true) {
		try {
			std::cin >> input;
			if (input < nuo || input > iki) {
				std::cout << "\n\n!!!!Iveskite skaiciu nuo " << nuo << " iki " << iki << ".!!!!\n\n\n";
				continue;
			}
		}
		catch (...) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "\n\n!!!!Ivestis neteisinga. Bandykite isnaujo.!!!!\n\n\n";
			continue;
		}
		break;
	}
	return input;
}

int ivestiesPatikrinimas(const int nuo, const int iki, const int sustabdymoSalyga) {
	int input{};
	while (true) {
		try {
			std::cin >> input;
			if (input == sustabdymoSalyga) {
				return sustabdymoSalyga;
			}

			if (input < nuo || input > iki) {
				std::cout << "\n\n!!!!Iveskite skaiciu nuo " << nuo << " iki " << iki << ".!!!!\n\n\n";
				continue;
			}
		}
		catch (...) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "\n\n!!!!Ivestis neteisinga. Bandykite isnaujo.!!!!\n\n\n";
			continue;
		}
		break;
	}
	return input;
}