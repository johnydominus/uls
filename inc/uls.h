#include "libmx.h"
#include <dirent.h>
#include <errno.h>
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

#define TEST false

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

typedef struct s_file {
    dev_t m_dev;                //inode's device
    ino_t m_ino;                //inode's number
    mode_t m_mode;              //inode's protection mode
    nlink_t m_nlink;            //number of hard links
    uid_t m_uid;                //user id of the file's owner
    gid_t m_gid;                //group id of the file's group
    dev_t m_rdev;               //device type
    off_t m_size;               //file size, in bytes
    blkcnt_t m_blocks;          //blocks allocated for file
    blksize_t m_blksize;        //optimal blocksize for I/O
    struct timespec m_atime;    //time of last access
//    long m_atimensec;           //nsec --------------
    struct timespec m_mtime;    //time of last modification
//    long m_mtimensec;           //nsec --------------------
    struct timespec m_ctime;    //time of last file status change
//    long m_ctimensec;           //nsec --------------------------
    struct timespec m_btime;    //time of file creation
    char *f_name;
    char *path;
    t_list **subdir;
} t_file;

typedef enum e_filetype {
    R_FILE,
    SP_CHAR,
    DIRECTORY,
    EXECUTABLE,
    SYMB_LINK,
    SOCKET,
    WHITEOUT,
    FIFO,
    BLOCK,
    NONE
} t_filetype;

typedef enum e_error {
    NO_FILE,
    ILLEGAL_FLAG
} t_error;

bool mx_check_flag_validity (char c);
t_flags *mx_init_flags(void);
t_file *mx_create_file(char *name, char *path);
char **mx_save_args (int *i, int *margc, int argc, char **argv);
void mx_error(t_error error_type, char *argument);
void mx_flag_parser (int *i, int argc, char **argv, t_flags *flags);
void mx_process_arg(t_list **files, t_flags *flags);
void mx_sort_lists (t_list **files, t_flags *flags);
void mx_output(t_list **files, t_flags *flags, char *path);
void mx_check_flags (char c, t_flags *flags);
