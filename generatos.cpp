#include "hashLib.h"
#include "functionCalls.h"

static std::string randomString(std::mt19937_64& rng, int length) {
    static const char charset[] =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";
    const size_t N = sizeof(charset) - 1;
    std::uniform_int_distribution<size_t> dist(0, N - 1);
    std::string s;
    s.resize(static_cast<size_t>(length));
    for (int i = 0; i < length; ++i) {
        s[static_cast<size_t>(i)] = charset[dist(rng)];
    }
    return s;
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

void similarPairGenerator() {
    cout << "\nPasirinkite eilutes ilgi poroms:\n"
        << "1 - 10\n2 - 100\n3 - 500\n4 - 1000\n";
    int choice = ivestiesPatikrinimas(1, 4);
    int length = (choice == 1 ? 10 : choice == 2 ? 100 : choice == 3 ? 500 : 1000);

    const size_t PAIRS = 100'000;
    std::string fileName = "similar_" + std::to_string(length) + ".txt";
    cout << "Generuojama " << PAIRS << " poru (failas: " << fileName << ")...\n";

    std::ofstream out(fileName, std::ios::binary);
    if (!out) {
        cout << "Nepavyko sukurti failo.\n";
        return;
    }

    std::random_device rd;
    std::mt19937_64 rng(rd());
    std::uniform_int_distribution<int> posDist(0, length - 1);
    static const char charset[] =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";
    const size_t charsetSize = sizeof(charset) - 1;
    std::uniform_int_distribution<size_t> chDist(0, charsetSize - 1);

    auto start = hrClock::now();
    for (size_t i = 0; i < PAIRS; ++i) {
        std::string a = randomString(rng, length); // now defined above
        std::string b = a;
        int p = posDist(rng);
        char original = b[static_cast<size_t>(p)];
        char replacement;
        do {
            replacement = charset[chDist(rng)];
        } while (replacement == original);
        b[static_cast<size_t>(p)] = replacement;

        out << a << '\t' << b << '\n';

        if ((i + 1) % 20000 == 0) {
            cout << "Sukurta: " << (i + 1) << "\n";
        }
    }
    out.close();
    auto end = hrClock::now();
    sec dur = end - start;
    cout << "Baigta per " << std::fixed << std::setprecision(6) << dur.count() << " s\n\n";
}