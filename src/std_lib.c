#include "std_lib.h" 

void reverse(char *str, int length) {
    int start = 0;
    int end = length - 1;
    char temp;
    while (start < end) {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

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
    return a % b;
}

char strcmp(char *str1, char *str2) { 
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return false;
        }
        str1++;
        str2++;
    }
    return (*str1 == *str2); 
}

void strcpy(char *dst, char *src) {
    while (*src != '\0') {
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';
}

void clear(byte *buf, unsigned int size) { 
    unsigned int i;
    for (i = 0; i < size; i++) {
        buf[i] = 0;
    }
}

void atoi(char *str, int *num) {
    *num = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-') {
        sign = -1;
        i++;
    } else if (str[0] == '+') {
        i++;
    }

    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            *num = (*num * 10) + (str[i] - '0');
        } else {
            break;
        }
        i++;
    }
    *num *= sign;
}

void itoa(int num, char *str) {
    int i = 0;
    char is_negative = false; 

    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    if (num < 0) {
        is_negative = true;
        num = -num;
    }

    while (num != 0) {
        int rem = num % 10;
        str[i++] = rem + '0';
        num = num / 10;
    }

    if (is_negative) {
        str[i++] = '-';
    }

    str[i] = '\0';
    reverse(str, i);
}
