#include "funcs.h"

void src_menu(void)
{
    int operation;

    //вывод заголовка, меню и ввод команды
    show_headline(1, "== Source Menu ==");
    show_src_menu();
    check_input(&operation);

    while (operation != 0)
    {
        switch(operation)
        {
        case 1:
            do_ar_proc();
            break;
        case 2:
            do_lst_proc();
            break;
        case 3:
            do_test();
            break;
        case 0:
            return;
        default:
            //show_result(INV_INPUT); //если введено неверное число
            break;
        }

        show_headline(1, "== Source Menu ==");
        show_src_menu();
        check_input(&operation);
    }
}

void do_ar_proc(void)
{
    int operation;

    double T1[2] = { 1, 5 }; //default time для первой очереди
    double T2[2] = { 0, 4 };

    double T3[2] = { 0, 3 }; //default time для второй очереди
    double T4[2] = { 0, 1 };

    arr_t *q1 = NULL;
    arr_t *q2 = NULL;

    arr_init(&q1, T1, T2);
    arr_init(&q2, T3, T4);

    show_headline(2, "== Menu ==", "== Array Queue ==");
    show_menu();
    check_input(&operation);

    while (operation)
    {
        switch (operation)
        {
        case 1:
            time_arr_init(q1);
            time_arr_init(q2);

            do_arr_module(q1, q2);
            show_arr_time(q1, q2);
            break;
        case 2:

            do_arr_module(q1, q2);
            show_arr_time(q1, q2);
            break;
        case 0:
            return;
        default:
            //show_result(INV_INPUT); //если введено неверное число
            break;
        }

        show_headline(2, "== Menu ==", "== Array Queue ==");
        show_menu();
        check_input(&operation);
    }
}

void do_lst_proc(void)
{
    int operation;

    double T1[2] = { 1, 5 }; //default time для первой очереди
    double T2[2] = { 0, 4 };

    double T3[2] = { 0, 3 }; //default time для второй очереди
    double T4[2] = { 0, 1 };

    wrap_t *queue1 = NULL;
    wrap_t *queue2 = NULL;

    wrap_init(&queue1, T1, T2); //инициализируем очереди с дефолтным временем
    wrap_init(&queue2, T3, T4);

    //вывод заголовка в консоль, проверка ввода
    show_headline(2, "== Menu ==", "== List Queue ==");
    show_menu();
    check_input(&operation);

    while (operation)
    {
        switch (operation)
        {
        case 1:
            time_user_init(queue1); //указание нового времени работы программы
            time_user_init(queue2);

            do_model(queue1, queue2); //выполнение модели работы очередей
            show_time(queue1, queue2);
            break;
        case 2:
            do_model(queue1, queue2);
            show_time(queue1, queue2);
            break;
        case 0:
            return;
        default:
            //show_result(INV_INPUT); //если введено неверное число
            break;
        }

        show_headline(2, "== Menu ==", "== List Queue ==");
        show_menu();
        check_input(&operation);
    }
}

//Проверка ввода
void check_input(int *value)
{
    int result;

    result = scanf("%d", value);
    while (result != 1)
    {
        fflush(stdin);
        printf(" Incorrect input.\n"
               " Put the number: ");

        result = scanf("%d", value);
    }
}

//Ввод элемента с проверкой ввода
int get_element(void)
{
    printf(" Input the element: ");
    int search;
    check_input(&search);
    printf(" _______________________________________________________\n");

    return search;
}

//текст меню
void show_src_menu(void)
{
    printf(" Choose the struct data\n"
           " 1. Array queue.\n"
           " 2. List queue.\n"
           " 3. Test.\n"
           " 0. Exit.\n"
           " Put the number: ");
}

void show_menu()
{
    printf(" Choose option:\n"
           " 1. Change time.\n"
           " 2. Default time.\n"
           " 0. Switch structure.\n"
           " Put the number: ");
}
//показывает заголовок
//принимает на вход текст заголовка и более менее
//красиво его выводит
void show_headline(int num, ...)
{
    va_list headlines;
    va_start(headlines, num);

    const char *line = " =======================================================\0";
    printf("%s\n", line);

    for (int i = 0; i < num; i++)
    {
        const char *headline = va_arg(headlines, char*);
        put_headline(line, headline);
    }

    printf("%s\n", line);
    va_end(headlines);
}

//Добавление заголовка
//считает сколько нужно добавить пробелов перед строкой,
//чтобы она оказалась по середине
void put_headline(const char *line, const char *headline)
{
    int len_line = my_strlen(line);
    int len_headline = my_strlen(headline);

    int required_spaces = len_line  - len_headline;
    int result = required_spaces;

    required_spaces /= 2;

    if (result % 2)
        required_spaces += 1;

    for (int i = 0; i < required_spaces; i++)
        printf(" ");

    printf("%s\n", headline);
}

//нахождение длины строки
int my_strlen(const char *line)
{
    int size = 0;

    for (; line[size] != '\0'; size++);

    return size;
}
