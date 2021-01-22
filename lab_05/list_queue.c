#include "funcs.h"

//инициализация элемента
list_t *init_element()
{
    list_t *element;
    element = malloc(sizeof(list_t)); //создаем элемент

    element->elememt = 0; // все равно оно бесполезно, пусть будет 0
    element->next = NULL;

    return element;
}

//получает на вход
//element - узел, который добавить(заявка)
//определяет время в переменную time
//из q берет границы времени прихода и генерирует время для time
void add_element(list_t *element, wrap_t *q, double *time)
{
    (*time) = get_t(q->T1[0], q->T1[1]); //создаем время
    (q->counter)++;                      //количество элементов в очереди
    if (q->counter < LIMIT)
        q->en_time += *time;                 //добавляем время прихода

    //добавление элемента в список
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

//пофантазируем и представим что простое безобидное
//удаление узла это у нас обработка заявки
void process_element(wrap_t *q, double *time, int *flag, data_t *data)
{
    //ниче делать не будет пока очередь пустая.
    if  (!(q->head))
    {
        *flag = (*flag == 0);
        return;
    }

    (*time) = get_t(q->T2[0], q->T2[1]); //создаем время

    q->pr_time += *time;                 //добавляем к общему времени обработки
    q->pr_counter += 1;                  //добавляем 1 к числу обработанных элементов

    list_t *element = q->head;
    (q->head) = (q->head)->next;
    free(element);

    //нужно для отображения памяти
    if (!(*flag) && q->pr_counter < 100)
        data->deleted[q->pr_counter - 1] = element;
}

void free_all(wrap_t *q)
{
    while (q->head)
    {
        list_t *element = q->head;
        (q->head) = (q->head)->next;
        free(element);
    }

    q->counter = 0;
    q->en_time = 0;
    q->pr_counter = 0;
    q->pr_time = 0;

    q->tmp = NULL;
}

void show_gap(wrap_t *q1, wrap_t *q2, data_t *data1, data_t *data2, int i, int flag)
{
    if (i && !(q1->pr_counter % 100) && !flag)
    {
        double time = (i - data1->time) / 100;
        data1->t_st = i;

        double qlen = (q1->counter > q1->pr_counter) ? q1->counter - q1->pr_counter : 0;
        double avg_len = (qlen + data1->l_st) / 200;

        printf(" Queue: 1 \n");
        printf(" Average queue length: %.0lf\n"
               " Average request time: %.3lf\n"
               " Temporary length:     %.0lf\n\n",
               avg_len, time, qlen);


        time = (i - data2->time) / 100;
        data1->t_st = i;

        qlen = (q2->counter > q2->pr_counter) ? q2->counter - q2->pr_counter : 0;
        avg_len = (qlen + data2->l_st) / 200;

        printf(" Queue: 2\n");
        printf(" Average queue length: %.0lf\n"
               " Average request time: %.3lf\n"
               " Temporary length:     %.0lf\n\n",
               avg_len, time, qlen);
    }
}

void data_init(data_t **data)
{
    (*data) = malloc(sizeof(data_t));

    (*data)->l_st = 0;
    (*data)->len = 0;

    (*data)->t_st = 0;
    (*data)->time = 0;
}
