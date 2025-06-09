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

Dibuat sebagai pemenuhan tugas Praktikum Sistem Operasi tentang pembuatan shell sederhana dengan fitur-fitur kustom di atas kernel dasar.

**Disusun oleh:**
- **Nama:** [Nama Anda]
- **NRP:** [NRP Anda]
- **Kelas:** [Kelas Anda]

---

## Deskripsi Umum

**EorzeOS** adalah sistem operasi sederhana yang dibuat untuk memenuhi serangkaian tugas yang diberikan dalam soal praktikum. OS ini memiliki shell interaktif yang mampu menangani berbagai perintah, mulai dari input/output sederhana, kustomisasi user dan terminal, hingga operasi aritmatika dasar dan output acak. Proyek ini dibangun menggunakan Assembly (NASM) untuk bootloader dan fungsi kernel level rendah, serta bahasa C untuk logika kernel dan shell. Proses kompilasi dan linking diatur oleh sebuah `Makefile` untuk mempermudah proses build.

---

## Implementasi Fitur dan Penjelasan Kode

Berikut adalah penjelasan untuk setiap fitur yang diimplementasikan sesuai dengan soal praktikum.

### 1. The Echo: Menangani Perintah Tidak Valid

**Soal:** Jika input dari pengguna bukan merupakan sebuah command yang valid, sistem akan mengulang kembali input tersebut.

**Implementasi:** Logika ini diimplementasikan di dalam loop utama `shell()` di `src/shell.c`. Sebuah variabel `bool command_executed` (bertipe `char`) digunakan sebagai flag. Flag ini diinisialisasi sebagai `false` di setiap awal iterasi loop. Jika sebuah perintah valid dieksekusi (misalnya, `yo`, `user`, `add`, dll.), flag ini akan diubah menjadi `true`. Di akhir loop, ada pengecekan: jika `command_executed` masih `false`, maka input asli pengguna akan dicetak kembali ke layar.

**Cuplikan Kode (`src/shell.c`):**
```c
void shell() {
    char buf[128];
    // ... deklarasi variabel lain ...
    char command_executed;

    // ... inisialisasi shell ...

    while (true) {
        command_executed = false; // Reset flag di setiap iterasi

        printString(current_username);
        // ... print prompt ...
        readString(buf);
        parseCommand(buf, cmd, args);

        // Rangkaian if-else if untuk command valid
        if (strcmp(cmd, "yo") == true) {
            printString("gurt\n");
            command_executed = true; // Set flag jika command valid
        } else if (strcmp(cmd, "gurt") == true) {
            // ...
            command_executed = true;
        } // ... dan seterusnya untuk command lain

        // Blok "The Echo"
        if (command_executed == false) {
            printString(buf); // Cetak kembali input jika tidak ada command yang dieksekusi
            printString("\n");
        }
    }
}
2. Perintah gurt dan yo
Soal: Membuat perintah gurt yang menghasilkan output yo, dan yo yang menghasilkan output gurt.

Implementasi: Di dalam shell.c, dua blok if-else if ditambahkan untuk menangani kedua perintah ini. Fungsi strcmp dari std_lib.c digunakan untuk membandingkan input dengan string "gurt" dan "yo".

Cuplikan Kode (src/shell.c):

C

// ... di dalam loop while(true) pada fungsi shell() ...
if (strcmp(cmd, "yo") == true) {
    printString("gurt\n");
    command_executed = true;
} else if (strcmp(cmd, "gurt") == true) {
    printString("yo\n");
    command_executed = true;
}
// ...
3. Perintah user untuk Mengubah Username
Soal:

user <username>: Mengubah nama user pada shell.
user: Mengembalikan nama user ke "user".
Implementasi: Sebuah variabel global current_username digunakan untuk menyimpan nama pengguna saat ini. Perintah user diperiksa menggunakan strcmp. Jika ada argumen (args[0][0] != '\0'), nama pengguna diubah sesuai argumen menggunakan strcpy. Jika tidak ada argumen, nama pengguna direset kembali ke "user".

Cuplikan Kode (src/shell.c):

C

// Variabel global
char current_username[64];

// ... di dalam loop while(true) pada fungsi shell() ...
else if (strcmp(cmd, "user") == true) {
    if (args[0][0] == '\0') { // Tidak ada argumen
        strcpy(current_username, "user");
        printString("Username changed to user\n");
    } else { // Ada argumen
        strcpy(current_username, args[0]);
        printString("Username changed to "); 
        printString(current_username); 
        printString("\n");
    }
    command_executed = true;
}
4. Grand Company: Kustomisasi Terminal
Soal: Perintah grandcompany untuk mengubah warna teks, membersihkan layar, dan menambahkan suffix pada prompt. Perintah clear untuk mengembalikan ke pengaturan default.

Implementasi:

Warna: Kode warna didefinisikan sebagai konstanta (#define). Fungsi setKernelTextAttribute() (di kernel.c) dipanggil untuk mengubah atribut warna teks global.
Suffix Prompt: Variabel global grand_company_suffix digunakan untuk menyimpan suffix. strcpy digunakan untuk mengubahnya.
Clear Screen: Fungsi clearScreen() dipanggil untuk membersihkan layar.
Perintah grandcompany: Memeriksa argumen pertama (args[0]) untuk "maelstrom", "twinadder", atau "immortalflames". Jika valid, ia akan memanggil setKernelTextAttribute(), clearScreen(), dan strcpy() untuk suffix. Jika tidak, pesan error ditampilkan.
Perintah clear: Mereset warna ke default, membersihkan layar, dan mengosongkan suffix.
Cuplikan Kode (src/shell.c):

C

// Definisi warna dan variabel global
#define COLOR_DEFAULT        0x07 // Putih
#define COLOR_MAELSTROM      0x04 // Merah
#define COLOR_TWINADDER      0x0E // Kuning
#define COLOR_IMMORTALFLAMES 0x01 // Biru

char grand_company_suffix[16];

// ... di dalam loop while(true) pada fungsi shell() ...
else if (strcmp(cmd, "grandcompany") == true) {
    char gc_valid = false;
    if (strcmp(args[0], "maelstrom") == true) {
        setKernelTextAttribute(COLOR_MAELSTROM); 
        clearScreen(); 
        strcpy(grand_company_suffix, "@Storm"); 
        gc_valid = true;
    } else if (strcmp(args[0], "twinadder") == true) {
        setKernelTextAttribute(COLOR_TWINADDER); 
        clearScreen(); 
        strcpy(grand_company_suffix, "@Serpent"); 
        gc_valid = true;
    } else if (strcmp(args[0], "immortalflames") == true) {
        setKernelTextAttribute(COLOR_IMMORTALFLAMES); 
        clearScreen(); 
        strcpy(grand_company_suffix, "@Flame"); 
        gc_valid = true;
    }
    if (gc_valid == false) {
        printString("Error: Invalid Grand Company specified.\n");
    }
    command_executed = true;
} else if (strcmp(cmd, "clear") == true) {
    setKernelTextAttribute(COLOR_DEFAULT); 
    clearScreen(); 
    grand_company_suffix[0] = '\0'; // Kosongkan suffix
    command_executed = true;
}
5. Kalkulator Sederhana Rowena
Soal: Implementasi perintah add, sub, mul, div.

Implementasi: Sebuah blok if-else if tunggal memeriksa keempat perintah kalkulator.

Memeriksa apakah kedua argumen (args[0] dan args[1]) tersedia.
Menggunakan atoi() (dari std_lib.c) untuk mengubah argumen string menjadi integer.
Melakukan operasi matematika yang sesuai.
Untuk div, ada pengecekan khusus untuk menghindari pembagian dengan nol.
Hasil integer dikonversi kembali ke string menggunakan itoa() (dari std_lib.c) dan dicetak.
Cuplikan Kode (src/shell.c):

C

// ... di dalam loop while(true) pada fungsi shell() ...
else if (strcmp(cmd, "add") == true || strcmp(cmd, "sub") == true || strcmp(cmd, "mul") == true || strcmp(cmd, "div") == true) {
    if (args[0][0] == '\0' || args[1][0] == '\0') {
        printString("Error: Calculator commands require two arguments.\n");
    } else {
        int val1, val2, result_val;
        char calc_error = false;
        
        atoi(args[0], &val1); 
        atoi(args[1], &val2);

        if (strcmp(cmd, "add") == true) result_val = val1 + val2;
        else if (strcmp(cmd, "sub") == true) result_val = val1 - val2;
        else if (strcmp(cmd, "mul") == true) result_val = val1 * val2;
        else if (strcmp(cmd, "div") == true) {
            if (val2 == 0) {
                printString("Error: Division by zero.\n"); 
                calc_error = true;
            } else {
                result_val = div(val1, val2);
            }
        }

        if (calc_error == false) {
            char result_str[16];
            itoa(result_val, result_str); 
            printString(result_str); 
            printString("\n");
        }
    }
    command_executed = true;
}
6. Perintah yogurt dengan Output Acak
Soal: Perintah yogurt akan menampilkan salah satu dari tiga pesan secara acak.

Implementasi:

Seed Generator: Di awal shell(), random_seed diinisialisasi menggunakan _getBiosTick(), sebuah fungsi assembly yang mengambil tick clock dari BIOS. Ini memastikan urutan acak yang berbeda setiap kali OS di-boot.
Random Number Generator: Fungsi simple_rand() dan get_random_int() diimplementasikan untuk menghasilkan angka acak menggunakan algoritma Linear Congruential Generator (LCG).
Handler Perintah: Ketika yogurt dipanggil, get_random_int(3) menghasilkan angka 0, 1, atau 2. Sebuah struktur if-else if-else kemudian memilih pesan yang sesuai untuk ditampilkan.
Cuplikan Kode (src/shell.c):

C

// Variabel global dan fungsi random
unsigned int random_seed;

int simple_rand() {
    random_seed = random_seed * 1103515245 + 12345;
    return (unsigned int)(random_seed / 65536) % 32768;
}

int get_random_int(int max_val) {
    if (max_val <= 0) return 0;
    return simple_rand() % max_val;
}

void shell() {
    // ...
    random_seed = _getBiosTick(); // Inisialisasi seed di awal
    // ...
    while (true) {
        // ...
        else if (strcmp(cmd, "yogurt") == true) {
            int choice = get_random_int(3); // Dapat 0, 1, atau 2
            printString("gurt> ");
            if (choice == 0) printString("yo\n");
            else if (choice == 1) printString("ts unami gng </3\n");
            else printString("sygau\n");
            command_executed = true;
        }
        // ...
    }
}
7. Makefile
Soal: Melengkapi Makefile untuk mengompilasi dan menggabungkan seluruh komponen OS.

Implementasi: Makefile yang disediakan sudah sangat lengkap dan terstruktur dengan baik untuk menangani proses build.

Variabel: Mendefinisikan compiler (CC), assembler (NASM), linker (LD), dan flag yang dibutuhkan.
Targets:
prepare: Membuat file image floppy disk kosong (floppy.img) menggunakan dd.
bootloader: Mengompilasi bootloader.asm menjadi file biner bootloader.bin.
stdlib, shell, kernel: Mengompilasi file-file C (.c) dan Assembly (.asm) menjadi file objek (.o). Target ini memiliki dependensi ke file header (.h) terkait.
link_kernel_elf: Menggabungkan semua file objek (.o) menjadi sebuah file ELF (kernel.elf) menggunakan linker ld.
convert_kernel_to_bin: Mengubah file kernel.elf menjadi format biner murni (kernel_image.bin) menggunakan objcopy.
link_to_floppy: Menulis bootloader.bin ke sektor pertama dari floppy.img dan kernel_image.bin ke sektor-sektor berikutnya menggunakan dd.
build: Target utama yang menjalankan semua langkah di atas secara berurutan.
run: Menjalankan OS di emulator Bochs.
clean: Menghapus semua file yang dihasilkan dari proses build.
Cuplikan Kode (makefile):

Makefile

# ... (definisi variabel) ...

# Target utama yang menjalankan semua langkah
build: prepare bootloader stdlib shell kernel_objects link_kernel_elf convert_kernel_to_bin link_to_floppy
	@echo "EorzeOS build complete!"

# Menggabungkan bootloader dan kernel ke image floppy
link_to_floppy: $(BOOTLOADER_BIN) $(KERNEL_IMAGE_BIN)
	@echo "Menggabungkan bootloader dan kernel ke floppy image: <span class="math-inline">\(FLOPPY\_IMG\)\.\.\."
@dd if\=</span>(BOOTLOADER_BIN) of=<span class="math-inline">\(FLOPPY\_IMG\) conv\=notrunc status\=none
@dd if\=</span>(KERNEL_IMAGE_BIN) of=$(FLOPPY_IMG) seek=1 conv=notrunc status=none
# ... (target lainnya) ...

run: $(FLOPPY_IMG)
	@echo "Menjalankan EorzeOS di Bochs..."
	@bochs -f bochsrc.txt -q
Cara Build dan Menjalankan
Untuk melakukan kompilasi dan menjalankan EorzeOS, pastikan Anda memiliki nasm, bochs, dan toolchain i686-linux-gnu (termasuk gcc, ld, objcopy).

Build OS:
Buka terminal di direktori root proyek dan jalankan perintah:

Bash

make build
Perintah ini akan secara otomatis mengompilasi semua sumber kode dan membuat bin/floppy.img.

Jalankan OS:
Setelah proses build selesai, jalankan OS di emulator Bochs dengan perintah:

Bash

make run
Bersihkan File Hasil Build:
Untuk menghapus semua file yang dihasilkan oleh kompilator, jalankan:

Bash

make clean
Screenshot Hasil (Ilustrasi Teks)
Berikut adalah ilustrasi sesi terminal yang menunjukkan fungsionalitas EorzeOS.

Sesi Awal & Fitur Echo
Welcome to EorzeOS!
user> Hello world!
Hello world!
user> yo
gurt
user> gurt
yo
Kustomisasi User & Grand Company
user> user Alphinaud
Username changed to Alphinaud
Alphinaud> grandcompany maelstrom
-- (Layar dibersihkan, teks menjadi merah) --
Alphinaud@Storm> add 100 50
150
Alphinaud@Storm> clear
-- (Layar dibersihkan, teks kembali putih) --
Alphinaud> user
Username changed to user
user>
Kalkulator & Perintah Acak
user> add 5 3
8
user> sub 10 -2
12
user> mul -4 5
-20
user> div 10 0
Error: Division by zero.
user> div -9 3
-3
user> yogurt
gurt> ts unami gng </3
user> yogurt
gurt> yo
