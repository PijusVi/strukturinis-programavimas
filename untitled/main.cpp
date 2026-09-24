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

    // string password;
    //
    // do {
    //     cout << "Iveskite bent 8 simboliu slaptazodi: ";
    //     cin >> password;
    //
    //     if (password.length() < 8) {
    //         cout << "Slaptazodis turi buti maziausiai 8 simboliu."<<endl;
    //     }
    //
    // } while (password.length() < 8);
    //
    // cout << "Slaptazodis priimtas"<<endl;


    //4 Pavyzdys. Saskaitos valdymo meniu

    // int balance = 100;
    // int choice;
    //
    // do {
    //     cout<< "\n--- SASKAITOS MENIU --- \n";
    //     cout<<"1. Perziureti saskaitos likuti\n";
    //     cout<<"2. Papildyti saskaita\n";
    //     cout<<"3. Atlikti mokejima\n";
    //     cout<<"0. Baigti programa\n";
    //     cout<<"Pasirnkite funkcija\n";
    //     cin>>choice;
    //
    //     switch (choice) {
    //         case 1:
    //             cout << "Saskaitos likutis: " << balance << "Eur \n";
    //             break;
    //         case 2: {
    //             int amount;
    //             cout << "Papildymo suma: ";
    //             cin >> amount;
    //
    //             if (amount > 0) {
    //                 balance += amount;
    //                 cout << "Saskaita yra papildyta. \n";
    //             } else {
    //                 cout<< "Netinkama suma";
    //             }
    //             break;
    //         }
    //         case 3: {
    //             int amount;
    //             cout << "Mokejimo suma: ";
    //             cin >> amount;
    //
    //             if (amount <= 0) {
    //                 cout << "Netinkama suma";
    //             } else if (amount > balance) {
    //                 cout << "Nepakankamas likutis saskaitoje. \n";
    //             } else {
    //                 balance -= amount;
    //                 cout << "Mokejimas atliktas";
    //             }
    //         }
    //         case 0:
    //             cout<<"Programa baige darba \n";
    //             break;
    //         default:
    //             cout <<"Tokios operacijos nera \n";
    //     }
    // } while (choice != 0);

    //5 pavyzdys Studento pazymiu statistika

    const int studentGradesNum = 5;
    int grade;
    int sum = 0;
    int highestGrade = 0;
    for (int i = 1; i <= studentGradesNum; i++) {
        cout<<"Iveskite "<<i<<" studento pazymi: "<<endl;
        cin>>grade;
        sum += grade;
        highestGrade = (grade > highestGrade) ? grade : highestGrade;
    }

    double averageGrade = static_cast<double>(sum) / studentGradesNum;
    cout<<fixed<<setprecision(2)<<"Pazymiu vidurkis"<<averageGrade<<endl;
    cout<<"Didziausias pazymys"<<highestGrade<<endl;
     return 0;
}

