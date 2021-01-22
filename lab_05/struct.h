#define LIMIT 1000
#define QMAX 3000

typedef struct array aq_t; //array_queue_type
typedef  struct list lq_t; //list_queue_type

enum result
{
    QUEUE_OVERFLOW = -103,
    INV_INPUT,
    SUCCESS = 0
};

typedef struct List list_t;
typedef struct wrap_list wrap_t;
typedef struct data data_t;
typedef struct array arr_t;

//очередь списком
struct List
{
    int elememt;

    list_t *next;
};

//время обработки и поступление может принимать не любые значения
//писать проверки для каждого случая я не в состоянии
//поэтому настоятельная рекомендация не быть бессердечными
//и воодить хотя бы отдаленно адекватные значения
struct wrap_list
{
    list_t *head;
    list_t *tmp;

    double en_time; //счетчик времени поступления в очередь (entry_time)
    double pr_time; //счетчик времеми обработки (processing time)

    int pr_counter; //количество обработанных заявок
    int counter; //количество заявок в очереди

    double *T1; //время прихода очереди
    double *T2; //время обработки очереди
};

struct data
{
    list_t *added[100];
    list_t *deleted[100];

    double l_st; //len_start
    double len;

    double t_st; //time_start
    double time;
};

struct array
{
    int q[QMAX]; //QMAX 3000

    int pin; //начало
    int pout; //конец очереди

    double en_time;
    double pr_time;

    int pr_counter;
    int en_counter;

    double *T1;
    double *T2;
};


