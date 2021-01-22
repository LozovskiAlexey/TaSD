#include "funcs.h"

void a_add(arr_t *ar)
{
    int result = isfull(ar);
    if (!result)
    {
        ar->pout++;
        ar->q[ar->pout] = 0;
    }
}

void a_del(arr_t *ar)
{
    int result = isempty(ar);
    if (!result)
    {
        for (int i = ar->pin; i < ar->pout - 1; i++)
            ar->q[i] = ar->q[i+1];

        (ar->pout)--;
    }
}

void l_add(wrap_t *q, list_t *element)
{
    if (!(q->head))
    {
        q->head = element;
        q->tmp = q->head;
    }
    else
    {
        q->tmp->next = element;
        q->tmp = q->tmp->next;
    }
}

void l_del(wrap_t *q)
{
    if  (!(q->head))
        return;

    list_t *element = q->head;
    (q->head) = (q->head)->next;
    free(element);
}

void do_test(void)
{
    double T1[2] = { 1, 5 }; //default time для первой очереди
    double T2[2] = { 0, 4 };

    wrap_t *queue1 = NULL;
    arr_t *q1 = NULL;

    wrap_init(&queue1, T1, T2); //инициализируем очереди с дефолтным временем
    arr_init(&q1, T1, T2);

    show_headline(1, "== Test ==");

    //время для первой и второй очереди
    unsigned long long start1, finish1, result1;
    unsigned long long start2, finish2, result2;

    start1 = tick();
    for (int i = 0; i < LIMIT; i++)
        a_add(q1);

    for (int i = 0; i < LIMIT; i++)
        a_del(q1);

    finish1 = tick();
    result1 = finish1 - start1;
    int memory1 = LIMIT * sizeof(int) + 4 * sizeof(double);

    start2 = tick();
    for (int i = 0; i < LIMIT; i++)
    {
        list_t *request1 = init_element();
        l_add(queue1, request1);
    }
    for (int i = 0; i < LIMIT; i++)
        l_del(queue1);

    finish2 = tick();
    result2 = finish2 - start2;
    int memory2 = sizeof(wrap_t) + sizeof(list_t) * LIMIT + 4 * sizeof(double);

    printf("                     Массив              Список \n\n"
           "  Время              %4d              %2d         \n"
           "  Память             %d               %4d       \n\n",
           (int)result2, (int)result1, memory1, memory2);
}

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}
