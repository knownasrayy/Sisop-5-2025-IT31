#include "std_lib.h"

int div(int a, int b) {
    if (b == 0) {
        return 0; 
    }
    return a / b;
}

int mod(int a, int b) {
    if (b == 0) {
        return 0;
    }

    while (a >= b) {
        a -= b;
    }
    return a;
}

bool strcmp(char *str1, char *str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return false;
        }
        i++;
    }
    return str1[i] == '\0' && str2[i] == '\0';
}

void strcpy(char *dst, char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
}

void clear(byte *buf, unsigned int size) {
    unsigned int i;
    for (i = 0; i < size; ++i) {
        buf[i] = 0;
    }
}

void atoi(char *str, int *num) {
    int i = 0;
    bool is_negative = false;

    *num = 0;

    if (str[0] == '-') {
        is_negative = true;
        i = 1;
    }


    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            *num = *num * 10 + (str[i] - '0');
        }
        i++;
    }

    if (is_negative) {
        *num = -(*num);
    }
}

void itoa(int num, char *str) {
    char temp[12];
    int i = 0;
    int j = 0;
    bool is_negative = false;

    if (num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    if (num < 0) {
        is_negative = true;
        num = -num;
    }
)
    while (num != 0) {
        temp[i] = mod(num, 10) + '0';
        num = div(num, 10);
        i++;
    }

    if (is_negative) {
        str[j] = '-';
        j++;
    }

    while (i > 0) {
        i--;
        str[j] = temp[i];
        j++;
    }
    str[j] = '\0';
}
