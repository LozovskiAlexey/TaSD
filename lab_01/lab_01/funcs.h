#include <stdio.h>
#include <stdlib.h>
#define N 40
#define M 6
#define INPUT_ERR -2
#define ERR_ZERO_DIVISION -1

int read_int(int *arr, int *ex);
int read_double(int *arr, int *ex, int *dot_pos);
void align_int(int *arr1, int *n1);
void subtract(int *arr1, int *n1, int *arr2, int n2);
void multiplication(int *arr, int *n, int num);
int divide_ints(int *arr1, int n1, int *arr2, int n2, int *res);
int compare(int *arr1, int n1, int *arr2, int n2);
int print_res(int *res, int len, int ex);
void incr(int *arr, int *n);
void print_arr(int *arr, int len);
