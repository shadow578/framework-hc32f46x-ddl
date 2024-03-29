/**
 * stubs for compatibility with newlib.
 * as per https://sourceware.org/newlib/libc.html#Stubs
 */

__attribute__((weak)) int _close(int file)
{
  return -1;
}

#include <sys/stat.h>
__attribute__((weak)) int _fstat(int file, struct stat *st)
{
  st->st_mode = S_IFCHR;
  return 0;
}

__attribute__((weak)) int _getpid(void)
{
  return 1;
}

__attribute__((weak)) int _isatty(int file)
{
  return 1;
}

#include <errno.h>
#undef errno
extern int errno;
__attribute__((weak)) int _kill(int pid, int sig)
{
  errno = EINVAL;
  return -1;
}

__attribute__((weak)) int _lseek(int file, int ptr, int dir)
{
  return 0;
}

__attribute__((weak)) int _read(int file, char *ptr, int len)
{
  return 0;
}

__attribute__((weak)) int _write(int file, char *ptr, int len)
{
  return len;
}
