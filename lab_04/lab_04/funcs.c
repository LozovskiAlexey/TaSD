#include "funcs.h"

int stack_menu()
{
    int result;

    printf(" Работать со стеком реализованным как\n"
           " 1. Массив\n"
           " 2. Список\n"
           " Введите: ");

    result = check_input();

    switch (result)
    {
    case 1:
    case 2:
        break;

    default:
        result = ERROR;
        break;
    }

    return result;
}

int do_menu(stack_t *stack)
{
    int result;

    printf(" 1. Добавить элемент в стек.\n"
           " 2. Удалить элемент из стека.\n"
           " 3. Вывести убывающие серии последовательности.\n"
           " 4. Сравнить работу стеков.\n"
           " 5. Показать содержимое стека. \n"
           " 0. Выход.\n"
           " Введите число: ");

    result = check_input();
    switch (result)
    {
    case 1:
        show_title(4);
        push_data(stack);
        break;

    case 2:
        show_title(5);
        pop_data(stack);
        break;

    case 3:
        show_sequences(stack);
        break;

    case 4:
        test();
        break;

    case 5:
        show_title(9);
        show_stack_ar(stack);
        break;

    case 0:
        result = EXIT;
        break;

    default:
        printf(" Неверный ввод.\n");
    }

    return result;
}

void push_data(stack_t *stack)
{
    Type element;
    int result;
    int amount = 0; //Число добавляемых элементов

    if (!stack->overflow)
    {
        printf(" Добавить: \n"
               " 1. Элемент\n"
               " 2. Последовательность\n"
               " Введите число: ");

        result = check_input();
        switch (result)
        {
        case 1:
            printf("_______________________________________________________\n");
            amount = 1;
            printf(" Введите число:              ");
            break;

        case 2:
            printf("_______________________________________________________\n");
            printf(" Введите число элементов:    ");
            amount = check_input();
            fflush(stdin);
            printf(" Введите последовательность: ");
            break;

        default:
            printf(" Некорректный ввод.\n");
            return;
        }


        if (amount > 0)
        {
            for (int i = 0; i < amount; i++)
            {
                element = check_input();
                push(stack, element);
                if (i < STACK_SIZE)
                    printf("%14d                 %18p \n",
                           element, (void *)&stack->data[stack->tmp]);

                if (stack->overflow)
                    break;
            }
        }
    }
    fflush(stdin);
    if (stack->overflow)
    {
        printf("_______________________________________________________\n");
        printf("                 Стек переполнен.\n");
    }
}

void pop_data(stack_t *stack)
{
    Type *element = NULL;

    if (!stack->underflow)
    {
        element = pop(stack);
        show_data(element);
    }
    else
        printf("                     Стек пустой.\n");
}

void show_sequences(stack_t *head)
{
    if (head->underflow)
    {
        printf("_______________________________________________________\n");
        printf("                     Стек пустой.\n");
    }

    Type *element = NULL;

    int array[STACK_SIZE];
    int counter = 0;

    while (!head->underflow)
    {
        element = pop(head);
        if (element)
        {
            show_data(element);
            array[counter++] = *element;
        }
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

//проверка ввода
int check_input(void)
{
    int result;
    int value;

    result = scanf("%d", &value);
    while (result != 1)
    {
        fflush(stdin);
        printf("Некорректный ввод.\n");
        printf("Введите число: ");

        result = scanf("%d", &value);
    }

    result = value;
    return result;
}

void show(stack_t *stack)
{
    int size = stack->tmp;
    printf("size = %d", size);

    for (Type i = 0; i < size; i++)
        printf("%d ", stack->data[i]);

    printf("\n");
}

void push(stack_t *stack, Type element)
{
    stack->underflow = 0;

    if ((stack->tmp + 1) < stack->end)
    {
        stack->data[++(stack->tmp)] = element;
    }
    else
    {
        fflush(stdin);
        stack->overflow = 1;
    }
}

Type *pop(stack_t *stack)
{
    stack->overflow = 0;

    if ((stack->tmp) > stack->start)
        return (stack->data + stack->tmp--);
    else
    {
        stack->underflow = 1;
        return NULL;
    }
}

stack_t *init(void)
{
    stack_t *stack = NULL;
    stack = malloc(sizeof(stack_t));

    stack->start = -1;
    stack->end = STACK_SIZE;
    stack->tmp = -1;

    stack->overflow = 0;
    stack->underflow = 1;

    return stack;
}

void show_stack_ar(stack_t *head)
{
    if (head->underflow)
    {
        printf("_______________________________________________________\n");
        printf("                     Стек пустой.\n");
        return;
    }

    int i = head->tmp;

    while ( i > -1)
    {
        printf("%14d                 %18p\n", head->data[i], (void *)(head->data + i));
        i--;
    }
}

adress_t *adress_init(void)
{
    adress_t *adress = NULL;
    adress = malloc(sizeof(adress_t));

    adress->counter = -1;

    return adress;
}

void show_data(Type *element)
{
    if (element)
        printf("%14d                 %18p \n",
               *element, (void *)element);
    else
        printf("                     Стек пустой.\n");
}
