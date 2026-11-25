
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <limits>
#include <cmath>

using namespace std;

const int MAX_PREKIU = 100;

// ------------------------------------------
// Funkcija pašalina tarpus eilutės pradžioje
// ir pabaigoje
// ------------------------------------------
string pasalintiTarpus(string tekstas) {
    size_t pradzia = tekstas.find_first_not_of(" \t\r\n");

    if (pradzia == string::npos) {
        return "";
    }

    size_t pabaiga = tekstas.find_last_not_of(" \t\r\n");

    return tekstas.substr(pradzia, pabaiga - pradzia + 1);
}

// ------------------------------------------
// Patikrina, ar kategorija tinkama
// ------------------------------------------
bool tinkamaKategorija(string kategorija) {
    return kategorija == "Dviraciai" ||
           kategorija == "Dalys" ||
           kategorija == "Aksesuarai";
}

// ------------------------------------------
// Nuskaito sveikąjį skaičių iš eilutės
// ------------------------------------------
bool nuskaitytiSveikaji(string tekstas, int &skaicius) {
    stringstream ss(tekstas);
    char papildomas;

    if (!(ss >> skaicius)) {
        return false;
    }

    if (ss >> papildomas) {
        return false;
    }

    return true;
}

// ------------------------------------------
// Nuskaito kainą iš eilutės
// ------------------------------------------
bool nuskaitytiKaina(string tekstas, double &kaina) {
    stringstream ss(tekstas);
    char papildomas;

    if (!(ss >> kaina)) {
        return false;
    }

    if (ss >> papildomas) {
        return false;
    }

    if (!isfinite(kaina) || kaina <= 0) {
        return false;
    }

    return true;
}

// ------------------------------------------
// Duomenų nuskaitymas iš failo
// ------------------------------------------
bool nuskaitytiDuomenis(
    string duomenys,
    string kategorijos[],
    string pavadinimai[],
    double kainos[],
    int kiekiai[],
    int &n
) {
    ifstream failas(duomenys);

    if (!failas.is_open()) {
        cout << "Nepavyko atidaryti failo "
             << duomenys << "!" << endl;
        return false;
    }

    string eilute;

    // Nuskaitome pirmą eilutę - prekių skaičių
    if (!getline(failas, eilute)) {
        cout << "Failas yra tuscias!" << endl;
        return false;
    }

    eilute = pasalintiTarpus(eilute);

    if (!nuskaitytiSveikaji(eilute, n)) {
        cout << "Netinkamas prekiu skaicius!" << endl;
        return false;
    }

    if (n < 1 || n > MAX_PREKIU) {
        cout << "Prekiu skaicius turi buti nuo 1 iki 100!"
             << endl;
        return false;
    }

    // Nuskaitome visas prekes
    for (int i = 0; i < n; i++) {
        if (!getline(failas, eilute)) {
            cout << "Truksta duomenu apie preke "
                 << i + 1 << "!" << endl;
            return false;
        }

        stringstream ss(eilute);

        string kategorija;
        string pavadinimas;
        string kainaTekstas;
        string kiekisTekstas;
        string papildomas;

        // Nuskaitome 4 laukus, atskirtus kabliataškiu
        if (!getline(ss, kategorija, ';') ||
            !getline(ss, pavadinimas, ';') ||
            !getline(ss, kainaTekstas, ';') ||
            !getline(ss, kiekisTekstas, ';')) {

            cout << "Netinkamas duomenu formatas "
                 << i + 1 << " eiluteje!" << endl;
            return false;
        }

        // Patikriname, ar nėra papildomų laukų
        if (getline(ss, papildomas, ';')) {
            cout << "Per daug duomenu "
                 << i + 1 << " eiluteje!" << endl;
            return false;
        }

        kategorija = pasalintiTarpus(kategorija);
        pavadinimas = pasalintiTarpus(pavadinimas);
        kainaTekstas = pasalintiTarpus(kainaTekstas);
        kiekisTekstas = pasalintiTarpus(kiekisTekstas);

        if (!tinkamaKategorija(kategorija)) {
            cout << "Netinkama kategorija "
                 << i + 1 << " eiluteje!" << endl;
            return false;
        }

        if (pavadinimas.empty()) {
            cout << "Prekes pavadinimas negali buti tuscias!"
                 << endl;
            return false;
        }

        if (!nuskaitytiKaina(kainaTekstas, kainos[i])) {
            cout << "Netinkama kaina "
                 << i + 1 << " eiluteje!" << endl;
            return false;
        }

        if (!nuskaitytiSveikaji(kiekisTekstas, kiekiai[i]) ||
            kiekiai[i] <= 0) {
            cout << "Netinkamas kiekis "
                 << i + 1 << " eiluteje!" << endl;
            return false;
        }

        kategorijos[i] = kategorija;
        pavadinimai[i] = pavadinimas;
    }

    // Patikriname, ar faile nėra papildomų įrašų
    while (getline(failas, eilute)) {
        if (!pasalintiTarpus(eilute).empty()) {
            cout << "Faile yra papildomu eiluciu!" << endl;
            return false;
        }
    }

    failas.close();

    return true;
}

// ------------------------------------------
// Apskaičiuoja vienos eilutės sumą
// ------------------------------------------
double eilutesSuma(double kaina, int kiekis) {
    return kaina * kiekis;
}

// ------------------------------------------
// Apskaičiuoja vienos eilutės nuolaidą
// ------------------------------------------
double nuolaida(double suma, int kiekis) {
    if (kiekis >= 10) {
        return suma * 0.10;
    }

    return 0;
}

// ------------------------------------------
// Apskaičiuoja sumą po nuolaidos
// ------------------------------------------
double moketinaSuma(double kaina, int kiekis) {
    double suma = eilutesSuma(kaina, kiekis);
    double nuolaidaSuma = nuolaida(suma, kiekis);

    return suma - nuolaidaSuma;
}

// ------------------------------------------
// Apskaičiuoja bendrą užsakymo sumą
// ------------------------------------------
double visoSuma(
    double kainos[],
    int kiekiai[],
    int n
) {
    double suma = 0;

    for (int i = 0; i < n; i++) {
        suma += eilutesSuma(kainos[i], kiekiai[i]);
    }

    return suma;
}

// ------------------------------------------
// Apskaičiuoja bendrą nuolaidų sumą
// ------------------------------------------
double visoNuolaida(
    double kainos[],
    int kiekiai[],
    int n
) {
    double suma = 0;

    for (int i = 0; i < n; i++) {
        double eilute = eilutesSuma(kainos[i], kiekiai[i]);

        suma += nuolaida(eilute, kiekiai[i]);
    }

    return suma;
}

// ------------------------------------------
// Apskaičiuoja pasirinktos kategorijos sumą
// po nuolaidų
// ------------------------------------------
double kategorijosSuma(
    string kategorija,
    string kategorijos[],
    double kainos[],
    int kiekiai[],
    int n
) {
    double suma = 0;

    for (int i = 0; i < n; i++) {
        if (kategorijos[i] == kategorija) {
            suma += moketinaSuma(kainos[i], kiekiai[i]);
        }
    }

    return suma;
}

// ------------------------------------------
// Spausdina prekių lentelę
// ------------------------------------------
void spausdintiPrekes(
    ostream &out,
    string kategorijos[],
    string pavadinimai[],
    double kainos[],
    int kiekiai[],
    int n,
    string pasirinktaKategorija = ""
) {


    out << left
     << setw(16) << "Kategorija"
     << setw(25) << "Preke"
     << right
     << setw(20) << "Kaina"
     << setw(10) << "Kiekis"
     << setw(12) << "Suma"
     << setw(12) << "Nuolaida"
     << setw(15) << "Moketi"
     << endl;

    out << string(120, '-') << endl;

    for (int i = 0; i < n; i++) {
        if (pasirinktaKategorija != "" &&
            kategorijos[i] != pasirinktaKategorija) {
            continue;
        }

        double suma = eilutesSuma(kainos[i], kiekiai[i]);
        double nuolaidosSuma = nuolaida(suma, kiekiai[i]);
        double moketi = suma - nuolaidosSuma;

        out << left
            << setw(16) << kategorijos[i]
            << setw(25) << pavadinimai[i]
            << right
            << fixed << setprecision(2)
            << setw(20) << kainos[i]
            << setw(10) << kiekiai[i]
            << setw(12) << suma
            << setw(12) << nuolaidosSuma
            << setw(15) << moketi
            << endl;
    }

    out << string(120, '-') << endl;
}

// ------------------------------------------
// Spausdina bendras užsakymo sumas
// ------------------------------------------
void rodytiSumas(
    ostream &out,
    double kainos[],
    int kiekiai[],
    int n
) {
    double suma = visoSuma(kainos, kiekiai, n);
    double nuolaidosSuma = visoNuolaida(kainos, kiekiai, n);
    double moketi = suma - nuolaidosSuma;

    out << fixed << setprecision(2);

    out << "Bendra uzsakymo suma: "
        << suma << " EUR" << endl;

    out << "Bendra nuolaida: "
        << nuolaidosSuma << " EUR" << endl;

    out << "Galutine moketina suma: "
        << moketi << " EUR" << endl;
}

// ------------------------------------------
// Spausdina kategorijų sumas
// ------------------------------------------
void rodytiKategorijas(
    ostream &out,
    string kategorijos[],
    double kainos[],
    int kiekiai[],
    int n
) {
    string kategorijuPavadinimai[3] = {
        "Dviraciai",
        "Dalys",
        "Aksesuarai"
    };

    out << fixed << setprecision(2);

    out << "\nKATEGORIJU SUMOS" << endl;
    out << string(40, '-') << endl;

    for (int i = 0; i < 3; i++) {
        double suma = kategorijosSuma(
            kategorijuPavadinimai[i],
            kategorijos,
            kainos,
            kiekiai,
            n
        );

        out << left
            << setw(20) << kategorijuPavadinimai[i]
            << right
            << setw(12) << suma
            << " EUR" << endl;
    }

    out << string(40, '-') << endl;
}

// ------------------------------------------
// Spausdina visą ataskaitą
// ------------------------------------------
void ataskaita(
    ostream &out,
    string kategorijos[],
    string pavadinimai[],
    double kainos[],
    int kiekiai[],
    int n
) {
    out << "\nDVIRACIU PARDUOTUVES UZSAKYMO ATASKAITA"
        << endl;

    out << string(120, '=') << endl;

    spausdintiPrekes(
        out,
        kategorijos,
        pavadinimai,
        kainos,
        kiekiai,
        n
    );

    rodytiSumas(out, kainos, kiekiai, n);

    rodytiKategorijas(
        out,
        kategorijos,
        kainos,
        kiekiai,
        n
    );
}

// ------------------------------------------
// Leidžia pasirinkti kategoriją
// ------------------------------------------
string pasirinktiKategorija() {
    int pasirinkimas;

    while (true) {
        cout << "\nPasirinkite kategorija:" << endl;
        cout << "1. Dviraciai" << endl;
        cout << "2. Dalys" << endl;
        cout << "3. Aksesuarai" << endl;
        cout << "Jusu pasirinkimas: ";

        if (cin >> pasirinkimas) {
            if (pasirinkimas >= 1 && pasirinkimas <= 3) {
                break;
            }
        }

        cout << "Netinkamas pasirinkimas!" << endl;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (pasirinkimas == 1) {
        return "Dviraciai";
    }

    if (pasirinkimas == 2) {
        return "Dalys";
    }

    return "Aksesuarai";
}

// ------------------------------------------
// Pagrindinė programa
// ------------------------------------------
int main() {
    string kategorijos[MAX_PREKIU];
    string pavadinimai[MAX_PREKIU];
    double kainos[MAX_PREKIU];
    int kiekiai[MAX_PREKIU];

    int n;

    // Nuskaitome duomenis
    if (!nuskaitytiDuomenis(
        "duom.txt",
        kategorijos,
        pavadinimai,
        kainos,
        kiekiai,
        n
    )) {
        cout << "Programa baigiama del netinkamu duomenu."
             << endl;
        return 1;
    }

    cout << "Duomenys sekmingai nuskaityti!" << endl;
    cout << "Prekiu skaicius: " << n << endl;

    int pasirinkimas;

    do {
        cout << "\n========== MENIU ==========" << endl;
        cout << "1. Rodyti visas prekes" << endl;
        cout << "2. Rodyti pasirinkta kategorija" << endl;
        cout << "3. Rodyti kategoriju sumas" << endl;
        cout << "4. Rodyti uzsakymo sumas" << endl;
        cout << "5. Rodyti visa ataskaita" << endl;
        cout << "6. Issaugoti ataskaita i faila" << endl;
        cout << "7. Baigti programa" << endl;
        cout << "Pasirinkite: ";

        if (!(cin >> pasirinkimas)) {
            cout << "Iveskite skaiciu!" << endl;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            pasirinkimas = 0;
            continue;
        }

        switch (pasirinkimas) {
            case 1:
                cout << "\nVISOS PREKES" << endl;

                spausdintiPrekes(
                    cout,
                    kategorijos,
                    pavadinimai,
                    kainos,
                    kiekiai,
                    n
                );
                break;

            case 2: {
                string kategorija = pasirinktiKategorija();

                cout << "\nKATEGORIJA: "
                     << kategorija << endl;

                spausdintiPrekes(
                    cout,
                    kategorijos,
                    pavadinimai,
                    kainos,
                    kiekiai,
                    n,
                    kategorija
                );

                cout << fixed << setprecision(2);

                cout << "Kategorijos moketina suma: "
                     << kategorijosSuma(
                         kategorija,
                         kategorijos,
                         kainos,
                         kiekiai,
                         n
                     )
                     << " EUR" << endl;

                break;
            }

            case 3:
                rodytiKategorijas(
                    cout,
                    kategorijos,
                    kainos,
                    kiekiai,
                    n
                );
                break;

            case 4:
                rodytiSumas(cout, kainos, kiekiai, n);
                break;

            case 5:
                ataskaita(
                    cout,
                    kategorijos,
                    pavadinimai,
                    kainos,
                    kiekiai,
                    n
                );
                break;

            case 6: {
                ofstream ataskaitosFailas("ataskaita.txt");

                if (!ataskaitosFailas.is_open()) {
                    cout << "Nepavyko sukurti ataskaitos failo!"
                         << endl;
                    break;
                }

                ataskaita(
                    ataskaitosFailas,
                    kategorijos,
                    pavadinimai,
                    kainos,
                    kiekiai,
                    n
                );

                ataskaitosFailas.close();

                if (ataskaitosFailas.fail()) {
                    cout << "Nepavyko issaugoti ataskaitos!"
                         << endl;
                } else {
                    cout << "Ataskaita issaugota faile "
                         << "ataskaita.txt" << endl;
                }

                break;
            }

            case 7:
                cout << "Programa baigiama." << endl;
                break;

            default:
                cout << "Tokio pasirinkimo nera!" << endl;
        }

    } while (pasirinkimas != 7);

    return 0;
}
