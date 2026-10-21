#include <iostream>   // ivedimas / isvedimas (cin, cout)
#include <iomanip>    // isvedimo formatavimas (setprecision)
#include <string>     // string tipas vardams
using namespace std;

int main() {
    // ----- DUOMENU SAUGOJIMAS -----
    string vardai[100];          // iki 100 mokiniu vardu
    int pazymiai[100][10];       // kiekvienam mokiniui iki 10 pazymiu (eilute = mokinys)
    int kiekPaz[100] = {0};      // kiek pazymiu turi kiekvienas mokinys (pradzioje visi 0)

    int mokiniuKiekis = 0;       // kiek mokiniu yra sarase
    int pasirinkimas;            // meniu pasirinkimas

    // ----- PAGRINDINIS MENIU CIKLAS -----
    // Kartojasi, kol vartotojas pasirenka 7 (iseiti)
    do {
        cout << "\n--- MOKINIU PAZYMIU SISTEMA ---\n";
        cout << "1. Ivesti mokini ir jo pazymius\n";
        cout << "2. Perziureti visu mokiniu pazymius\n";
        cout << "3. Perziureti konkretaus mokinio pazymius\n";
        cout << "4. Atnaujinti pazymi\n";
        cout << "5. Apskaiciuoti mokinio vidurki\n";
        cout << "6. Pasalinti mokini\n";
        cout << "7. Iseiti\n";
        cout << "Pasirinkite: ";
        cin >> pasirinkimas;

        switch (pasirinkimas) {

        // ===== 1. NAUJO MOKINIO PRIDEJIMAS =====
        case 1: {
            // Tikriname, ar dar yra vietos masyve
            if (mokiniuKiekis >= 100) {
                cout << "Mokiniu sarasas pilnas!\n";
                break;
            }

            cout << "Iveskite mokinio varda: ";
            cin >> vardai[mokiniuKiekis];   // vardas irasomas i pirma laisva vieta

            // Klausiame, kiek pazymiu bus ivesta, kol gaunamas teisingas kiekis (0-10)
            int kiek;
            do {
                cout << "Kiek pazymiu ivesite (0-10): ";
                cin >> kiek;

                if (kiek < 0 || kiek > 10) {
                    cout << "Neteisingas kiekis. Iveskite nuo 0 iki 10.\n";
                }
            } while (kiek < 0 || kiek > 10);

            kiekPaz[mokiniuKiekis] = kiek;  // issaugome pazymiu kieki

            // Ivedame pazymius po viena; kartojame, kol pazymys yra 1-10
            for (int j = 0; j < kiek; j++) {
                do {
                    cout << "Iveskite " << j + 1 << "-aji pazymi (1-10): ";
                    cin >> pazymiai[mokiniuKiekis][j];

                    if (pazymiai[mokiniuKiekis][j] < 1 ||
                        pazymiai[mokiniuKiekis][j] > 10) {
                        cout << "Pazymys turi buti nuo 1 iki 10!\n";
                    }
                } while (pazymiai[mokiniuKiekis][j] < 1 ||
                         pazymiai[mokiniuKiekis][j] > 10);
            }

            mokiniuKiekis++;                // mokiniu padaugejo vienu
            cout << "Mokinys pridetas!\n";
            break;
        }

        // ===== 2. VISU MOKINIU PAZYMIU PERZIURA =====
        case 2:
            // Jei saraso nera, nera ko rodyti
            if (mokiniuKiekis == 0) {
                cout << "Mokiniu sarasas tuscias.\n";
                break;
            }

            // Einame per visus mokinius
            for (int i = 0; i < mokiniuKiekis; i++) {
                cout << "\nMokinys Nr. " << i + 1
                     << ": " << vardai[i] << "\n";
                cout << "Pazymiai: ";

                if (kiekPaz[i] == 0) {
                    cout << "Pazymiu nera";
                }

                // Isvedame visus sio mokinio pazymius
                for (int j = 0; j < kiekPaz[i]; j++) {
                    cout << pazymiai[i][j] << " ";
                }

                cout << "\n";
            }
            break;

        // ===== 3. KONKRETAUS MOKINIO PAZYMIU PERZIURA =====
        case 3: {
            if (mokiniuKiekis == 0) {
                cout << "Mokiniu sarasas tuscias.\n";
                break;
            }

            // Prasome mokinio numerio; 0 reiskia grizti atgal
            int nr;
            do {
                cout << "Mokinio numeris (1-"
                     << mokiniuKiekis << ", 0 - atgal): ";
                cin >> nr;

                if (nr == 0) break;   // iseiname is ciklo

                if (nr < 1 || nr > mokiniuKiekis) {
                    cout << "Neteisingas mokinio numeris. "
                         << "Iveskite nuo 1 iki "
                         << mokiniuKiekis << ".\n";
                }
            } while (nr < 1 || nr > mokiniuKiekis);

            if (nr == 0) break;       // vartotojas pasirinko "atgal" -> grizta i meniu

            int i = nr - 1;           // numeris nuo 1, o masyvo indeksas nuo 0

            cout << vardai[i] << " pazymiai: ";

            if (kiekPaz[i] == 0) {
                cout << "Pazymiu nera";
            }

            for (int j = 0; j < kiekPaz[i]; j++) {
                cout << pazymiai[i][j] << " ";
            }

            cout << "\n";
            break;
        }

        // ===== 4. PAZYMIO ATNAUJINIMAS =====
        case 4: {
            if (mokiniuKiekis == 0) {
                cout << "Mokiniu sarasas tuscias.\n";
                break;
            }

            // 1) Pasirenkame mokini (kaip 3 punkte)
            int nr;
            do {
                cout << "Mokinio numeris (1-"
                     << mokiniuKiekis << ", 0 - atgal): ";
                cin >> nr;

                if (nr == 0) break;

                if (nr < 1 || nr > mokiniuKiekis) {
                    cout << "Neteisingas mokinio numeris. "
                         << "Iveskite nuo 1 iki "
                         << mokiniuKiekis << ".\n";
                }
            } while (nr < 1 || nr > mokiniuKiekis);

            if (nr == 0) break;

            int i = nr - 1;

            // Jei mokinys neturi pazymiu, atnaujinti nera ko
            if (kiekPaz[i] == 0) {
                cout << "Sis mokinys neturi pazymiu.\n";
                break;
            }

            // 2) Pasirenkame, kuri pazymi keisime (1 .. pazymiu kiekis)
            int p;
            do {
                cout << "Pazymio numeris (1-"
                     << kiekPaz[i] << ", 0 - atgal): ";
                cin >> p;

                if (p == 0) break;

                if (p < 1 || p > kiekPaz[i]) {
                    cout << "Neteisingas pazymio numeris. "
                         << "Iveskite nuo 1 iki "
                         << kiekPaz[i] << ".\n";
                }
            } while (p < 1 || p > kiekPaz[i]);

            if (p == 0) break;

            // 3) Ivedame nauja pazymi (1-10)
            int naujas;
            do {
                cout << "Iveskite nauja pazymi (1-10): ";
                cin >> naujas;

                if (naujas < 1 || naujas > 10) {
                    cout << "Pazymys turi buti nuo 1 iki 10!\n";
                }
            } while (naujas < 1 || naujas > 10);

            pazymiai[i][p - 1] = naujas;   // p - 1, nes indeksai prasideda nuo 0
            cout << "Pazymys atnaujintas!\n";
            break;
        }

        // ===== 5. MOKINIO VIDURKIO SKAICIAVIMAS =====
        case 5: {
            if (mokiniuKiekis == 0) {
                cout << "Mokiniu sarasas tuscias.\n";
                break;
            }

            // Pasirenkame mokini
            int nr;
            do {
                cout << "Mokinio numeris (1-"
                     << mokiniuKiekis << ", 0 - atgal): ";
                cin >> nr;

                if (nr == 0) break;

                if (nr < 1 || nr > mokiniuKiekis) {
                    cout << "Neteisingas mokinio numeris. "
                         << "Iveskite nuo 1 iki "
                         << mokiniuKiekis << ".\n";
                }
            } while (nr < 1 || nr > mokiniuKiekis);

            if (nr == 0) break;

            int i = nr - 1;

            // Be pazymiu vidurkio skaiciuoti negalima (dalyba is 0)
            if (kiekPaz[i] == 0) {
                cout << "Mokinys neturi pazymiu. "
                     << "Vidurkio apskaiciuoti negalima.\n";
                break;
            }

            // Susumuojame visus pazymius
            int suma = 0;

            for (int j = 0; j < kiekPaz[i]; j++) {
                suma += pazymiai[i][j];
            }

            // (double) kad dalyba butu realiu skaiciu, o ne sveikuju
            double vidurkis = (double)suma / kiekPaz[i];

            cout << fixed << setprecision(2);   // 2 skaitmenys po kablelio
            cout << vardai[i] << " vidurkis: "
                 << vidurkis << "\n";
            break;
        }

        // ===== 6. MOKINIO PASALINIMAS =====
        case 6: {
            if (mokiniuKiekis == 0) {
                cout << "Mokiniu sarasas tuscias.\n";
                break;
            }

            // Pasirenkame, kuri mokini salinti
            int nr;
            do {
                cout << "Mokinio numeris (1-"
                     << mokiniuKiekis << ", 0 - atgal): ";
                cin >> nr;

                if (nr == 0) break;

                if (nr < 1 || nr > mokiniuKiekis) {
                    cout << "Neteisingas mokinio numeris. "
                         << "Iveskite nuo 1 iki "
                         << mokiniuKiekis << ".\n";
                }
            } while (nr < 1 || nr > mokiniuKiekis);

            if (nr == 0) break;

            int i = nr - 1;

            // Visus mokinius, esancius po pasalinamo, "pastumiame" per viena vieta
            // i prieki (perrasome ant pasalinamo mokinio duomenu)
            for (int j = i; j < mokiniuKiekis - 1; j++) {
                vardai[j] = vardai[j + 1];
                kiekPaz[j] = kiekPaz[j + 1];

                for (int k = 0; k < kiekPaz[j]; k++) {
                    pazymiai[j][k] = pazymiai[j + 1][k];
                }
            }

            mokiniuKiekis--;                // mokiniu sumazejo vienu
            cout << "Mokinys pasalintas!\n";
            break;
        }

        // ===== 7. IEJIMAS =====
        case 7:
            cout << "Programa baigta.\n";
            break;                          // ciklas pasibaigs, nes pasirinkimas == 7

        // ===== NETEISINGAS PASIRINKIMAS =====
        default:
            cout << "Neteisingas pasirinkimas. "
                 << "Pasirinkite nuo 1 iki 7.\n";
        }

    } while (pasirinkimas != 7);   // meniu kartojamas, kol nepasirinkta "Iseiti"

    return 0;
}