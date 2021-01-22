#include "funcs.h"

//присваивает время
void time_add(double *time)
{
    get_time(&time[0], " Input the first time limit ");
    get_time(&time[1], " Input the last time limit  ");
}

//сюда подаются обертки каждой из очередей(списков)
//им присваиваются значения времени прихода и обработки
void time_user_init(wrap_t *list)
{
    const char *line = " =======================================================\0";
    show_headline(2, "== Queue ==", "== Arriving time ==");

    time_add(list->T1);

    printf("\n");
    put_headline(line, "== Processing time ==\n");

    time_add(list->T2);
}

//В общем, иначе никак.
void time_arr_init(arr_t *ar)
{
    const char *line = " =======================================================\0";
    show_headline(2, "== Queue ==", "== Arriving time ==");

    time_add(ar->T1);

    printf("\n");
    put_headline(line, "== Processing time ==\n");

    time_add(ar->T2);
}

//проверка ввода для корректного времени
//не проверяет если конечное время меньше начального
void get_time(double *time, const char *text)
{
    int result;

    printf("%s: ", text);

    result = scanf("%lf", time);
    if (result == 1 && *time < 0)
        result = 0;

    while (result != 1)
    {
        fflush(stdin);
        printf(" Incorrect input.\n"
               " %s: ", text);

        result = scanf("%lf", time);
        if (result == 1 && *time < 0)
            result = 0;
    }
}

//инициализация обертки очереди(списком)
//с default значениями времени
void wrap_init(wrap_t **queue, double *T1, double *T2)
{
    (*queue) = malloc(sizeof (wrap_t));

    (*queue)->head = NULL;
    (*queue)->tmp = NULL;

    (*queue)->en_time = 0;
    (*queue)->pr_time = 0;

    (*queue)->pr_counter = 0;
    (*queue)->counter = 0;

    (*queue)->T1 = T1; //default time
    (*queue)->T2 = T2;
}

void do_model(wrap_t *q1, wrap_t *q2)
{
    //переменные времени входа и обработки элемента
    double en_time1, en_time2;         //entry_time
    double pr_time;                  //process_time

    wrap_t *q[2] = { q1, q2 };
    list_t *request1 = init_element(); //инициализация заявок
    list_t *request2 = init_element();

    int flag = 0; //приоритет очереди
    int i = 0;

    if  (q2->T2[0] >= q1->T1[1] || q2->T1[1] < q2->T2[0])
    {
        printf(" _______________________________________________________\n");
        printf(" Failed to simulate module. The first queue\n"
               " will never be processed\n");
        return;
    }

    data_t *data = NULL; //храним тут промежуточные результаты
    data_t *data1 = NULL; //храним тут промежуточные результаты
    data_init(&data);
    data_init(&data1);

    show_headline(1, "== Do module ==");

    //добавление заявок
    add_element(request1, q1, &en_time1);
    add_element(request2, q2, &en_time2);

    flag = (en_time1 < en_time2) ? 0 : 1;
    pr_time = get_t((q[flag])->T2[0], (q[flag])->T2[1]); //поиск первой заявки
    process_element(q[flag], &pr_time, &flag, data);     //на обработку в ОА

    while (q1->pr_counter < LIMIT) //LIMIT 1000
    {
        request1 = init_element(); //инициализация заявок
        request2 = init_element();

        if (!(int)en_time1 || !(i % (int)en_time1)) //добавление заявок в очереди
        {
            add_element(request1, q1, &en_time1);
            if (q1->counter < 100)
                data->added[q1->counter - 1] = request1;
        }

        if (!(int)en_time2 || !(i % (int)en_time2))
            add_element(request2, q2, &en_time2);

        if (!(int)pr_time || !(i % (int)pr_time)) //обработка заявки
        {
            process_element(q[flag], &pr_time, &flag, data);
            show_gap(q1, q2, data, data1, i, flag);
        }
        i++;
    }
    show_headline(1, "== Show Memory ==");
    printf("             Added                   Deleted\n");

    int n = 0;
    int flag1 = 1;
    int j = 1;

    while (1)
    {
        n += 10; // показывать по 10 элементов

        if (flag1 == 1 && n < 100)
        {
            for (; j < n; j++)
            {
                printf(" %22p  %24p\n",
                       (void *)data->added[j], (void *)data->deleted[j]);
            }

            if ( j + 1 == 100)
                return;

            printf(" _______________________________________________________\n");
            printf(" Shown adresses of the first 10 elements\n");
            printf(" Show more: \n"
                   " 1. Yes\n"
                   " 2. No\n"
                   " Put the number: ");
            check_input(&flag1);

            while (flag1 != 1 && flag1 != 2)
            {
                printf(" Incorrect input.\n");
                printf(" Put the number: ");
                check_input(&flag1);
            }
            printf(" _______________________________________________________\n");
        }
        else return;
    }
}

double get_t(double min, double max)
{
    double t = (double)(rand()) / RAND_MAX;
    double res = (max - min) * t + min;

    return res;
}

void show_time(wrap_t *q1, wrap_t *q2)
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
           q1->counter, q2->counter,
           q1->pr_counter, q2->pr_counter);

    //среднее время обработки каждого типа заявок
    double avr_time1 = (q1->T2[0] + q1->T2[1]) / 2;
    double avr_time2 = (q2->T2[0] + q2->T2[1]) / 2;

    //число обработок и время обработок обеих очередей
    int pr_counter = q1->pr_counter + q2->pr_counter;
    double pr_time = q1->pr_counter * avr_time1 + q2->pr_counter * avr_time2;

    // Аппарат обработал
    printf(" Handler processed:      %d requests\n"
           " Handler time(counted):  %.3lf t.u\n"
           " Handler worked:         %.3lf\n\n", //t.u - time units - ед. времени
           pr_counter, pr_time, q1->pr_time + q2->pr_time);

    // проверяем корректность количества пришедших заявок 1 очереди
    double come = q1->en_time / avr_en_time;
    printf(" Counted entry:          %.3lf\n", come);
    double inf = (LIMIT - come) / come;
    printf(" Exp/real entry amount:  %.3lf%%\n", fabs(inf * 100));

    free_all(q1);
    free_all(q2);
}
