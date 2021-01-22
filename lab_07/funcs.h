#ifndef FUNCS_H
#define FUNCS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "struct.h"

//отображение заголовка
void show_headline(int num, ...);
void put_headline(const char *line, const char *headline);
void print_line(char symb);
int my_strlen(const char *line);

//результат работы функций
void print_result(int code);

//считывание файла из графа
void get_name(char *name);
wr_t *get_graph(void);

//иницализация списка
wr_t *graph_init(int size);
node_t *node_init(int value);
node_t *add_node(node_t *head, node_t *elem);
void free_gr(wr_t *head);

//отображение графа
void show_graph(wr_t *gr);

//проверка на связность
void check(wr_t *head);
int isconnected(node_t **head, int size, int *status);

//создает файл для вывода графа
void make_gv(wr_t *head);

//работа с очередью
que_t *q_init(int size);

//добавление и удаление
void push(que_t *q, int elem);
void pop(que_t *q);

//проверка на переполнение и пустоту
int isempty(que_t *q);
int isfull(que_t *ar);

//выводит элементы очереди(для проверки работы)
void show_q(que_t *q);

//меню
void menu(void);
void show_options(void);
void check_input(int *value);
void check_time(void);
#endif
