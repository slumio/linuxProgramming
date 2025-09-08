#ifndef TLPI_HDR_H
#define TLPI_HDR_H  /*Prevent accidental double inclusion*/

#include<sys/types.h> // type defintion used by many program
#include<stdio.h>   /* standard i/o functions*/
#include<stdlib.h>  /*exit_success and exit failure constants*/
#include<unistd.h> /* prototypes for many system calls*/
#include<errno.h>  /*Declares errno and defines error cosntants*/

#include "getnum.h"
#include "error_functions.h" /*error handling function*/

typedef enum {FALSE ,TRUE} Boolean;

#define min(m,n) ((m)<(n)?(m):(n))
#define max(n,m) ((m)>(n)?(m):(n))


#endif