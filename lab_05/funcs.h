#ifndef FUNCS_H
#define FUNCS_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "struct.h"

//проверки и оформление меню
//проверка ввода
void check_input(int *value);
int get_element(void);

//вывод заголовка
void show_headline(int, ...);
void put_headline(const char *, const char *);
int my_strlen(const char *);

//меню выбора структуры
void src_menu(void);
void show_src_menu(void);
void show_menu(void);

//работа с меню-структурой
void do_ar_proc(void);  //меню работы с массивом
void do_lst_proc(void); //меню работы со списком

void arr_init(arr_t **array, double *T1, double *T2);
int arr_add(arr_t *ar, double *time);
int isempty(arr_t *ar);
int isfull(arr_t *ar);
int arr_delete(arr_t *ar, double *time, int *flag);
void do_arr_module(arr_t *q1, arr_t *q2);
void time_arr_init(arr_t *ar);
void show_arr_gap(arr_t *q1, arr_t *q2, data_t *data1, data_t *data2, int i, int flag);
void show_arr_time(arr_t *q1, arr_t *q2);
void free_arr(arr_t *q);
void do_test(void);

//алгоритм задания (Список)
void do_model(wrap_t *, wrap_t *); //модель работы для списка
void add_element(list_t *, wrap_t *, double *);  //добавление элемента очередь
void process_element(wrap_t *, double *, int *, data_t *); //удаление-обработка элемента в ОА
void show_time(wrap_t *, wrap_t *);  //показывает результат работы do_model
void free_all(wrap_t *);             //освобождает всю память
void show_gap(wrap_t *, wrap_t *, data_t *, data_t *, int, int);

//хранение промежуточных данных очереди
void data_init(data_t **head);

//инициализация структур
list_t *init_element(void);                    //инициализация элемента очереди
void wrap_init(wrap_t **, double *, double *); //инициализация обертки

//для заполнения времени в структуре
void time_user_init(wrap_t *);         //показывает меню времени
void time_add(double *);               //делает функцию ниже менее бесполезной
void get_time(double *, const char *); //ввод времени пользователем
double get_t(double, double);  //получение времени на промежутке

unsigned long long tick(void);

//вывод результатов
void show_result(int); //выводит текст работы функций
#endif
