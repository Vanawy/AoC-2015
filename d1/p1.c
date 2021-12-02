#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 256

int main (int argc, char *argv[])
{
    if (argc < 2) return 1;
    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Failed");
        return 2;
    }

    int floor = 0;
    int basement_enter_pos = 0;

    char direction;
    while(!feof(fp))
    {
        direction = fgetc(fp);
        if(direction == '(') floor++; else
        if(direction == ')') floor--;
    }
    
    printf("Result: \e[32m%d\e[0m\n", floor);
    fclose(fp);
    return 0;
}