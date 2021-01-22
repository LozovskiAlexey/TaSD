#include "funcs.h"

void menu()
{
    int code, option;
    wr_t *head = get_graph();

    if (head)
    {
        //show_graph(head); выводит содержимое файла
        code = SUCCESS;
        print_result(code);

        show_headline(1, "--== Menu ==--");
        show_options();
        check_input(&option);

        while (option)
        {
            switch(option)
            {
            case 1:          //сделать gv файл
                make_gv(head);
                break;
            case 2:          //проверить граф на связность
                check(head);
                break;
            case 3:          //обновить граф
                free_gr(head);
                head = get_graph();
                break;
            case 4:
                check_time();
                break;
            case 0:
                return;
            default:         //ошибка ввода
                code = INV_INPUT;
                print_result(code);
                break;
            }

            show_headline(1, "--== Menu ==--");
            show_options();
            check_input(&option);
        }
    }
    else
    {
        code = INV_DATA;
        print_result(code);
    }

}

void free_gr(wr_t *head)
{
    for (int i = 0; i < head->size; i++)
    {
        node_t *tmp = head->head[i];
        node_t *curr = tmp;
        while (tmp)
        {
            tmp = tmp->next;
            free(curr);
            curr = tmp;
        }
    }

    free(head);
}

void show_options(void)
{
    printf(" 1. Make .gv file.\n"
           " 2. Check graph.\n"
           " 3. Switch graph.\n"
           " 4. Check time.\n"
           " 0. Exit. \n"
           " Put the digit: ");
}

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

//показывает заголовок
//принимает на вход текст заголовка и более менее
//красиво его выводит
void show_headline(int num, ...)
{
    va_list headlines;
    va_start(headlines, num);

    const char *line = " ============"
                       "============="
                       "============="
                       "============="
                       "==== ";
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

//печатает строку-разделитель
void print_line(char symb)
{
    printf(" ");
    for (int i = 0; i < 55; i++, printf("%c", symb));
    printf("\n");
}
