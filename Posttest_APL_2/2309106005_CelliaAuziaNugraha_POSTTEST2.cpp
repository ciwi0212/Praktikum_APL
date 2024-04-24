#include <iostream>
using namespace std;

#define max 10

struct Pengguna {
    string username;
    string password;
};

Pengguna pengguna[max];
char ulang = 'y';
int jmlh = 0;

void display() {
    system("cls");
    if (jmlh > 0) {
        cout << "Data Tersimpan" << endl;
        for (int a = 0; a < jmlh; a++) {
            cout << a + 1 << ". Username: " << pengguna[a].username << ", Password: " << pengguna[a].password << endl;
        }
    } else {
        cout << "<-- Data Kosong -->" << endl;
    }
}

void add() {
    do {
        display();
        if (jmlh < max) {
            cin.ignore();
            cout << "Masukkan Username: ";
            getline(cin, pengguna[jmlh].username);
            cout << "Masukkan Password: ";
            getline(cin, pengguna[jmlh].password);
            jmlh++;
            display();
            cout << "ulang? (y/t): ";
            cin >> ulang;
        } else {
            cout << "Maaf, Penyimpanan Penuh. Silahkan Hapus Salah Satu Data Untuk Menambah." << endl;
            cout << "isi t untuk kembali: ";
            cin >> ulang;
        }
    } while (ulang == 'y');
}

void update() {
    int y;
    do {
        display();
        cout << "Ubah data ke-";
        cin >> y;
        cin.ignore();
        cout << "Masukkan Username Baru: ";
        getline(cin, pengguna[y - 1].username);
        cout << "Masukkan Password Baru: ";
        getline(cin, pengguna[y - 1].password);
        display();
        cout << "Ubah lagi? (y/t)";
        cin >> ulang;
    } while (ulang == 'y');
}

void del() {
    int x;
    do {
        display();
        if (jmlh > 0) {
            cout << "Hapus Data Ke-";
            cin >> x;
            for (int i = x; i < jmlh; i++) {
                pengguna[i - 1] = pengguna[i];
            }
            jmlh--;
            display();
            cout << "Hapus Lagi? (y/t): ";
            cin >> ulang;
        } else {
            cout << "ketik t: ";
            cin >> ulang;
        }
    } while (ulang == 'y');
}

int main() {
    string user, pass;
    int i;
    int login = 0;
    i = 1;
    do {
        cout << "Masukkan Username: "; cin >> user;
        cout << "Masukkan Password: "; cin >> pass;
        if (user == "cellia" && pass == "2309106005") {
            i = 4;
            login = 1;
        } else {
            cout << "Username atau Password salah!" << endl;
            i = i + 1;
        }
    } while (i < 4);

    if (login != 1) {
        cout << "Maaf Anda Telah Mencapai Batas Maksimum Percobaan" << endl;
        return 0;
    }

    int pil;
    do {
        system("cls");
        cout << "1. Tambah Pengguna\n2. Ubah Data Pengguna\n3. Hapus Data Pengguna\n4. Tampilkan Data Pengguna\n5. Keluar Program" << endl;
        cout << "Pilihan: ";
        cin >> pil;
        switch (pil) {
        case 1:
            add();
            break;
        case 2:
            update();
            break;
        case 3:
            del();
            break;
        case 4:
            do {
                display();
                cout << "Kembali (y): ";
                cin >> ulang;
            } while (ulang != 'y');

            break;
        case 5:
            cout << ". . ." << endl;
            break;
        default:
            cout << "Pilih 1-5" << endl;
            break;
        }
    } while (pil != 5);
    cout << "Program Selesai ...";
    return 0;
}
