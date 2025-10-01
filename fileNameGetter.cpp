#include "hashLib.h"
#include "functionCalls.h"

string fileNameGetter() {
    vector<string> txtFiles;
    int index = 1;

    // Collect and display .txt files
    for (const auto& entry : fs::directory_iterator(".")) {
        if (entry.path().extension() == ".txt") {
            txtFiles.push_back(entry.path().filename().string());
            cout << index << ": " << txtFiles.back() << endl;
            ++index;
        }
    }

    if (txtFiles.empty()) {
        cout << "No .txt files found." << endl;
        return "";
    }

    int choice = 0;
    cout << "Enter the number of the file you want to select: ";
    while (true) {
		choice = ivestiesPatikrinimas(1, static_cast<int>(txtFiles.size()));
        break;
    }

    string ivestas_vardas = txtFiles[choice - 1];
    return ivestas_vardas;
}