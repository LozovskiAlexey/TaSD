#include "funcs.h"
void get_name(char *name)
{
    int result;

    printf(" Введите имя файла: ");
    result = scanf("%s", name);

    while (result != 1)
    {
        printf(" Некорректный ввод.\n");
        printf(" Введите имя файла: ");
        result = scanf("%s", name);
    }
}

int check_input(int amount)
{
    int result;
    int choice;

    printf(" Введите число: ");
    result = scanf("%d", &choice);

    if (choice > amount || choice < 1 || !result)
    {
        rewind(stdin);
        result = ERROR;
    }
    else
        result = choice;

    return result;
}

void f_file()
{
    char name[50];

    get_name(name);
    FILE *file = fopen(name, "w");

    int result;
    scanf("Введите число: %d", &result);

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            int digit = (j < result) ? 1 : 0;
            fprintf(file, "%d ", digit);
        }
        fprintf(file, "\n");
    }
}

int fill_mtr(matrix **mtr)
{
    int result;
    int **mtrx = NULL;
    int row;
    int col;

    show_title(10, 0);

    printf(" Заполнить матрицу:\n"
           " 1. Из файла.\n"
           " 2. В консоли.\n"
           " 3. По позициям с консоли.\n"
           " 4. Создать файл.\n");
    result = check_input(4);

    while (result == ERROR)
    {
        printf("Некорректный ввод.\n");
        result = check_input(3);
    }

    switch (result)
    {
    case 1:
        result = read_file(mtr, result);
        break;

    case 2:
        fill_file();
        result = read_file(mtr, result); //запись матрицы из файла.
        break;

    case 3:
        mtrx = get_position(&row, &col); //отсюда вернуть матрицу
        put_in_file(mtrx, row, col);
        result = read_file(mtr, 2);

        break;

    case 4:
        f_file();
        break;
    }

    return result;
}

int menu(matrix *mtr1, matrix *mtr2)
{
    int **mtrx1 = NULL;
    int **mtrx2 = NULL;
    int **result_add2   = NULL;
    matrix *result_add1 = NULL;

    show_title(9, 0);

    printf(" Выполнить: \n"
           " 1. Сложение матриц в разреженном виде.\n"
           " 2. Сложение матриц стандартным способом\n"
           " 3. Сравнение времени работы алгоритмов.\n"
           " 4. Показать в матричном виде.\n"
           " 5. Показать в векторном виде.\n"
           " 0. Выход из программы.\n");

    //возможно добавить автозаполнение матрицы
    int result;
    result = check_input(7);

    while (result == ERROR)
    {
        printf(" Некорретный ввод.\n");
        result = check_input(7);
    }

    mtrx1 = make_mtrx(mtr1);
    mtrx2 = make_mtrx(mtr2);

    switch (result)
    {
    case 1:
        show_title(result, 0);
        result_add1 = do_addition_1(mtr1, mtr2);
        if (result_add1)
        {
            if (result_add1->counter != 0)
                show_vectors(result_add1, 1);
            else
                free_all(&result_add1);
        }
        break;

    case 2:
        show_title(result, 0);
        result_add2 = do_addition_2(mtrx1, mtrx2, mtr1, mtr2);
        //Выводит матрицу стандартного вида
        show_mtrx(mtr1->rows, mtr1->cols, result_add2, 1);
        break;

    case 3:
        show_title(result, 0);
        cmp_time();
        break;

    case 4:
        show_title(result, 0);
        show_mtrx(mtr1->rows, mtr1->cols, mtrx1, 1);
        show_mtrx(mtr2->rows, mtr2->cols, mtrx2, 2);
        break;

    case 5:
        show_title(result, 0);
        show_vectors(mtr1, 1);
        show_vectors(mtr2, 2);
        break;

    case 0:
        result = SUCCESS;

        free_all(&mtr1);
        free_all(&mtr2);
        free(mtrx1);
        free(mtrx2);

        break;
    }

    return result;
}

int show_result_text(int err_code)
{
    switch (err_code)
    {
    case SUCCESS:
        printf(" Успешно. \n");
        break;
    }

    return err_code;
}

void show_vectors(matrix *mtr, int flag)
{
    int elements;
    int points;

    show_title(8, flag);
    points =   mtr->points;
    elements = mtr->counter;

    printf(" value  = { ");
    for (int i = 0; i < elements; i++)
        printf("%d ", mtr->value[i]);
    printf("};\n");

    printf(" column = { ");
    for (int i = 0; i < elements; i++)
        printf("%d ", mtr->col[i]);
    printf("};\n");

    printf(" points = { ");
    for (int i = 0; i < points; i++)
    {
        printf("%d ", mtr->pointer[i]);
        if (i % 21 == 0 && i != 0)
            printf("\n            ");
    }
    printf("};\n\n");
}

//матричное сложние
int **do_addition_2(int **mtrx1, int **mtrx2, matrix *mtr1, matrix *mtr2)
{
    int rows1 = mtr1->rows;
    int cols1 = mtr1->cols;

    int rows2 = mtr2->rows;
    int cols2 = mtr2->cols;

    int **res_mtrx = NULL;

    int result = SUCCESS;
    if (rows1 != rows2 || cols1 != cols2)
        result = ERROR;

    if (result == SUCCESS)
    {
        res_mtrx = mtr_alloc(rows1, cols1);
        if (res_mtrx)
        {
            for (int i = 0; i < rows1; i++)
            {
                for (int j = 0; j < cols1; j++)
                {
                    int sum;

                    sum = mtrx1[i][j] + mtrx2[i][j];
                    res_mtrx[i][j] = sum;
                }
            }
        }
        else
            printf(" Не удалось сложить матрицы.\n");
    }
    else
        printf(" Не удалось сложить матрицы.\n");
    return res_mtrx;
}

int comparator(int el1, int el2)
{
    //printf("Сравнение позиции 1 и 2:  %d %d\n", el1, el2);

    if (el1 > el2)
    {
        //printf("%d > %d\n", el1, el2);
        return 1;
    }

    else if (el1 < el2)
    {
        //printf("%d < %d\n", el1, el2);
        return -1;
    }

    else
    {
        //printf("%d = %d\n", el1, el2);
        return 0;
    }
}

//векторное сложение
matrix *do_addition_1(matrix *mtr1, matrix *mtr2)
{
    int rows1 = mtr1->rows;
    int cols1 = mtr1->cols;

    int rows2 = mtr2->rows;
    int cols2 = mtr2->cols;

    matrix *res_mtr = NULL;
    int result = SUCCESS;

    if (rows1 != rows2 || cols1 != cols2)
        result = ERROR;

    if (result == SUCCESS)
    {
        res_mtr = malloc(sizeof (matrix));

        init_mtrx(&res_mtr, rows1, cols1);

        if (res_mtr)
        {
            int counter = 0;
            int points = 0;

            //номер ненулевого элемента строки(конец предыдущей строки матриц 1 и 2)
            int line_end1;
            int line_end2;

            int pos1; //номер первого ненулевого элемента в матрице1 в строке i + 1
            int pos2; //номер первого ненулевого элемента в матрице2 в строке i + 1

            int sum;
            int flag = 0; //определяет был ли в строке ненулевой элемент
            //если был он записывается в pointer
            int cmp = 0;      //результат сравнения
            int cmp_flag;

            for (int i = 0; i < rows1; i++)
            {
                line_end1 = mtr1->pointer[i+1];
                line_end2 = mtr2->pointer[i+1];

                pos1 = mtr1->pointer[i]; //индекс в массиве столбцов матрицы 1 и 2
                pos2 = mtr2->pointer[i];

                //printf("Pos1 : %d\n", pos1);
                //printf("Pos2 : %d\n", pos2);

                //printf("line_end1 %d\n", line_end1);
                //printf("line_end2 %d\n", line_end2);

                flag = 1;

                int flag1 = 0;
                int flag2 = 0;
				//если в строке нет ненулевых элементов 
                if (!(line_end1 - pos1) && !(line_end2 - pos2))
                    res_mtr->pointer[points++] = counter;
				//если они есть 
                else
                {
					//если в одной матрице строка нулевая, записываем элементы ненулевой строки 
					//второй матрицы
                    if (!(line_end1 - pos1))
                    {
                        //printf("1 условие.\n");
                        for (int j = pos2; j < line_end2; j++)
                        {
                            if (flag)
                            {
                                res_mtr->pointer[points++] = counter;
                                flag = 0;
                            }

                            res_mtr->col[counter]   = mtr2->col[j];
                            res_mtr->value[counter] = mtr2->value[j];

                            counter++;
                        }
                    }
                    else if (!(line_end2 - pos2))
                    {
                        //printf("2 условие.\n");
                        for (int j = pos1; j < line_end1; j++)
                        {
                            if (flag)
                            {
                                res_mtr->pointer[points++] = counter;
                                flag = 0;
                            }

                            res_mtr->col[counter]   = mtr1->col[j];
                            res_mtr->value[counter] = mtr1->value[j];

                            counter++;
                        }
                    }
                    else
                    {
                        cmp_flag = 0;
                        //printf("3 условие.\n");
						//если обе матрицы ненулевые 
                        while (!flag1 || !flag2)
                        {
                            if (!cmp_flag)
                            {
                                //printf("Сравнение епта\n");
                                cmp = comparator(mtr1->col[pos1], mtr2->col[pos2]);
                            }
                            switch (cmp)
                            {
                            case 1:
                                //printf("__________________________________________________________________\n");
                                //printf("Номер колонки в 1 матрице: %d во 2: %d\n", mtr1->col[pos1], mtr2->col[pos2]);
                                //printf("%d > %d\n\n", mtr1->col[pos1], mtr2->col[pos2]);
                                //printf("Идет запись mtr2[%d][%d] = %d\n",i,  mtr2->col[pos2],  mtr2->value[pos2]);
                                if (flag)
                                {
                                    //printf("      ПЕРВЫЙ НЕНУЛЕВОЙ ЭЛЕМЕНТ НАЙДЕН\n");
                                    //printf("Пощзиция первого ненулевого элемента: %d\n", points);

                                    res_mtr->pointer[points++] = counter;
                                    flag = 0;
                                }

                                res_mtr->col[counter]   = mtr2->col[pos2];
                                res_mtr->value[counter] = mtr2->value[pos2];

                                //printf("Номер элемента: %d\n", counter);

                                counter++;

                                //printf("Позиция элемента за последним в строке: %d\n", line_end2);
                                if (pos2 + 1 < line_end2)
                                    pos2++;
                                else
                                {
                                    flag2 = 1;
                                    cmp_flag = 1;
                                    cmp = -1;
                                    //printf("Итератор pos2 дошел до граничного значенияюю\n");
                                }

                                break;

                            case 0:
                                //исправить условие
                                sum = mtr2->value[pos2] + mtr1->value[pos1];

                                if (sum)
                                {
                                    //printf("__________________________________________________________________\n");
                                    //printf("Номер колонки в 1 матрице: %d во 2: %d\n", mtr1->col[pos1], mtr2->col[pos2]);
                                    //printf("%d == %d Совпадение.\n\n", mtr1->col[pos1], mtr2->col[pos2]);
                                    //printf("Идет запись %d на пощиции %d\n", mtr2->value[pos2] + mtr1->value[pos1],  mtr2->col[pos2]);

                                    if (flag)
                                    {
                                        //printf("      ПЕРВЫЙ НЕНУЛЕВОЙ ЭЛЕМЕНТ НАЙДЕН\n");
                                        //printf("Пощзиция первого ненулевого элемента: %d\n", points);

                                        res_mtr->pointer[points++] = counter;
                                        flag = 0;
                                    }

                                    res_mtr->col[counter]   = mtr1->col[pos1];
                                    res_mtr->value[counter] = sum;

                                    //printf("Номер элемента: %d\n", counter);
                                    counter++;
                                }
                                //printf("MTR1 Позиция элемента за последним в строке: %d\n", line_end1);
                                //printf("MTR2 Позиция элемента за последним в строке: %d\n", line_end2);

                                if (pos2 + 1 < line_end2)
                                    pos2++;
                                else
                                {
                                    flag2 = 1;
                                    cmp_flag = 1;
                                    cmp = -1;
                                   // printf("Итератор pos2 дошел до граничного значенияюю\n");
                                }
                                if (pos1 + 1 < line_end1)
                                    pos1++;
                                else
                                {
                                    // printf("Итератор pos1 дошел до граничного значенияюю\n");
                                    cmp_flag = 1;
                                    cmp = 1;
                                    flag1 = 1;
                                }
                                break;

                            case -1:
                                //printf("__________________________________________________________________\n");
                                //printf("Номер колонки в 1 матрице: %d во 2: %d\n", mtr1->col[pos1], mtr2->col[pos2]);
                                //printf("%d < %d\n", mtr1->col[pos1], mtr2->col[pos2]);
                                //printf("Идет запись mtr1[%d][%d] = %d\n",i,  mtr1->col[pos1],  mtr1->value[pos1]);

                                if (flag)
                                {
                                    //printf("      ПЕРВЫЙ НЕНУЛЕВОЙ ЭЛЕМЕНТ НАЙДЕН\n");
                                    //printf("Пощзиция первого ненулевого элемента: %d\n", points);
                                    res_mtr->pointer[points++] = counter;
                                    flag = 0;
                                }

                                res_mtr->col[counter]   = mtr1->col[pos1];
                                res_mtr->value[counter] = mtr1->value[pos1];

                                //printf("Номер элемента: %d\n", counter);
                                counter++;
                                //printf("Позиция элемента за последним в строке: %d\n", line_end1);
                                if (pos1 + 1 < line_end1)
                                    pos1++;
                                else
                                {
                                    //printf("Итератор pos1 дошел до граничного значенияюю\n");
                                    cmp_flag = 1;
                                    cmp = 1;
                                    flag1 = 1;
                                }
                                break;
                            }
                        }
                    }
                }
                //printf(" строка %d считана.\n", i + 1);
            }
            res_mtr->counter = counter;

            if (res_mtr->counter == 0)
            {
                printf("Получилась нулевая матрица\n");
                free_all(&res_mtr);
            }
            else
            {
                res_mtr->pointer[points++] = counter; //добавление указателя на конец
                res_mtr->points = points;             //последней строки
                res_mtr->counter = counter;
            }
        }
    }
    else
    {
        printf("Не удалось сложить матрицы.\n");
        res_mtr = NULL;
    }
    return res_mtr;
}

void init_mtrx(matrix **mtr, int rows, int cols)
{
    (*mtr)->rows = rows;
    (*mtr)->cols = cols;

    (*mtr)->col =     malloc(rows * cols * sizeof(int));
    (*mtr)->value =   malloc(rows * cols * sizeof(int));
    (*mtr)->pointer = malloc((rows + 1) * sizeof(int));
}

void cmp_time(void)
{
    double percent;

    unsigned long long start1, finish1, result1;
    unsigned long long start2, finish2, result2;

    int size1;
    int size2;

    FILE *file3 = fopen("3.txt","r");
    matrix *mtr3 = calloc(1, sizeof(matrix));
    create_mtrx(&mtr3, file3);
    fclose(file3);

    int **mtrx3 = NULL;
    mtrx3 = make_mtrx(mtr3);

    start1 = tick();
    do_addition_1(mtr3, mtr3);
    finish1 = tick();

    result1 = finish1 - start1;
    percent = (double)(mtr3->counter) / (double)((mtr3->cols) * (mtr3->rows));
    percent *= 100;

    start2 = tick();
    do_addition_2(mtrx3, mtrx3, mtr3, mtr3);
    finish2 = tick();

    result2 = finish2 - start2;

    size1 = (sizeof(int)) * 100 * 100;
    size2 = sizeof(matrix) + 101 * sizeof(int) + 2 * sizeof(int) * (mtr3->counter);

    printf(" Коэффициент заполнения:             %.0lf%%\n", percent);
    printf(" Сложение матриц в стандартном виде: %d\n", (int)result2);
    printf(" Сложение матриц в векторном виде:   %d\n\n", (int)result1);
    printf(" Памяти затрачено на стандартный формат: %d Байт(а).\n", size1);
    printf(" Памяти затрачено на векторный формат:   %d Байт(а).\n", size2);

    FILE *file5 = fopen("5.txt","r");
    matrix *mtr5 = calloc(1, sizeof(matrix));
    create_mtrx(&mtr5, file5);
    fclose(file5);

    int **mtrx5 = NULL;
    mtrx5 = make_mtrx(mtr5);

    start1 = tick();
    do_addition_1(mtr5, mtr5);
    finish1 = tick();

    result1 = finish1 - start1;
    percent = (double)(mtr5->counter) / (double)((mtr5->cols) * (mtr5->rows));
    percent *= 100;

    start2 = tick();
    do_addition_2(mtrx5, mtrx5, mtr5, mtr5);
    finish2 = tick();

    result2 = finish2 - start2;

    size1 = (sizeof(int)) * 100 * 100;
    size2 = sizeof(matrix) + 101 * sizeof(int) + 2 * sizeof(int) * (mtr5->counter);

    printf(" Коэффициент заполнения:             %.0lf%%\n", percent);
    printf(" Сложение матриц в стандартном виде: %d\n", (int)result2);
    printf(" Сложение матриц в векторном виде:   %d\n\n", (int)result1);
    printf(" Памяти затрачено на стандартный формат: %d Байт(а).\n", size1);
    printf(" Памяти затрачено на векторный формат:   %d Байт(а).\n", size2);

    FILE *file10 = fopen("10.txt","r");
    matrix *mtr10 = calloc(1, sizeof(matrix));
    create_mtrx(&mtr10, file10);
    fclose(file10);

    int **mtrx10 = NULL;
    mtrx10 = make_mtrx(mtr10);

    start1 = tick();
    do_addition_1(mtr10, mtr10);
    finish1 = tick();

    result1 = finish1 - start1;
    percent = (double)(mtr10->counter) / (double)((mtr10->cols) * (mtr10->rows));
    percent *= 100;

    start2 = tick();
    do_addition_2(mtrx10, mtrx10, mtr10, mtr10);
    finish2 = tick();

    result2 = finish2 - start2;
    size1 = (sizeof(int)) * 100 * 100;
    size2 = sizeof(matrix) + 101 * sizeof(int) + mtr10->counter * 2 * sizeof(int);


    printf(" Коэффициент заполнения:             %.0lf%%\n", percent);
    printf(" Сложение матриц в стандартном виде: %d\n", (int)result2);
    printf(" Сложение матриц в векторном виде:   %d\n", (int)result1);
    printf(" Памяти затрачено на стандартный формат: %d Байт(а).\n", size1);
    printf(" Памяти затрачено на векторный формат:   %d Байт(а).\n\n", size2);

    FILE *file20 = fopen("20.txt","r");
    matrix *mtr20 = calloc(1, sizeof(matrix));
    create_mtrx(&mtr20, file20);
    fclose(file20);

    int **mtrx20 = NULL;
    mtrx20 = make_mtrx(mtr20);

    start1 = tick();
    do_addition_1(mtr20, mtr20);
    finish1 = tick();

    result1 = finish1 - start1;
    percent = (double)(mtr20->counter) / (double)((mtr20->cols) * (mtr20->rows));
    percent *= 100;

    start2 = tick();
    do_addition_2(mtrx20, mtrx20, mtr20, mtr20);
    finish2 = tick();

    result2 = finish2 - start2;

    size1 = (sizeof(int)) * 100 * 100;
    size2 = sizeof(matrix) + 101 * sizeof(int) + mtr20->counter * 2 * sizeof(int);

    printf(" Коэффициент заполнения:             %.0lf%%\n", percent);
    printf(" Сложение матриц в стандартном виде: %d\n", (int)result2);
    printf(" Сложение матриц в векторном виде:   %d\n\n", (int)result1);
    printf(" Памяти затрачено на стандартный формат: %d Байт(а).\n", size1);
    printf(" Памяти затрачено на векторный формат:   %d Байт(а).\n", size2);

    FILE *file50 = fopen("50.txt","r");
    matrix *mtr50 = calloc(1, sizeof(matrix));
    create_mtrx(&mtr50, file50);
    fclose(file50);

    int **mtrx50 = NULL;
    mtrx50 = make_mtrx(mtr50);

    start1 = tick();
    do_addition_1(mtr50, mtr50);
    finish1 = tick();

    result1 = finish1 - start1;
    percent = (double)(mtr50->counter) / (double)((mtr50->cols) * (mtr50->rows));
    percent *= 100;

    start2 = tick();
    do_addition_2(mtrx50, mtrx50, mtr50, mtr50);
    finish2 = tick();

    result2 = finish2 - start2;

    size1 = (sizeof(int)) * 100 * 100;
   size2 = sizeof(matrix) + 101 * sizeof(int) + mtr50->counter * 2 * sizeof(int);

    printf(" Коэффициент заполнения:             %.0lf%%\n", percent);
    printf(" Сложение матриц в стандартном виде: %d\n", (int)result2);
    printf(" Сложение матриц в векторном виде:   %d\n\n", (int)result1);
    printf(" Памяти затрачено на стандартный формат: %d Байт(а).\n", size1);
    printf(" Памяти затрачено на векторный формат:   %d Байт(а).\n", size2);

    FILE *file70 = fopen("70.txt","r");
    matrix *mtr70 = calloc(1, sizeof(matrix));
    create_mtrx(&mtr70, file70);
    fclose(file70);

    int **mtrx70 = NULL;
    mtrx70 = make_mtrx(mtr70);

    start1 = tick();
    do_addition_1(mtr70, mtr70);
    finish1 = tick();

    result1 = finish1 - start1;
    percent = (double)(mtr70->counter) / (double)((mtr70->cols) * (mtr70->rows));
    percent *= 100;

    start2 = tick();
    do_addition_2(mtrx70, mtrx70, mtr70, mtr70);
    finish2 = tick();

    result2 = finish2 - start2;

    size1 = (sizeof(int)) * 100 * 100;
    size2 = sizeof(matrix) + 101 * sizeof(int) + mtr70->counter * 2 * sizeof(int);

    printf(" Коэффициент заполнения:             %.0lf%%\n", percent);
    printf(" Сложение матриц в стандартном виде: %d\n", (int)result2);
    printf(" Сложение матриц в векторном виде:   %d\n\n", (int)result1);
    printf(" Памяти затрачено на стандартный формат: %d Байт(а).\n", size1);
    printf(" Памяти затрачено на векторный формат:   %d Байт(а).\n", size2);

    FILE *file100 = fopen("100.txt","r");
    matrix *mtr100 = calloc(1, sizeof(matrix));
    create_mtrx(&mtr100, file100);
    fclose(file100);

    int **mtrx100 = NULL;
    mtrx100 = make_mtrx(mtr100);

    start1 = tick();
    do_addition_1(mtr100, mtr100);
    finish1 = tick();

    result1 = finish1 - start1;
    percent = (double)(mtr100->counter) / (double)((mtr100->cols) * (mtr100->rows));
    percent *= 100;

    start2 = tick();
    do_addition_2(mtrx100, mtrx100, mtr100, mtr100);
    finish2 = tick();

    result2 = finish2 - start2;

    size1 = (sizeof(int)) * 100 * 100;
    size2 = sizeof(matrix) + 101 * sizeof(int) + mtr100->counter * 2 * sizeof(int);

    printf(" Коэффициент заполнения:             %.0lf%%\n", percent);
    printf(" Сложение матриц в стандартном виде: %d\n", (int)result2);
    printf(" Сложение матриц в векторном виде:   %d\n\n", (int)result1);
    printf(" Памяти затрачено на стандартный формат: %d Байт(а).\n", size1);
    printf(" Памяти затрачено на векторный формат:   %d Байт(а).\n", size2);
}

int min(int el1, int el2)
{
    int result;

    if (el1 >= el2)
        result = el2;
    else
        result = el1;

    return result;
}

int max(int el1, int el2)
{
    int result;

    if (el1 <= el2)
        result = el2;
    else
        result = el1;

    return result;
}

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}

void show_title(int flag, int code)
{
    switch (flag)
    {
    case 1:
        printf(" ----================================================----\n"
               "                --== Сложение матриц 1 ==--\n"
               " ----================================================----\n"
               "                      ВЕКТОРНЫЙ ВИД \n"
               );
        break;
    case 2:
        printf(" ----================================================----\n"
               "                --== Сложение матриц 2 ==--\n"
               " ----================================================----\n"
               "                     СТАНДАРТНЫЙ ВИД \n"
               );
        break;
    case 3:
        printf(" ----================================================----\n"
               "                --== Сравнение времени ==--\n"
               " ----================================================----\n"
               "     Результат сравнения времени алгоритмов сложения\n");
        break;
    case 4:
        printf(" ----================================================----\n"
               "                --== Сравнение памяти ==--\n"
               " ----================================================----\n"
               "          Результат сравнения затраченной памяти\n\n");
        break;
    case 5:
        printf(" ----================================================----\n"
               "                 --== Векторный вывод ==--\n"
               " ----================================================----\n"
               "            Показаны матрицы в векторном виде\n");
        break;

    case 6:
        printf(" ----================================================----\n"
               "                --== Стандартный вывод ==--\n"
               " ----================================================----\n"
               "            Показаны матрицы в стандатрном виде\n");
        break;

    case 7:
        printf(" ----================================================----\n");
        break;

    case 8:
        printf("                   --== Матрица %d ==--\n\n", code);
        break;

    case 9:
        printf(" ----================================================----\n"
               "                      --== Меню ==--\n"
               " ----================================================----\n\n");
        break;

    case 10:
        printf(" ----================================================----\n"
               "              --== Заполнение матрицы ==--\n"
               " ----================================================----\n\n");
        break;
    }
}

void get_vector(matrix **mtr)
{
    int result;

    int row;
    int col;

    printf(" Введите размер матрицы:             ");
    result = scanf(" %d %d", &row, &col);

    while (result != 2)
    {
        rewind(stdin);
        printf(" Некорректный ввод.\n Введите размер матрицы:  ");
        result = scanf(" %d %d", &row, &col);
    }
    rewind(stdin);

    (*mtr)->cols = col;
    (*mtr)->rows = row;

    init_mtrx(mtr, row, col);

    int counter;

    printf(" Введите число ненулевых элементов:  ");

    result = scanf("%d", &counter);
    if (counter > (row * col) || counter < 1)
        result = 0;

    while (result != 1)
    {
        rewind(stdin);
        printf(" Некорректный ввод.\n");
        printf(" Введите число ненулевых элементов: ");
        result = scanf("%d", &counter);
    }
    rewind(stdin);

    (*mtr)->counter = counter;

    result = 0;
    int element;

    while (result != 1)
    {
        printf(" Введите ненулевые элементы матрицы:  ");
        for (int i = 0; i < counter; i++)
        {
            result = scanf("%d", &element);
            if (result == 1)
            {
                if (element > col -1 || element < 0)
                    break;

                (*mtr)->value[i] = element;
            }
            else
            {
                rewind(stdin);
                printf("\n");
                break;
            }
        }
    }
    rewind(stdin);
    result = 0;

    while (result != 1)
    {
        printf(" Введите номера столбцов элементов:  ");
        for (int i = 0; i < counter; i++)
        {
            result = scanf("%d", &element);
            if (result == 1)
            {
                if (element > col -1 || element < 0)
                    break;

                (*mtr)->col[i] = element;
            }
            else
            {
                rewind(stdin);
                printf("\n");
                break;
            }
        }
    }
    rewind(stdin);
    result = 0;
    int points = 0;

    while (result != 1)
    {
        printf(" Введите номера 1х элементов строки: ");
        for ( ; points < row + 1; points++)
        {
            result = scanf(" %d", &element);
            if (result == 1)
            {
                if (element < 0)
                    break;

                (*mtr)->pointer[points] = element;
            }
            else
            {
                rewind(stdin);
                printf("\n");
                break;
            }
        }
    }

    (*mtr)->points = points + 1;
    rewind(stdin);
}

int **get_position(int *rows, int *cols)
{
    int row;
    int col;
    int result;

    printf("────────────────────────────────────────────────────────\n");

    printf(" Введите размеры матрицы:                 ");
    result = scanf("%d %d", &row, &col);

    while (result != 2)
    {
        rewind(stdin);
        printf(" Некорректный ввод!\n");
        printf(" Введите размеры матрицы:                 ");
        result = scanf("%d %d", &row, &col);
    }
    rewind(stdin);

    (*rows) = row;
    (*cols) = col;

    int **mtr1 = NULL;
    mtr1 = mtr_alloc(row, col);

    if (mtr1 != NULL)
    {
        int rows_1 = 0;
        int cols_1 = 0;
        int flag;
        int counter;
        int element = 0;

        printf(" Введите количество ненулевых элементов:  ");
        result = scanf("%d", &counter);

        while (result != 1)
        {
            rewind(stdin);
            printf(" Некорректный ввод!\n");
            printf(" Введите количество ненулевых элементов:  ");
            result = scanf("%d", &counter);
        }

        printf("────────────────────────────────────────────────────────\n");

        for (int i = 0; i < counter; i++)
        {
            result = 0;
            flag = 1;
            while (result != 3 || !flag)
            {
                rewind(stdin);

                if (flag == 0)
                    printf(" Введены некорректные значения\n");

                printf(" Введите координаты и значение %d элемента: ", (i+1));
                result = scanf("%d %d %d", &rows_1, &cols_1, &element);

                if (result == 3)
                {
                    if (rows_1 < 0 || rows_1 >= (*rows) || cols_1 < 0 || cols_1 >= (*cols))
                    {
                        result = ERROR;
                        flag =   0;
                    }
                    else
                        flag = 1;
                }
            }
            rewind(stdin);

            mtr1[rows_1][cols_1] = element;
        }
    }
    if (!mtr1)
        printf("broken");
    return mtr1;
}

void put_in_file(int **mtr, int row, int col)
{
    FILE *file = NULL;
    file = fopen("data.txt", "w");

    fprintf(file, "%d %d\n", row, col);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            fprintf(file, "%d ", mtr[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}
