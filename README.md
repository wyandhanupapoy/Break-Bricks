# Skor

## Nama Pembuat
Siti Soviyyah

## Nama Fitur
Skor

## Deskripsi Fitur
Fitur ini berguna untuk menampilkan skor yang diperoleh pemain selama permainan. Skor dihitung berdasarkan waktu bermain, di mana semakin lama pemain bermain, semakin sedikit skor yang diperoleh. Perhitungan skor dilakukan dengan mengurangi nilai maksimum skor per blok berdasarkan waktu yang telah berlalu, dengan batas minimum tertentu. Fitur ini juga mencakup tampilan skor pada layar permainan.

### Fungsi Utama:
- `InitSkor(Skor skor[MAX_PLAYERS])` → Menginisialisasi skor awal pemain.
- `TambahSkorDenganWaktu(Skor *skor, float elapsedTime)` → Menambah skor pemain dengan mempertimbangkan waktu yang berlalu.
- `DrawSkor(Skor skor[MAX_PLAYERS], int x, int y)` → Menampilkan skor pemain di layar.

Fitur ini menggunakan Raylib untuk menampilkan skor secara grafis dan berinteraksi dengan sistem permainan.