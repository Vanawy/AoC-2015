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
        
    char line[MAX_LEN];
    int w, h, l;
	w = h = l = 0;
	int total = 0;

    while (fgets(line, MAX_LEN, fp))
    {
        line[strcspn(line, "\n")] = 0;
        sscanf(line, "%dx%dx%d", &w, &h, &l);

        int a = w;
        int b = h;
        if (l < a) {
            a = l;
            if (w < b) {
                b = w;
            }
        } else if (l < b) {
            b = l;
            if (h < w) {
                a = h;
            }
        }
        int ribbon = w * h * l + 2 * (a + b);
		total += ribbon;
    }
    
    printf("Result: \e[32m%d\e[0m\n", total);
    fclose(fp);
    return 0;
}
