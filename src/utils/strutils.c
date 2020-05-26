#include <stdbool.h>
#include <ctype.h>

bool str_is_numeric(char *str) {
    if (str == NULL)
        return false;
    char c = str[0];
    if (c == '\0')
        return false;
    for (int i = 0; true; i++) {
        c = str[i];
        if (c == '\0')
            break;
        if (!isdigit(c))
            return false;
    }
    return true;
}
