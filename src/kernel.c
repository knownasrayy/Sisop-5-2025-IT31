#include "shell.h"
#include "kernel.h"


int main() {
  clearScreen();     
  printString("Welcome to EorzeOS, Warrior of Light!\n");
  shell();      
}


void printString(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            interrupt(0x10, 0x0E00 | '\r', 0, 0, 0); 
            interrupt(0x10, 0x0E00 | '\n', 0, 0, 0); 
        } else {

            interrupt(0x10, 0x0E00 | str[i], 0, 0, 0);
        }
        i++;
    }
}



void readString(char *buf) {
    int i = 0;
    char c;

    while (true) {

        c = interrupt(0x16, 0x00, 0, 0, 0);

        if (c == '\r') { 
            buf[i] = '\0';
            printString("\n");
            return;
        } else if (c == '\b') { 
            if (i > 0) {
                i--;
                printString("\b"); 
                printString(" ");  
                printString("\b");
            }
        } else { 
            buf[i] = c;
            interrupt(0x10, 0x0E00 | c, 0, 0, 0);
            i++;
        }
    }
}


void clearScreen() {
    // Service 0x06: Scroll up/clear window
    // AL = 0x00: Jumlah baris untuk di-scroll (0 = seluruh window)
    // BH = 0x07: Atribut warna (putih di atas hitam)
    // CX = 0x0000: Posisi awal (baris 0, kolom 0)
    // DX = 0x184F: Posisi akhir (baris 24, kolom 79)
    interrupt(0x10, 0x0600, 0x0700, 0x0000, 0x184F);

    // Service 0x02: Set cursor position
    // BH = 0x00: Page number
    // DH = 0x00: Baris 0
    // DL = 0x00: Kolom 0
    interrupt(0x10, 0x0200, 0x0000, 0x0000, 0);
}
