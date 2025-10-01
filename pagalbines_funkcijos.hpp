#include "lib.hpp"

void nuskaitytimp3(vector<int> &nuskaityti_binary_duomenys);

void KonvertCharIx10 (string input, vector<int> &konvertuota_ivestis);

int Sumax10(vector<int> &konvertuota_ivestis);

void failo_pasirinkimas_ir_nuskaitymas(int &pasirinkimas, vector<string> &txtsarasas, string &input);

void clearData(string &input, string &hash, string &salt, int &suma, vector<int> &konvertuota_ivestis, vector<int> &konvertuota_druskyte);

static string read_first_n_lines(const string &filepath, int n);