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

typedef struct dirent t_dirent;
typedef struct stat t_stat;

typedef struct s_file {
    t_stat stat;
    t_dirent *dirent;
    char *full_path;
    char *error;
} t_file;

typedef struct s_core {
    dev_t m_dev;           //device
    ino_t m_ino;           //inode
    mode_t m_mode;         //access mode
    nlink_t m_nlink;       //hard link ammount
    uid_t m_uid;           //user-owner id
    gid_t m_gid;           //group-owner id
    dev_t m_rdev;          //device type
    off_t m_size;          //general size in bytes
    blksize_t m_blksize;   //input-output block size in file system
    blkcnt_t m_blocks;     //ammount of allocated blocks
    time_t m_atime;        //last access time
    time_t m_mtime;        //last modification time
    time_t m_ctime;        //last change time
    ino_t d_fileno;         //file serial number
    unsigned char d_namlen; //name length
    unsigned char d_type;   //filetype
    char d_name[];          //null-terminated file name
} t_core;

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
