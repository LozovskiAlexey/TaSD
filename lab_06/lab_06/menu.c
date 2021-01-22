#include "funcs.h"

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

//Показывает ошибку
void show_result(int code)
{
    char *text;
    switch (code)
    {
    case empty_file:
        text = " File is empty.";
        break;

    case open_file_error:
        text = " Failed to open the file.";
        break;

    case inv_input:
        text = "Incorrext input.";
        break;

    case find_error:
        text = " Failed to find the element.";
        break;

    case empty_data:
        text = "No data to show.";
        break;

    case restructurisation_error:
        text = " Need to restructure hash-table.";
        break;

    default:
        text = " Successfully done.";
        break;
    }

    printf("%s\n", text);
}

void show_main_menu()
{
    printf(" Select data structure:    \n"
           " 1. Tree.                  \n"
           " 2. AVL-tree.              \n"
           " 3. Hash-table.            \n"
           " 4. Test.                  \n"
           " 0. Exit.                  \n"
           " Put the number: ");
}

void main_menu()
{
    int inp_result;

    //показывает заголовок, показывает меню и проверяет ввод
    //show_headline(1, "== Menu ==");
    show_main_menu();
    check_input(&inp_result);

    while (inp_result)
    {
        switch(inp_result)
        {
        case 1:
            tree_menu();
            break;

        case 2:
            avl_tree_menu();
            break;

        case 3:
            hash_menu();
            break;

        case 4:
            test();
            break;

        case 0:
            return;

        default:
            show_result(inv_input);
            break;
        }

        //show_headline(1, "== Menu ==");
        show_main_menu();
        check_input(&inp_result);
    }
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

void get_name(char *name)
{
    int result;

    printf(" Input file name: ");
    result = scanf("%s", name);

    while (result != 1)
    {
        printf(" Incorrect input.\n");
        printf(" Input file name: ");
        result = scanf("%s", name);
    }
}

int get_element(void)
{
    printf(" Input the element: ");
    int search;
    check_input(&search);
    printf(" _______________________________________________________\n");

    return search;
}
