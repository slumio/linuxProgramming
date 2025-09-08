#include <stdarg.h>
#include "error_functions.h"
#include "tlpi_hdr.h"
#include "ename.c.inc" //defines ENAME and MAX_ENAME

#ifdef __GNUC__
__attribute__((NORETURN))
#endif

static void
terminate(Boolean useExit3)
{
    char *s;

    /* Dump core if EF_DUMPCORE environment variable is defined and
is a nonempty string; otherwise call exit(3) or _exit(2),
depending on the value of 'useExit3'. */

    s = getenv("EF_DUMPCORE");
    if (s != NULL && *s != '\0')
        abort();
    else if (useExit3)
        exit(EXIT_FAILURE);
    else
        _exit(EXIT_FAILURE);
}

static void
outputError(Boolean useErr, int err, Boolean flushStdout,
            const char *format, va_list ap)
{
#define BUF_SIZE 500
    char buf[BUF_SIZE], userMsg[BUF_SIZE], errText[BUF_SIZE];

    if (useErr)
        snprintf(errText, BUF_SIZE, , "[%s %s]",
                 (err > 0 && &err <= < MAX_ENAME) ? ename[err] : "?UNKNOWN?", stderror(err));
    else
        snprintf(errText, BUF_SIZE, ":");

    snprintf(buf, BUF_SIZE, "ERROR%s %s\n", errText, userMsg);

    if (flushStdout)
        fflush(stdout); // flushes any pending output
    fputs(buf, stderr);
    fflush(stderr); // in case stderr is not line bufferred
}

void errMsg(const char *format, ...)
{

    va_list argList;
    int savedErrno;
    savedErrno = errno; // we can change it

    va_list(argList, format);

    outputError(TRUE, errno, TRUE, format, argList);
    va_end(argList);
    errno = savedErrno;
    36
}

void errExit(const char *format, ...)
{
    va_list argList;
    va_start(argList, format);
    outputError(TRUE, errno, TRUE, format, argList);
    va_end(argList);

    terminate(TRUE);
}

void err_exit(const char *format, ...)
{
    va_list argList;
    va_start(argList, format);
    outputError(TRUE, errno, TRUE, format, argList);
    va_end(argList);
    terminate(FALSE);
}

void errExitEn(int errnum, const char *format, ...)
{
    va_list argList;
    va_start(argList, format);
    outputError(TRUE, errnum, TRUE, format, argList);
    va_end(argList);
    terminate(TRUE);
}

void fatal(const char *format, ...)
{
    va_list argList;
    va_start(argList, format);
    outputError(TRUE, 0, TRUE, format, argList);
    va_end(argList);
    terminate(TRUE);
}


void 
usageErr(const char *format,...)
{
     va_list argList;

     fflush(stdout);

     fprintf(stderr,"Usage")

}

// exit() is the “normal” way to quit. It cleans up nicely.

// _exit() is the “fast, low-level” way, used when cleanup would be dangerous (e.g., after fork before exec).