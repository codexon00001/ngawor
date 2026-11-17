
#include <iostream>
#include <limits>
#include "dandy.hpp"

using namespace std;

// Fungsi bantu agar program tidak error jika pengguna mengetik huruf pada input angka
void bersihkanInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    // OBJECT: Membuat wujud nyata bernama 'gudang' dari cetakan 'Inventaris'
    Inventaris gudang;
    int pilihan = -1;

    do {
        cout << "\n=== SISTEM INVENTARIS GUDANG ===\n";
        cout << "1. Tambah Barang Baru\n";
        cout << "2. Lihat Semua Stok Barang\n";
        cout << "3. Cari Barang (Kode)\n";
        cout << "4. Catat Barang Masuk (+ Stok)\n";
        cout << "5. Catat Barang Keluar (- Stok)\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu (0-5): ";

        if (!(cin >> pilihan)) {
            cout << "[PERINGATAN] Input harus berupa angka!\n";
            bersihkanInput();
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (pilihan == 1) {
            // 1. Menu Tambah Barang Baru
            string kode, nama;
            int stok;
            double harga;

            cout << "Kode Barang  : ";
            getline(cin, kode);
            cout << "Nama Barang  : ";
            getline(cin, nama);
            cout << "Stok Awal    : ";
            cin >> stok;
            cout << "Harga Satuan : ";
            cin >> harga;

            if (cin.fail()) {
                cout << "[GAGAL] Stok dan harga harus berupa angka!\n";
                bersihkanInput();
                continue;
            }

            // OBJECT: Membuat objek 'barangBaru' lalu memasukkannya ke dalam 'gudang'
            Barang barangBaru(kode, nama, stok, harga);
            gudang.tambahBarang(barangBaru);

        } else if (pilihan == 2) {
            // 2. Menu Lihat Semua Barang
            gudang.tampilkanSemuaBarang();

        } else if (pilihan == 3) {
            // 3. Menu Cari Barang
            string kode;
            cout << "Masukkan Kode Barang: ";
            getline(cin, kode);
            gudang.cariBarang(kode);

        } else if (pilihan == 4) {
            // 4. Menu Barang Masuk (+ Stok)
            string kode;
            int jumlah;
            cout << "Kode Barang  : ";
            getline(cin, kode);
            cout << "Jumlah Masuk : ";
            cin >> jumlah;

            if (cin.fail()) {
                cout << "[GAGAL] Jumlah harus berupa angka!\n";
                bersihkanInput();
                continue;
            }
            gudang.barangMasuk(kode, jumlah);

        } else if (pilihan == 5) {
            // 5. Menu Barang Keluar (- Stok)
            string kode;
            int jumlah;
            cout << "Kode Barang   : ";
            getline(cin, kode);
            cout << "Jumlah Keluar : ";
            cin >> jumlah;

            if (cin.fail()) {
                cout << "[GAGAL] Jumlah harus berupa angka!\n";
                bersihkanInput();
                continue;
            }
            gudang.barangKeluar(kode, jumlah);

        } else if (pilihan == 0) {
            cout << "Program selesai. Terima kasih!\n";
        } else {
            cout << "[PERINGATAN] Pilihan menu tidak tersedia.\n";
        }

    } while (pilihan != 0);

    return 0;
}
