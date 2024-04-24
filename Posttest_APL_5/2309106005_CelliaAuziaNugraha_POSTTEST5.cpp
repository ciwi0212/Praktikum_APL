#include<iostream>
using namespace std;

struct lokasi{
    string kota;
    string negara;
};

struct data_diri{
    struct Pengguna{
        string username;
        string password;
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
            cin.ignore();
            cout<<"Masukkan Username: ";
            getline(cin,penggunaPtr[jmlh]->username);
            cout<<"Masukkan Password: ";
            getline(cin,penggunaPtr[jmlh]->password);
            cout<<"Masukkan Kota: ";
            getline(cin,penggunaPtr[jmlh]->loc.kota);
            cout<<"Masukkan Negara: ";
            getline(cin,penggunaPtr[jmlh]->loc.negara);
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
        cout<<"Masukkan Username Baru: ";
        getline(cin,penggunaPtr[y-1]->username);
        cout<<"Masukkan Password Baru: ";
        getline(cin,penggunaPtr[y-1]->password);
        cout<<"Masukkan Kota Baru: ";
        getline(cin,penggunaPtr[y-1]->loc.kota);
        cout<<"Masukkan Negara Baru: ";
        getline(cin,penggunaPtr[y-1]->loc.negara);
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
       cout<<"1. Tambah Data Pengguna\n2. Ubah Data Pengguna\n3. Hapus Data Pengguna\n4. Tampilkan Data Pengguna\n5. Keluar Program"<<endl;
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
            cout<<". . ."<<endl;
            break;
        default:
            cout<<"Pilih 1-5"<<endl;
            break;
        } 
    } while (pil != 5);
    cout<<"Program Selesai";
    return 0;
}