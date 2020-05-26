#include "../utils/fileutils.c"

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
