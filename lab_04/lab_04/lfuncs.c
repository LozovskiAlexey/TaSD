#include "funcs.h"

//добавить просмотр стека
//добавить просмотр массива адресов

int do_lmenu(Stack_t **stack, adress_t *adress)
{
    int result;

    printf(" 1. Добавить элемент в стек.\n"
           " 2. Удалить элемент из стека.\n"
           " 3. Вывести убывающие серии последовательности.\n"
           " 4. Сравнить работу стеков.\n"
           " 5. Показать содержимое стека\n"
           " 0. Выход.\n"
           " Введите число: ");

    result = check_input();
    switch (result)
    {
    case 1:
        show_title(4);
        lpush_data(stack, adress);
        break;

    case 2:
        show_title(5);
        lpop_data(stack, adress);
        break;

     case 3:
        show_lsequences(stack, adress);
        break;

     case 4:
        test();
        break;

     case 5:
        show_title(9);
        show_stack(*stack, adress);
        break;

     case 0:
        result = EXIT;
        break;

      default:
        printf(" Неверный ввод.\n");
    }

    return result;
}

void lpush(Stack_t **head, Type value)
{
    Stack_t *tmp = malloc(sizeof(Stack_t));

    tmp->next = *head;

    if (*head == NULL)
        tmp->limit = 1;
    else
        tmp->limit += (*head)->limit + 1;

    tmp->value = value;
    *head = tmp;
}

void lpush_data(Stack_t **head, adress_t *adress)
{
    if (*head)
        if ((*head)->limit + 1 > STACK_SIZE)
        {
            printf("_______________________________________________________\n");
            printf("                    Стек переполнен.\n");
            return;
        }

    int result;

    printf(" Введите элемент: ");
    result = check_input();

    lpush(head, result);

    adress->value[++adress->counter] = result;
    adress->p[adress->counter] = (*head);
    printf("_______________________________________________________\n");
    printf("         Элемент                      Адрес            \n");
    printf("%14d                 %18p\n",
            adress->value[adress->counter],
            (void *)(adress->p[adress->counter]));

    printf("_______________________________________________________\n");
    printf(" Успешно.\n");
}

void lpop_data(Stack_t **head, adress_t *adress)
{
    if (!(*head))
    {
        printf("                     Стек пустой.\n");
        return;
    }

    Stack_t *element = NULL;
    element = lpop(head);
    if (element)
    {
        //вывод
        adress->p[adress->counter] = element;
        printf("%14d                 %18p\n",
                adress->value[adress->counter],
                (void *)(adress->p[adress->counter]));

        adress->counter--;
    }
}

Stack_t *lpop(Stack_t **head)
{
    Stack_t *element = NULL; //элемент который я верну аки моисей вернул свободу людям

    element = *head;
    *head = (*head)->next;

    free(element);

    return element;
}

void show_stack(Stack_t *head, adress_t *adress)
{
    if (!head)
    {
        printf("                     Стек пустой.\n");
        return;
    }

    int i = adress->counter;
    for (Stack_t *tmp = head; tmp; tmp = tmp->next)
    {
        printf("%14d                 %18p\n",
               tmp->value, (void *)(adress->p[i--]));
    }
}

void show_lsequences(Stack_t **head, adress_t *adress)
{
    if (adress->counter == -1)
    {
        printf("_______________________________________________________\n");
        printf("                     Стек пустой.\n");
        return;
    }

    show_title(5);
    int array[STACK_SIZE];
    int counter = 0;

    while ((*head) && adress->counter > -1)
    {
        array[counter] = adress->value[adress->counter];
        lpop_data(head, adress);

        counter++;
    }

    printf("_______________________________________________________\n");
    printf("\n Считанные данные: ");
    for (int i = 0; i < counter; i++)
        printf("%d ", array[counter - 1 - i]);
    printf("\n");

    printf(" Реузльтат:        ");

    int count = 1; //считает длинну последовательности
    int flag = 0;  //если были найдены серии

    for (int i = 0; i < counter - 1; i++)
    {
        if (array[i] < array[i + 1])
            count++;
        else
        {
            if (count > 1)
            {
                int j = i;
                flag = 1;
                while (count != 0)
                {
                    printf("%d ", array[j]);
                    j--;
                    count--;
                }
                printf(" ");
                count = 1;
            }
        }
    }
    if (count > 1)
    {
        flag = 1;
        int j = counter - 1;
        while (count != 0)
        {
            printf("%d ", array[j]);
            j--;
            count--;
        }
    }

    if (!flag)
        printf(" - \n Убывающих серий последовательности не найдено.");

    printf("\n");
}
void show_title(int flag)
{
    switch (flag)
    {
    case 1:
        printf("=======================================================\n"
               "                  == Выбор стека ==                    \n"
               "=======================================================\n");
        break;

    case 2:
        printf("=======================================================\n"
               "                      == Меню ==                       \n"
               "                == Стек как массив ==                  \n"
               "=======================================================\n");
        break;

    case 3:
        printf("=======================================================\n"
               "                      == Меню ==                       \n"
               "                 == Стек как список ==                 \n"
               "=======================================================\n");
        break;

    case 4:
        printf("=======================================================\n"
               "                   == Заполнение ==                    \n"
               "=======================================================\n");
        break;

    case 5:
        printf("=======================================================\n"
               "                  == Освобождение ==                   \n"
               "=======================================================\n"
               "         Элемент                      Адрес            \n");
        break;

    case 6:
        printf("=======================================================\n"
               "                   == Результат ==                   \n"
               "=======================================================\n");
        break;

    case 7:
        printf("=======================================================\n"
               "                    == Адреса ==                   \n"
               "=======================================================\n");
        break;

    case 8:
        printf("=======================================================\n"
               "            == Вывод последовательности ==             \n"
               "=======================================================\n");
        break;

    case 9:
        printf("=======================================================\n"
               "                 == Содержимое стека ==                \n"
               "=======================================================\n"
               "         Элемент                      Адрес            \n");
        break;

    }
}
