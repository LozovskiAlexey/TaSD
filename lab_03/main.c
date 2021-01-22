#include "funcs.h"

int main()
{
    int result;

    int mtr1_res;
    int mtr2_res;

    setbuf(stdout, NULL);
    matrix *mtr1 = calloc(1, sizeof(matrix));
    matrix *mtr2 = calloc(1, sizeof(matrix));

    mtr1_res = fill_mtr(&mtr1);
    mtr2_res = fill_mtr(&mtr2); //заполнение матрицы

    while (mtr1_res == ERROR || mtr2_res == ERROR)
    {
        free_all(&mtr1);
        free_all(&mtr2);

        mtr1_res = fill_mtr(&mtr1);
        mtr2_res = fill_mtr(&mtr2);
    }

    result = menu(mtr1, mtr2);
    while (result)
    {
        result = menu(mtr1, mtr2);
    }

    return show_result_text(result);
}
