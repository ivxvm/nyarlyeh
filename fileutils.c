#define WITH_FILE(var, path, mode, call) { FILE *var = fopen(path, mode); call; fclose(var); }

int file_next_byte(FILE *f) {
    int x;
    if (!fread(&x, 1, 1, f)) {
        printf("Can't read /dev/random");
        exit(1);
    }
    return x;
}

int file_count_lines(FILE *f) {
    int result = 0;
    while (!feof(f)) {
        char c = fgetc(f);
        if (c == '\n') {
            result++;
        }
    }
    return result;
}

void file_nth_line(FILE *f, int n, char *buf) {
    while (!feof(f)) {
        char c = fgetc(f);
        if (c == '\n') {
            if (n == 0) {
                *buf = '\0';
                return;
            }
            n--;
        } else if (n == 0) {
            *(buf++) = c;
        }
    }
}
