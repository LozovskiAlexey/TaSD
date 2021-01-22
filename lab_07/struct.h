//структура графа
typedef struct graph node_t;
struct graph{
    int data;
    node_t *next;
};

//обертка на граф
typedef struct wrap wr_t;
struct wrap{
    node_t **head;

    int size;
};

typedef struct queuee que_t;
struct queuee
{
    int *q; //QMAX 3000

    int size;
    int pin; //начало
    int pout; //конец очереди

};

enum res{
    NO = -1,
    YES = 1
};
enum code{
    INV_DATA = -103,
    INV_INPUT,
    SUCCESS = 0
};
