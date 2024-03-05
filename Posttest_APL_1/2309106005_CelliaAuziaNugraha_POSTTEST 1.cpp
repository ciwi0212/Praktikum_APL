#include<iostream>
using namespace std;

//form login
int main() {
    string user, pass;
    int i;
    int login = 0;
    i = 1;
    do {
        cout << "Masukkan Username: "; cin >> user;
        cout << "Masukkan Password: "; cin >> pass;
        if (user == "cellia" && pass == "2309106005") {
            cout << "Anda Berhasil Login!" << endl;
            i = 4;
            login = 1;
        }
        else {
            cout << "Username atau Password salah!" << endl;
            i = i + 1;
        }
    } while (i < 4);

    if (login != 1) {
        cout << "Maaf Anda Telah Mencapai Batas Maksimum Percobaan" << endl;
        return 0;
    }

    int pilih;
    float rupiah, dollar, euro, yen;
    double amount;

    do {
        cout << "Menu Konversi Mata Uang" << endl;
        cout << "1. Rupiah ke (Dollar, Euro, Yen)" << endl;
        cout << "2. Dollar ke (Rupiah, Euro, Yen)" << endl;
        cout << "3. Euro ke (Rupiah, Dollar, Yen)" << endl;
        cout << "4. Yen ke (Rupiah, Dollar, Euro)" << endl;
        cout << "5. Keluar Program" << endl;
        cout << "Pilih Menu: ";
        cin >> pilih;
        switch (pilih) {
        case 1:
            cout << "Masukkan nominal Rupiah: "; cin >> rupiah;
            dollar = rupiah / 15695;
            euro = rupiah / 17008;
            yen = rupiah / 104;
            cout << "Konversi Rupiah ke Dollar: " << dollar << " | Ke Euro: " << euro << " | Ke Yen: " << yen << endl;
            break;

        case 2:
            cout << "Masukkan nominal Dollar: "; cin >> dollar;
            rupiah = dollar * 15695;
            euro = dollar * 0.92;
            yen = dollar * 150.11;
            cout << "Konversi Dollar ke Rupiah: " << rupiah << " | Ke Euro: " << euro << " | Ke Yen: " << yen << endl;
            break;

        case 3:
            cout << "Masukkan nominal Euro: "; cin >> euro;
            rupiah = euro * 17008;
            dollar = euro * 1.08;
            yen = euro * 162.67;
            cout << "Konversi Euro ke Rupiah: " << rupiah << " | Ke Dollar: " << dollar << " | Ke Yen: " << yen << endl;
            break;

        case 4:
            cout << "Masukkan nominal Yen: "; cin >> yen;
            rupiah = yen * 104.54;
            dollar = yen * 0.0067;
            euro = yen * 0.0061;
            cout << "Konversi Yen ke Rupiah: " << rupiah << " | Ke Dollar: " << dollar << " | Ke Euro: " << euro << endl;
            break;

        case 5:
            cout << "Anda Telah Keluar Dari Program" << endl;
            break;
        default:
            cout << "Menu Yang Anda Pilih Tidak Tersedia" << endl;

        }

        cout << "Apakah anda ingin mengulang program? (1: ya, 0: tidak)";
        cin >> pilih;
    } while (pilih == 1);

    return 0;
}




  