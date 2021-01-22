#ifndef FUNCS_H
#define FUNCS_H

#include <stdio.h>
#include <stdlib.h>

enum stackSize
{
    STACK_SIZE = 5,
    TEST_SIZE = 1000,
    STACK_OVERFLOW = -101,
    STACK_UNDERFLOW
};

enum result
{
    EXIT = -2,
    ERROR,
    SUCCESS
};


typedef int Type;               //Тип хранящихся внутри данных
typedef struct stack stack_t;   //Массив
typedef struct Stack Stack_t;   //Список
typedef struct adress adress_t; //Адреса

// Для тестовых значений
//(надеюсь Бог или кто-нибудь меня простит потому что я не знаю как сделать по-человечески)

typedef struct test test_t;
//typedef struct ltest ltest_t;
typedef struct test_adress atest_t;

//структуры для тестов
//структура для массива
struct test
{
    Type data[TEST_SIZE];
    Type start;
    Type end;

    int overflow;
    int underflow;

    Type tmp;  //указатель позиция верхнего элемента
};

//структура для хранения адресов
struct test_adress
{
    Stack_t *p[TEST_SIZE]; //тут хранятся указатели
    Type value[TEST_SIZE]; //тут значения
    int counter;            //указатель на текущую позицию
};

//структуры для работы программы
//Массив
struct stack
{
    Type data[STACK_SIZE];
    Type start;
    Type end;

    int overflow;
    int underflow;

    Type tmp;  //указатель позиция верхнего элемента
};

//Список
struct Stack
{
    Type value;
    int limit;

    Stack_t *next;
};

//хранение адресов удаленных их стека элементов
struct adress
{
    Stack_t *p[STACK_SIZE]; //тут хранятся указатели
    Type value[STACK_SIZE]; //тут значения
    int counter;            //указатель на текущую позицию
};

//меню
int do_menu(stack_t *);
int do_lmenu(Stack_t **stack, adress_t *adress);
int stack_menu(void);
void show_title(int flag);

int check_input(void);
void push_data(stack_t *stack);
void pop_data(stack_t *stack);
void test(void);

void lpush_data(Stack_t **head, adress_t *adress);
void lpop_data(Stack_t **head, adress_t *adress);

//инициализация стеков
stack_t *init(void);
adress_t *adress_init(void);

//Для тестов
test_t *tinit(void);
atest_t *A_init(void);
unsigned long long tick(void);\
void tpush(test_t *stack, Type element);
Type *tpop(test_t *stack);

//работа со стеком
//для стека в виде массива
void push(stack_t *stack, Type element);
Type *pop(stack_t *stack);
void show(stack_t *stack);
void show_data(Type *element);
void show_sequences(stack_t *head);
void show_stack_ar(stack_t *stack);

//для стека в виде списка
void lpush(Stack_t **stack, Type element);
Stack_t *lpop(Stack_t **head);
void show_lsequences(Stack_t **head, adress_t *adress);
void show_stack(Stack_t *stack, adress_t *adress);

#endif
