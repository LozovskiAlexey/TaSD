#include "funcs.h"

void tree_menu()
{
    int inp_result;

    //считывание дерева из файла
    //имя файла задается внутри функции
    tree_t *head = NULL;
    read_tree(&head);

    //заголовок меню, проверка ввода
    //show_headline(2, "== Menu ==", "==  Tree  ==");
    show_tree_menu();
    check_input(&inp_result);

    //если inp_result будет с кодом выхода - конец.
    while (inp_result)
    {
        switch(inp_result)
        {
        case 1:
            do_addition_tree(&head);
            break;

        case 2:
            do_delete_tree_element(&head);
            break;

        case 3:
            do_find_element(head);
            break;

        case 4:
            do_traversal_tree(head);
            break;

        case 5:
            do_show_tree(head);
            break;

        case 0:
            return;

        default:
            show_result(inv_input);
            break;
        }

        //show_headline(2, "== Menu ==", "==  Tree  ==");
        show_tree_menu();
        check_input(&inp_result);
    }
}

void do_traversal_tree(tree_t *head)
{
    int inp_result;

    //show_headline(1, "== Traversal ==");
    show_traversal_menu();
    check_input(&inp_result);

    switch (inp_result)
    {
    case 1:
        do_order_tree(head, "In", inorder_traversal_tree);
        break;

    case 2:
        do_order_tree(head, "Pre", preorder_traversal_tree);
        break;

    case 3:
        do_order_tree(head, "Post", postorder_traversal_tree);
        break;
    }
}

void do_order_tree(tree_t *tree, const char *name, void (*traversal)(tree_t *tree))
{
    printf(" _______________________________________________________\n");
    printf(" %sorder traversal result: ", name);

    traversal(tree);

    printf("\n");
}

void inorder_traversal_tree(tree_t *tree)
{
    if (tree)
    {
        inorder_traversal_tree(tree->left);
        printf("%d ", tree->key);
        inorder_traversal_tree(tree->right);
    }
}

void preorder_traversal_tree(tree_t *tree)
{
    if (tree)
    {
        printf("%d ", tree->key);
        preorder_traversal_tree(tree->left);
        preorder_traversal_tree(tree->right);
    }
}

void postorder_traversal_tree(tree_t *tree)
{
    if (tree)
    {
        postorder_traversal_tree(tree->left);
        postorder_traversal_tree(tree->right);
        printf("%d ", tree->key);
    }
}

//работа с файлом
//читает из файла элемент, создает узел, добавляет его в список
void read_tree(tree_t **head)
{
    FILE *file = NULL;
    char name[50];
    int code = success; //код ошибки

    printf(" _______________________________________________________\n");
    get_name(name);
    file = fopen(name, "r");

    if (file)
    {
        int value;
        int result = fscanf(file, "%d", &value);
        while (result == 1)
        {
            tree_t *node = tree_init(value);
            add_tree_element(head, node);
            result = fscanf(file, "%d", &value);
        }
        if (!(*head))
            code = empty_file;
    }
    else
        code = open_file_error;
    show_result(code);
}


//инициализация узла
tree_t *tree_init(int data)
{
    tree_t *node = malloc(sizeof(tree_t));

    node->key = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

//Возможно, но только возможно, оно добавит элемент
//в дерево, но это только если бог позволит
void do_addition_tree(tree_t **head)
{
    //show_headline(1, "== Addition ==");

    int value;
    printf(" Input value: ");
    check_input(&value);

    tree_t *node = tree_init(value);
    add_tree_element(head, node);

    printf(" The node with value %d was added.\n", value);
}

//функция добавления элемента в дерево
//Получает на вход голову и узел  и добавляет его.
void add_tree_element(tree_t **head, tree_t *node)
{
    if (!(*head))
        (*head) = node;
    else
    {
        if ((*head)->key > node->key)
            add_tree_element(&((*head)->left), node);
        else
            add_tree_element(&((*head)->right), node);
    }
}


//функция для использования в меню.
void do_show_tree(tree_t *head)
{
    //show_headline(1, "== Show tree ==");
    show_tree(head, 0);
}

//показывает дерево.
void show_tree(tree_t *head, int level)
{
    if (head)
    {
        show_tree(head->right, level + 1);

        for (int i = 0; i < level; i++)
            printf("  ");

        printf("% d\n", head->key);
        show_tree(head->left, level + 1);
    }
}

//Удаление элемента(вызов из меню)
void do_delete_tree_element(tree_t **head)
{
    //show_headline(1, "== Delete ==");

    int element = get_element();
    tree_t *copy = delete_element(*head, element);
    if(!copy)
        show_result(find_error);
    else
        show_result(success);
}

//удаление элемента
tree_t *delete_element(tree_t *head, int key)
{
    if (head)
    {
        if (key < head->key)
            head->left = delete_element(head->left, key);

        else if (key > head->key)
            head->right = delete_element(head->right, key);

        else if (head->left && head->right)
        {
            head->key = find_tree_max(head->left)->key;
            head->left = delete_element(head->left, head->key);
        }
        else
        {
            if (head->left)
                head = head->left;
            else
                head = head->right;
        }
    }
    return head;
}

//В левой ветке находим самый правый элемент
tree_t *find_tree_max(tree_t *head)
{
    if (!(head->right))
        return head;
    return find_tree_max(head->right);
}

void do_find_element(tree_t *tree)
{
    //show_headline(1, "== Find ==");

    int element = get_element();
    int comparison = 0;
    tree_t *node = find_element_trew(tree, element, &comparison);

    if (!node)
        show_result(find_error);
    else
        show_node(node, comparison);
}

//Поиск элементв
tree_t *find_element_trew(tree_t *head, int key, int *comparison)
{
    (*comparison)++;
    if (!head || key == head->key)
        return head;
    else
    {
        if (key > head->key)
            return find_element_trew(head->right, key, comparison);
        else
            return find_element_trew(head->left, key, comparison);
    }
}

void show_node(tree_t *tree, int comparison)
{
    printf(" Founded value: \n"
           " key: %-40d              \n"
           " comparison counted:  %d\n",
           tree->key, comparison);
}
