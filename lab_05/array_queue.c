#include "funcs.h"

//инциализация
void arr_init(arr_t **array, double *T1, double *T2)
{
    (*array) = malloc(sizeof(arr_t));

    (*array)->pin = 1; // позиция первого элемента в очереди
    (*array)->pout = 0; //позиция последнего

    (*array)->pr_counter = 0;
    (*array)->en_counter = 0;

    (*array)->T1 = T1;
    (*array)->T2 = T2;
}

//добавление
int arr_add(arr_t *ar, double *time) //добавить время
{
    int result = isfull(ar);
    if (!result)
    {
        ar->pout++;
        ar->q[ar->pout] = 0;
        (*time) = get_t(ar->T1[0], ar->T1[1]);

        ar->en_counter++;

        if (ar->en_counter < LIMIT)
            ar->en_time += *time;                 //добавляем время прихода

    }
    return result;
}

//удаление
int arr_delete(arr_t *ar, double *time, int *flag) //добавить время
{
    int result = isempty(ar);
    if (!result)
    {
        for (int i = ar->pin; i < ar->pout - 1; i++)
            ar->q[i] = ar->q[i+1];

        (*time) = get_t(ar->T2[0], ar->T2[1]);

        ar->pr_counter++;
        ar->pr_time += *time;

        (ar->pout)--;
    }
    else
        *flag = (*flag == 0);
    return result;
}

//проверка на пустоту
int isempty(arr_t *ar)
{
    return (ar->pout < ar->pin) ? 1 : 0;
}

//проверка на переполнение
int isfull(arr_t *ar)
{
    return (ar->pout >= QMAX - 1) ? 1 : 0;
}

//симулятор
void do_arr_module(arr_t *q1, arr_t *q2)
{
    double en_time1, en_time2;         //entry_time
    double pr_time;                  //process_time

    arr_t *q[2] = { q1, q2 };

    int flag = 0; //приоритет очереди
    int i = 0;

    if  (q2->T2[0] >= q1->T1[1])
    {
        printf(" _______________________________________________________\n");
        printf(" Failed to simulate module. The first queue\n"
               " will never be processed\n");
        return;
    }

    data_t *data = NULL; //храним тут промежуточные результаты
    data_init(&data);
    data_t *data1 = NULL; //храним тут промежуточные результаты
    data_init(&data1);

    show_headline(1, "== Do module ==");

    arr_add(q1, &en_time1);
    arr_add(q1, &en_time2);

    flag = (en_time1 < en_time2) ? 0 : 1;
    pr_time = get_t((q[flag])->T2[0], (q[flag])->T2[1]); //поиск первой заявки
    arr_delete(q[flag], &pr_time, &flag);     //на обработку в ОА

    while (q1->pr_counter < LIMIT) //LIMIT 1000
    {
        if (!(int)en_time1 || !(i % (int)en_time1)) //добавление заявок в очереди
        {
            int result = arr_add(q1, &en_time1);
            if (result == 1)
            {
                printf("Queue overflow.\n");
                return;
            }
        }
        if (!(int)en_time2 || !(i % (int)en_time2)) //добавление заявок в очереди
        {
            int result = arr_add(q2, &en_time2);
            if (result == 1)
            {
                printf("Queue overflow.\n");
                return;
            }
        }
        if (!(int)pr_time || !(i % (int)pr_time)) //обработка заявки
        {
            arr_delete(q[flag], &pr_time, &flag);
            show_arr_gap(q1,q2, data,data1, i, flag);
        }
        //printf("%d\n", i);
        i++;
    }
}

//вывод результатов
void show_arr_gap(arr_t *q1, arr_t *q2, data_t *data1, data_t *data2, int i, int flag)
{
    if (i && !(q1->pr_counter % 100) && !flag)
    {
        double time = (i - data1->time) / 100;
        data1->t_st = i;

        double qlen = (q1->en_counter > q1->pr_counter) ? q1->en_counter - q1->pr_counter : 0;
        double avg_len = (qlen + data1->l_st) / 200;

        printf(" Queue: 1 \n");
        printf(" Average queue length: %.0lf\n"
               " Average request time: %.3lf\n"
               " Temporary length:     %.0lf\n\n",
               avg_len, time, qlen);


        time = (i - data2->time) / 100;
        data1->t_st = i;

        qlen = (q2->en_counter > q2->pr_counter) ? q2->en_counter - q2->pr_counter : 0;
        avg_len = (qlen + data2->l_st) / 200;

        printf(" Queue: 2\n");
        printf(" Average queue length: %.0lf\n"
               " Average request time: %.3lf\n"
               " Temporary length:     %.0lf\n\n",
               avg_len, time, qlen);
    }
}

void free_arr(arr_t *q)
{
    q->pin = 1; //начало
    q->pout = 0; //конец очереди

    q->en_time = 0;
    q->pr_time = 0;

    q->pr_counter = 0;
    q->en_counter = 0;
}

void show_arr_time(arr_t *q1, arr_t *q2)
{
    show_headline(1, "== Result ==");
    double avr_en_time = (q1->T1[0] + q1->T1[1]) / 2; //среднее время входа

    //  Вывод количества заявок
    printf(" Requests came:           \n"
           " First queue:            %d requests\n"
           " Second queue:           %d requests\n\n"
           " Requests out:            \n"
           " First queue:            %d requests\n"
           " Second queue:           %d requests\n\n",
           q1->en_counter, q2->en_counter,
           q1->pr_counter, q2->pr_counter);

    //среднее время обработки каждого типа заявок
    double avr_time1 = (q1->T2[0] + q1->T2[1]) / 2;
    double avr_time2 = (q2->T2[0] + q2->T2[1]) / 2;

    //число обработок и время обработок обеих очередей
    int pr_counter = q1->pr_counter + q2->pr_counter;
    double pr_time = q1->pr_counter * avr_time1 + q2->pr_counter * avr_time2;

    // Аппарат обработал
    printf(" Handler processed:      %d requests\n"
           " Handler time:           %.3lf t.u\n\n", //t.u - time units - ед. времени
           pr_counter, pr_time);

    // проверяем корректность количества пришедших заявок 1 очереди
    double come = q1->en_time / avr_en_time;
    printf(" Counted entry:          %.3lf\n", come);
    double inf = (LIMIT - come) / come;
    printf(" Exp/real entry amount:  %.3lf%%\n", fabs(inf * 100));


    free_arr(q1);
    free_arr(q2);
}
