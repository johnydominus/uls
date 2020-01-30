#include "uls.h"

int main(int argc, char **argv) {
    DIR *m_dir = NULL;
    struct stat *m_stat = NULL;
    char *arg = NULL;
    struct dirent *entry;

    if (argc < 2)
        arg = ".";
    else
        arg = argv[1];
    (void)argc;
    lstat(arg, m_stat);
    m_dir = opendir(arg);
    while ((entry = readdir(m_dir)) != NULL) {
        if(entry->d_name[0] != '.')
            printf("%s\n", entry->d_name);
    }
}
