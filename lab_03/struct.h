#include "libs.h"

enum result{
    ERROR = -1,
    SUCCESS
};

struct element
{
    int rows; //размер матрицы
    int cols;

    int points; //число элементов в векторном виде
    int counter;

    int *pointer; //подумать это будет указатель на массив
    int *col; //или на элемент внутри массива
    int *value;
};

typedef struct element matrix;
