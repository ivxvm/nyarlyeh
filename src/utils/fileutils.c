#pragma once

#define WITH_FILE(var, path, mode, call) { FILE *var = fopen(path, mode); call; fclose(var); }

unsigned int file_next_unsigned_int(FILE *f) {
    unsigned int result;
    if (!fread(&result, sizeof(unsigned int), 1, f)) {
        printf("file_next_unsigned_int: can't read file");
        exit(1);
    }
    return result;
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
