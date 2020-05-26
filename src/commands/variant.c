#include "../utils/fileutils.c"

void cmd_variant(int count, char **variants) {
    WITH_FILE(f, "/dev/random", "rb", {
        int x = file_next_byte(f);
        printf("%s\n", variants[x % count]);
    });
}
