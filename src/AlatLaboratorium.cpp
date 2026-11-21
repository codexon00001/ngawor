#include "AlatLaboratorium.hpp"

#include <iomanip>
#include <iostream>
#include <limits>

using namespace std;

AlatLaboratorium::AlatLaboratorium(string nama, string kategori, int jumlah) {
    this->nama = nama;
    this->kategori = kategori;
    this->jumlah = (jumlah >= 0) ? jumlah : 0;
}

string AlatLaboratorium::getNama() const { return nama; }
string AlatLaboratorium::getKategori() const { return kategori; }
int AlatLaboratorium::getJumlah() const { return jumlah; }

void AlatLaboratorium::tampilkanInfo() const {
    cout << left << setw(22) << nama
         << setw(18) << kategori
         << jumlah << "\n";
}

bool AlatLaboratorium::tambahJumlah(int n) {
    if (n <= 0) {
        return false;
    }
    if (n > numeric_limits<int>::max() - jumlah) {
        return false;
    }
    jumlah += n;
    return true;
}

bool AlatLaboratorium::kurangiJumlah(int n) {
    if (n <= 0) {
        return false;
    }
    if (n > jumlah) {
        return false;
    }
    jumlah -= n;
    return true;
}
