#include <unistd.h>
#include <stdio.h>

int main(void) {
    if (isatty(1) == 1)
        printf("1");
    // if (isatty(2) == 1)
        // printf("2");
    // if (isatty(3) == 1)
        // printf("3");
    // if (isatty(0) == 1)
        // printf("0");
}
