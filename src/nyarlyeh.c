#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// https://stackoverflow.com/questions/232693/including-one-c-source-file-in-another
#include "commands/help.c"
#include "commands/test.c"
#include "commands/mod.c"
#include "commands/variant.c"
#include "commands/file.c"

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
