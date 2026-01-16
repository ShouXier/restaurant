#include "Utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
#endif

void clearScreen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen(void) {
    printf("\n按回车键继续...  ");
    while(getchar() != '\n');
    getchar();
}

void printHeader(const char* title) {
    printf("\n");
    printf("============================================================\n");
    printf("          %s\n", title);
    printf("============================================================\n");
}