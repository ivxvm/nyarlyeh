#include "../utils/fileutils.c"

void cmd_variant(int count, char **variants) {
    WITH_FILE(f, "/dev/random", "rb", {
        unsigned int x = file_next_unsigned_int(f);
        printf("%s\n", variants[x % count]);
    });
}
