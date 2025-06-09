#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

static unsigned int random_seed;

int rand() {
    random_seed = random_seed + getBiosTick();
    random_seed = (random_seed * 25173 + 13849);
    return random_seed;
}


void handle_grandcompany(char* company);
void handle_yogurt();
void handle_calc(char* op, char* arg1, char* arg2);
void handle_user(char* new_user);

char username[32];
char company_suffix[16];

void shell() {
    char buf[128];
    char cmd[64];
    char args[2][64];

    strcpy(username, "user");
    clear(company_suffix, 16);
    
    random_seed = getBiosTick();

    while (true) {
        printString(username);
        printString(company_suffix);
        printString("> ");

        readString(buf);

        parseCommand(buf, cmd, args);

        if (strcmp(cmd, "yo")) {
            printString("gurt\n");
        } else if (strcmp(cmd, "gurt")) {
            printString("yo\n");
        } else if (strcmp(cmd, "user")) {
            handle_user(args[0]);
        } else if (strcmp(cmd, "grandcompany")) {
            handle_grandcompany(args[0]);
        } else if (strcmp(cmd, "clear")) {
            clearScreen();
            strcpy(company_suffix, "");
        } else if (strcmp(cmd, "add") || strcmp(cmd, "sub") || strcmp(cmd, "mul") || strcmp(cmd, "div")) {
            handle_calc(cmd, args[0], args[1]);
        } else if (strcmp(cmd, "yogurt")) {
            handle_yogurt();
        } else if (cmd[0] != '\0') {
            printString(buf);
            printString("\n");
        }
    }
}

void parseCommand(char *buf, char *cmd, char args[2][64]) {
    int i = 0, j = 0, arg_idx = 0;

    clear(cmd, 64);
    clear(args[0], 64);
    clear(args[1], 64);

    while (buf[i] != ' ' && buf[i] != '\0') {
        cmd[j++] = buf[i++];
    }
    cmd[j] = '\0';

    while (buf[i] == ' ') i++;

    while (buf[i] != '\0' && arg_idx < 2) {
        j = 0;
        while (buf[i] != ' ' && buf[i] != '\0') {
            args[arg_idx][j++] = buf[i++];
        }
        args[arg_idx][j] = '\0';
        arg_idx++;
        while (buf[i] == ' ') i++;
    }
}

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
