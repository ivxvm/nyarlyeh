#include <stdio.h>
#include <string.h>

void print_mod_distr(int n, int m) {
    int freqs[m];
    memset(freqs, 0, m * sizeof(int));
    FILE *f = fopen("/dev/random", "rb");
    for (int i = 0; i < n; i++) {
        int x;
        if (!fread(&x, 1, 1, f)) {
            printf("Can't read /dev/random");
            return;
        }
        freqs[x % m]++;
    }
    for (int i = 0; i < m; i++) {
        printf("%d -> %d\n", i, freqs[i]);
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        // print help
    } else if (strcmp(argv[1], "--test") == 0) {
        switch (argc) {
            case 2:
                print_mod_distr(1000, 10);
                return 0;
            case 3: {
                int n;
                sscanf(argv[2], "%d", &n);
                print_mod_distr(n, 10);
                return 0;
            }
            case 4: {
                int n, m;
                sscanf(argv[2], "%d", &n);
                sscanf(argv[3], "%d", &m);
                print_mod_distr(n, m);
                return 0;
            }
            default:
                printf("Unknown number of parameters!");
                return 1;
        }
    }
    // unsigned char x;
    // if (!fread(&x, 1, 1, f)) {
    //     printf("Can't read /dev/random");
    //     return 1;
    // } else {
    //     printf("Nyarlyeah! %d\n", x);
    //     return 0;
    // }
    // for (int i = 0; i < argc; i++) {
    //     printf("arg#%d: %s\n", i, argv[i]);
    // }
}
