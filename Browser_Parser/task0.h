#ifndef TASK0_H
#define TASK0_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char url[50];
    int accesari;
    int checksum;
    int octeti;
    char titlu[50];
    char continut[1000];
}date;

void parsare(char *,date *);
void site_names(date *);
#endif