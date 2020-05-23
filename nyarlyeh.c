#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// https://stackoverflow.com/questions/232693/including-one-c-source-file-in-another
#include "fileutils.c"

void cmd_help() {
    printf("usage: nyarlyeh <command> [<args>]\n\n");
    printf("commands:\n");
    printf("    m, mod <m> [<n>]              use modulo generator\n");
    printf("    v, variant [<variants>]       choose variant from the list\n");
    printf("    f, file [<filepath>]          choose variant from the file\n");
    printf("    t, test <command> [<args>]    test command (eg print freq distribution)\n");
}

void cmd_mod(int m, int n) {
    WITH_FILE(f, "/dev/random", "rb", {
        for (int i = n; i > 0; i--) {
            int x = file_next_byte(f);
            if (i > 1) {
                printf("%d ", x % m);
            } else {
                printf("%d\n", x % m);
            }
        }
    });
}

void cmd_variant(int count, char **variants) {
    WITH_FILE(f, "/dev/random", "rb", {
        int x = file_next_byte(f);
        printf("%s\n", variants[x % count]);
    });
}

void cmd_file(char *path) {
    int lines_count;
    WITH_FILE(f, path, "r", {
        lines_count = file_count_lines(f);
    });
    int r;
    WITH_FILE(f, "/dev/random", "rb", {
        r = file_next_byte(f);
    });
    int n = r % lines_count;
    char buf[256];
    WITH_FILE(f, path, "r", {
        file_nth_line(f, n, buf);
    });
    printf("%s\n", buf);
}

void cmd_test(int m, int n) {
    int freqs[m];
    memset(freqs, 0, m * sizeof(int));
    WITH_FILE(f, "/dev/random", "rb", {
        for (int i = 0; i < n; i++) {
            int x = file_next_byte(f);
            freqs[x % m]++;
        }
    });
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
                cmd_test(10, 1000);
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
    } else if (
        argc > 2 && (
            strcmp(argv[1], "file") == 0 ||
            strcmp(argv[1], "f") == 0
        )
    ) {
        cmd_file(*(argv + 2));
    } else {
        cmd_help();
        return 0;
    }
}
