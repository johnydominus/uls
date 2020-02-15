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
} t_flags;

typedef enum e_filetype {
    R_FILE,
    DIRECTORY,
    EXECUTABLE,
    SYMB_LINK,
    SOCKET,
    WHITEOUT,
    FIFO
} t_filetype;

typedef enum e_error {
    NO_FILE,
    ILLEGAL_FLAG
} t_error;

char **mx_save_args (int *i, int *margc, int argc, char **argv);
bool mx_check_flag_validity (char c);
t_flags *mx_init_flags(void);
void mx_flag_parser (int *i, int argc, char **argv, t_flags *flags);
void mx_error(t_error error_type, char *argument);
void mx_process_arg(char **args, t_flags *flags);
void mx_sort_lists (t_flags *flags, t_list **stats, t_list **entries);
void mx_check_flags (char c, t_flags *flags);
void mx_output(t_flags *flags,
               t_list **stats,
               t_list **entries,
               char **args);
void mx_save_info(char *arg,
                   t_flags *flags,
                   t_list **stats,
                   t_list **entries);
void mx_process_dir(char *arg,
                           t_list **stats,
                           t_list **entries,
                           t_flags *flags);
