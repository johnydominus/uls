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

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define MX_ISBLK(m) (((m) & S_IFMT) == S_IFBLK)     //block special
#define MX_ISCHR(m) (((m) & S_IFMT) == S_IFCHR)     //char special
#define MX_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)     //directory
#define MX_ISFIFO(m) (((m) & S_IFMT) == S_IFIFO)    //fifo or socket
#define MX_ISREG(m) (((m) & S_IFMT) == S_IFREG)     //regular fil
#define MX_ISLNK(m) (((m) & S_IFMT) == S_IFLNK)     //symbolic link
#define MX_ISSOCK(m) (((m) & S_IFMT) == S_IFSOCK)   //socket
#define MX_ISEXEC(m) (MX_ISREG(m) && m & S_IXUSR)   //executable

typedef struct s_flags {
    bool dog;
    bool one;
    bool A;
    bool a;
    bool B;
    bool b;
    bool C;
    bool c;
    bool d;
    bool e;
    bool F;
    bool f;
    bool G;
    bool g;
    bool H;
    bool h;
    bool i;
    bool k;
    bool L;
    bool l;
    bool m;
    bool n;
    bool O;
    bool o;
    bool P;
    bool p;
    bool q;
    bool R;
    bool r;
    bool S;
    bool s;
    bool T;
    bool t;
    bool U;
    bool u;
    bool v;
    bool W;
    bool w;
    bool x;
    bool first;
} t_flags;

typedef struct dirent t_dirent;
typedef struct stat t_stat;

typedef struct s_file {
    t_stat stat;
    t_dirent *dirent;
    char *full_path;
    char *error;
} t_file;

typedef enum e_print {
    ALL;
    DIREC;
} t_print;

typedef enum e_error {
    NO_FILE,
    ILLEGAL_FLAG
} t_error;

void args_to_list(int argc, char **argv,
t_list **files_args, t_list **dir_flags);

t_list *mx_file_args_to_list (int *i, t_list **dir_args, int argc, char **argv);
t_file *mx_create_t_file();

void mx_print_list(t_list *files);
char **mx_save_args (int *i, int *margc, int argc, char **argv);
bool mx_check_flag_validity (char c);
t_flags *mx_init_flags(void);
void mx_flag_parser (int *i, int argc, char **argv, t_flags *flags);
void mx_error(t_error error_type, char *argument);
void mx_process_arg(char **args, t_flags *flags);
void mx_sort_lists (t_flags *flags, t_list **stats, t_list **entries);
void mx_check_flags (char c, t_flags *flags);
void mx_output(t_flags *flags, t_list *files, char **args);
void mx_save_info(char *arg,
                   t_flags *flags,
                   t_list **stats,
                   t_list **entries);
// void mx_process_dir(char *arg,
                           // t_list **stats,
                           // t_list **entries,
                           // t_flags *flags);
void mx_process_dir(char *arg, t_list **files, t_flags *flags, DIR **m_dir);
