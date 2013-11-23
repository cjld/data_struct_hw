#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));
    printf("Input n(1<=n<=10^6): ");
    int n;
    scanf("%d", &n);
    if(n < 1 || n > 1000000) {
        fputs("Wrong input!", stderr);
        exit(1);
    }
    int dit = 0;//1 <= dit <= 6
    {
        int x = 1;
        while (x <= n) {
            dit++;
            x *= 10;
        }
    }
    FILE *fp = fopen("input.txt", "w");
    fprintf(fp, "%d\n", n);
    for (int i = 0; i < n; i++) {
        int len = rand() % 14 + 51;
        for (int j = 0; j < len; j++) {
            fprintf(fp, "%c", '0' + rand() % 2);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    return 0;
}

