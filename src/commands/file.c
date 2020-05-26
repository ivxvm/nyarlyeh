#include "../utils/fileutils.c"

void cmd_file(char *path) {
    int lines_count;
    WITH_FILE(f, path, "r", {
        lines_count = file_count_lines(f);
    });
    unsigned int r;
    WITH_FILE(f, "/dev/random", "rb", {
        r = file_next_unsigned_int(f);
    });
    int n = r % lines_count;
    char buf[256];
    WITH_FILE(f, path, "r", {
        file_nth_line(f, n, buf);
    });
    printf("%s\n", buf);
}
