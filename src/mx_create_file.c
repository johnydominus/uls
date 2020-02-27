#include "uls.h"

static char *make_fullpath(char *name, char *path) {
    char *new_arg = NULL;
    if (TEST) printf(">make_fullpath\n");
    if (mx_strlen(path) == 0) 
        new_arg = mx_strdup(name);
    else if (mx_strlen(path) > 0 && path[mx_strlen(path) - 1] == '/')
        new_arg = mx_strjoin(path, name);
    else {
        char *temp_arg = mx_strjoin(path, "/");
        new_arg = mx_strjoin(temp_arg, name);
        free(temp_arg);
    }
    if (TEST) printf(">argument: %s\n", new_arg);
    return new_arg;
}

t_file *mx_create_file(char *name, char *path) {
    if (TEST) printf(">mx_create_file\n");
    t_file *new_file = (t_file*)malloc(sizeof(t_file));
    struct stat *fstat = (struct stat*)malloc(sizeof(struct stat));
    char *temp_path = make_fullpath(name, path);
    if (lstat(temp_path, fstat) == -1)
        if (TEST) printf(">THERE IS NO STAT!\n");

    if (TEST) printf(">m_dev\n");
    new_file->m_dev = fstat->st_dev;
    if (TEST) printf(">m_ino\n");
    new_file->m_ino = fstat->st_ino;
    if (TEST) printf(">m_mode\n");
    new_file->m_mode = fstat->st_mode;
    if (TEST) printf(">m_nlink\n");
    new_file->m_nlink = fstat->st_nlink;
    if (TEST) printf(">m_uid\n");
    new_file->m_uid = fstat->st_uid;
    if (TEST) printf(">m_gid\n");
    new_file->m_gid = fstat->st_gid;
    if (TEST) printf(">m_rdev\n");
    new_file->m_rdev = fstat->st_rdev;
    if (TEST) printf(">m_atime\n");
    new_file->m_atime = fstat->st_atimespec;
    if (TEST) printf(">m_mtime\n");
    new_file->m_mtime = fstat->st_mtimespec;
    if (TEST) printf(">m_ctime\n");
    new_file->m_ctime = fstat->st_mtimespec;
    new_file->m_btime = fstat->st_birthtimespec;;
    if (TEST) printf(">m_size\n");
    new_file->m_size = fstat->st_size;
    if (TEST) printf(">m_blocks\n");
    new_file->m_blocks = fstat->st_blocks;
    if (TEST) printf(">m_blksize\n");
    new_file->m_blksize = fstat->st_blksize;
    if (TEST) printf(">f_name\n");
    new_file->f_name = mx_strdup(name);
    if (TEST) printf(">full_path\n");
    new_file->path = mx_strdup(temp_path);
    if (TEST) printf(">subdir create\n");
    new_file->subdir = (t_list**)malloc(sizeof(t_list*));
    *(new_file->subdir) = NULL;
    if (TEST) printf(">file created!\n");
    free (fstat);
    free (temp_path);
    return new_file;
}
