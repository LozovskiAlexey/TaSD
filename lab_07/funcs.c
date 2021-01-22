#include "funcs.h"

//----------------------------------------
//работа с файлами
wr_t *get_graph(void)
{
    show_headline(1, "--== Get graph ==--");
    char name[50];
    get_name(name);

    FILE *file = fopen(name, "r");
    wr_t *graph = NULL;

    if (file)
    {
        int size;
        int result = fscanf(file, "%d", &size); //считываем количество вершин
        if (result == 1)
        {
            graph = graph_init(size);
            int neighbours; //число соседей у вершины графа
            for (int i = 0; i < size; i++) //заполнение массива указателей
            {
                result = fscanf(file, "%d", &neighbours);
                if (result == 1)
                {
                    int digit;
                    node_t *node, *head = NULL;
                    for (int i = 0; i < neighbours; i++)
                    {
                        result = fscanf(file, "%d", &digit); //считываем соседей
                        if (digit > size || digit < 0)
                            return NULL;

                        node = node_init(digit); //добавляем в узел
                        head = add_node(head, node); //добавляем узел в список
                    }
                    graph->head[i] = head; //добавляем список в ячейку массива
                }
                else return NULL;
            }
        }
        else return NULL;

        fclose(file);
        return graph;
    }
    else return NULL;
}


void make_gv(wr_t *head)
{
    show_headline(1, "--== Make gv ==--");

    char name[50];
    get_name(name);

    FILE *file = fopen(name, "w");

    fprintf(file, "graph png {\n");
    for (int i = 0; i < head->size; i++) //head->size - размер массива
    {
        node_t *tmp = (head->head[i])->next; //проход по соседям вершины

        if (tmp == NULL)
        {
            fprintf(file, "\t%d -- %d;\n", i + 1, i + 1);
            printf("\t%d -- %d;\n", i + 1, i + 1);
        }
        for (; tmp; tmp = tmp->next)
            if (i + 1 < tmp->data)
            {
                printf("\t%d -- %d;\n", i + 1, tmp->data);
                fprintf(file, "\t%d -- %d;\n", i + 1, tmp->data);
            }
    }
    fprintf(file, "}\n");

    printf(" %s was successfuly created.\n", name);
    fclose(file);
}
//-----------------------------------------------

//-----------------------------------------------
//функция которая вызаывает проверку графа и выводит текст.
void check(wr_t *head)
{
    show_headline(1, "--== Check graph ==--");

    //массив встреч элементов - если элемент обходили на его позиции в массиве
    //ставится 1.
    int *status = calloc((unsigned)head->size, sizeof (int));
    int result = isconnected(head->head, head->size, status);

    int code = (result == head->size) ? YES : NO;
    print_result(code);

    free(status);
}

//проверка на связность графа
int isconnected(node_t **head, int size, int *checked)
{
    int counter = 1, i = 0;

    que_t *q = q_init(size);
    int elem = head[i]->data;

    push(q, elem);
    checked[elem - 1] = 1;

    while (!isempty(q))  //добавление элементов в очередь
    {
        node_t *tmp = head[i]->next;
        for (; tmp; tmp = tmp->next)
        {
            elem = tmp->data;
            if (!checked[elem - 1])
            {
                push(q, elem);
                counter++;
                checked[elem - 1] = 1;
            }
        }
        pop(q);

        i = q->q[q->pin] - 1;
    }

    return counter;
}
//-------------------------------------------

//-------------------------------------------
que_t *q_init(int size)
{
    que_t *array = malloc(sizeof(que_t));

    array->q = malloc(sizeof(int) * (unsigned)(size + 1));
    array->size = size;
    array->pin = 1; // позиция первого элемента в очереди
    array->pout = 0; //позиция последнего

    return array;
}

void push(que_t *q, int elem)
{
    int result = isfull(q);
    if (!result)
    {
        q->pout++;
        q->q[q->pout] = elem;
    }
}

void pop(que_t *q)
{
    int result = isempty(q);
    if (!result)
    {
        for (int i = q->pin; i < q->pout; i++)
            q->q[i] = q->q[i+1];

        q->pout--;
    }
}

//проверка на пустоту
int isempty(que_t *ar)
{
    return (ar->pout < ar->pin) ? 1 : 0;
}

//проверка на переполнение
int isfull(que_t *ar)
{
    return (ar->pout >= ar->size - 1) ? 1 : 0;
}

void show_q(que_t *q)
{
    for (int i = q->pin; i <= q->pout; i++)
        printf("%d ", q->q[i]);
    printf("\n");
}
//-----------------------------------------

//-----------------------------------------
wr_t *graph_init(int size)
{
    wr_t *graph = NULL;
    graph = malloc(sizeof(wr_t));

    graph->head = malloc(sizeof(node_t *) * (unsigned)size);
    graph->size = size;

    return graph;
}

node_t *node_init(int value)
{
    node_t *node = malloc(sizeof(node_t));
    node->data = value;
    node->next = NULL;

    return node;
}

node_t *add_node(node_t *head, node_t *elem)
{
    if (!head)
        return elem;

    node_t *tmp = head;
    for (; tmp->next; tmp = tmp->next);
    tmp->next = elem;

    return head;
}
//-----------------------------------------

//-----------------------------------------
//отображение графа(в виде списка из файла)
void show_graph(wr_t *gr)
{
    if (gr)
    {
        for (int i = 0; i < gr->size; i++)
        {
            node_t *tmp = gr->head[i];

            for (; tmp; tmp = tmp->next)
                printf("%d ", tmp->data);

            printf("\n");
        }
    }
}

//Вывод результата работы функций
void print_result(int code)
{
    switch (code) {
    case YES:
        printf("\t\tThis graph is related.\n");
        break;

    case NO:
        printf("\t\tThis graph is NOT related.\n");
        break;

    case INV_DATA:
        printf(" Incorrect data.\n");
        break;

    case SUCCESS:
        printf(" Successfully done\n");
        break;
    }
}
//----------------------------------------

//----------------------------------------
unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}

void check_time(void)
{
    wr_t *graph = get_graph();
    unsigned long long start1, finish1, result1;
    int *status = calloc((unsigned)graph->size, sizeof (int));

    start1 = tick();
    isconnected(graph->head, graph->size, status);
    finish1 = tick();
    result1 = (finish1 - start1);

    printf(" Time %d\n", (int)result1);

    free(status);
    status = NULL;
}
//----------------------------------------
