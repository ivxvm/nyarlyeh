#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE* open_dev_random() {
    return fopen("/dev/random", "rb");
}

int next_byte(FILE *f) {
    int x;
    if (!fread(&x, 1, 1, f)) {
        printf("Can't read /dev/random");
        exit(1);
    }
    return x;
}

void cmd_help() {
    printf("usage: nyarlyeh <command> [<args>]\n\n");
    printf("commands:\n");
    printf("    m, mod <m> [<n>]              use modulo generator\n");
    printf("    v, variant [<variants>]       choose variant from the list\n");
    printf("    t, test <command> [<args>]    test command (eg print freq distribution)\n");
}

void cmd_mod(int m, int n) {
    FILE *f = open_dev_random();
    for (int i = n; i > 0; i--) {
        int x = next_byte(f);
        if (i > 1) {
            printf("%d ", x % m);
        } else {
            printf("%d\n", x % m);
        }
    }
}

void cmd_variant(int count, char **variants) {
    FILE *f = open_dev_random();
    int x = next_byte(f);
    printf("%s\n", variants[x % count]);
}

void cmd_test(int m, int n) {
    int freqs[m];
    memset(freqs, 0, m * sizeof(int));
    FILE *f = open_dev_random();
    for (int i = 0; i < n; i++) {
        int x = next_byte(f);
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
    } else if (
        argc > 2 && (
            strcmp(argv[1], "variant") == 0 ||
            strcmp(argv[1], "v") == 0
        )
    ) {
        cmd_variant(argc - 2, argv + 2);
        return 0;
    } else {
        cmd_help();
        return 0;
    }
}
