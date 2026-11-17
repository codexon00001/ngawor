### File `Barang.cpp` *(Tugas Mahasiswa 1)*

```cpp
#include "dandy.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

// 1. Default Constructor (jika objek dibuat tanpa mengisi data awal)
Barang::Barang() {
    kode = "-";
    nama = "Tanpa Nama";
    stok = 0;
    harga = 0.0;
}

// 2. Parameterized Constructor (langsung mengisi data saat objek dibuat)
Barang::Barang(string kode, string nama, int stok, double harga) {
    this->kode = kode;
    this->nama = nama;
    this->stok = (stok >= 0) ? stok : 0;
    this->harga = (harga >= 0) ? harga : 0.0;
}

// 3. Method Getter (mengambil nilai atribut private secara aman)
string Barang::getKode() const { return kode; }
string Barang::getNama() const { return nama; }
int Barang::getStok() const { return stok; }
double Barang::getHarga() const { return harga; }

// 4. Method Menambah Stok
void Barang::tambahStok(int jumlah) {
    if (jumlah > 0) {
        stok += jumlah;
        cout << "[SUKSES] Stok bertambah " << jumlah << ". Total stok: " << stok << "\n";
    } else {
        cout << "[GAGAL] Jumlah barang masuk harus lebih dari 0.\n";
    }
}

// 5. Method Mengurangi Stok
bool Barang::kurangiStok(int jumlah) {
    if (jumlah <= 0) {
        cout << "[GAGAL] Jumlah barang keluar harus lebih dari 0.\n";
        return false;
    }
    if (jumlah > stok) {
        cout << "[GAGAL] Stok tidak mencukupi! Sisa stok: " << stok << "\n";
        return false;
    }
    stok -= jumlah;
    cout << "[SUKSES] Stok berkurang " << jumlah << ". Sisa stok: " << stok << "\n";
    return true;
}

// 6. Method Menampilkan 1 Baris Info Barang
void Barang::tampilkanBaris() const {
    cout << left << setw(10) << kode
         << setw(24) << nama
         << setw(10) << stok
         << "Rp " << fixed << setprecision(0) << harga << "\n";
}

```
