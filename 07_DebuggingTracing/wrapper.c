#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>
#include <errno.h>

typedef int (* real_unlinkat)(int dirfd, const char *pathname, int flags);

int unlinkat(int dirfd, const char *pathname, int flags) {
    if (strstr(pathname, "FIX")) {
        errno = EPERM;
        return 1;
    }

    real_unlinkat f = (real_unlinkat)dlsym(RTLD_NEXT, "unlinkat");
    return f(dirfd, pathname, flags);
}

