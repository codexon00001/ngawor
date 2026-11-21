#ifndef INVENTARIS_HPP
#define INVENTARIS_HPP

#include <string>
#include <vector>

class Barang {
private:
    std::string kode;
    std::string nama;
    int stok;
    double harga;

public:
    Barang();
    Barang(std::string kode, std::string nama, int stok, double harga);
    std::string getKode() const;
    std::string getNama() const;
    int getStok() const;
    double getHarga() const;
    void tambahStok(int jumlah);
    bool kurangiStok(int jumlah);
    void tampilkanBaris() const;
};

class Inventaris {
private:
    std::vector<Barang> daftarBarang;
    Barang* temukanBarang(const std::string& kode);
    void tampilkanJudul() const;

public:
    void tambahBarang(const Barang& barang);
    void tampilkanSemuaBarang() const;
    void cariBarang(const std::string& kode);
    void barangMasuk(const std::string& kode, int jumlah);
    void barangKeluar(const std::string& kode, int jumlah);
};

#endif
