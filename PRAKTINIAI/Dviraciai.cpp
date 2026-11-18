
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

const int MAX = 100;

// Funkciju deklaracijos
bool nuskaitytiDuomenis(string failas, string kat[],
    string pav[], double kainos[], int kiekiai[], int &n);

double eilutesSuma(double kaina, int kiekis);
double nuolaida(double kaina, int kiekis);
double moketinaSuma(double kaina, int kiekis);

double kategorijosSuma(string kategorija, string kat[],
    double kainos[], int kiekiai[], int n);

double visoSuma(double kainos[], int kiekiai[], int n);
double visoNuolaida(double kainos[], int kiekiai[], int n);

void spausdintiPrekes(ostream &out, string kat[], string pav[],
    double kainos[], int kiekiai[], int n, string pasirinkta = "");

void rodytiSumas(double kainos[], int kiekiai[], int n);

void rodytiKategorijas(string kat[], double kainos[],
    int kiekiai[], int n);

void ataskaita(ostream &out, string kat[], string pav[],
    double kainos[], int kiekiai[], int n);

string pasirinktiKategorija();


// PAGRINDINE FUNKCIJA
int main()
{
    string kategorijos[MAX];
    string pavadinimai[MAX];
    double kainos[MAX];
    int kiekiai[MAX];

    int n = 0;

    // Nuskaitome duomenis
    if (!nuskaitytiDuomenis(    "C:/Users/Kazkas/CLionProjects/PRAKTINIAI/duom.txt", kategorijos,
        pavadinimai, kainos, kiekiai, n))
    {
        cout << "Nepavyko nuskaityti duomenu!\n";
        return 1;
    }

    cout << "Duomenys nuskaityti sekmingai!\n";

    int pasirinkimas = 0;

    do
    {
        cout << "\n========== MENIU ==========\n";
        cout << "1. Perziureti visas prekes\n";
        cout << "2. Perziureti pasirinktos kategorijos prekes\n";
        cout << "3. Perziureti viso uzsakymo sumas\n";
        cout << "4. Perziureti sumas pagal kategorijas\n";
        cout << "5. Parodyti visa ataskaita\n";
        cout << "6. Issaugoti ataskaita i faila\n";
        cout << "7. Iseiti\n";
        cout << "Pasirinkite: ";

        if (!(cin >> pasirinkimas))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Neteisingas pasirinkimas!\n";
            continue;
        }

        switch (pasirinkimas)
        {
            case 1:
                spausdintiPrekes(cout, kategorijos, pavadinimai,
                    kainos, kiekiai, n);
                break;

            case 2:
            {
                string kat = pasirinktiKategorija();

                spausdintiPrekes(cout, kategorijos, pavadinimai,
                    kainos, kiekiai, n, kat);

                cout << "\nKategorijos moketina suma: "
                     << fixed << setprecision(2)
                     << kategorijosSuma(kat, kategorijos,
                        kainos, kiekiai, n) << " Eur\n";
                break;
            }

            case 3:
                rodytiSumas(kainos, kiekiai, n);
                break;

            case 4:
                rodytiKategorijas(kategorijos, kainos,
                    kiekiai, n);
                break;

            case 5:
                ataskaita(cout, kategorijos, pavadinimai,
                    kainos, kiekiai, n);
                break;

            case 6:
            {
                ofstream out("ataskaita.txt");

                if (!out)
                {
                    cout << "Nepavyko sukurti ataskaitos failo!\n";
                }
                else
                {
                    ataskaita(out, kategorijos, pavadinimai,
                        kainos, kiekiai, n);

                    out.close();

                    if (out.fail())
                        cout << "Klaida issaugant ataskaita!\n";
                    else
                        cout << "Ataskaita issaugota sekmingai!\n";
                }
                break;
            }

            case 7:
                cout << "Programa baigiama.\n";
                break;

            default:
                cout << "Tokio pasirinkimo nera!\n";
        }

    } while (pasirinkimas != 7);

    return 0;
}


// DUOMENU NUSKAITYMAS
bool nuskaitytiDuomenis(string failas, string kat[],
    string pav[], double kainos[], int kiekiai[], int &n)
{
    ifstream in(failas);

    if (!in)
    {
        cout << "Nepavyko atidaryti duomenu failo!\n";
        return false;
    }

    if (!(in >> n))
    {
        cout << "Nepavyko nuskaityti irasu skaiciaus!\n";
        return false;
    }

    in.ignore(10000, '\n');

    if (n < 1 || n > MAX)
    {
        cout << "Netinkamas irasu skaicius!\n";
        return false;
    }

    string eilute;

    for (int i = 0; i < n; i++)
    {
        if (!getline(in, eilute))
        {
            cout << "Truksta duomenu eiluciu!\n";
            return false;
        }

        stringstream ss(eilute);

        string kainaTekstas;
        string kiekisTekstas;
        string papildomas;

        if (!getline(ss, kat[i], ';') ||
            !getline(ss, pav[i], ';') ||
            !getline(ss, kainaTekstas, ';') ||
            !getline(ss, kiekisTekstas, ';'))
        {
            cout << "Netinkamas duomenu formatas!\n";
            return false;
        }

        if (getline(ss, papildomas))
        {
            cout << "Per daug duomenu eiluteje!\n";
            return false;
        }

        if (kat[i] != "Dviraciai" &&
            kat[i] != "Dalys" &&
            kat[i] != "Aksesuarai")
        {
            cout << "Netinkama kategorija!\n";
            return false;
        }

        if (pav[i] == "")
        {
            cout << "Nera prekes pavadinimo!\n";
            return false;
        }

        stringstream kainaSrautas(kainaTekstas);

        if (!(kainaSrautas >> kainos[i]) ||
            kainos[i] <= 0 ||
            (kainaSrautas >> papildomas))
        {
            cout << "Netinkama prekes kaina!\n";
            return false;
        }

        stringstream kiekisSrautas(kiekisTekstas);

        if (!(kiekisSrautas >> kiekiai[i]) ||
            kiekiai[i] <= 0 ||
            (kiekisSrautas >> papildomas))
        {
            cout << "Netinkamas prekes kiekis!\n";
            return false;
        }
    }

    in.close();

    return true;
}


// PREKES SUMA
double eilutesSuma(double kaina, int kiekis)
{
    return kaina * kiekis;
}


// NUOLAIDOS SUMA
double nuolaida(double kaina, int kiekis)
{
    if (kiekis >= 10)
        return eilutesSuma(kaina, kiekis) * 0.10;

    return 0;
}


// MOKETINA SUMA
double moketinaSuma(double kaina, int kiekis)
{
    return eilutesSuma(kaina, kiekis) -
           nuolaida(kaina, kiekis);
}


// KATEGORIJOS SUMA
double kategorijosSuma(string kategorija, string kat[],
    double kainos[], int kiekiai[], int n)
{
    double suma = 0;

    for (int i = 0; i < n; i++)
    {
        if (kat[i] == kategorija)
        {
            suma += moketinaSuma(kainos[i], kiekiai[i]);
        }
    }

    return suma;
}


// VISO UZSAKYMO SUMA
double visoSuma(double kainos[], int kiekiai[], int n)
{
    double suma = 0;

    for (int i = 0; i < n; i++)
    {
        suma += eilutesSuma(kainos[i], kiekiai[i]);
    }

    return suma;
}


// VISO UZSAKYMO NUOLAIDA
double visoNuolaida(double kainos[], int kiekiai[], int n)
{
    double suma = 0;

    for (int i = 0; i < n; i++)
    {
        suma += nuolaida(kainos[i], kiekiai[i]);
    }

    return suma;
}


// PREKIU ATVAIZDAVIMAS
void spausdintiPrekes(ostream &out, string kat[], string pav[],
    double kainos[], int kiekiai[], int n, string pasirinkta)
{
    out << fixed << setprecision(2);

    out << "\n";
    out << left << setw(15) << "Kategorija"
        << setw(40) << "Preke"
        << right << setw(10) << "Kaina"
        << setw(8) << "Kiekis"
        << setw(12) << "Suma"
        << setw(12) << "Nuolaida"
        << setw(12) << "Moketina" << "\n";

    out << string(109, '-') << "\n";

    int rasta = 0;

    for (int i = 0; i < n; i++)
    {
        if (pasirinkta == "" || kat[i] == pasirinkta)
        {
            out << left << setw(15) << kat[i]
                << setw(40) << pav[i]
                << right << setw(10) << kainos[i]
                << setw(8) << kiekiai[i]
                << setw(12) << eilutesSuma(kainos[i], kiekiai[i])
                << setw(12) << nuolaida(kainos[i], kiekiai[i])
                << setw(12) << moketinaSuma(kainos[i], kiekiai[i])
                << "\n";

            rasta++;
        }
    }

    if (rasta == 0)
        out << "Prekiu sioje kategorijoje nera.\n";

    out << string(109, '-') << "\n";
}


// VISO UZSAKYMO SUMOS
void rodytiSumas(double kainos[], int kiekiai[], int n)
{
    double suma = visoSuma(kainos, kiekiai, n);
    double nuol = visoNuolaida(kainos, kiekiai, n);

    cout << fixed << setprecision(2);

    cout << "\nSuma pries nuolaidas: " << suma << " Eur\n";
    cout << "Bendra nuolaida: " << nuol << " Eur\n";
    cout << "Galutine suma: " << suma - nuol << " Eur\n";
}


// KATEGORIJU SUMOS
void rodytiKategorijas(string kat[], double kainos[],
    int kiekiai[], int n)
{
    cout << fixed << setprecision(2);

    cout << "\nDviraciai: "
         << kategorijosSuma("Dviraciai", kat, kainos, kiekiai, n)
         << " Eur\n";

    cout << "Dalys: "
         << kategorijosSuma("Dalys", kat, kainos, kiekiai, n)
         << " Eur\n";

    cout << "Aksesuarai: "
         << kategorijosSuma("Aksesuarai", kat, kainos, kiekiai, n)
         << " Eur\n";
}


// VISA ATASKAITA
void ataskaita(ostream &out, string kat[], string pav[],
    double kainos[], int kiekiai[], int n)
{
    double suma = visoSuma(kainos, kiekiai, n);
    double nuol = visoNuolaida(kainos, kiekiai, n);

    out << fixed << setprecision(2);

    out << "\n========== UZSAKYMO ATASKAITA ==========\n";

    spausdintiPrekes(out, kat, pav, kainos, kiekiai, n);

    out << "\nSuma pries nuolaidas: " << suma << " Eur\n";
    out << "Bendra nuolaida: " << nuol << " Eur\n";
    out << "Galutine moketina suma: " << suma - nuol << " Eur\n";

    out << "\nSUMOS PAGAL KATEGORIJAS:\n";

    out << "Dviraciai: "
        << kategorijosSuma("Dviraciai", kat, kainos, kiekiai, n)
        << " Eur\n";

    out << "Dalys: "
        << kategorijosSuma("Dalys", kat, kainos, kiekiai, n)
        << " Eur\n";

    out << "Aksesuarai: "
        << kategorijosSuma("Aksesuarai", kat, kainos, kiekiai, n)
        << " Eur\n";
}


// KATEGORIJOS PASIRINKIMAS
string pasirinktiKategorija()
{
    int pasirinkimas;

    do
    {
        cout << "\nPasirinkite kategorija:\n";
        cout << "1. Dviraciai\n";
        cout << "2. Dalys\n";
        cout << "3. Aksesuarai\n";
        cout << "Jusu pasirinkimas: ";

        if (!(cin >> pasirinkimas))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Neteisingas pasirinkimas!\n";
            continue;
        }

        if (pasirinkimas == 1)
            return "Dviraciai";

        if (pasirinkimas == 2)
            return "Dalys";

        if (pasirinkimas == 3)
            return "Aksesuarai";

        cout << "Tokios kategorijos nera!\n";

    } while (true);
}
