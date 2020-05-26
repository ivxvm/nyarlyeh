#include "../utils/fileutils.c"

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
