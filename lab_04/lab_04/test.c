#include "funcs.h"

void test(void)
{
    //создать массив
    test_t *array = NULL;
    array = tinit();

    //создать список
    Stack_t *list = NULL;

    Type values[TEST_SIZE];
    int element;

    //структура для хранения адресов и значений
    Type *A_adress[TEST_SIZE];
    atest_t *Ladress = NULL; //Для списка
    Ladress = A_init();      //Инциализация

    //Заполнение массива значениями
    for (int i = 0; i < TEST_SIZE; i++)
    {
        element = rand() % 10 + 1;
        values[i] = element;
        Ladress->value[++Ladress->counter] = element;
    }

    //время для первого и второго стеков
    unsigned long long start1, finish1, result1;
    unsigned long long start2, finish2, result2;

//____________________________________________
    //Список

    Stack_t *data = NULL;
    start1 = tick();
    for (int i = 0; i < TEST_SIZE; i++)
        lpush(&list, values[i]);

    finish1 = tick();
    result1 = finish1 - start1;
    printf("Время добавления элемента: %d\n", (int)result1 / TEST_SIZE);

    start1 = tick();
    for (int i = 0; i < TEST_SIZE; i++)
    {
        data = lpop(&list);
        Ladress->p[Ladress->counter--] = data;
    }
    finish1 = tick();
    result1 = finish1 - start1;

    printf("Время удаления элемента: %d\n\n", (int)result1 / TEST_SIZE);
    int memory1 = sizeof(Stack_t) * TEST_SIZE;

//____________________________________________
    //Массив

    Type *Data = NULL;
    start2 = tick();
    for (int i = 0; i < TEST_SIZE; i++)
        tpush(array, values[i]);
    finish2 = tick();
    result2 = finish2 - start2;

    printf("Время добавления элемента: %d\n", (int)result2 / TEST_SIZE);

    start2 = tick();
    for (int i = 0; i < TEST_SIZE; i++)
    {
        Data = tpop(array);
        A_adress[i] = Data;
        //printf("%d %p\n", *A_adress[i], (void *)A_adress[i]);
    }
    finish2 = tick();
    result2 = finish2 - start2;

    printf("Время удаления элемента: %d\n\n", (int)result2 / TEST_SIZE);

    int memory2 = (5 + TEST_SIZE) * sizeof(int);

//____________________________________________

    show_title(6);

    printf("                     Массив                Список \n\n"
           "  Время               %4d                 %2d     \n"
           "  Память              %d                  %4d \n\n",
           (int)result2, (int)result1, memory2, memory1);

    show_title(7);

    printf("  Значение                       Адрес\n"
           "                     Массив                 Список              \n");

    int n = 0;
    int i = 0;
    int flag = 1;

    while (1)
    {
        n += 10; //показывать каждые 10 сл элементов

        if (flag == 1 && n < TEST_SIZE)
        {
            for (; i < n; i++)
            {
                printf("     %-6d  %19p  %21p\n",
                       *A_adress[TEST_SIZE - 1 - i], (void *)A_adress[TEST_SIZE - 1 - i],
                        (void*)Ladress->p[Ladress->counter + 1]);
                Ladress->counter++;
            }

            printf(" Показаны адреса первых 10 освобожденных элементов.\n");
            printf(" Показать еще?\n"
                   " 1. Да\n"
                   " 2. Нет\n"
                   " Введите число: ");
            flag = check_input();

            while (flag != 1 && flag != 2)
            {
                printf("Некорректный ввод.\n");
                printf("Введите число: ");
                flag = check_input();
            }
        }
        else
            return;
    }
}

test_t *tinit(void)
{
    test_t *array = NULL;
    array = malloc(sizeof(test_t));
    array->start = -1;
    array->end = TEST_SIZE;
    array->tmp = -1;

    array->overflow = 0;
    array->underflow = 1;

    return array;
}

atest_t *A_init(void)
{
    atest_t *adress = NULL;
    adress = malloc(sizeof(atest_t));

    adress->counter = -1;

    return adress;
}

void tpush(test_t *stack, Type element)
{
    stack->underflow = 0;

    if ((stack->tmp + 1) < stack->end)
        stack->data[++(stack->tmp)] = element;
    else
    {
        fflush(stdin);
        stack->overflow = 1;
    }
}

Type *tpop(test_t *stack)
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

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}
