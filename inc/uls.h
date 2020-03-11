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

#define MX_USED_FLAGS "ACGRSUclmrtux1"

#define MX_RED     "\x1b[31m"
#define MX_GREEN   "\x1b[32m"
#define MX_YELLOW  "\x1b[33m"
#define MX_BLUE    "\x1b[34m"
#define MX_MAGENTA "\x1b[35m"
#define MX_CYAN    "\x1b[36m"
#define MX_RESET   "\x1b[0m"

#define MX_ISBLK(mode) (((mode) & S_IFMT) == S_IFBLK)
#define MX_ISCHR(mode) (((mode) & S_IFMT) == S_IFCHR)
#define MX_ISDIR(mode) (((mode) & S_IFMT) == S_IFDIR)
#define MX_ISLNK(mode) (((mode) & S_IFMT) == S_IFLNK)
#define MX_ISSOCK(mode) (((mode) & S_IFMT) == S_IFSOCK)
#define MX_ISFIFO(mode) (((mode) & S_IFMT) == S_IFIFO)
#define MX_ISWHT(mode) (((mode) & S_IFMT) == S_IFWHT)
#define MX_ISREG(mode) (((mode) & S_IFMT) == S_IFREG)
#define MX_ISEXEC(mode) ((mode) & S_IXUSR)

typedef struct {
    bool one;
    bool A;
    bool C;
    bool c;
    bool G;
    bool l;
    bool m;
    bool R;
    bool r;
    bool S;
    bool t;
    bool U;
    bool u;
    bool x;
    bool first;
    bool forcedc;
    bool printpath;
    bool file_args;
} t_flags;

typedef struct dirent t_dirent;
typedef struct stat t_stat;

typedef struct s_daddy{
    long n_link;
    long own_name;
    long grp_name;
    long size;
    long ma_size;
    long total;
} t_daddy;

typedef struct {
    t_stat stat;
    char d_name[258];
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

bool mx_OMG_auditor(int set);
void args_to_list(int argc, char **argv,
t_list **files_args, t_list **dir_flags);
void mx_process_list(t_print arguments, t_list *files, t_flags *flags);
void mx_free_list(t_list **files);
void mx_output(t_flags *flags, t_list *files);
void mx_multicol_output(t_list *files, t_flags *flags);
void mx_x_output(t_list *files, t_flags *flags, t_multicol *mltcl);
void mx_c_output(t_list *files, t_flags *flags, t_multicol *mltcl);
void mx_m_output(t_list *files, t_flags *flags);
void mx_print_filename (t_file *file, t_flags *flags);
t_list *mx_process_dir(t_file *dir, t_flags *flags);
t_list *mx_file_args_to_list (int *i, t_list **dir_args, 
int argc, char **argv);
t_file *mx_create_t_file(void);
char *mx_four_to_one(char *first_part, char *text,
char *second_part, char *third_part);
void mx_print_path(t_file *data, t_flags *flags);
void mx_print_name_list(t_list *files, t_flags* flags);
void mx_print_long_format(t_list *files, t_flags *flags);
void mx_file_mode(t_file *file);
void mx_user_group(t_file *file, t_daddy *daddy);
void mx_print_time(t_file *file, t_flags *flags);
void mx_print_list(t_list *files);
char **mx_save_args (int *i, int *margc, int argc, char **argv);
bool mx_check_flag_validity (char c);
t_flags *mx_init_flags(void);
void mx_check_flags (char c, t_flags *flags);
void mx_flag_parser (int *i, int argc, char **argv, t_flags *flags);
void mx_error(t_error error_type, char *argument);
void mx_process_arg(char **args, t_flags *flags);
void mx_sort_files(t_list *files, t_flags *flags);
t_list *mx_sort_lists(t_list *lst, bool (*cmp)(void *, void*, bool reverse),
t_flags *flags);
void mx_print_with_tabl(long num, long num_of_dig, bool dig);
char mx_which_file(t_file *file);
long mx_strlen_own(t_file *file);
long mx_strlen_grp(t_file *file);
void mx_set_daddy(t_daddy *daddy);
void mx_print_link(t_file *file);
void mx_print_major_minor(t_file *file, long ma_size);
void mx_print_errors_list(t_list *files);

//Sorting comparators:
bool mx_size_cmp(void *data1, void *data2, bool reverse);
bool mx_time_chngd_cmp(void *data1, void *data2, bool reverse);
bool mx_time_access_cmp(void *data1, void *data2, bool reverse);
bool mx_time_creat_cmp(void *data1, void *data2, bool reverse);
bool mx_time_mod_cmp(void *data1, void *data2, bool reverse);
bool mx_alpha_cmp(void *data1, void *data2, bool reverse);
bool mx_errors_cmp(void *data1, void *data2);
bool mx_alpha_cmp_lst(void *data1, void *data2);
