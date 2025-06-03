#include "kernel.h" 

static byte KERNEL_CURRENT_TEXT_ATTRIBUTE = 0x07; 

void setKernelTextAttribute(byte attribute) {
    KERNEL_CURRENT_TEXT_ATTRIBUTE = attribute;
}

int main() {
    clearScreen();   
    shell();        

    while (true);
    return 0;
}

void printString(char *str) {
    int i = 0;
    int ax_val;

    while (str[i] != '\0') {
        ax_val = (0x0E << 8) | str[i]; 
        _interrupt(0x10, ax_val, 0, 0, 0);
        i++;
    }
}

void readString(char *buf) {
    int i = 0;
    char c;
    int ax_val;

    while (true) {
        ax_val = _interrupt(0x16, 0x0000, 0, 0, 0);
        c = (char)(ax_val & 0xFF);

        if (c == '\r') { 
            buf[i] = '\0'; 
            printString("\r\n");
            return;
        } else if (c == '\b') {
            if (i > 0) {
                i--;
                printString("\b \b");
            }
        } else if (c >= ' ' && c <= '~') { 
            buf[i] = c;
            i++;

     
            ax_val = (0x0E << 8) | c;
            _interrupt(0x10, ax_val, 0, 0, 0);
        }
       
    }
}

void clearScreen() {
    int i;
    for (i = 0; i < 25 * 80; i++) {
        _putInMemory(0xB800, i * 2, ' ');
        _putInMemory(0xB800, i * 2 + 1, KERNEL_CURRENT_TEXT_ATTRIBUTE);
    }


    _interrupt(0x10, 0x0200, 0, 0, 0);
}
