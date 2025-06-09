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

# Laporan Praktikum Sistem Operasi Modul 5: EorzeOS

## Deskripsi Umum

**EorzeOS** adalah sistem operasi sederhana yang dibuat untuk memenuhi serangkaian tugas yang diberikan dalam soal praktikum. OS ini memiliki shell interaktif yang mampu menangani berbagai perintah, mulai dari input/output sederhana, kustomisasi user dan terminal, hingga operasi aritmatika dasar dan output acak. Proyek ini dibangun menggunakan Assembly (NASM) untuk bootloader dan fungsi kernel level rendah, serta bahasa C untuk logika kernel dan shell. Proses kompilasi dan linking diatur oleh sebuah `Makefile` untuk mempermudah proses build.

---

## Implementasi Fitur dan Penjelasan Kode

Berikut adalah penjelasan untuk setiap fitur yang diimplementasikan sesuai dengan soal praktikum.

### 1. The Echo: Menangani Perintah Tidak Valid

**Soal:** Kekuatan "The Echo" diimplementasikan sebagai mekanisme fallback di dalam loop utama shell(). Jika perintah yang dimasukkan pengguna tidak cocok dengan perintah valid manapun (yo, gurt, user, grandcompany, clear, dll.), sistem akan mencetak kembali string perintah yang dimasukkan oleh pengguna, sesuai dengan ilustrasi pada soal.

**Implementasi:** Kekuatan "The Echo" diimplementasikan sebagai mekanisme fallback di dalam loop utama shell(). Jika perintah yang dimasukkan pengguna tidak cocok dengan perintah valid manapun (yo, gurt, user, grandcompany, clear, dll.), sistem akan mencetak kembali string perintah yang dimasukkan oleh pengguna, sesuai dengan ilustrasi pada soal.

**Cuplikan Kode (`src/shell.c`):**

```c
// src/shell.c

// ... di dalam loop while(true)
if (strcmp(cmd, "yo")) { /* ... */ }
// ... (kondisi-kondisi lain)
else if (cmd[0] != '\0') {
    // Jika command tidak kosong dan tidak dikenali, cetak kembali (The Echo)
    printString(buf);
    printString("\n");
}

```

### 2. Perintah gurt dan yo

**Soal:** Membuat perintah gurt yang menghasilkan output yo, dan yo yang menghasilkan output gurt.

**Implementasi:** Implementasi dua perintah ini sangat sederhana, yaitu menggunakan if-else if untuk membandingkan string perintah dan mencetak respons yang sesuai.

**Cuplikan Kode (`src/shell.c`):**

```c
// src/shell.c

if (strcmp(cmd, "yo")) {
    printString("gurt\n");
} else if (strcmp(cmd, "gurt")) {
    printString("yo\n");
}
```

### 3. Perintah user untuk Mengubah Username

**Soal:**

* `user <username>`: Mengubah nama user pada shell.
* `user`: Mengembalikan nama user ke "user".

**Implementasi:** Perintah user ditangani oleh fungsi handle_user(char* new_user). Fungsi ini memeriksa apakah argumen pertama (new_user) kosong.

*Jika kosong, nama pengguna di-reset ke "user".

*Jika tidak kosong, nama pengguna akan diubah sesuai dengan argumen yang diberikan.

**Cuplikan Kode (`src/shell.c`):**

```c
// src/shell.c

void handle_user(char* new_user) {
    if (new_user[0] == '\0') {
        strcpy(username, "user");
        printString("Username changed to default\n");
    } else {
        strcpy(username, new_user);
        printString("Username changed to ");
        printString(new_user);
        printString("\n");
    }
}
```

### 4. Grand Company: Kustomisasi Terminal

**Soal:** Perintah `grandcompany` untuk mengubah warna teks, membersihkan layar, dan menambahkan suffix pada prompt. Perintah `clear` untuk mengembalikan ke pengaturan default.

**Implementasi:**

*Perintah grandcompany <nama> berfungsi untuk mengubah warna teks terminal dan menambahkan suffix pada prompt.

*Mekanisme Perubahan Warna: Menggunakan interrupt 0x10 dengan service 0x06 (scroll/clear window). Atribut warna (misal: merah 0x04) disisipkan ke register BH untuk diaplikasikan ke seluruh layar.

*Perubahan Suffix: Menggunakan strcpy untuk mengubah variabel global company_suffix.

*Perintah clear: Memanggil clearScreen() untuk mengembalikan layar ke warna default (putih) dan mengosongkan company_suffix.

**Cuplikan Kode (`src/shell.c`):**

```c
void handle_grandcompany(char* company) {
    byte new_color;
    char* new_suffix = "";

    if (strcmp(company, "maelstrom")) {
        new_color = 0x04;
        new_suffix = "@Storm";
    } else if (strcmp(company, "twinadder")) {
        new_color = 0x0E;
        new_suffix = "@Serpent";
    } else if (strcmp(company, "immortalflames")) {
        new_color = 0x01; 
        new_suffix = "@Flame";
    } else {
        printString("Invalid Grand Company. Choose: maelstrom, twinadder, or immortalflames.\n");
        return;
    }
    
    interrupt(0x10, 0x0600, new_color << 8, 0x0000, 0x184F);
    interrupt(0x10, 0x0200, 0x0000, 0x0000, 0); 
    strcpy(company_suffix, new_suffix);
}
```

### 5. Kalkulator Sederhana Rowena

**Soal:** Implementasi perintah `add`, `sub`, `mul`, `div`.

**Implementasi:**

*Keempat operasi ini ditangani oleh satu fungsi handle_calc().

*Perintah diparsing untuk mendapatkan operator (add, sub, dll.) dan dua argumen string.

*Fungsi atoi() digunakan untuk mengubah argumen string menjadi integer. Fungsi ini juga mampu menangani angka negatif.

*Hasil kalkulasi diubah kembali menjadi string menggunakan itoa() untuk ditampilkan ke layar.

*Ada penanganan khusus untuk pembagian dengan nol.

**Cuplikan Kode (`src/shell.c`):**

```c
void handle_calc(char* op, char* arg1_str, char* arg2_str) {
    int num1, num2, result;
    char result_str[12];

    if (arg1_str[0] == '\0' || arg2_str[0] == '\0') {
        printString("Error: Missing arguments for calculation.\n");
        return;
    }

    atoi(arg1_str, &num1);
    atoi(arg2_str, &num2);

    if (strcmp(op, "add")) {
        result = num1 + num2;
    } else if (strcmp(op, "sub")) {
        result = num1 - num2;
    } else if (strcmp(op, "mul")) {
        result = num1 * num2;
    } else if (strcmp(op, "div")) {
        if (num2 == 0) {
            printString("Error: Division by zero.\n");
            return;
        }
        result = div(num1, num2);
    }

    itoa(result, result_str);
    printString(result_str);
    printString("\n");
}

```

### 6. Perintah yogurt dengan Output Acak

**Soal:** Perintah `yogurt` akan menampilkan salah satu dari tiga pesan secara acak.

**Implementasi:**

Perintah yogurt memberikan salah satu dari tiga respons secara acak.

*Generator Angka Acak (PRNG): Dibuat sebuah fungsi rand() sederhana menggunakan algoritma Linear Congruential Generator (LCG) yang aman untuk aritmatika 16-bit.

*Keacakan Ditingkatkan: Untuk memastikan hasil yang berbeda setiap kali dijalankan, seed dari PRNG diinisialisasi dengan getBiosTick() saat shell pertama kali berjalan. Selanjutnya, setiap kali rand() dipanggil, nilai seed juga dicampur dengan nilai getBiosTick() saat itu juga.

*Pemilihan Respons: Hasil dari mod(rand(), 3) digunakan dalam switch-case untuk memilih respons yang akan dicetak.

**Cuplikan Kode (`src/shell.c`):**

```c
void handle_yogurt() {
    int random_num;

    random_num = mod(rand(), 3);

    printString("gurt > ");
    switch (random_num) {
        case 0:
            printString("yo\n");
            break;
        case 1:
            printString("ts unami gng </3\n");
            break;
        case 2:
            printString("sygau\n");
            break;
    }
}
```


### 7. Make file


**Implementasi:**

Makefile telah dilengkapi untuk mengotomatisasi seluruh proses kompilasi dan linking.

prepare: Membuat direktori bin/ dan image floppy floppy.img.

bootloader: Mengompilasi bootloader.asm.

stdlib, shell, kernel: Mengompilasi masing-masing file C dan Assembly menjadi file objek.

link: Menggabungkan semua file objek menjadi kernel.sys menggunakan ld86, lalu menulis bootloader.bin dan kernel.sys ke dalam floppy.img menggunakan dd.

build: Menjalankan semua target di atas secara berurutan.


```c
# Makefile (Contoh target link)
link:
	ld86 -o bin/kernel.sys -d bin/kernel.o bin/kernel_asm.o bin/shell.o bin/std_lib.o
	dd if=bin/bootloader.bin of=bin/floppy.img bs=512 count=1 conv=notrunc
	dd if=bin/kernel.sys of=bin/floppy.img bs=512 seek=1 conv=notrunc
```

**Cara Kompilasi dan Menjalankan**

Prasyarat: Pastikan nasm, bcc, dan bochs sudah terinstal di sistem Anda.

Kompilasi: Buka terminal pada direktori utama proyek, lalu jalankan perintah:

```sudo make build ```

Perintah ini akan secara otomatis melakukan semua langkah yang diperlukan dan menghasilkan file bin/floppy.img.

Menjalankan: Setelah proses build selesai, jalankan EorzeOS pada emulator Bochs dengan perintah:

```bochs -f bochsrc.txt```

Sebuah jendela emulator akan muncul dan EorzeOS akan berjalan.

### 8. Dokumentasi Pengerjaan



https://github.com/user-attachments/assets/aabe3f32-141a-45da-9a6c-cb7548856280





