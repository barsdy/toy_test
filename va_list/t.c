/*
 * =====================================================================================
 *
 *       Filename:  t.c
 *
 *    Description:  only for test using
 *
 *        Version:  1.0
 *        Created:  01/23/2015 01:49:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Rui Ma (marui3@lenovo.com)
 *     Department:  X86-STG Mod HW DE
 *
 * =====================================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <dlfcn.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>
#include <curl/curl.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <regex.h>
#include <arpa/inet.h>
#include <time.h>
#include <arpa/inet.h>
#include <dlfcn.h>

struct st_mr {
    int a;
    int b;
};

void show_func(int level, char *fmt, ...)
{
    va_list ap;
    char str[32] = "";

    if (level == 0)
    {
            va_start(ap, fmt);
            vsnprintf(str, 32, fmt, ap);
            va_end(ap);
            printf("%s", str);
    }
    else
        printf("error\n");
}

void func( struct st_mr *p, void (*show)(int, char *, ...))
{
    show(0, "hhaa,%d, %d\n", p->a, p->b);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main (int argc, char *argv[])
{
    struct st_mr x[3][3];

    memset(x, 0, sizeof(struct st_mr) * 9);

    func(&x[1][0], (void *)show_func);

    return 0;
}

