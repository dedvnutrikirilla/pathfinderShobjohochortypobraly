#include "../inc/libmx.h"

void mx_print_strarr(char**arr, const char*delim) {
    if(*arr == NULL && arr[0] == NULL) {
        return;
    }

    int i = 0;

    while (arr[i]) {
        if(i != 0) {
            mx_printstr(delim);
        }
        mx_printstr(arr[i]);
        i++;
    }

    mx_printchar('\n');
}
