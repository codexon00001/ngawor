#ifndef ALAT_LABORATORIUM_HPP
#define ALAT_LABORATORIUM_HPP

#include <string>

// Kelas yang mewakili satu jenis alat di laboratorium sekolah.
class AlatLaboratorium {
private:
    std::string nama;
    std::string kategori;
    int jumlah;

public:
    // Constructor: mengisi nama, kategori, dan jumlah awal.
    // Jika jumlah awal negatif, jumlah dijadikan 0.
    AlatLaboratorium(std::string nama, std::string kategori, int jumlah);

    // Getter (atribut bersifat private, jadi dibaca lewat method ini)
    std::string getNama() const;
    std::string getKategori() const;
    int getJumlah() const;

    // Menampilkan satu baris informasi alat.
    void tampilkanInfo() const;

    // Menambah jumlah. Mengembalikan false jika n <= 0 atau hasil melebihi batas int.
    bool tambahJumlah(int n);

    // Mengurangi jumlah. Mengembalikan false jika n <= 0 atau n > jumlah saat ini,
    // sehingga jumlah tidak pernah negatif.
    bool kurangiJumlah(int n);
};

#endif
