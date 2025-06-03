#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "std_type.h" // For byte

extern void _putInMemory(int segment, int address, char character);
extern int _interrupt(int number, int AX, int BX, int CX, int DX);
extern unsigned int _getBiosTick();

// Functions buat kernel.c 
void printString(char* str);
void readString(char* buf);
void clearScreen();
void setKernelTextAttribute(byte attribute);


void shell();

#endif // __KERNEL_H__
