# Sisop-5-2025-IT-31

## Kelompok

Nama | NRP
--- | ---
Erlangga Valdhio Putra Sulistio | 5027241030
Rayhan Agnan Kusuma | 5027241102
S. Farhan Baig | 5027241097

## Daftar Isi

- [Kelompok](#kelompok)
- [Daftar Isi](#daftar-isi)
- [Soal](#soal)
- [Petunjuk Soal](#petunjuk-soal)
  - [Source](#source)
  - [Headers](#headers)
  - [Makefile](#makefile)
  - [Video Demonstrasi](#video-demonstrasi)
- [Laporan](#laporan)

## Soal

Pada suatu hari, anda merasa sangat lelah dari segala macam praktikum yang sudah ada, sehingga anda berencana untuk tidur yang nyenyak di sebuah jam 3:34AM yang cerah. Tetapi, anda terbangun di dalam dunia berbeda yang bernama "Eorzea". Ada sesuatu yang mengganggu pikiran anda sehingga anda diharuskan membuat sebuah operating system bernama "EorzeOS" untuk mendampingi diri anda dalam dunia ini.

1. Sebagai seorang main character dari dunia ini, ternyata anda memiliki kekuatan yang bernama "The Echo", kekuatan ini memungkinkan anda untuk berbicara pada Operating System ini (mungkin sebenarnya bukan ini kekuatannya, tetapi ini cukup kuat juga), dengan tujuan agar semua hal yang anda katakan, bila bukan merupakan sebuah command yang valid, akan mengulang hal yang anda katakan.

   Ilustrasi:
   ```
   user> Hello!
   Hello!
   user> I have the Echo
   I have the Echo
   ```

2. gurt: yo

   Ilustrasi:
   ```
   user> yo
   gurt
   user> gurt
   yo
   ```

3. Seorang main character memerlukan sebuah nama yang semua orang bisa ingat dengan baik. Buatlah sebuah command yang memungkinkan pengguna untuk mengubah nama user pada shell yang digunakan:
   * `user <username>` = mengubah username menjadi `<username>`
   * `user` = mengubah username menjadi default `user`
   
   Ilustrasi:
   ```
   user> user Tia
   Username changed to Tia
   Tia> user
   Username changed to user
   user>
   ```

4. Tiga negara besar dari Eorzean Alliance butuh bantuan anda untuk ikut serta dalam "Grand Company" mereka sehingga anda bisa mengubah warna terminal ajaib anda sesuai warna utama dari company mereka:
   * `grandcompany maelstrom` = clear terminal, ubah semua teks berikutnya jadi merah
   * `grandcompany twinadder` = clear terminal, ubah semua teks berikutnya jadi kuning
   * `grandcompany immortalflames` = clear terminal, ubah semua teks berikutnya jadi biru
   * `grandcompany <selain atau kosong>` = tunjukkan error message
   * `clear` = clear terminal, ubah semua teks berikutnya kembali jadi awal (para Grand Company sedih kamu netral)

   Selain mengubah seluruh warna terminal, nama anda di dalam terminal akan diberikan tambahan nama judul Grand Company:
   * Maelstrom = `user@Storm`
   * Twin Adder = `user@Serpent`
   * Immortal Flames = `user@Flame`
   * `clear` = menghapus nama grand company

   Ilustrasi:
   ```
   gurt> grandcompany maelstrom
   -- terminal clear menjadi warna merah --
   gurt@Storm> clear
   -- terminal clear menjadi warna putih --
   ```

5. Sebagai pahlawan terkenal di antara ketiga negara besar Eorzean Alliance, salah satu supplier senjata terbesar di seluruh Eorzea bernama "Rowena's House of Splendors" tiba-tiba memerlukan bantuan anda untuk membuat sebuah sistem kalkulator sederhana melalui command karena pemimpin mereka tertidur setelah mengurus semua orang di dalam Eorzea:
   * `add <x> <y>` = x + y
   * `sub <x> <y>` = x - y
   * `mul <x> <y>` = x * y
   * `div <x> <y>` = x / y

   Ilustrasi:
   ```
   user> add 4 2
   6
   user> sub 4 2
   2
   user> mul 3 -2
   -6
   user> div -6 -2
   3
   ```

6. me: yogurt
   
   gurt:
   * `yo`
   * `ts unami gng </3`
   * `sygau`

   pilih secara *random*

   Ilustrasi:
   ```
   user> yogurt
   gurt> yo
   user> yogurt
   gurt> ts unami gng </3
   user> yogurt
   gurt> sygau
   ```

8. Perusahaan mesin "Garlond Ironworks" tiba-tiba lelah mengurus permintaan senjata perang untuk orang ke-148649813234 yang berusaha menghadapi final boss yang sama, sehingga mereka perlu bantuan kamu untuk melengkapi `Makefile` yang diberikan dengan command-command yang sesuai untuk compile seluruh operating system ini.

## Petunjuk Soal

### Source

* [kernel.asm](src/kernel.asm)
  * `_putInMemory`: penjelasan terdapat dalam modul
  * `_interrupt`: fungsi untuk interrupt
    * `number`: interrupt vector number
    * `AX`,`BX`,`CX`,`DX`: register untuk diisi
    * `AX` merupakan kombinasi dari `AH` dan `AL`, pola ini juga berlaku untuk `BX`,`CX`, dan `DX`
    * Untuk menggabungkan jenis register `H` dan `L` menjadi `X` bisa menggunakan salah satu metode berikut:
      ```c
      AX = AH << 8 | AL    // first method
      AX = AH * 256 + AL   // second method
      ```
   * `getBiosTick`: fungsi untuk mendapatkan tick dari BIOS
* [kernel.c](src/kernel.c)
  * Diisi penerapan fungsi `printString`, `readString`, dan `clearScreen` dengan bantuan `kernel.asm`
    * untuk `printString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` dengan parameter `AH = 0x0E` untuk _teletype output_. Karakter yang ditampilkan dapat dimasukkan pada register `AL`. Fungsi ini akan menampilkan string karakter ASCII (_null-terminated_) ke layar.
    * untuk `readString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 16h` dengan parameter `AH = 0x00` untuk _keyboard input_. Fungsi ini akan membaca karakter ASCII (_non-control_) yang dimasukkan oleh pengguna dan menyimpannya pada buffer hingga menekan tombol `Enter`. Handle tombol `Backspace` dibebaskan kepada praktikan.
    * untuk `clearScreen`: Ukuran layar adalah `80x25` karakter. Setelah layar dibersihkan, kursor akan kembali ke posisi awal yaitu `(0, 0)` dan buffer video untuk warna karakter diubah ke warna putih. Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` atau menggunakan fungsi `putInMemory` untuk mengisi memori video.
* [shell.c](src/shell.c)
  * Diisi penerapan shell yang menggunakan fungsi kernel untuk parsing keseluruhan command yang diinput

### Headers

* [std_type.h](include/std_type.h)
  * `byte`: unsigned char data type, untuk angka 0-255 (`0x00`-`0xFF`)
  * `bool`: untuk boolean (true/false), karena boolean tidak built-in
* [std_lib.h](include/std_lib.h)
  * `div`: division
  * `mod`: modulo
  * Pembagian dan modulo tidak ada dalam assembly, sehingga harus dilengkapi dengan operator yang tersedia (`+`,`-`,`*`,`<<`,`>>`)
  * `strcmp`: membandingkan dua string
  * `strcpy`: copy string
  * `clear`: fill memory dengan `0`
  * `atoi`: alphanumeric to integer (string menjadi angka)
  * `itoa`: integer to alphanumeric (angka menjadi string)
* [kernel.h](include/kernel.h)
  * Deklarasi header untuk fungsi-fungsi dalam `kernel.c`
* [shell.h](include/shell.h)
  * Deklarasi header untuk fungsi-fungsi dalam `shell.c`

### Makefile

* [makefile](./makefile)
   * `prepare` : membuat disk image baru `floppy.img` pada direktori `bin/` dengan ukuran 1.44 MB.
   * `bootloader` : mengkompilasi `bootloader.asm` menjadi `bootloader.bin` pada direktori `bin/`.
   * `stdlib` : mengkompilasi `std_lib.c` menjadi `std_lib.o` pada direktori `bin/`.
   * `shell`: mengkompilasi `shell.c` menjadi `shell.o` pada direktori `bin/`.
   * `kernel` : mengkompilasi `kernel.c` menjadi `kernel.o` pada direktori `bin/` dan mengkompilasi `kernel.asm` menjadi `kernel_asm.o` pada direktori `bin/`.
   * `link` : menggabungkan `bootloader.bin`, `kernel.o`, `kernel_asm.o`, dan `std_lib.o` menjadi `floppy.img`.
   * `build` : menjalankan perintah `prepare`, `bootloader`, `stdlib`, `kernel`, dan `link`.

### Video Demonstrasi

[Akses Video dalam Assets](./assets/demo.mp4)

https://github.com/user-attachments/assets/1cfa66b1-b2f5-4e3e-a4b2-ec8b012f6fbb


## Laporan

 **Laporan Praktikum Sistem Operasi Modul 5: EorzeOS**

| | |
| :--- | :--- |
| **Nama** | `[Isi dengan Nama Lengkap Anda]` |
| **NRP** | `[Isi dengan NRP Anda]` |
| **Mata Kuliah** | Sistem Operasi |
| **Dosen Pengampu** | `[Isi dengan Nama Dosen Anda]` |

---

## **Daftar Isi**
1.  [Abstrak](#1-abstrak)
2.  [Struktur Proyek](#2-struktur-proyek)
3.  [Implementasi Fitur](#3-implementasi-fitur)
4.  [Analisis Implementasi Teknis](#4-analisis-implementasi-teknis)
    - [4.1. Bootloader](#41-bootloader---bootloaderasm)
    - [4.2. Kernel](#42-kernel---kernelc--kernelasm)
    - [4.3. Shell](#43-shell---shellc)
    - [4.4. Makefile](#44-makefile)
5.  [Langkah-langkah Penggunaan](#5-langkah-langkah-penggunaan)
6.  [Hasil dan Tangkapan Layar](#6-hasil-dan-tangkapan-layar)
7.  [Kesimpulan](#7-kesimpulan)

---

## **1. Abstrak**

Praktikum Modul 5 ini bertujuan untuk merancang dan mengimplementasikan sebuah sistem operasi 16-bit sederhana bernama **EorzeOS**. Proyek ini mencakup pengembangan komponen-komponen fundamental sistem operasi, mulai dari *bootloader* yang memuat sistem ke memori, *kernel* yang menyediakan layanan dasar untuk interaksi hardware, hingga *shell* sebagai antarmuka baris perintah (CLI) bagi pengguna. EorzeOS dilengkapi dengan berbagai fitur kustom sesuai tema yang diberikan, seperti kustomisasi prompt, perubahan warna terminal, kalkulator sederhana, dan perintah interaktif lainnya. Seluruh sistem dibangun menggunakan bahasa Assembly (NASM) untuk operasi tingkat rendah dan bahasa C (GCC 16-bit) untuk logika tingkat tinggi, serta diotomatisasi proses kompilasinya menggunakan `Makefile`.

---

## **2. Struktur Proyek**

Struktur direktori proyek dirancang secara modular untuk memisahkan kode sumber, file *header*, dan hasil *build*.

.
├── bin/
├── bochsrc.txt
├── include/
│   ├── kernel.h
│   ├── shell.h
│   ├── std_lib.h
│   └── std_type.h
├── makefile
└── src/
├── bootloader.asm
├── kernel.asm
├── kernel.c
├── shell.c
└── std_lib.c

- **`src/`**: Berisi seluruh kode sumber (`.c` dan `.asm`).
- **`include/`**: Berisi semua file *header* (`.h`) yang mendefinisikan *interface* antar modul.
- **`bin/`**: Direktori keluaran untuk semua berkas hasil kompilasi, termasuk *object files*, *binary*, dan *disk image* akhir.
- **`makefile`**: Mengatur seluruh alur kompilasi dan *linking*.
- **`bochsrc.txt`**: File konfigurasi untuk menjalankan sistem operasi pada emulator Bochs.

---

## **3. Implementasi Fitur**

Semua fitur yang disyaratkan dalam soal praktikum telah berhasil diimplementasikan.

| Fitur / Perintah | Deskripsi Implementasi | Ilustrasi Penggunaan |
| :--- | :--- | :--- |
| **The Echo** | Merupakan kasus *default* pada parser perintah di `shell.c`. Jika tidak ada perintah valid yang cocok, input pengguna akan dicetak kembali. | `user> I have the Echo`<br>`I have the Echo` |
| **`gurt` & `yo`** | Diimplementasikan dengan `strcmp()` untuk memeriksa input dan mencetak string balasan yang sudah ditentukan. | `user> gurt`<br>`yo` |
| **`user`** | Menggunakan variabel global `current_username` di `shell.c`. Perintah ini memodifikasi variabel tersebut menggunakan `strcpy()`. Prompt akan membaca variabel ini setiap kali ditampilkan. | `user> user Tia`<br>`Username changed to Tia` |
| **`grandcompany`** | Memvalidasi argumen (`maelstrom`, `twinadder`, `immortalflames`), lalu memanggil fungsi `setKernelTextAttribute()` dari kernel untuk mengatur warna, `strcpy()` untuk mengatur *suffix* prompt, dan `clearScreen()` untuk menerapkan perubahan. | `gurt> grandcompany maelstrom`<br>`-- terminal clear, warna jadi merah --` |
| **`clear`** | Mengembalikan atribut warna ke nilai *default* (`0x07`), mengosongkan *string suffix* Grand Company, dan memanggil `clearScreen()`. | `gurt@Storm> clear`<br>`-- terminal clear, warna jadi putih --` |
| **Kalkulator** | Mem-parsing dua argumen numerik dari input. Fungsi `atoi()` digunakan untuk konversi string ke integer, operasi aritmatika dilakukan, dan `itoa()` digunakan untuk mengonversi hasil kembali ke string untuk dicetak. | `user> mul 3 -2`<br>`-6` |
| **`yogurt`** | Menggunakan `_getBiosTick()` dari kernel sebagai *seed* untuk generator angka acak sederhana. Hasil modulo 3 dari angka acak tersebut digunakan untuk memilih salah satu dari tiga respons teks. | `user> yogurt`<br>`gurt> ts unami gng </3` |

---

## **4. Analisis Implementasi Teknis**

### **4.1. Bootloader - `bootloader.asm`**
*Bootloader* adalah program 512-byte yang bertanggung jawab untuk memulai sistem. Prosesnya adalah sebagai berikut:
1.  BIOS memuat *bootloader* dari sektor pertama *floppy disk* ke memori.
2.  *Bootloader* menggunakan layanan **BIOS Interrupt `0x13`** (Disk Services) untuk membaca sektor-sektor berikutnya yang berisi *kernel* dari *disk*.
3.  *Kernel* dimuat ke alamat fisik **`0x1000:0x0000`**.
4.  Setelah berhasil, *bootloader* melakukan `jump` ke alamat tersebut, menyerahkan kontrol sepenuhnya kepada *kernel*.

### **4.2. Kernel - `kernel.c` & `kernel.asm`**
*Kernel* adalah inti dari EorzeOS yang menyediakan abstraksi perangkat keras untuk aplikasi tingkat tinggi (*shell*).
-   **Interaksi Hardware (`kernel.asm`)**: Fungsi-fungsi krusial seperti `_interrupt` dan `_getBiosTick` ditulis dalam Assembly untuk dapat berinteraksi langsung dengan register CPU dan memanggil *interrupt* BIOS.
-   **Layanan Kernel (`kernel.c`)**:
    -   `printString()`: Mengiterasi *string* dan mencetak setiap karakter ke layar menggunakan *teletype output* dari **BIOS Interrupt `0x10` (Video Services)** dengan `AH = 0x0E`.
    -   `readString()`: Mengambil input per karakter dari **BIOS Interrupt `0x16` (Keyboard Services)**. Implementasi ini juga menangani *backspace* (`\b`) untuk menghapus karakter dari *buffer* dan layar.
    -   `clearScreen()`: Mengimplementasikan pembersihan layar dengan menulis langsung ke **Video Memory `0xB800`**. Setiap sel karakter (2 byte) diisi dengan spasi dan atribut warna teks saat ini (`KERNEL_CURRENT_TEXT_ATTRIBUTE`).

### **4.3. Shell - `shell.c`**
*Shell* bertindak sebagai *user interface*.
-   **Struktur**: Sebuah *loop* tak terbatas (`while(true)`) menjadi inti dari *shell*, yang secara berulang: menampilkan *prompt*, membaca input, mem-parsing, dan mengeksekusi.
-   **Parsing**: Fungsi `parseCommand()` bertanggung jawab memisahkan *string* input menjadi perintah utama dan maksimal dua argumen.
-   **Eksekusi**: Logika `if-else if` yang ekstensif digunakan untuk mencocokkan perintah dengan fungsi yang sesuai. Sebuah *flag* `command_executed` digunakan untuk melacak apakah sebuah perintah valid telah dijalankan, yang jika tidak, akan memicu fitur "The Echo".

### **4.4. Makefile**
Sesuai dengan poin 7, sebuah `Makefile` telah dibuat untuk mengotomatisasi proses *build*.
-   **Kompilator**: Menggunakan `nasm` untuk Assembly dan `i686-linux-gnu-gcc` sebagai *cross-compiler* C dengan *flag* `-m16` untuk menghasilkan kode 16-bit.
-   **Proses**:
    1.  Mengompilasi semua berkas `.c` dan `.asm` menjadi *object files* (`.o`).
    2.  Menyatukan (*link*) semua *object files* menjadi sebuah berkas *kernel* dalam format ELF.
    3.  Mengonversi berkas ELF menjadi *binary flat* (`.bin`).
    4.  Membuat *disk image* kosong (`floppy.img`).
    5.  Menulis `bootloader.bin` ke sektor pertama dan `kernel_image.bin` ke sektor berikutnya pada `floppy.img` menggunakan `dd`.

---

## **5. Langkah-langkah Penggunaan**

**Prasyarat**:
-   `make`
-   `nasm`
-   `i686-linux-gnu-gcc` (atau *cross-compiler* 16-bit lain)
-   Emulator `bochs`

**Perintah**:
1.  **Build Proyek**: Untuk mengompilasi semua kode dan membuat `floppy.img`.
    ```bash
    make build
    ```

2.  **Jalankan OS**: Untuk menjalankan `floppy.img` pada emulator Bochs.
    ```bash
    make run
    ```

3.  **Bersihkan Build**: Untuk menghapus semua berkas hasil kompilasi.
    ```bash
    make clean
    ```
---

## **6. Hasil dan Tangkapan Layar**

Berikut adalah tangkapan layar yang mendokumentasikan fungsionalitas EorzeOS.

**1. Tampilan Awal dan Fitur Echo**
*Tampilan saat EorzeOS pertama kali dijalankan, menunjukkan prompt default dan respons "Echo" saat perintah tidak valid dimasukkan.*
`[SISIPKAN GAMBAR DI SINI]`

**2. Kustomisasi User dan Perintah Interaktif**
*Menunjukkan perubahan prompt setelah perintah `user Tia` dan contoh output dari perintah `gurt` dan `yogurt`.*
`[SISIPKAN GAMBAR DI SINI]`

**3. Fitur Kalkulator**
*Contoh penggunaan perintah `add`, `sub`, `mul`, dan `div`, termasuk dengan bilangan negatif.*
`[SISIPKAN GAMBAR DI SINI]`

**4. Fitur Grand Company**
*Kolase gambar yang menunjukkan perubahan warna terminal dan prompt untuk `maelstrom` (merah), `twinadder` (kuning), `immortalflames` (biru), dan setelah `clear`.*
`[SISIPKAN GAMBAR DI SINI]`

---

## **7. Kesimpulan**

Proyek EorzeOS telah berhasil diimplementasikan sesuai dengan semua spesifikasi yang diberik
