#!/bin/bash
# Uji otomatis berbasis input: menjalankan program dengan skenario dan memeriksa output.
BIN=./inventaris
gagal=0

jalankan() {  # $1 = nama uji, $2 = input, sisanya = teks yang harus muncul
  local nama="$1" input="$2"; shift 2
  local out
  out=$(printf "%b" "$input" | $BIN 2>&1)
  for pola in "$@"; do
    # Pola berawalan "~" dibaca sebagai regex; selain itu dicocokkan apa adanya.
    if [[ "$pola" == "~"* ]]; then
      cocok() { grep -qE -- "${pola#\~}" <<<"$out"; }
    else
      cocok() { grep -qF -- "$pola" <<<"$out"; }
    fi
    if ! cocok; then
      echo "GAGAL  $nama  (tidak ditemukan: $pola)"
      gagal=$((gagal+1))
      return
    fi
  done
  echo "LULUS  $nama"
}

jalankan "T1 tambah alat dan tampilkan" \
  "1\nMikroskop\nOptik\n5\n4\n0\n" \
  "[SUKSES] Alat 'Mikroskop' ditambahkan." "Mikroskop" "Optik"

jalankan "T2 tambah jumlah" \
  "1\nMultimeter\nListrik\n3\n2\n1\n4\n4\n0\n" \
  "Jumlah Multimeter sekarang 7."

jalankan "T3 kurangi jumlah" \
  "1\nTabung Reaksi\nGelas\n10\n3\n1\n4\n0\n" \
  "Jumlah Tabung Reaksi sekarang 6."

jalankan "T4 kurangi melebihi jumlah ditolak, tidak negatif" \
  "1\nMikroskop\nOptik\n2\n3\n1\n5\n4\n0\n" \
  "[GAGAL] Jumlah pengurangan harus lebih dari 0" "~^1 +Mikroskop +Optik +2$"

jalankan "T5 jumlah awal negatif ditolak" \
  "1\nPipet\nGelas\n-5\n4\n0\n" \
  "[GAGAL] Jumlah awal tidak boleh negatif." "Daftar alat masih kosong."

jalankan "T6 input huruf pada jumlah ditolak" \
  "1\nPipet\nGelas\nabc\n0\n" \
  "[GAGAL] Jumlah harus berupa bilangan bulat."

jalankan "T7 input desimal ditolak" \
  "1\nPipet\nGelas\n2.5\n0\n" \
  "[GAGAL] Jumlah harus berupa bilangan bulat."

jalankan "T8 duplikat nama+kategori (abaikan huruf besar/kecil)" \
  "1\nMikroskop\nOptik\n1\n1\n  mikroskop \nOPTIK\n9\n4\n0\n" \
  "sudah terdaftar" "~^1 +Mikroskop +Optik +1$"

jalankan "T9 nama sama kategori beda dianggap alat lain" \
  "1\nLensa\nOptik\n1\n1\nLensa\nKamera\n1\n4\n0\n" \
  "Optik" "Kamera"

jalankan "T10 tambah jumlah nol atau negatif ditolak" \
  "1\nPipet\nGelas\n4\n2\n1\n0\n2\n1\n-3\n0\n" \
  "[GAGAL] Jumlah tambahan harus lebih dari 0"

jalankan "T11 nomor alat tidak valid" \
  "1\nPipet\nGelas\n4\n2\n7\n0\n" \
  "[GAGAL] Nomor alat tidak ada dalam daftar."

jalankan "T12 menu bukan angka dan menu tidak tersedia" \
  "halo\n9\n0\n" \
  "[PERINGATAN] Input harus berupa angka." "[PERINGATAN] Pilihan menu tidak tersedia."

jalankan "T13 ubah jumlah saat daftar kosong" \
  "2\n3\n0\n" \
  "Daftar alat masih kosong. Tambahkan alat terlebih dahulu."

jalankan "T14 input habis (EOF) tidak membuat program menggantung" \
  "1\nPipet\n" \
  "Nama alat"

jalankan "T15 batas int: tambah melebihi INT_MAX ditolak" \
  "1\nPipet\nGelas\n2147483647\n2\n1\n1\n4\n0\n" \
  "[GAGAL] Jumlah tambahan harus lebih dari 0 dan tidak melebihi batas."

echo "----"
[ "$gagal" -eq 0 ] && echo "Semua uji lulus." || echo "$gagal uji gagal."
exit $gagal
