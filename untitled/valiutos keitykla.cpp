#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main() {
    // Užduotyje nurodytos valiutų kursų konstantos
    const double GBP_Bendras   = 0.8729;
    const double GBP_Pirkti    = 0.8600;
    const double GBP_Parduoti  = 0.9220;

    const double USD_Bendras   = 1.1793;
    const double USD_Pirkti    = 1.1460;
    const double USD_Parduoti  = 1.2340;

    const double INR_Bendras   = 104.6918;
    const double INR_Pirkti    = 101.3862;
    const double INR_Parduoti  = 107.8546;

    int veiksmas = 0;

    // Nustatome išvesties formatą: fiksuotas taškas ir 2 skaitmenys po kablelio
    cout << fixed << setprecision(2);

    do {
        cout << "         VALIUTOS KEITYKLA (EUR)        \n";
        cout << "1. Valiutos kurso palyginimas su EUR\n";
        cout << "2. Pirkti valiuta (EUR -> Valiuta)\n";
        cout << "3. Parduoti valiuta (Valiuta -> EUR)\n";
        cout << "4. Iseiti\n";
        cout << "Pasirinkite veiksma (1-4): ";
        cin >> veiksmas;

        if (veiksmas == 4) {
            cout << "\nAciu, kad naudojates programa. Viso gero!\n";
            break;
        }

        if (veiksmas < 1 || veiksmas > 4) {
            cout << "\nKLAIDA: Neteisingas veiksmo pasirinkimas! Bandykite dar karta.\n";
            continue;
        }

        // Valiutos pasirinkimas
        cout << "\nPasirinkite valiuta:\n";
        cout << "1 – GBP (Didziosios Britanijos svaras)\n";
        cout << "2 – USD (JAV doleris)\n";
        cout << "3 – INR (Indijos rupija)\n";
        cout << "Pasirinkimas (1-3): ";
        int valiutaPasirinkimas;
        cin >> valiutaPasirinkimas;

        if (valiutaPasirinkimas < 1 || valiutaPasirinkimas > 3) {
            cout << "\nKLAIDA: Neteisingas valiutos pasirinkimas! Bandykite dar karta.\n";
            continue;
        }

        string valiutosKodas = "";
        double bendrasKursas = 0.0;
        double pirkimoKursas = 0.0;
        double pardavimoKursas = 0.0;

        switch (valiutaPasirinkimas) {
            case 1:
                valiutosKodas = "GBP";
                bendrasKursas = GBP_Bendras;
                pirkimoKursas = GBP_Pirkti;
                pardavimoKursas = GBP_Parduoti;
                break;
            case 2:
                valiutosKodas = "USD";
                bendrasKursas = USD_Bendras;
                pirkimoKursas = USD_Pirkti;
                pardavimoKursas = USD_Parduoti;
                break;
            case 3:
                valiutosKodas = "INR";
                bendrasKursas = INR_Bendras;
                pirkimoKursas = INR_Pirkti;
                pardavimoKursas = INR_Parduoti;
                break;
        }

        // Veiksmu apdorojimas
        if (veiksmas == 1) {
            // 1. Valiutos kurso palyginimas (rodomos abi kryptys)
            cout << "\n----------------------------------------\n";
            cout << "VALIUTOS KURSO PALYGINIMAS:\n";
            cout << "1 EUR = " << bendrasKursas << " " << valiutosKodas << "\n";
            cout << "1 " << valiutosKodas << " = " << (1.0 / bendrasKursas) << " EUR\n";
            cout << "----------------------------------------\n";
        }
        else if (veiksmas == 2 || veiksmas == 3) {
            double suma = 0.0;

            if (veiksmas == 2) {
                cout << "Iveskite sumi eurais (EUR), kuria norite konvertuoti: ";
            } else {
                cout << "Iveskite sumi " << valiutosKodas << ", kuria norite parduoti: ";
            }
            cin >> suma;

            if (suma <= 0) {
                cout << "\nKLAIDA: Suma turi buti teigiamas skaicius!\n";
                continue;
            }

            if (veiksmas == 2) {
                // Pirkimas: EUR -> Pasirinkta valiuta
                double gautaSuma = suma * pirkimoKursas;
                cout << "\n----------------------------------------\n";
                cout << "PIRKIMO REZULTATAS:\n";
                cout << "Pradine suma: " << suma << " EUR\n";
                cout << "Pirkimo kursas: " << pirkimoKursas << "\n";
                cout << "Gauta suma: " << gautaSuma << " " << valiutosKodas << "\n";
                cout << "----------------------------------------\n";
            }
            else if (veiksmas == 3) {
                // Pardavimas: Pasirinkta valiuta -> EUR
                double gautaSuma = suma / pardavimoKursas;
                cout << "\n----------------------------------------\n";
                cout << "PARDAVIMO REZULTATAS:\n";
                cout << "Pradine suma: " << suma << " " << valiutosKodas << "\n";
                cout << "Pardavimo kursas: " << pardavimoKursas << "\n";
                cout << "Gauta suma: " << gautaSuma << " EUR\n";
                cout << "----------------------------------------\n";
            }
        }

    } while (veiksmas != 4);

    return 0;
}