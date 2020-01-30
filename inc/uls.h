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

typedef struct s_filestat {
    char *name;
    int size;
} t_filestat;

typedef enum s_flags {
    dog,
    one,
    A,
    a,
    B,
    b,
    C,
    c,
    d,
    e,
    F,
    f,
    G,
    g,
    H,
    h,
    i,
    k,
    L,
    l,
    m,
    n,
    O,
    o,
    P,
    p,
    q,
    R,
    r,
    S,
    s,
    T,
    t,
    U,
    u,
    v,
    W,
    w,
    x
} t_flags;

typedef enum e_filetype {
    M_FILE,
    DIRECTORY,
    EXECUTABLE,
    SYMB_LINK,
    SOCKET,
    WHITEOUT,
    FIFO
} t_filetype;

typedef enum e_error {
    NO_ARGS,
    NO_FILE,
    ILLEGAL_FLAG
} t_error;
