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
	int sides[3];
	int total = 0;

    while (fgets(line, MAX_LEN, fp))
    {
        line[strcspn(line, "\n")] = 0;
        sscanf(line, "%dx%dx%d", &w, &h, &l);
		sides[0] = l*w;
		sides[1] = w*h;
		sides[2] = h*l;

		int min = sides[0];
		int gift_total = 0;
		for (size_t i = 0; i < 3; i++)
		{
			int side = sides[i];
			if (side < min) min = side;
			gift_total += 2 * side;
		}
		total += gift_total + min;
    }
    
    printf("Result: \e[32m%d\e[0m\n", total);
    fclose(fp);
    return 0;
}
