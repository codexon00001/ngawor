#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "AlatLaboratorium.hpp"

using namespace std;

string rapikan(const string& teks) {
    size_t awal = teks.find_first_not_of(" \t\r\n");
    if (awal == string::npos) {
        return "";
    }
    size_t akhir = teks.find_last_not_of(" \t\r\n");
    return teks.substr(awal, akhir - awal + 1);
}

string kecil(string teks) {
    transform(teks.begin(), teks.end(), teks.begin(),
              [](unsigned char c) { return static_cast<char>(tolower(c)); });
    return teks;
}

bool bacaTeks(const string& label, string& hasil) {
    cout << label;
    if (!getline(cin, hasil)) {
        return false;
    }
    hasil = rapikan(hasil);
    return true;
}

int bacaAngka(const string& label, int& hasil) {
    string baris;
    if (!bacaTeks(label, baris)) {
        return -1;
    }
    if (baris.empty()) {
        return 0;
    }
    try {
        size_t posisi = 0;
        long nilai = stol(baris, &posisi);
        if (posisi != baris.size() || nilai > 2147483647L || nilai < -2147483648L) {
            return 0;
        }
        hasil = static_cast<int>(nilai);
        return 1;
    } catch (...) {
        return 0;
    }
}

int cariAlat(const vector<AlatLaboratorium>& daftar, const string& nama, const string& kategori) {
    for (size_t i = 0; i < daftar.size(); i++) {
        if (kecil(daftar[i].getNama()) == kecil(nama) &&
            kecil(daftar[i].getKategori()) == kecil(kategori)) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

void tampilkanDaftar(const vector<AlatLaboratorium>& daftar) {
    if (daftar.empty()) {
        cout << "Daftar alat masih kosong.\n";
        return;
    }
    cout << left << setw(4) << "No"
         << setw(22) << "Nama"
         << setw(18) << "Kategori"
         << "Jumlah\n";
    for (size_t i = 0; i < daftar.size(); i++) {
        cout << left << setw(4) << (i + 1);
        daftar[i].tampilkanInfo();
    }
}

void menuTambahAlat(vector<AlatLaboratorium>& daftar) {
    string nama, kategori;
    int jumlah;
    if (!bacaTeks("Nama alat     : ", nama)) return;
    if (!bacaTeks("Kategori      : ", kategori)) return;
    if (nama.empty() || kategori.empty()) {
        cout << "[GAGAL] Nama dan kategori tidak boleh kosong.\n";
        return;
    }
    int status = bacaAngka("Jumlah awal   : ", jumlah);
    if (status != 1) {
        if (status == 0) cout << "[GAGAL] Jumlah harus berupa bilangan bulat.\n";
        return;
    }
    if (jumlah < 0) {
        cout << "[GAGAL] Jumlah awal tidak boleh negatif.\n";
        return;
    }
    if (cariAlat(daftar, nama, kategori) != -1) {
        cout << "[GAGAL] Alat dengan nama dan kategori yang sama sudah terdaftar. "
                "Gunakan menu tambah jumlah.\n";
        return;
    }
    daftar.push_back(AlatLaboratorium(nama, kategori, jumlah));
    cout << "[SUKSES] Alat '" << nama << "' ditambahkan.\n";
}

void menuUbahJumlah(vector<AlatLaboratorium>& daftar, bool menambah) {
    if (daftar.empty()) {
        cout << "Daftar alat masih kosong. Tambahkan alat terlebih dahulu.\n";
        return;
    }
    tampilkanDaftar(daftar);
    int nomor, n;
    int status = bacaAngka("Nomor alat    : ", nomor);
    if (status != 1) {
        if (status == 0) cout << "[GAGAL] Nomor harus berupa bilangan bulat.\n";
        return;
    }
    if (nomor < 1 || nomor > static_cast<int>(daftar.size())) {
        cout << "[GAGAL] Nomor alat tidak ada dalam daftar.\n";
        return;
    }
    status = bacaAngka(menambah ? "Jumlah ditambah : " : "Jumlah dikurangi: ", n);
    if (status != 1) {
        if (status == 0) cout << "[GAGAL] Jumlah harus berupa bilangan bulat.\n";
        return;
    }
    AlatLaboratorium& alat = daftar[nomor - 1];
    if (menambah) {
        if (alat.tambahJumlah(n)) {
            cout << "[SUKSES] Jumlah " << alat.getNama() << " sekarang " << alat.getJumlah() << ".\n";
        } else {
            cout << "[GAGAL] Jumlah tambahan harus lebih dari 0 dan tidak melebihi batas.\n";
        }
    } else {
        if (alat.kurangiJumlah(n)) {
            cout << "[SUKSES] Jumlah " << alat.getNama() << " sekarang " << alat.getJumlah() << ".\n";
        } else {
            cout << "[GAGAL] Jumlah pengurangan harus lebih dari 0 dan tidak boleh melebihi jumlah saat ini ("
                 << alat.getJumlah() << ").\n";
        }
    }
}

int main() {
    vector<AlatLaboratorium> daftar;
    int pilihan = -1;

    do {
        cout << "\n=== INVENTARIS ALAT LABORATORIUM ===\n";
        cout << "1. Tambah alat baru\n";
        cout << "2. Tambah jumlah alat\n";
        cout << "3. Kurangi jumlah alat\n";
        cout << "4. Tampilkan semua alat\n";
        cout << "0. Keluar\n";

        int status = bacaAngka("Pilih menu (0-4): ", pilihan);
        if (status == -1) {
            cout << "\n";
            break;
        }
        if (status == 0) {
            cout << "[PERINGATAN] Input harus berupa angka.\n";
            pilihan = -1;
            continue;
        }

        switch (pilihan) {
            case 1: menuTambahAlat(daftar); break;
            case 2: menuUbahJumlah(daftar, true); break;
            case 3: menuUbahJumlah(daftar, false); break;
            case 4: tampilkanDaftar(daftar); break;
            case 0: cout << "Program selesai. Terima kasih!\n"; break;
            default: cout << "[PERINGATAN] Pilihan menu tidak tersedia.\n";
        }
    } while (pilihan != 0);

    return 0;
}
