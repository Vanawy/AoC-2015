#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>  

#define MAX_LEN 256
#define BUCKET_SIZE 16

int main (int argc, char *argv[])
{
    if (argc < 2) return 1;
    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Failed");
        return 2;
    }

    int x = 0, y = 0;
    int sx = 0, sy = 0;
    int rx = 0, ry = 0;

    int size = BUCKET_SIZE;
    int center = size/2;
    bool santasTurn = true;


    bool *is_visited = {false};

    if(!(is_visited = calloc(size * size, sizeof(bool)))){
        printf("Cant create array with size %d", size);
        return 3;
    }

    char direction;

    is_visited[center + size * center] = true;

    while(!feof(fp))
    {
        if (santasTurn) {
            x = sx;
            y = sy;
        } else {
            x = rx;
            y = ry;
        }
        direction = fgetc(fp);
        if(direction == '>') x++; else
        if(direction == '<') x--; else
        if(direction == '^') y++; else
        if(direction == 'v') y--;
        
        // Resize houses map if santa is out of bounds
        if (center + x >= size || center + y >= size || center + x <= 0 || center + y <= 0) {
            bool *new_map = {false};
            
            if(!(new_map = calloc(4 * size * size, sizeof(bool)))){
                printf("Cant create array with size %d", size * 2);
                return 3;
            }
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    int lx, ly;
                    lx = center + i;
                    ly = center + j;
                    new_map[2 * size * lx + ly] = is_visited[size * i + j];
                }
            }
            center = size;
            size *= 2;
            printf("Resized to: %d\n", size);
            is_visited = new_map;
            
        }
        
        int lx = center + x;
        int ly = center + y;
        is_visited[size * lx + ly] = true;
        if (santasTurn) {
            sx = x;
            sy = y;
        } else {
            rx = x;
            ry = y;
        }
        santasTurn = !santasTurn;
    }

    int total = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (is_visited[size * i + j]) total++;
        }
    }
    
    printf("Result: \e[32m%d\e[0m\n", total);
    fclose(fp);
    return 0;
}