#include "funcs.h"

int main(void)
{
    setbuf(stdout, NULL);
    int rc;
    int int_arr[N];
    int mant_arr[N];
    int res[N];
    int ex = 0;
    int int_ex = 0;
    int dot_pos;
    int int_len;
    int double_len;

    printf("Деление целого числа на вещественное.\n");
    //Чтение целого числа.
    int_len = read_int(int_arr, &int_ex);
    if (int_len <= 0)
    {
        printf("Ошибка ввода\n");
        return INPUT_ERR;
    }
    //Чтение вещественного числа.
    double_len = read_double(mant_arr, &ex, &dot_pos);
    if (double_len <= 0)
    {
        printf("Ошибка ввода\n");
        return INPUT_ERR;
    }
    if (double_len == 1 && mant_arr[1] == 0)
    {
        printf("Деление на 0.");
        return ERR_ZERO_DIVISION;
    }
    //Вычисление порядка результата.
    ex = -ex + int_len  + int_ex - dot_pos + 1;
    if (int_arr[1] < mant_arr[1])
        ex--;
    //Деление целого числа на вещественное.
    rc = divide_ints(int_arr, int_len, mant_arr, double_len, res);
    if (1 < rc)
        for (; rc > 1 && res[rc] == 0; rc--);
    res[0] = int_arr[0] ^ mant_arr[0];
    //Вывод результата.
    print_res(res, rc, ex);

    return 0;
}
