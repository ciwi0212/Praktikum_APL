#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm> 
#include <vector> 
#include <cstdlib>
#include <limits>
using namespace std;

const int penyimpanan_max = 100;
const int riwayatpembelian_max = 100;

struct Merchandise {
    string nomorProduk;
    string film;
    string jenis;
    int stock;
    double harga;
};

struct RiwayatPembelian {
    string namaPelanggan;
    string judul_film;
    string tipe_produk;
    int jumlah;
    double total_biaya;
};

// Deklarasi fungsi-fungsi yang akan digunakan
// void clear(){
//     system("cls");
// }


void riwayat_pembelian();
void menu_masuk();
void login();
void registrasi();
void lupa();
void menu_admin();
void menu_pembeli();
void tampilkan_produk(const Merchandise* memori, int total_memori);
void tambah_produk(Merchandise* memori, int& total_memori);
void update_produk(Merchandise* memori, int total_memori);
void hapus_produk(Merchandise* memori, int& total_memori);
void tambah_riwayat_pembelian(const string& nama, const string& film, const string& jenis, int jumlah, double total);
void tambah_belanjaan(Merchandise* memori, int& total_memori, Merchandise* keranjang, int& total_keranjang);


void menu_masuk() {
    int pilihan;
    do {
        system("cls");
        cout << "============================================" << endl;
        cout << "               MENU AKUN " << endl;
        cout << "============================================" << endl;
        cout << "1. Registrasi" << endl;
        cout << "2. Login" << endl;
        cout << "3. Lupa Username atau Password" << endl;
        cout << "4. Keluar" << endl;
        cout << "Masukkan pilihan anda: ";
        cin >> pilihan;

         if (cin.fail()) {
            cin.clear(); // Menghapus flag error dari cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Menghapus karakter dari buffer
            pilihan = -1; // Menetapkan pilihan ke nilai yang tidak valid
            cout << "\033[1;31mPilihan tidak valid, coba lagi.\033[0m" << endl;
            system("pause");
        }

        cout << endl;

        switch (pilihan) {
            case 1:
                registrasi();
                break;
            case 2:
                login();
                break;
            case 3:
                lupa();
                break;
            case 4:
                system("cls");
                cout << "Terima kasih sampai jumpa lagi...";
                exit(0);
            default:
                cout << "\033[1;31mPilihan tidak valid, coba lagi.\033[0m" << endl;
                system("pause");
        }
    } while (pilihan != 4);
}


void login() {
    int count = 0;
    string user, pass, username, password;
    int attempts = 0; // Menyimpan jumlah percobaan login yang gagal

    while (attempts < 3) {
        system("cls");
        cout << "============================================" << endl;
        cout << "               LOGIN" << endl;
        cout << "============================================" << endl;
        cout << "Username: ";
        cin >> user;
        cout << "Password: ";
        cin >> pass;

        if (user == "admin" && pass == "admin") {
            cout << "\033[1;32mHalo Admin\nLOGIN BERHASIL\n\033[0m";
            system("pause");
            menu_admin();
            return;
        }

        ifstream input("akun.txt");
        bool found = false;
        while (input >> username >> password) {
            if (username == user && password == pass) {
                count = 1;
                cout << "\033[1;32mHalo\nLOGIN BERHASIL\n\033[0m";
                system("pause");
                menu_pembeli();
                return;
            }
        }
        input.close();
        
        if (count == 0) {
            attempts++;
            cout << "\n\033[1;31m=============================\n\033[0m";
            cout << "\033[1;31mUsername / Password Salah!!! (" << attempts << "x)\n\033[0m";
            cout << "\033[1;31m=============================\n\n\033[0m";
            if (attempts < 3) {
                cout << "Anda memiliki " << 3 - attempts << " percobaan tersisa." << endl;
                system("pause");
            } else {
                cout << "\033[1;31mAnda telah 3x salah login.\n\033[0m";
                cout << "Silahkan coba setelah 24 jam dari sekarang. Terima Kasih..\n\n";
                exit(0); // Menghentikan program setelah 3 kali percobaan gagal
            }
        }
    }
}

bool isStrongPassword(const string& password) {
    bool hasLowerCase = false, hasUpperCase = false, hasDigit = false, hasSpecialChar = false;
    for (char ch : password) {
        if (islower(ch)) hasLowerCase = true;
        else if (isupper(ch)) hasUpperCase = true;
        else if (isdigit(ch)) hasDigit = true;
        else if (ispunct(ch)) hasSpecialChar = true;
    }
    return password.length() >= 8 && hasLowerCase && hasUpperCase && hasDigit && hasSpecialChar;
}


void registrasi() {
    string regisuser, regispass;
    bool validUsername = false;
    system("cls");
    cout << "============================================" << endl;
    cout << "               REGISTRASI" << endl;
    cout << "============================================" << endl;
    
while (!validUsername) {
        cout << "Ketik username anda: ";
        cin >> regisuser;

        if (regisuser == "admin") {
            cout << "\033[1;31mUsername 'admin' tidak diizinkan. Silakan pilih username lain.\033[0m" << endl;
        } else {
            validUsername = true;
        }
    }

    while (true) {
        cout << "\033[1;33mKetik password anda (minimal 8 karakter, mengandung huruf besar, huruf kecil, angka, dan karakter khusus): \033[0m";
        cin >> regispass;

        if (isStrongPassword(regispass)) {
            break; // Jika password kuat, keluar dari loop
        } else {
            cout << "Password tidak memenuhi persyaratan keamanan. Silakan coba lagi." << endl;
        }
    }


    ofstream reg("akun.txt", ios::app);
    reg << regisuser << " " << regispass << endl;
    cout << "\033[1;32m\nSelamat, anda berhasil registrasi.\033[0m" << endl;
    system("pause");
    menu_masuk();
}

void lupa() {
    int pilihan_lupa;
    string input;
    system("cls");
    cout << "Apakah anda ingin mengganti username atau password anda?" << endl;
    cout << "1. Lupa Username" << endl;
    cout << "2. Ganti Password" << endl;
    cout << "3. Kembali ke menu login" << endl;
    cout << "Masukan pilihan anda" << endl;
    cin >> pilihan_lupa;
    
     if (cin.fail()) {
            cin.clear(); // Menghapus flag error dari cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Menghapus karakter dari buffer
            pilihan_lupa= -1; // Menetapkan pilihan ke nilai yang tidak valid
            cout << "\033[1;31mPilihan tidak valid, coba lagi.\033[0m" << endl;
            system("pause");
        }

    switch (pilihan_lupa) {
        case 1: {
            string pass, username, password;
            cout << "Masukkan password anda: ";
            cin >> pass;
            ifstream input("akun.txt");
            bool ditemukan = false;
            while (input >> username >> password) {
                if (password == pass) {
                    cout << "Username anda adalah: " << username << endl;
                    ditemukan = true;
                    break;
                }
            }
            input.close();
            if (!ditemukan) {
                cout << "\033[1;31mPassword tidak ditemukan.\033[0" << endl;
            }
            system("pause");
            menu_masuk();
            break;
        }
        case 2: {
            string user, newpass, username, password;
            cout << "Masukkan username: ";
            cin >> user;
            cout << "Masukkan password baru: ";
            cin >> newpass;
            ifstream input("akun.txt");
            stringstream temp;
            bool ditemukan = false;
            while (input >> username >> password) {
                if (username == user) {
                    temp << username << " " << newpass << endl;
                    ditemukan = true;
                } else {
                    temp << username << " " << password << endl;
                }
            }
            input.close();
            ofstream output("akun.txt");
            output << temp.str();
            output.close();
            if (ditemukan) {
                cout << "\033[1;32mPassword berhasil diganti.\033[0m" << endl;
            } else {
                cout << "\033[1;31mUsername tidak ditemukan.\033[0m" << endl;
            }
            system("pause");
            menu_masuk();
            break;
        }
        case 3:
            menu_masuk();
            break;
        default:
            cout << "\033[1;31mPilihan tidak valid, coba lagi.\033[0m" << endl;
            system("pause");
            lupa();
            break;
    }
}


// menu admin
void tampilkan_produk(const Merchandise* memori, int total_memori) {
    system("cls");
    if (total_memori > 0) {
        cout << "Daftar Produk Tersimpan:" << endl;
    cout << "==============================================================" << endl;
    cout << " | " << setw(3) << left << "ID" 
         << " | " << setw(14) << left << "Nama"
         << " | " << setw(10) << left << "Kategori"
         << " | " << setw(6) << right << "Jumlah"
         << " | " << setw(7) << right << "Harga"
         << " |" << endl;
    cout << "==============================================================" << endl;
    
    for (int i = 0; i < total_memori; i++) {
        cout << " | " << setw(3) << left << memori[i].nomorProduk
             << " | " << setw(14) << left << memori[i].film
             << " | " << setw(10) << left << memori[i].jenis
             << " | " << setw(6) << right << memori[i].stock
             << " | $" << setw(6) << right << fixed << setprecision(2) << memori[i].harga
             << " |" << endl;
    }
    system("pause");
    } else {
        cout << "\033[1;33m<---Data Kosong--->\033[0m"  << endl;
    }
    
}

void tambah_produk(Merchandise* memori, int& total_memori) {
    tampilkan_produk(memori, total_memori);
    char ulang;
    do {
        if (total_memori >= penyimpanan_max) {
            cout << "\033[1;31mMemori penuh. Tidak dapat menambahkan merchandise.\033[0m" << endl;
            system("pause");
            return;
        }

        Merchandise merch_baru;
        cout << "Masukkan Nomor Produk: ";
        cin >> merch_baru.nomorProduk;
        cout << "Masukkan Nama Film: ";
        cin >> merch_baru.film;
        cout << "Masukkan Jenis Produk: ";
        cin >> merch_baru.jenis;
        cout << "Masukkan Jumlah Produk: ";
        cin >> merch_baru.stock;
        cout << "Masukkan Harga Produk: $.";
        cin >> merch_baru.harga;

        memori[total_memori] = merch_baru;
        total_memori++;
        cout << "\033[1;34mMerchandise Berhasil Ditambahkan!\033[0m" << endl;
        system("pause");

        cout << "Ingin tambah produk lagi? (y/n): ";
        cin >> ulang;
    } while (ulang == 'y' || ulang == 'Y');
}

void update_produk(Merchandise* memori, int total_memori) {
    char ulang;
    int a;
    do {
        tampilkan_produk(memori, total_memori);
        cout << "Ubah data ke-";
        cin >> a;
        cin.ignore();
        if (a < 1 || a > total_memori) {
            cout << "\033[1;31mIndeks Tidak Valid!\033[0m" << endl;
            system("pause");
            return;
        }

        cout << "Pilih Data Yang Ingin Diubah: " << endl;
        cout << "1. Film: " << endl;
        cout << "2. Jenis Produk:" << endl;
        cout << "3. Jumlah Produk: " << endl;
        cout << "4. Harga: " << endl;
        cout << "Pilih (1-4): ";

        int pilih;
        cin >> pilih;
        cin.ignore();

         if (cin.fail()) {
            cin.clear(); // Menghapus flag error dari cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Menghapus karakter dari buffer
            pilih = -1; // Menetapkan pilihan ke nilai yang tidak valid
            cout << "\033[1;31mPilihan tidak valid, coba lagi.\033[0m" << endl;
            system("pause");
        }

        switch (pilih) {
            case 1:
                cout << "Masukkan nama film: ";
                cin >> memori[a - 1].film;
                cout << "\033[1;34mNama film berhasil diubah!\033[0m" << endl;
                system("pause");
                break;
            case 2:
                cout << "Masukkan Jenis Produk: ";
                cin >> memori[a - 1].jenis;
                cout << "\033[1;34mJenis produk berhasil diubah!\033[0m" << endl;
                system("pause");
                break;
            case 3:
                cout << "Masukkan jumlah produk: ";
                cin >> memori[a - 1].stock;
                cout << "\033[1;34mJumlah produk berhasil diubah!\033[0m" << endl;
                system("pause");
                break;
            case 4:
                cout << "Masukkan Harga: $";
                cin >> memori[a - 1].harga;
                cout << "\033[1;34mHarga produk berhasil diubah!\033[0m" << endl;
                system("pause");
                break;
            default:
                cout << "\033[1;31mPilihan tidak valid.\033[0m" << endl;
                break;
        }
        cout << "Ingin mengubah produk lagi? (y/n): ";
        cin >> ulang;
        cin.ignore();
    } while (ulang == 'y' || ulang == 'Y');
}

void hapus_produk(Merchandise* memori, int& total_memori) {
    char ulang;
    do {
        tampilkan_produk(memori, total_memori);
        if (total_memori == 0) {
            cout << "\033[1;33mTidak ada produk untuk dihapus.\033[0m" << endl;
            system("pause");
            return;
        }
        cout << "Hapus data ke-";
        int x;
        cin >> x;
        cin.ignore();

        if (x < 1 || x > total_memori) {
            cout << "\033[1;31mIndeks tidak valid!\033[0m" << endl;
            system("pause");
            return;
        }
        for (int i = x - 1; i < total_memori - 1; ++i) {
            memori[i] = memori[i + 1];
        }
        total_memori--;
        cout << "\033[1;34mProduk berhasil dihapus\033[0m" << endl;
        system("pause");

        cout << "Ingin hapus produk lagi? (y/n): ";
        cin >> ulang;
        cin.ignore();
    } while (ulang == 'y' || ulang == 'Y');
}

void urutkan_termurah(Merchandise* memori, int total_memori) {
    // Menggunakan fungsi sort dari STL untuk mengurutkan memori berdasarkan harga
    sort(memori, memori + total_memori, [](const Merchandise& a, const Merchandise& b) {
        return a.harga < b.harga;
    });

    cout << "Daftar Produk Tersimpan (Diurutkan dari Harga Termurah):" << endl;
    for (int i = 0; i < total_memori; i++) {
        cout << i + 1 << ". Nomor Produk: " << memori[i].nomorProduk
             << " | Film: " << memori[i].film
             << " | Jenis Produk: " << memori[i].jenis
             << " | Stock: " << memori[i].stock
             << " | Harga: $" << memori[i].harga << endl;
        system("pause");
    }
}


void cari_produk(const Merchandise* memori, int total_memori) {
    string keyword;
    cout << "Masukkan kata kunci: ";
    cin >> keyword;

    bool found = false;
    for (int i = 0; i < total_memori; i++) {
        if (memori[i].film.find(keyword) != string::npos || memori[i].jenis.find(keyword) != string::npos) {
            cout << "Nomor Produk: " << memori[i].nomorProduk
                 << " | Film: " << memori[i].film
                 << " | Jenis Produk: " << memori[i].jenis
                 << " | Stock: " << memori[i].stock
                 << " | Harga: $" << memori[i].harga << endl;
            found = true;
            system("pause");
        }
    }

    if (!found) {
        cout << "Produk dengan kata kunci '" << keyword << "' tidak ditemukan." << endl;
        system("pause");
    }
}

void tampilkan_riwayat_pembelian() {
    ifstream file_riwayat("riwayat_pembelian.txt");
    if (file_riwayat.is_open()) {
        string line;
        cout << "Riwayat Pembelian:" << endl;
        while (getline(file_riwayat, line)) {
            cout << line << endl;
        }
        file_riwayat.close();
    } else {
        cout << "\033[1;33mTidak ada riwayat pembelian yang tersimpan.\033[0m" << endl;
    }
}

void tambah_riwayat_pembelian(const string& nama, const string& film, const string& jenis, int jumlah, double total) {
    ofstream file_riwayat("riwayat_pembelian.txt", ios::app);
    if (file_riwayat.is_open()) {
        file_riwayat << "Nama Pelanggan: " << nama << ", Film: " << film << ", Jenis: " << jenis 
                     << ", Jumlah: " << jumlah << ", Total Biaya: $" << total << endl;
        file_riwayat.close();
    }
}


// MENU PENGGUNA
void tambah_belanjaan(Merchandise* memori, int& total_memori, Merchandise* keranjang, int& total_keranjang) {
    int nomor_produk;
    int jumlah_beli;

    tampilkan_produk(memori, total_memori);
    cout << "Masukkan nomor produk yang ingin dibeli: ";
    cin >> nomor_produk;
    cin.ignore();

    if (nomor_produk < 1 || nomor_produk > total_memori) {
        cout << "\033[1;31mNomor produk tidak valid!\033[0m" << endl;
        system("pause");
        return;
    }

    cout << "Masukkan jumlah yang ingin dibeli: ";
    cin >> jumlah_beli;
    cin.ignore();

    if (jumlah_beli <= 0 || jumlah_beli > memori[nomor_produk - 1].stock) {
        cout << "\033[1;31mJumlah pembelian tidak valid!\033[0m" << endl;
        return;
    }

    keranjang[total_keranjang] = memori[nomor_produk - 1];
    keranjang[total_keranjang].stock = jumlah_beli;
    total_keranjang++;

    memori[nomor_produk - 1].stock -= jumlah_beli;

    string nama_pelanggan;
    cout << "Masukkan nama pelanggan: ";
    getline(cin, nama_pelanggan);

    cout << "\033[1;34mProduk berhasil ditambahkan ke dalam keranjang belanja!\033[0m" << endl;
    system("pause");
}


void lihat_daftar_belanjaan(Merchandise* keranjang, int total_keranjang) {
    if (total_keranjang == 0) {
        cout << "\033[1;33m<--- Keranjang belanjaan Anda kosong --->\033[0m" << endl;
        system("pause");
        return;
    }

    cout << "==============================================================" << endl;
    cout << " | ID  | Nama           | Kategori    | Jumlah |  Harga  |" << endl;
    cout << "==============================================================" << endl;
    for (int i = 0; i < total_keranjang; ++i) {
        cout  
             << " | " << setw(3) << keranjang[i].nomorProduk
             << " | " << setw(14) << keranjang[i].film
             << " | " << setw(10) << keranjang[i].jenis
             << " | " << setw(6) << keranjang[i].stock
             << " | $" << setw(7) << fixed << setprecision(2) << keranjang[i].harga
             << " |" << endl;
    }
    cout << "==============================================================" << endl;
}


void ubah_keranjang(Merchandise* keranjang, int& total_keranjang) {
    if (total_keranjang == 0) {
        cout << "\033[1;33mKeranjang belanjaan Anda kosong\033[0m" << endl;
        system("pause");
        return;
    }

    cout << "Daftar Keranjang Belanja: " << endl;
    lihat_daftar_belanjaan(keranjang, total_keranjang);

    string nomorProduk;
    cout << "Masukkan ID produk yang ingin diubah: ";
    cin >> nomorProduk;

    int index_produk = -1;
    for (int i = 0; i < total_keranjang; ++i) {
        if (keranjang[i].nomorProduk == nomorProduk) {
            index_produk = i;
            break;
        }
    }

    if (index_produk == -1) {
        cout << "\033[1;31mID produk tidak ditemukan!\033[0m" << endl;
        system("pause");
        return;
    }

    int jumlah_beli;
    string input_jumlah_beli;
    do {
        cout << "Masukkan jumlah baru: ";
        cin >> input_jumlah_beli;

        bool valid_input = true;
        for (char digit : input_jumlah_beli) {
            if (!isdigit(digit)) {
                valid_input = false;
                break;
            }
        }


        if (!valid_input || stoi(input_jumlah_beli) <= 0) {
            cout << "\033[1;31mJumlah pembelian tidak valid!\033[0m" << endl;
            system("pause");
            return;
        } else{
            jumlah_beli = stoi(input_jumlah_beli);
            break;
        }

    } while (true);


   
    keranjang[index_produk].stock = jumlah_beli;
    cout << "\033[1;34mJumlah produk dalam keranjang berhasil diubah!\033[0m" << endl;
    system("pause");

    cout << "Daftar Keranjang Belanja Setelah Perubahan: " << endl;
    lihat_daftar_belanjaan(keranjang, total_keranjang);
    system("pause");
}

void hapus_keranjang(Merchandise* keranjang, int& total_keranjang) {
    if (total_keranjang == 0) {
        cout << "\033[1;33mKeranjang belanjaan Anda kosong\033[0m" << endl;
        system("pause");
        return;
    }

    cout << "Daftar Keranjang Belanja: " << endl;
    lihat_daftar_belanjaan(keranjang, total_keranjang);

    string nomorProduk;
    cout << "Masukkan ID produk yang ingin dihapus: ";
    cin >> nomorProduk;

    int index_produk = -1;
    for (int i = 0; i < total_keranjang; ++i) {

        if (keranjang[i].nomorProduk == nomorProduk) {
            index_produk = i;
            break;
        }
    }

    if (index_produk == -1) {
        cout << "\033[1;31mID produk tidak ditemukan!\033[0m" << endl;
        system("pause");
        return;
    }

    for (int i = index_produk; i < total_keranjang - 1; ++i) {
        keranjang[i] = keranjang[i + 1];
    }
    total_keranjang--;

    cout << "\033[1;34mProduk berhasil dihapus dari keranjang belanja!\033[0m" << endl;
    system("pause");

    cout << "Daftar Keranjang Belanja Setelah Penghapusan: " << endl;
    lihat_daftar_belanjaan(keranjang, total_keranjang);
    system("pause");
}

void urutkan(Merchandise* keranjang, int total_keranjang) {
    if (total_keranjang == 0) {
        cout << "\033[1;33mKeranjang belanjaan Anda kosong\033[0m" << endl;
        system("pause");
        return;
    }

    // Menyalin array ke dalam vector
    vector<Merchandise> v_keranjang(keranjang, keranjang + total_keranjang);
    
    // Mengurutkan vector berdasarkan harga
    sort(v_keranjang.begin(), v_keranjang.end(), [](const Merchandise& a, const Merchandise& b) {
        return a.harga < b.harga;
    });

    // Mengembalikan vector yang sudah diurutkan ke dalam array
    for (int i = 0; i < total_keranjang; ++i) {
        keranjang[i] = v_keranjang[i];
    }

    // Menampilkan setiap elemen array setelah pengurutan
    cout << "Elemen-elemen array setelah pengurutan:" << endl;
    for (int i = 0; i < total_keranjang; ++i) {
        cout << "Nomor Produk: " << keranjang[i].nomorProduk
             << ", Film: " << keranjang[i].film
             << ", Jenis Produk: " << keranjang[i].jenis
             << ", Stock: " << keranjang[i].stock
             << ", Harga: $" << keranjang[i].harga << endl;
    }

    cout << "\033[1;34mKeranjang belanjaan berhasil diurutkan berdasarkan harga termurah.\033[0m" << endl;
    system("pause");
}

bool isValidAmount(const string& input) {
    bool hasDecimal = false;
    for (char c : input) {
        if (!isdigit(c)) {
            if (c == '.' && !hasDecimal) {
                hasDecimal = true;
            } else {
                return false;
            }
        }
    }
    return true;
}
void bayar(Merchandise* keranjang, int total_keranjang) {
    if (total_keranjang == 0) {
        // clear();
        cout << "\033[1;33mKeranjang belanjaan Anda kosong.\033[0m" << endl;
        system("pause");
        return;
    }

    double total_pembayaran = 0;
    cout << "==============================================================" << endl;
    cout << " | ID  | Nama           | Kategori    | Jumlah |  Harga  |" << endl;
    cout << "==============================================================" << endl;
    for (int i = 0; i < total_keranjang; ++i) {
        cout  
             << " | " << setw(3) << keranjang[i].nomorProduk
             << " | " << setw(14) << keranjang[i].film
             << " | " << setw(10) << keranjang[i].jenis
             << " | " << setw(6) << keranjang[i].stock
             << " | $" << setw(7) << fixed << setprecision(2) << keranjang[i].harga
             << " |" << endl;
        total_pembayaran += keranjang[i].harga * keranjang[i].stock;
    }
    cout << "==============================================================" << endl;
    cout << "Total Pembayaran: $" << fixed << setprecision(2) << total_pembayaran << endl;

    // Melakukan proses pembayaran
    double uang_dibayarkan;
    string input;

   while (true) {
        cout << "Masukkan jumlah uang yang dibayarkan: $";
        cin >> input;
        cin.ignore();

        if (!isValidAmount(input)) {
            cout << "\033[1;31mInput tidak valid. Harap masukkan angka.\033[0m" << endl;
            system("pause");
            break;
        } else {
            uang_dibayarkan = atof(input.c_str());
            if (uang_dibayarkan < total_pembayaran) {
                cout << "\033[1;31mUang yang dibayarkan kurang. Silakan coba lagi.\033[0m" << endl;
                system("pause");
                break;
            } else if (uang_dibayarkan == total_pembayaran){
                cout << "\033[1;34mTerima kasih atas pembayaran Anda!\033[0m" << endl;
                
                system("pause");
                break;
            } else {
                cout << "Kembalian Anda: $" << fixed << setprecision(2) << uang_dibayarkan - total_pembayaran << endl;
                cout << "\033[1;34mTerima kasih atas pembayaran Anda!\033[0m" << endl;
                
                string nama_pelanggan;
                cout << "Masukkan nama pelanggan: ";
                getline(cin, nama_pelanggan);

                for (int i = 0; i < total_keranjang; ++i){
                    double total_biaya = keranjang[i].harga * keranjang[i].stock;
                    tambah_riwayat_pembelian(nama_pelanggan, keranjang[i].film, keranjang[i].jenis, keranjang[i].stock, total_biaya);
                }
                
                total_keranjang = 0;
                system("pause");
                break;
            }
        }
    }
}
    

void menu_pembeli() {
    Merchandise memori[penyimpanan_max] = {
        {"01", "Tangled", "Mug", 100, 10.99},
        {"02", "Mickey Mouse", "T-shirt", 100, 29.99},
        {"03", "Moana", "Accessories", 100, 19.99},
        {"04", "Toy Story", "Action Figure", 100, 25.99},
        {"05", "Star Wars", "Tumblr", 100, 49.99}
    };
    int total_memori = 5;
    int pilih;
    Merchandise keranjang[penyimpanan_max];
    int total_keranjang = 0;

    do {
        system("cls");
        cout << "\n==========================================" << endl;
        cout << "|               Menu Pengguna            |" << endl;
        cout << "==========================================" << endl;
        cout << "| 1. Lihat Daftar Produk                 |" << endl;
        cout << "| 2. Tambah Belanjaan                    |" << endl;
        cout << "| 3. Ubah Keranjang                      |" << endl;
        cout << "| 4. Hapus Keranjang                     |" << endl;
        cout << "| 5. Urutkan dari yang termurah          |" << endl;
        cout << "| 6. Lihat isi keranjang                 |" << endl;
        cout << "| 7. Bayar                               |" << endl;
        cout << "| 8. Keluar                              |" << endl;
        cout << "==========================================" << endl;
        cout << "Pilih Menu (1-8): ";
        cin >> pilih;
        cin.ignore();

         if (cin.fail()) {
            cin.clear(); // Menghapus flag error dari cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Menghapus karakter dari buffer
            pilih = -1; // Menetapkan pilihan ke nilai yang tidak valid
            cout << "\033[1;31mPilihan tidak valid, coba lagi.\033[0m" << endl;
            system("pause");
        }

        switch (pilih) {
            case 1:
                tampilkan_produk(memori, total_memori);
                break;
            case 2:
                tambah_belanjaan(memori, total_memori, keranjang, total_keranjang);
                break;
            case 3:
                ubah_keranjang(keranjang, total_keranjang);
                break;
            case 4:
                hapus_keranjang(keranjang, total_keranjang);
                break;
            case 5:
                urutkan(keranjang, total_keranjang);
                break;
            case 6:
                lihat_daftar_belanjaan(keranjang, total_keranjang);
                system("pause");
                break;
            case 7:
                bayar(keranjang, total_keranjang);
                break;
            case 8:
                cout << "Terima kasih! Sampai jumpa lagi." << endl;
                break;
            default:
                cout << "\033[1;31mPilihan Tidak Valid. Silakan Coba Lagi\033[0m" << endl;
                break;
        }
    } while (pilih != 8);
}

void menu_admin() {
    Merchandise memori[penyimpanan_max] = {
        {"01", "Tangled", "Mug", 100, 10.99},
        {"02", "Mickey Mouse", "T-shirt", 100, 29.99},
        {"03", "Moana", "Accessories", 100, 19.99},
        {"04", "Toy Story", "Action Figure", 100, 25.99},
        {"05", "Star Wars", "Tumblr", 100, 49.99}
    };
    int total_memori = 5;
    int pilih;
    do {
        system("cls");
        cout << "\n==========================================" << endl;
        cout << "|               Menu Admin               |" << endl;
        cout << "==========================================" << endl;
        cout << "| 1. Tambah produk                       |" << endl;
        cout << "| 2. Update produk                       |" << endl;
        cout << "| 3. Hapus produk                        |" << endl;
        cout << "| 4. Tampilkan produk                    |" << endl;
        cout << "| 5. Riwayat pembelian                   |" << endl;
        cout << "| 6. Urutkan dari yang termurah          |" << endl;
        cout << "| 7. Cari barang                         |" << endl;
        cout << "| 8. Keluar                              |" << endl;
        cout << "==========================================" << endl;
        cout << "Pilih Menu (1-8): ";
        cin >> pilih;
        cin.ignore();

         if (cin.fail()) {
            cin.clear(); // Menghapus flag error dari cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Menghapus karakter dari buffer
            pilih = -1; // Menetapkan pilihan ke nilai yang tidak valid
            cout << "\033[1;31mPilihan tidak valid, coba lagi.\033[0m" << endl;
            system("pause");
        }

        switch (pilih) {
            case 1:
                tambah_produk(memori, total_memori);
                break;
            case 2:
                update_produk(memori, total_memori);
                break;
            case 3:
                hapus_produk(memori, total_memori);
                break;
            case 4:
                tampilkan_produk(memori, total_memori);
                break;
            case 5:
                tampilkan_riwayat_pembelian();
                system("pause");
                break;
            case 6:
                urutkan_termurah(memori, total_memori);
                break;
            case 7:
                cari_produk(memori, total_memori);
                break;
            case 8:
                cout << "Keluar Dari Menu Admin" << endl;
                break;
            default:
                cout << "\033[1;31mPilihan Tidak Valid. Silakan Coba Lagi\033[0m" << endl;
                system("pause");
                break;
        }
    } while (pilih != 8);
}

void riwayat_pembelian() {
    ifstream file_riwayat("riwayat_pembelian.txt");
    if (file_riwayat.is_open()) {
        cout << "\nRiwayat Pembelian: " << endl;
        string baris;
        while (getline(file_riwayat, baris)) {
            cout << baris << endl;
        }
        file_riwayat.close();
    } else {
        cout << "\033[1;33m<--Riwayat Pembelian Kosong-->\033[0m" << endl;
    }
}

int main() {
    int pilihan;
    do {
        system("cls");
        cout << "============================================" << endl;
        cout << "           MERCH DISNEYLAND" << endl;
        cout << "============================================" << endl ;
        cout << "1. Menu Masuk" << endl;
        cout << "2. Keluar" << endl;
        cout << "Masukkan pilihan anda: ";
        cin >> pilihan;
        cout << endl;

        if (cin.fail()) {
            cin.clear(); // Menghapus flag error dari cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Menghapus karakter dari buffer
            pilihan = -1; // Menetapkan pilihan ke nilai yang tidak valid
            cout << "\033[1;31mPilihan tidak valid, coba lagi.\033[0m" << endl;
            system("pause");
        }

        cout << endl;
        switch (pilihan) {
            case 1:
                menu_masuk();
                break;
            case 2:
                cout << "Terima kasih sampai jumpa lagi..." << endl;
                break;
            default:
                cout << "\033[1;31mPilihan tidak valid, coba lagi.\033[0m" << endl;
                break;
        }
    } while (pilihan != 2);
    return 0;
}