#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// https://stackoverflow.com/questions/232693/including-one-c-source-file-in-another
#include "commands/help.c"
#include "commands/test.c"
#include "commands/mod.c"
#include "commands/variant.c"
#include "commands/file.c"
#include "commands/dir.c"

#include "utils/strutils.c"

int main(int argc, char **argv) {
    if (argc < 2) {
        cmd_help();
        return 0;
    }
    int num_repeats = 1;
    if (str_is_numeric(argv[1])) {
        num_repeats = atoi(argv[1]);
        argc--;
        argv++;
    }
    for (int i = 0; i < num_repeats; i++) {
        if (
            strcmp(argv[1], "test") == 0 ||
            strcmp(argv[1], "t") == 0
        ) {
            switch (argc) {
                case 2:
                    cmd_test(10, 1000);
                    continue;
                case 3: {
                    int m;
                    sscanf(argv[2], "%d", &m);
                    cmd_test(m, 1000);
                    continue;
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
                    continue;
                case 3: {
                    int m;
                    sscanf(argv[2], "%d", &m);
                    cmd_mod(m, 1);
                    continue;
                }
                case 4: {
                    int m, n;
                    sscanf(argv[2], "%d", &m);
                    sscanf(argv[3], "%d", &n);
                    cmd_mod(m, n);
                    continue;
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
            continue;
        } else if (
            argc > 2 && (
                strcmp(argv[1], "file") == 0 ||
                strcmp(argv[1], "f") == 0
            )
        ) {
            cmd_file(*(argv + 2));
        } else if (
            argc > 2 && (
                strcmp(argv[1], "dir") == 0 ||
                strcmp(argv[1], "d") == 0
            )
        ) {
            cmd_dir(*(argv + 2), argc == 4 ? *(argv + 3) : NULL);
        } else {
            cmd_help();
            continue;
        }
    }
}
