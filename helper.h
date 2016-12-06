#ifndef HELPER
#define HELPER

#include "ucode.h"
#include "type.h"

#define TYPEBITS 0170000
#define     DIR 0040000
#define     REG 0100000
#define     LNK 0120000

int getLine(int fd, char *line, int length);
void cpystr(char *dest, char *src);
void printStr(char *str, int redirected);



#endif