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


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main (int argc, char *argv[])
{
    unsigned char tmp[1] = {0};
    unsigned char buf[4096];
    int fd;

    memset(buf, 0, 4096);

    if ((fd = open("./mr_testfile", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) < 0)
    {
        perror("open fail\n");
        return -1;
    }

    if (write(fd, buf, 4096) != 4096)
    {
        perror("write fail\n");
        return -1;
    }

    usleep(999999);
    printf("%d\n", tmp[0]);
    printf("SSIZE_MAX: %ld\n", SSIZE_MAX);
    printf("done!\n");
    return 0;
}
