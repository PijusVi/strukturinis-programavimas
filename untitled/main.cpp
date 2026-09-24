#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    //
    //     int number;
    //
    //     cout << "Iveskite teigiama skaiciu "<<endl;
    //     cin >> number;
    //
    //     while (number <=0) {
    //         cout <<"Klaida. Skaicius yra netinkamas"<<endl;
    //         cout << "Iveskite teigiama skaiciu "<<endl;
    //     }
    //     cout << "Ivesstas skaicius yra: "<<number<<endl;
    //     return 0;
    // }

    // 2 pavyzdys. Taupymas iki pasirinkto tikslo

//     double savings = 100.0;
//     const double target = 500.0;
//     const double monthlyDeposit = 75.0;
//     int month = 0;
//
//     while (savings < target) {
//         month++;
//         savings += monthlyDeposit;
//         cout << month << " menuo "
//             <<fixed<<setprecision(2)
//             <<savings<<"EUR"<<endl;
//     }
//     cout <<"Tikslas yra pasiektas per "<<month<<" menesius"<<endl;
//

    // 3 pavyzdys. Slaptazodzio kurimas

    string password;

    do {
        cout << "Iveskite bent 8 simboliu slaptazodi: ";
        cin >> password;

        if (password.length() < 8) {
            cout << "Slaptazodis turi buti maziausiai 8 simboliu."<<endl;
        }

    } while (password.length() < 8);

    cout << "Slaptazodis priimtas"<<endl;


     return 0;
}

