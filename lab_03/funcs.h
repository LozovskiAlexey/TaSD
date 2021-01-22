#include "struct.h"

//Проверка ввода
int check_input(int);
void get_name(char *);

//вызов меню
int menu(matrix *, matrix *);
matrix *do_addition_1(matrix *, matrix *);
int **do_addition_2(int **, int **, matrix *, matrix *);
void cmp_time(void);
void cmp_mem(int **, int **, matrix *, matrix *);

//Работа с файлом
int create_mtrx(matrix **, FILE *);
int **mtr_alloc(int, int);
int fill_mtr(matrix **);
int read_file(matrix **, int);
void fill_file(void);
void put_in_file(int **, int, int);


//Вывод
int show_result_text(int);
void show_mtrx(int, int, int **, int);
void show_vectors(matrix *, int);

//Всяческое интэресное
void free_all(matrix **);
int min(int, int);
int max(int, int);
unsigned long long tick(void);
void show_title(int, int);
int comparator(int el1, int el2);

//работа с матрицей
int **make_mtrx(matrix *);
void init_mtrx(matrix **, int, int);
void get_vector(matrix **);
int **get_position(int *rows, int *cols);
