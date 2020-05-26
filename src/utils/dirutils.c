#pragma once

#include <dirent.h>

int dir_count_files(char *dirpath) {
    int files_count = 0;
    DIR *dir = opendir(dirpath);
    struct dirent *entry;
    if (dir) {
        while ((entry = readdir(dir)) != NULL) {
            if (
                strcmp(entry->d_name, ".") == 0 ||
                strcmp(entry->d_name, "..") == 0
            ) {
                continue;
            }
            if (entry->d_type == DT_DIR) {
                char subdirpath[256];
                if (snprintf(subdirpath, 256, "%s/%s", dirpath, entry->d_name) < 0) {
                    printf("dir_count_files: error while building subdirectory path");
                    closedir(dir);
                    exit(1);
                }
                files_count += dir_count_files(subdirpath);
            } else if (entry->d_type == DT_REG) {
                files_count += 1;
            }
        }
        closedir(dir);
    }
    return files_count;
}

int dir_nth_file(char *dirpath, int n, char *filepath_buf, size_t limit) {
    int files_count = 0;
    DIR *dir = opendir(dirpath);
    struct dirent *entry;
    if (dir) {
        while ((entry = readdir(dir)) != NULL) {
            if (
                strcmp(entry->d_name, ".") == 0 ||
                strcmp(entry->d_name, "..") == 0
            ) {
                continue;
            }
            if (entry->d_type == DT_DIR) {
                char subdirpath[256];
                if (snprintf(subdirpath, 256, "%s/%s", dirpath, entry->d_name) < 0) {
                    printf("dir_nth_file: error while building subdirectory path");
                    closedir(dir);
                    exit(1);
                }
                files_count += dir_nth_file(subdirpath, n - files_count, filepath_buf, limit);
                if (files_count == n)
                    break;
            } else if (entry->d_type == DT_REG) {
                if (files_count == n) {
                    if (snprintf(filepath_buf, limit, "%s/%s", dirpath, entry->d_name) < 0) {
                        printf("dir_nth_file: error while building full filepath");
                        closedir(dir);
                        exit(1);
                    }
                    break;
                }
                files_count += 1;
            }
        }
        closedir(dir);
    }
    return files_count;
}
