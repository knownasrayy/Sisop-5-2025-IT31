#include "shell.h"   
#include "kernel.h"   
#include "std_lib.h"

char current_username[64];
char grand_company_suffix[16];
unsigned int random_seed;

#define COLOR_DEFAULT       0x07
#define COLOR_MAELSTROM     0x04
#define COLOR_TWINADDER     0x0E
#define COLOR_IMMORTALFLAMES 0x01

int simple_rand() {
    random_seed = random_seed * 1103515245 + 12345;
    return (unsigned int)(random_seed / 65536) % 32768;
}

int get_random_int(int max_val) {
    if (max_val <= 0) return 0;
    return simple_rand() % max_val;
}

void parseCommand(char *buf, char *cmd, char arg[2][64]) {
    int i = 0;
    int j = 0;

    clear((byte*)cmd, 64);
    clear((byte*)arg[0], 64);
    clear((byte*)arg[1], 64);

    while (buf[i] == ' ' && buf[i] != '\0') i++;

    j = 0;
    while (buf[i] != ' ' && buf[i] != '\0') {
        if (j < 63) cmd[j++] = buf[i];
        i++;
    }
    cmd[j] = '\0';

    while (buf[i] == ' ' && buf[i] != '\0') i++;

    j = 0;
    while (buf[i] != ' ' && buf[i] != '\0') {
        if (j < 63) arg[0][j++] = buf[i];
        i++;
    }
    arg[0][j] = '\0';

    while (buf[i] == ' ' && buf[i] != '\0') i++;

    j = 0;
    while (buf[i] != ' ' && buf[i] != '\0') {
        if (j < 63) arg[1][j++] = buf[i];
        i++;
    }
    arg[1][j] = '\0';
}

void shell() {
    char buf[128];
    char cmd[64];
    char args[2][64];
    char command_executed;
    int val1, val2, result_val = 0; 
    char result_str[16];

    strcpy(current_username, "user");
    grand_company_suffix[0] = '\0';
    setKernelTextAttribute(COLOR_DEFAULT);
    random_seed = _getBiosTick();

    printString("Welcome to EorzeOS!\n");

    while (true) {
        command_executed = false;

        printString(current_username);
        if (grand_company_suffix[0] != '\0') {
            printString(grand_company_suffix);
        }
        printString("> ");

        readString(buf);

        if (buf[0] == '\0') {
            continue;
        }

        parseCommand(buf, cmd, args);

        if (cmd[0] == '\0') {
            continue;
        }

        if (strcmp(cmd, "yo") == true) {
            printString("gurt\n");
            command_executed = true;
        } else if (strcmp(cmd, "gurt") == true) {
            printString("yo\n");
            command_executed = true;
        } else if (strcmp(cmd, "user") == true) {
            if (args[0][0] == '\0') {
                strcpy(current_username, "user");
                printString("Username changed to user\n");
            } else {
                strcpy(current_username, args[0]);
                printString("Username changed to "); printString(current_username); printString("\n");
            }
            command_executed = true;
        } else if (strcmp(cmd, "grandcompany") == true) {
            char gc_valid = false;
            if (strcmp(args[0], "maelstrom") == true) {
                setKernelTextAttribute(COLOR_MAELSTROM); clearScreen(); strcpy(grand_company_suffix, "@Storm"); gc_valid = true;
            } else if (strcmp(args[0], "twinadder") == true) {
                setKernelTextAttribute(COLOR_TWINADDER); clearScreen(); strcpy(grand_company_suffix, "@Serpent"); gc_valid = true;
            } else if (strcmp(args[0], "immortalflames") == true) {
                setKernelTextAttribute(COLOR_IMMORTALFLAMES); clearScreen(); strcpy(grand_company_suffix, "@Flame"); gc_valid = true;
            }
            if (gc_valid == false) {
                printString("Error: Invalid Grand Company specified.\nUsage: grandcompany [maelstrom|twinadder|immortalflames]\n");
            }
            command_executed = true;
        } else if (strcmp(cmd, "clear") == true) {
            setKernelTextAttribute(COLOR_DEFAULT); clearScreen(); grand_company_suffix[0] = '\0';
            command_executed = true;
        } else if (strcmp(cmd, "add") == true || strcmp(cmd, "sub") == true || strcmp(cmd, "mul") == true || strcmp(cmd, "div") == true) {
            if (args[0][0] == '\0' || args[1][0] == '\0') {
                printString("Error: Calculator commands require two arguments.\nUsage: "); printString(cmd); printString(" <x> <y>\n");
            } else {
                atoi(args[0], &val1); atoi(args[1], &val2);
                char calc_error = false;
                // result_val already initialized
                if (strcmp(cmd, "add") == true) result_val = val1 + val2;
                else if (strcmp(cmd, "sub") == true) result_val = val1 - val2;
                else if (strcmp(cmd, "mul") == true) result_val = val1 * val2;
                else if (strcmp(cmd, "div") == true) {
                    if (val2 == 0) { printString("Error: Division by zero.\n"); calc_error = true; }
                    else result_val = div(val1, val2);
                }
                if (calc_error == false) { itoa(result_val, result_str); printString(result_str); printString("\n"); }
            }
            command_executed = true;
        } else if (strcmp(cmd, "yogurt") == true) {
            int choice = get_random_int(3);
            printString("gurt> ");
            if (choice == 0) printString("yo\n");
            else if (choice == 1) printString("ts unami gng </3\n");
            else printString("sygau\n");
            command_executed = true;
        }

        if (command_executed == false) {
            printString(buf);
            printString("\n");
        }
    }
}
