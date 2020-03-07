#pragma once

#include "libmx.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/ioctl.h>
#include <sys/acl.h>
#include <sys/errno.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
#include <time.h>
#include <string.h>

#define MX_USED_FLAGS "CFRSUcflmnprtux1"

#define MX_RED     "\x1b[31m"
#define MX_GREEN   "\x1b[32m"
#define MX_YELLOW  "\x1b[33m"
#define MX_BLUE    "\x1b[34m"
#define MX_MAGENTA "\x1b[35m"
#define MX_CYAN    "\x1b[36m"
#define MX_RESET   "\x1b[0m"

#define MX_ISBLK(m) (((m) & S_IFMT) == S_IFBLK)     //block special
#define MX_ISCHR(m) (((m) & S_IFMT) == S_IFCHR)     //char special
#define MX_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)     //directory
#define MX_ISFIFO(m) (((m) & S_IFMT) == S_IFIFO)    //fifo or socket
#define MX_ISREG(m) (((m) & S_IFMT) == S_IFREG)     //regular fil
#define MX_ISLNK(m) (((m) & S_IFMT) == S_IFLNK)     //symbolic link
#define MX_ISSOCK(m) (((m) & S_IFMT) == S_IFSOCK)   //socket
#define MX_ISEXEC(m) (MX_ISREG(m) && m & S_IXUSR)   //executable

typedef struct {
    bool one;
    bool a;
    bool C;
    bool c;
    bool F;
    bool f;
    bool l;
    bool m;
    bool n;
    bool p;
    bool R;
    bool r;
    bool S;
    bool t;
    bool U;
    bool u;
    bool x;
    bool first;
    bool forcedc;
} t_flags;

typedef struct dirent t_dirent;
typedef struct stat t_stat;

typedef struct {
    t_stat stat;
    char d_name[256];
    char *full_path;
    bool error;
} t_file;

typedef struct {
    struct winsize win_size;
    int cols;
    int rows;
    int files_num;
    int max;
    int col_width;
} t_multicol;

typedef enum {
    ALL,
    DIREC
} t_print;

typedef enum {
    NO_FILE,
    ILLEGAL_FLAG
} t_error;

void args_to_list(int argc, 
                  char **argv,
                  t_list **files_args, 
                  t_list **dir_flags);
void mx_process_list(t_print arguments, t_list *files, t_flags *flags);
void mx_free_list(t_list **files);
void mx_output(t_flags *flags, t_list *files);
void mx_multicol_output(t_list *files, t_flags *flags);
void mx_x_output(t_list *files, t_flags *flags, t_multicol *mltcl);
void mx_c_output(t_list *files, t_flags *flags, t_multicol *mltcl);
void mx_m_output(t_list *files, t_flags *flags);
void mx_print_filename (t_file *file, t_flags *flags);
int mx_add_symb(t_file *file, t_flags *flags);
t_list *mx_process_dir(t_file *dir, t_flags *flags);
t_list *mx_file_args_to_list (int *i, t_list **dir_args, 
                              int argc, char **argv);
t_file *mx_create_t_file(void);
char *mx_four_to_one(char *first_part, char *text,
char *second_part, char *third_part);
void mx_print_path(char *path, t_flags *flags);
void mx_print_name_list(t_list *files);
void mx_print_long_format(t_list *files, t_flags *flags);
void mx_file_mode(t_file *file);
void mx_user_group(t_file *file, t_flags *flags);
void mx_print_time(t_file *file);

>>>>>>> master
void mx_print_list(t_list *files);
char **mx_save_args (int *i, int *margc, int argc, char **argv);
bool mx_check_flag_validity (char c);
t_flags *mx_init_flags(void);
void mx_check_flags (char c, t_flags *flags);
void mx_flag_parser (int *i, int argc, char **argv, t_flags *flags);
void mx_error(t_error error_type, char *argument);
void mx_process_arg(char **args, t_flags *flags);
void mx_sort_files(t_list *files, t_flags *flags);
t_list *mx_sort_lists(t_list *lst, 
                      bool (*cmp)(void *, void*, 
                      bool reverse),
                      t_flags *flags);

//Sorting comparators:
bool mx_size_cmp(void *data1, void *data2, bool reverse);
bool mx_time_chngd_cmp(void *data1, void *data2, bool reverse);
bool mx_time_access_cmp(void *data1, void *data2, bool reverse);
bool mx_time_creat_cmp(void *data1, void *data2, bool reverse);
bool mx_time_mod_cmp(void *data1, void *data2, bool reverse);
bool mx_alpha_cmp(void *data1, void *data2, bool reverse);
