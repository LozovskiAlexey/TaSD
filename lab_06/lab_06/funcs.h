#ifndef FUNCS_H
#define FUNCS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#include "struct.h"

//Для работы menu(menu.c)
void put_headline(const char *, const char*);
void show_headline(int, ...);
void check_input(int *);
int get_element(void);

void show_main_menu(void);
void show_tree_menu(void);
void show_hash_menu(void);
void avl_tree_menu(void);

void tree_menu(void);
void hash_menu(void);
void main_menu(void);
//___________________________________________________________________
//Для работы дерева(tree.c)

void read_tree(tree_t **head);

    //добавление
void do_addition_tree(tree_t **);
void add_tree_element(tree_t **, tree_t *);

    //удаление
void do_delete_tree_element(tree_t **);
tree_t *delete_element(tree_t *, int);
tree_t *find_tree_max(tree_t *);

    //инициализация и отображение дерева
void do_show_tree(tree_t *head);
void show_tree(tree_t *, int);
tree_t *tree_init(int);

    //Поиск
tree_t *find_element_trew(tree_t *, int, int *);
tree_t *find_tree_max(tree_t *);
void do_find_element(tree_t *);
void show_node(tree_t *, int);

    //Обход
void show_traversal_menu(void);
void do_traversal_tree(tree_t *);
void inorder_traversal_tree(tree_t *);
void preorder_traversal_tree(tree_t *);
void postorder_traversal_tree(tree_t *);
void do_order_tree(tree_t *, const char *, void (*)(tree_t *));

    //Освободмть дерево
//void free_tree(tree_t **tree);

//___________________________________________________________________
//Для работа АВЛ-дерева(avl-tree.c)

//Обработка дерева
unch height(avl_tree_t *head);
int bfactor(avl_tree_t *head);
void fixheight(avl_tree_t *head);
avl_tree_t *rotate_right(avl_tree_t *head);
avl_tree_t *rotate_left(avl_tree_t *head);
avl_tree_t *balance(avl_tree_t *head);

//добавление элемента
void do_addition_avl(avl_tree_t **head);
avl_tree_t *add_avl_element(avl_tree_t *head, avl_tree_t *node);

//удаление элемента
avl_tree_t *avl_minimun(avl_tree_t *head);
avl_tree_t *avl_delete_min(avl_tree_t *head);
avl_tree_t *avl_delete_node(avl_tree_t *head, int key);
void do_delete_avl_element(avl_tree_t **head);

//чтение из файла
void read_avl_tree(avl_tree_t **);
avl_tree_t *avl_tree_init(int value);

//поиск элемента
void do_find_element_avl(avl_tree_t *tree);
void show_node_avl(avl_tree_t *tree, int comparison);
avl_tree_t *find_element_avl(avl_tree_t *head, int key, int *comparison);

//вывод дерева
void show_avl(avl_tree_t *head, int level);
void do_show_avl(avl_tree_t *head);
avl_tree_t *find_element_avl(avl_tree_t *head, int key, int *comparison);

//показать дерево
void do_show_avl(avl_tree_t *head);
void do_traversal_avl(avl_tree_t *head);
void show_avl(avl_tree_t *head, int level);

//обход дерева
void do_order_avl(avl_tree_t *tree, const char *name, void (*traversal)(avl_tree_t *tree));
void inorder_traversal_avl(avl_tree_t *tree);
void preorder_traversal_avl(avl_tree_t *tree);
void postorder_traversal_avl(avl_tree_t *tree);

//___________________________________________________________________
//Для работы хэш-таблицы(hash_table.c)

//Добавление
void do_add_hash(wrap_t *wrap);
void add_hash(wrap_t *wrap, int key);

//Инициализация
wrap_t *init_wrap(int hash_func);
hash_t *init_hash(int key);

//вывод
void print_hash(hash_t *head, int i);
void do_show_hash(wrap_t *wrap);
void show_hash(wrap_t *wrap);

//чтение файла
void fill_hash(wrap_t *wrap);

//удаление
void delete_hash(wrap_t *wrap, int key);
void do_delete_hash(wrap_t *wrap);

//поиск
hash_t *find_hash(wrap_t *wrap, int key, int *comparison);
void show_find_result(hash_t *head, int comparison);
void do_find_hash(wrap_t *wrap);

int get_simple(int digit);
void do_fix_collision(wrap_t *wrap);
void print_new_hash(hash_t *head, int i, int j);
void show_new_hash(wrap_t *wrap, int compare);

//___________________________________________________________________
//Общие алгоритмы
int my_strlen(const char *);
unsigned long long tick(void);
void get_name(char *name);
void show_result(int);
void test(void);

#endif
