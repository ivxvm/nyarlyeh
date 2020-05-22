#include <stdio.h>
#include <string.h>

void cmd_help() {
    printf("usage: nyarlyeh <command> [<args>]\n\n");
    printf("commands:\n");
    printf("    m, mod     use modulo generator\n");
    printf("    t, test    print modulo division frequency distribution\n");
}

void cmd_mod(int m, int n) {
    FILE *f = fopen("/dev/random", "rb");
    int x;
    for (int i = n; i > 0; i--) {
        if (!fread(&x, 1, 1, f)) {
            printf("Can't read /dev/random");
            return;
        }
        if (i > 1) {
            printf("%d ", x % m);
        } else {
            printf("%d\n", x % m);
        }
    }
}

void cmd_test(int m, int n) {
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
    if (
        strcmp(argv[1], "test") == 0 ||
        strcmp(argv[1], "t") == 0
    ) {
        switch (argc) {
            case 2:
                cmd_test(1000, 10);
                return 0;
            case 3: {
                int m;
                sscanf(argv[2], "%d", &m);
                cmd_test(m, 1000);
                return 0;
            }
            default:
                printf("Unknown number of parameters!");
                return 1;
        }
    } else if (
        strcmp(argv[1], "mod") == 0 ||
        strcmp(argv[1], "m") == 0
    ) {
        switch (argc) {
            case 2:
                cmd_mod(10, 1);
                return 0;
            case 3: {
                int m;
                sscanf(argv[2], "%d", &m);
                cmd_mod(m, 1);
                return 0;
            }
            case 4: {
                int m, n;
                sscanf(argv[2], "%d", &m);
                sscanf(argv[3], "%d", &n);
                cmd_mod(m, n);
                return 0;
            }
            default:
                printf("Unknown number of parameters!");
                return 1;
        }
    } else {
        cmd_help();
        return 0;
    }
}
