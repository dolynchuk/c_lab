#include "help.h"


///ParseValue - helper function =)
///@param stringToParse
///@param param
char *ParseValue(char *stringToParse, char *param) {
    char *buffer = malloc(sizeof(char) * 100);
    for (int i = 0; i < strlen(buffer); i++) {
        buffer[i] = ' ';
    }
    char *a = strstr(stringToParse, param);
    char *b = strstr(a, "=");
    for (int i = 1; i < strlen(buffer); i++) {
        if (b[i] == '&' || b[i] == ' ' || b[i] == '\0') {
            return buffer;
        }
        buffer[i - 1] = b[i];
    }
    free(b);
    free(a);

    return buffer;
}