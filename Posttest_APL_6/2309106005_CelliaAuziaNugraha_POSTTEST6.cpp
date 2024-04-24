#include<iostream>
#include<stdexcept>
#include<string>
using namespace std;

struct lokasi{
    string kota;
    string negara;
};

struct data_diri{
    struct Pengguna{
        string username;
        float password;
        lokasi loc;
    };
    Pengguna *penggunaPtr[10];
    char ulang = 'y';
    int jmlh = 0;

    void display(){
        system("cls");
        if(jmlh > 0){
            cout<<"Data Tersimpan"<<endl;
            for (int a=0; a<jmlh; a++){
                cout<<a+1<<". Username : "<<penggunaPtr[a]->username<<", Password: "<<penggunaPtr[a]->password<<endl;
                cout<<"Lokasi: "<<penggunaPtr[a]->loc.kota<<", "<<penggunaPtr[a]->loc.negara<<endl;
        }
    } else{
        cout<<"<-- Data Kosong -->"<<endl;
        }
    }

    void add(){
        display();
        if (jmlh < 10){
            penggunaPtr[jmlh] = new Pengguna();
            cin.ignore();
            cout<<"Masukkan Username: ";
            cin>>penggunaPtr[jmlh]->username;

            string inputpass;
            bool pass_valid = false;
            while(!pass_valid){
                cout<<"Masukkan Password (hanya angka): ";
                cin>>inputpass;
                try{
                    penggunaPtr[jmlh]->password = stof (inputpass);
                    pass_valid = true;
                } catch (const invalid_argument&) {
                    cout<<"Password harus berupa angka. Silahkan coba lagi."<<endl;
                }
            }

            cout<<"Masukkan Kota: ";
            cin>>penggunaPtr[jmlh]->loc.kota;

            cout<<"Masukkan Negara: ";
            cin>>penggunaPtr[jmlh]->loc.negara;
            jmlh++;
            display();
            cout<<"ulang? (y/t): ";
            cin>>ulang;
            if (ulang == 'y'){
                add();
            }
        } else{
            cout<<"Maaf, Penyimpanan Penuh. Silahkan Hapus Salah Satu Data Untuk Menambah"<<endl;
            cout<<"isi t untuk kembali: ";
            cin>>ulang;
        }
    }

    void update(){
        int y;
        display();
        cout<<"Ubah Data Ke-";
        cin>>y;
        cin.ignore();
        if (y < 1 || y > jmlh) {
            cout<<"Indeks tidak valid!"<<endl;
            return;
        }
        cout<<"Masukkan Username Baru: ";
        cin>>penggunaPtr[y-1]->username;

        string inputpass;
            bool pass_valid = false;
            while(!pass_valid){
                cout<<"Masukkan Password (hanya angka): ";
                cin>>inputpass;
                try{
                    penggunaPtr[jmlh]->password = stof (inputpass);
                    pass_valid = true;
                } catch (const invalid_argument&) {
                    cout<<"Password harus berupa angka. Silahkan coba lagi."<<endl;
                }
            }

        cout<<"Masukkan Kota Baru: ";
        cin>>penggunaPtr[y-1]->loc.kota;
        cout<<"Masukkan Negara Baru: ";
        cin>>penggunaPtr[y-1]->loc.negara;
        display();
        cout<<"Ubah Lagi? (y/t): ";
        cin>>ulang;
        if (ulang == 'y'){
            update();
        }
    }

    void del(){
        int x;
        display();
        if(jmlh > 0){
            cout<<"Hapus Data Ke-";
            cin>>x;
            if(x <= 0 ||  x > jmlh) {
                cout<<"Data Tidak Valid!"<<endl;
                return;
            }
            for(int i=x; i<jmlh; i++ ){
                penggunaPtr[i-1] = penggunaPtr[i];
            }
            jmlh--;
            display();
            cout<<"Hapus Lagi? (y/t): ";
            cin>>ulang;
            if(ulang=='y'){
                del();
            } 
        } else{
            cout<<"Ketik t: ";
            cin>>ulang;
        }
    }

    void insertion_sort(){
        for(int i=1;  i<jmlh; i++){
            Pengguna *temp = penggunaPtr[i];
            int j = i - 1;
            while((j >= 0) && penggunaPtr[j]->password<temp->password) {
                penggunaPtr[j + 1] = penggunaPtr[j];
                j--;
            }
            penggunaPtr[j + 1] = temp;
        }
    }

    void bubble_sort(){
        for(int i=0; i<jmlh; i++){
            for(int j=0; j<jmlh-i-1; j++){
                if(penggunaPtr[j]->loc.kota>penggunaPtr[j+1]->loc.kota){
                    swap(penggunaPtr[j], penggunaPtr[j+1]);
                }
            }
        }
    }

    void quick_sort(int low, int high, bool urut_berdasarkan_usn = true){
        if(low < high){
            int pi = partition(low, high, urut_berdasarkan_usn);
            quick_sort(low, pi - 1, urut_berdasarkan_usn);
            quick_sort(pi + 1, high, urut_berdasarkan_usn);
        }
    }

    int partition(int low, int high, bool urut_berdasarkan_usn){
        Pengguna* pivot = penggunaPtr[high];
        int i = low-1;

        for(int j=low; j<high; j++){
            bool condition = urut_berdasarkan_usn
            ? (penggunaPtr[j]->username<pivot->username) : (penggunaPtr[j]->password > pivot->password);
            
            if(condition){
                i++;    
                swap(penggunaPtr[i], penggunaPtr[j]);
            }
        }
        swap(penggunaPtr[i+1], penggunaPtr[high]);
        return i+1;
    }

    void menu_sort(){
        int pil;
        char ulang;
        do {
            system("cls");
            cout<<"Menu Sorting\n"<<endl;
            cout<<"1. Urutkan berdasarkan username(ascending)"<<endl;
            cout<<"2. Urutkan berdasarkan password(descending)"<<endl;
            cout<<"3. Urutkan berdasarkan kota(ascending)"<<endl;
            cout<<"Masukkan Pilihan: ";
            cin>>pil;

            switch(pil){
                case 1:
                    quick_sort(0, jmlh-1, true);
                    break;
                case 2:
                    insertion_sort();
                    break;
                case 3:
                    bubble_sort();
                    break;
                default:
                    cout<<"Pilihan tidak valid"<<endl;
                    break;
                }
                display();

                cout<<"Ingin mengulang? (y/t): ";
                cin>>ulang;
            } while(ulang=='y');
        }

    int binary_search(string data){
        int awal = 0;
        int akhir = jmlh-1;
        while(awal<=akhir){
            int tengah = awal + (akhir - awal)/2;
            if (penggunaPtr[tengah]->username == data){
                return tengah;
            }
            else if (penggunaPtr[tengah]->username<data){
                awal = tengah + 1;
            }
            else {
                akhir = tengah - 1;
            }
        }
        return -1;
    }

    int interpolation_search(string data){
        int low = 0;
        int high = jmlh-1;
        int posisi;

        while(low <= high && data >= penggunaPtr[high]->username && data <= penggunaPtr[low]->username){
            int posisi = low +(((double)(high-low)/(penggunaPtr[high]->username.length() - penggunaPtr[low]->username.length())) * (data.length() - penggunaPtr[low]->username.length()));
            if(posisi < low || posisi > high){
                break;
            }
            if(penggunaPtr[posisi]->username == data){
                return posisi;
            }
            if(penggunaPtr[posisi]->username < data){
                low = posisi + 1;
            }
            else{
                high = posisi - 1;
            }
        }
    return -1;
    
    }
    void menu_search(){
        system("cls");
        cout<<"Menu Searching\n"<<endl;
        cout<<"1. Cari pengguna berdasarkan username(ascending): "<<endl;
        cout<<"2. Cari pengguna berdasarkan username(descending): "<<endl;
        cout<<"Masukkan pilihan: ";

        int choice;
        cin>>choice;

        cout<<"Masukkan username yang ingin dicari: ";
        string data;
        cin>>data;
        int hasil_indeks;

        switch(choice){
            case 1: 
                hasil_indeks = binary_search(data);
                break;
            case 2: 
                hasil_indeks = interpolation_search(data);
                break;
            default:
                cout<<"Pilihan tidak valid.\n";
                return; 
        }
        if (hasil_indeks != -1) {
            cout<<"Data ditemukan di indeks ke-"<<hasil_indeks+1<<endl;
            cout<<"Username: "<<penggunaPtr[hasil_indeks]->username<<endl;
            cout<<"Password: "<<penggunaPtr[hasil_indeks]->password<<endl;
            cout<<"Lokasi: "<<penggunaPtr[hasil_indeks]->loc.kota<<", "<<penggunaPtr[hasil_indeks]->loc.negara<<endl;
        }else{
            cout<<"Data tidak ditemukan."<<endl;
        }
        cout<<"Cari lagi? (y/t): ";
        char ulang;
        cin>>ulang;
        if(ulang == 'y'){
           menu_search();
        }
    }
};

int main(){
    data_diri usr;
    string username, pass;
    int i;
    int login = 0;
    i = 1;
    char ulang = 'y';
    do{
        cout<<"Masukkan Username: ";cin>>username;
        cout<<"Masukkan Password: ";cin>>pass;
        if(username == "cellia" && pass == "2309106005"){
            i=4;
            login=1;
        } else{
            cout<<"Username atau Password Salah!"<<endl;
            i=i+1;
        }
    } while(i < 4);

    if (login != 1){
        cout<<"Maaf, Anda Telah Mencapai Batas Maksimum Percobaan"<<endl;
        return 0;
    }

    int pil;
    do{
       system("cls");
       cout<<"1. Tambah Data Pengguna\n2. Ubah Data Pengguna\n3. Hapus Data Pengguna\n4. Tampilkan Data Pengguna\n5. Urutkan Data Pengguna\n6. Cari Data Pengguna\n7. Keluar Program"<<endl;
       cout<<"Masukkan Pilihan: ";
       cin>>pil;
       switch(pil){
        case 1:
            usr.add();
            break;
        case 2:
            usr.update();
            break;
        case 3:
            usr.del();
            break;
        case 4:
            do{
                usr.display();
                cout<<"Kembali (y): ";
                cin>>usr.ulang;
            } while(usr.ulang != 'y');
            break;
        case 5:
            usr.menu_sort();
            break;
        case 6:
            usr.menu_search();
            break;
        case 7:
            cout<<". . .\n";
            break;
        default:
            cout<<"Pilih 1-7\n";
            break;
        } 
    } while (pil != 7);
    cout<<"Program Selesai";
    return 0;
}
