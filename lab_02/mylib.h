#ifndef MYLIB_H
#define MYLIB_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define SUCCESS          0

#define ADD              1
#define SHOW             2
#define DELETE           3
#define SHOW_TABLE       4
#define SHOW_KEYS        5
#define SHOW_SORTED      6
#define SHOW_KEY_SORTED  7
#define SHOW_TIME        8
#define EXIT             9

#define ERROR            -2
#define INV_INPUT        -3
#define EMPTY_BASE       -4
#define NO_MATCHES       -5
#define BAD_BEHAVE       -6
#define BAD_DATA         -7

#define N                6
#define BUFF_SIZE        50
#define BASE_SIZE        30
#endif