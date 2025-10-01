#include "hashLib.h"
#include "functionCalls.h"

int main(){
	std::cin.exceptions(std::ios::failbit);
	int end = 5;
	while (true) {
		cout << "Pasirinkite norima hasho veikla irasant skaiciu nuo 1 iki " << end << ".\n";
		cout << "------------------------------------------------------------------------\n";
		cout << "1 - Ivestis ranka\n";
		cout << "2 - Failo nuskaitymas\n";
		cout << "3 - File read with Line Amount Selection\n";
		cout << "4 - Testine aplinka\n";
		cout << end << " - Baigti darba\n";
		cout << "------------------------------------------------------------------------\n";

		int menuPasirinkimas = ivestiesPatikrinimas(1, end, end);


		if (menuPasirinkimas == end) { cout << "\nProgram finished\n\n"; break; }

		switch (menuPasirinkimas) {
		case 1:
			hashManual();
			break;
		case 2:
			hashFile();
			break;
		case 3:
			hashFileLAS();
			break;
		case 4:
			hashTest();
			break;
		default:
			cout << "Klaida pasirenkant meniu punkta. Bandykite is naujo.\n";
			break;
		}
	}
}
