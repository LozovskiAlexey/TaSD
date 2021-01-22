#include "funcs.h"

void fill_file()
{
    FILE *file = NULL;

    file = fopen("data.txt", "w");

    int result;
    int row;
    int col;

    printf(" Введите размеры матрицы: ");
    result = scanf(" %d %d", &row, &col);

    while (result != 2)
    {
        rewind(stdin);
        printf(" Некорректный ввод.\n Введите размер матрицы: ");
        result = scanf(" %d %d", &row, &col);
    }
    rewind(stdin);

    fprintf(file, "%d %d\n", row, col);

    printf(" Введите строки матрицы: \n");
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            int element;
            scanf("%d", &element);
            fprintf(file, "%d ", element);
        }
        rewind(stdin);
        fprintf(file, "\n");
    }
    fclose(file);
}

int read_file(matrix **mtr, int flag)
{
    FILE *file =      NULL;
    char *file_name = NULL;
    int result =      1;
    char name[50];

    switch (flag)
    {
    case 1:
        get_name(name);
        file_name = name;
        break;
    case 2:
        file_name = "data.txt"; //ввод в консоль
        break;
    }

    file = fopen(file_name, "r");
    if (!file)
        result =  ERROR;

    if (result != ERROR)
        result = create_mtrx(mtr, file);

    if (result != ERROR)
        printf(" Заполнение выполнено.\n");
    else
        printf(" Заполнение не выполнено.\n");

    return result;
}

int create_mtrx(matrix **mtr, FILE *file)
{
    int result;
    int rows_numb, cols_numb;

    result = fscanf(file, "%d %d\n", &rows_numb, &cols_numb);
    if (result != 2)
        result =  ERROR;

    if (result != ERROR)
    {

        init_mtrx(mtr, rows_numb, cols_numb);

        int flag =    0; //первый элемент
        int counter = 0; //считает количество элементов;
        int line =    0; //считает количество первых элементов;
        int res;
        int el;

        for (int i = 0; i < rows_numb; i++)
        {
            if (result == ERROR) // если произошла ошибка чтения
                break;

            flag = 1;    //переход на новую строку

            for (int j = 0; j < cols_numb; j++)
            {
                res = fscanf(file, "%d ", &el); //считывание элемента матрицы
                if (res == 1 && el != 0)        //если элемент считался и не ноль
                {
                    if (flag == 1)         //проверка, если обрабатывается первый
                    {                      //ненулевой элемент
                        (*mtr)->pointer[line] =  counter;
                        (*mtr)->col[counter] =   j;
                        (*mtr)->value[counter] = el;

                        line++;

                        flag = 0;
                    }
                    else
                    {
                        (*mtr)->col[counter] =   j;
                        (*mtr)->value[counter] = el;
                    }
                    counter++;
                }
                if (!res)
                {
                    result = ERROR;
                    free_all(mtr);
                    break;
                }
            }
            //проверка, если последний элемент а ненулевой не встретился
            if (flag)
            {
                (*mtr)->pointer[line] =  counter;
                line++;
            }
        }

        (*mtr)->pointer[line++] = counter; //добавление указателя на конец
        (*mtr)->points = line;             //последней строки
        (*mtr)->counter = counter;

        if (counter == 0)
        {
            free_all(mtr);
            mtr = NULL;
            result = ERROR;
        }

        if (result != ERROR)
        {
            if (counter < rows_numb * cols_numb)
            {
                (*mtr)->col   = realloc((*mtr)->col, counter * sizeof(int));
                (*mtr)->value = realloc((*mtr)->value, counter * sizeof(int));
            }
        }
    }
    return result;
}

int **make_mtrx(matrix *mtr)
{
    int rows;
    int cols;

    rows = mtr->rows;
    cols = mtr->cols;

    int **mtrx = NULL;
    mtrx = mtr_alloc(rows, cols);

    if (mtrx != NULL)
    {
        int sizeofPointer;

        sizeofPointer = mtr->points;

        for (int i = 0; i < (sizeofPointer - 1); i++)
        {
            int line_beg = mtr->pointer[i];
            int line_end = mtr->pointer[i + 1];

            for (int j = line_beg; j < line_end; j++)
            {
                int row = i;
                int col = mtr->col[j];

                mtrx[row][col] = mtr->value[j];
            }
        }
    }
    else
        printf(" Не удалось вывести матрицу. \n");

    return mtrx;
}

void show_mtrx(int rows, int cols, int **mtrx, int flag)
{
    if (mtrx != NULL)
    {
        show_title(8, flag);
        printf("                         %d х %d\n", rows, cols);

//        printf("                 ");
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
                printf(" % -3d", mtrx[i][j]);

            printf("\n");
        }
        printf("\n"); //Для читабельности
    }
}

int **mtr_alloc(int row, int col)
{
    int **result = NULL;
    int *data =    NULL;

    result = calloc(row, sizeof(int *));
    if (!result)
        return NULL;

    data = calloc(row * col, sizeof(int));
    if (!data)
    {
        free(result);
        return NULL;
    }

    for (int i = 0; i < row; i++)
        result[i] = data + i * col;

    return result;
}

void free_all(matrix **mtr)
{
    free((*mtr)->pointer);
    free((*mtr)->value);
    free((*mtr)->col);

    (*mtr)->pointer = NULL;
    (*mtr)->value =   NULL;
    (*mtr)->col =     NULL;
}
