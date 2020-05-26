#include "../utils/fileutils.c"
#include "../utils/dirutils.c"

void cmd_dir(char *dirpath) {
    int files_count = dir_count_files(dirpath);
    unsigned int r;
    WITH_FILE(f, "/dev/random", "rb", {
        r = file_next_unsigned_int(f);
    });
    int n = r % files_count;
    char filepath[256];
    dir_nth_file(dirpath, n, filepath, 256);
    printf("%s\n", filepath);
}
