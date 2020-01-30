#include "libmx.h"

char *mx_file_to_str(const char* filename) {
    int fd_dst = open(filename, O_RDWR | O_EXCL, 0666);
    char buf[1024];
    int cnt;
    char *temp = NULL;
    char *result = NULL;

    if (fd_dst < 0)
        return NULL;
    while ((cnt = read(fd_dst, buf, sizeof(buf))) > 0) {
        buf[cnt] = '\0';
        temp = result;
        result = mx_strjoin(result, buf);
        free(temp);
    }
    close(fd_dst);
    return result;
}
