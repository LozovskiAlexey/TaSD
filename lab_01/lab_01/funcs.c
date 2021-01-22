#include "funcs.h"

void print_arr(int *arr, int len)
{
    for (int i = 1; i <= len; i++)
    {
        printf("%d", arr[i]);
    }
    printf("\n");
}

int print_res(int *res, int len, int ex)
{
    //Округление мантисы до 30 знаков
    while (len > 30)
    {
        if (res[31] > 4)
            res[30]++;
        for (int i = 30; i > 1; i--)
        {
            if (res[i] > 9)
            {
                res[i - 1] += 1;
                res[i] -= 10;
            }
        }
        if (res[1] > 9)
        {
            for (int i = 31; i > 1; i--)
                res[i] = res[i - 1];
            res[1] = 1;
            res[2] -= 10;
            ex++;
            len++;
        }
        len--;
    }

    //Проверка переполнения порядка
    while (res[1] == 0 && ex > 99999 && len > 1)
    {
        for (int i = 1; i < len; i++)
            res[i] = res[i + 1];
        ex--;
        len--;
    }
    if (ex > 99999)
    {
        printf("Переполнение порядка результата.\n");
        return 0;
    }
    //Проверка получения машинного нуля
    if (ex < -99999)
    {
        printf("Порядок меньше -99999\n");
        return 0;
    }
    printf("\nРезультат: ");
    //Вывод знака.
    if (res[0])
        printf("-");
    //Вывод числа.
    printf("0.");
    for (int i = 1; i <= len; i++)
        printf("%d", res[i]);
    if (len == 0)
        printf("0");
    printf("E%d\n", ex);

    return 0;
}

int divide_ints(int *arr1, int n1, int *arr2, int n2, int *res)
{
    int q;
    int tmp_arr[N];
    int tmp_len;
    int n = 1;
    int len = 0;
    int tmp = compare(arr1, n1, arr2, n2);

    if (tmp == 0)
    {
        res[1] = 1;
        return 1;
    }
    else if (n2 == 1 && arr2[1] == 1)
    {
        for (int i = 1; i <= n1; i++)
            res[i] = arr1[i];
        return n1;
    }
    else while (len < 31 && arr1[1] != 0)
    {
        tmp = compare(arr1, n, arr2, n2);

        if (tmp < 0)
        {
            n++;
            arr1[++n1] = 0;
            if (len > 0 && compare(arr1, n, arr2, n2) < 0)
                res[++len] = 0;
        }
        else if (tmp == 0)
        {
            for (tmp_len = 0; tmp_len <= n2; tmp_len ++)
                tmp_arr[tmp_len] = arr2[tmp_len];
            for (; tmp_len <= n2 + (n1 - n2); tmp_len++)
                tmp_arr[tmp_len] = 0;
            res[++len] = 1;
            subtract(arr1, &n1, tmp_arr, tmp_len - 1);
            if (arr1[1] == 0 && n1 > n && arr1[2] == 0)
            {
                for (int i = 1; i < n1; i++)
                    arr1[i] = arr1[i + 1];
                n1--;
                res[++len] = 0;
            }
            align_int(arr1, &n1);
        }
        else
        {
            q = 1;
            for (tmp_len = 0; tmp_len <= n2; tmp_len++)
                tmp_arr[tmp_len] = arr2[tmp_len];

            tmp_len--;
            while (compare(arr1, n, tmp_arr, tmp_len) >= 0)
            {
                for (tmp_len = 0; tmp_len <= n2; tmp_len++)
                    tmp_arr[tmp_len] = arr2[tmp_len];
                tmp_len--;
                q++;
                multiplication(tmp_arr, &tmp_len, q);
            }
            for (tmp_len = 0; tmp_len <= n2; tmp_len++)
                tmp_arr[tmp_len] = arr2[tmp_len];
            --tmp_len;
            multiplication(tmp_arr, &tmp_len, q-1);
            int k = n1;
            res[++len] = q - 1;
            subtract(arr1, &n, tmp_arr, tmp_len);
            if (arr1[1] == 0 && arr1[2] == 0 && n1 > n && n1 >= 2 && n >= 2)
            {
                for (int i = 1; i < n1; i++)
                    arr1[i] = arr1[i + 1];
                n1--;
                n--;
                if (len > 0)
                    res[++len] = 0;
            }
            align_int(arr1, &k);
            n -= n1 - k;
            n1 = k;
        }
    }

    return len;
}

void multiplication(int *arr, int *n, int num)
{
    //Умножение длинного числа на натуральное <= 9
    int ost = 0;

    if (num == 0 || (arr[1] == 0 && *n == 1))
    {
        arr[1] = 0;
        *n = 1;
        return;
    }
    for (int i = *n; i > 0; i--)
    {
        arr[i] = arr[i] * num + ost;
        for (int j = i; j > 0; j--)
        {
            if (arr[j] > 9)
            {
                if (j == 1)
                {
                    for (int k = (*n) + 1; k > 0; k--)
                        arr[k] = arr[k-1];
                    (*n)++;
                }
                ost = arr[j] / 10;
                arr[j] %= 10;
            }
        }
    }

    if (*n > 1 && arr[2] >= 10)
    {
        arr[1] = arr[2] / 10;
        arr[2] %= 10;
    }
}

void subtract(int *arr1, int *n1, int *arr2, int n2)
{
    //Вычитание из длинного числа длинного числа.
    for (int i = *n1; i > 0; i--)
    {
        if (n2 - (*n1 - i) >= 1 && n2 - (*n1 - i) <= n2)
            arr1[i] -= arr2[n2 - (*n1 - i)];
        if (arr1[i] < 0)
        {
            arr1[i - 1] -= 1;
            arr1[i] += 10;
        }
    }
}

void align_int(int *arr1, int *n1)
{
    //Удаление незначащих нулей в начале числа.
    while (arr1[1] == 0 && (*n1) > 1)
    {
        for (int i = 2; i <= *n1; i++)
            arr1[i - 1] = arr1[i];
        (*n1)--;
    }
}

int compare(int *arr1, int n1, int *arr2, int n2)
{
    /*
    Сравнение 2ух длинных чисел
    Возвращает 1 если первое число больше, 0 если числа равны,
    -1 если второе число больше
    */
    if (n2 > n1)
        return -1;
    if (n1 > n2)
        return 1;

    for (int i = 1; i <= n1; i++)
    {
        if (arr1[i] > arr2[i])
            return 1;
        if (arr1[i] < arr2[i])
            return -1;
    }

    return 0;
}

void rm_insignificant_zeroes(int *arr, int *len, int *dot, int *ex)
{
    //Удаление незначащих нулей в начале числа.
    if (arr[1] == 0 && *len + *dot > 1)
    {
        for (int i = 1; i < *len && arr[i] == 0; i++, len--)
            arr[i] = arr[i + 1];
        if (*len > 1)
            (*len)--;
        else
            (*dot)--;
    }
}

int read_int(int *arr, int *ex)
{
    //Считывание целого числа.
    arr[0] = 0;
    _Bool sign = 0;
    int len = 0;
    char buff[2] = {'0', '\0'};
    char input[N];

    printf("Введите целое число не длиннее 30 цифр:\n");
    printf("|------------------------------|\n|");
    gets(input);

    for (int i = 0; input[i] != '\0'; i++)
    {
        if (len >= 30)
            return INPUT_ERR;
        if (!sign && (input[i] == '-' || input[i] == '+'))
        {
            sign = 1;
            if (input[i] == '-')
                arr[0] = 1;
            else
                arr[0] = 0;
            continue;
        }
        if (input[i] <= '9' && input[i] >= '0')
        {
            buff[0] = input[i];
            arr[++len] = atoi(buff);
        }
        else
        {
            return INPUT_ERR;
        }
    }

    for (int i = len; i > 1 && arr[i] == 0 ; i--, len--)
        (*ex)++;
    align_int(arr, &len);

    return len;
}

int read_double(int *arr, int *ex, int *dot_pos)
{
    //Считывание действительного числа.
    arr[0] = 0;
    short int tmp;
    char input[N + M];
    char buff[2] = {'0', '\0'};
    _Bool sign = 0;
    _Bool sign_exp = 0;
    _Bool exp_neg = 0;
    _Bool dot = 0;
    int int_count = 0;
    int float_count = 0;
    *ex = 0;

    printf("\nВведите действительное число (мантиса не длинне 30 цифр, порядок не длиннее 5):\n");
    printf("|------------------------------|\n|");
    gets(input);

    for (int i = 0; input[i] != '\0'; i++)
    {
        if (!sign && (input[i] == '-' || input[i] == '+') && i == 0)
        {
            sign = 1;
            if (input[i] == '-')
                arr[0] = 1;
            else
                arr[0] = 0;
            continue;
        }
        if (input[i] <= '9' && input[i] >= '0')
        {
            if (int_count + float_count >= 30)
                return INPUT_ERR;
            if (dot)
                float_count++;
            else
                int_count++;
            buff[0] = input[i];
            arr[float_count + int_count] = atoi(buff);
        }
        else if (input[i] == '.' || input[i] == ',')
        {
            if (dot)
                return INPUT_ERR;
            if (i == 0 || (sign && i == 1))
            {
                int_count++;
                arr[1] = 0;
            }
            dot = 1;
        }
        else if (input[i] == 'E' || input[i] == 'e')
        {
            i++;
            int len_ex = 0;
            while (1)
            {
                if (len_ex >= 5)
                    return INPUT_ERR;
                if (!sign_exp && (input[i] == '-' || input[i] == '+'))
                {
                    sign_exp = 1;
                    exp_neg = (input[i++] == '-');
                    continue;
                }
                if (input[i] <= '9' && input[i] >= '0')
                {
                    len_ex++;
                    buff[0] = input[i];
                    tmp = atoi(buff);
                    *ex = *ex * 10 + tmp;
                }
                else
                {
                    return INPUT_ERR;
                }
                if (input[i + 1] == '\0')
                    break;
                i++;
            }
            if (exp_neg)
                *ex = -(*ex);
        }
        else
        {
            return INPUT_ERR;
        }
    }
    *dot_pos = int_count;
    while (arr[1] == 0 && float_count-- >= 0 && int_count == 1)
    {
        for (int i = 1; i <= 1 + float_count; i++)
            arr[i] = arr[i + 1];
        (*ex)--;
    }
    if (float_count < 0)
    {
        float_count = 0;
    }
    rm_insignificant_zeroes(arr, &int_count, &float_count, ex);

    return int_count + float_count;
}
