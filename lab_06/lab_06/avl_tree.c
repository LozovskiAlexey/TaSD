#include "funcs.h"

void avl_tree_menu()
{
    int inp_result;

    //функция для файла
    avl_tree_t *head = NULL;
    read_avl_tree(&head);

    //show_headline(2, "== Menu ==", "== AVL-tree ==");
    show_tree_menu();
    check_input(&inp_result);

    while (inp_result)
    {
        switch(inp_result)
        {
        case 1:
            do_addition_avl(&head);
            break;

        case 2:
            do_delete_avl_element(&head);
            break;

        case 3:
            do_find_element_avl(head);
            break;

        case 4:
            do_traversal_avl(head);
            break;

        case 5:
            do_show_avl(head);
            break;

        case 0:
            return;

        default:
            show_result(inv_input);
            break;
        }

        //show_headline(2, "== Menu ==", "== AVL-ree ==");
        show_tree_menu();
        check_input(&inp_result);
    }
}

void show_tree_menu()
{
    printf(" 1. Add element.           \n"
           " 2. Delete element.        \n"
           " 3. Find element.          \n"
           " 4. Tree traversal.        \n"
           " 5. Show tree.             \n"
           " 0. Change data structure. \n"
           " Put the number: ");
}

void show_traversal_menu()
{
    printf(" 1. Inorder Traversal      \n" //Обход узлов в отсортированнаом порядке
           " 2. Preorder Traversal     \n" //Вершина -> Левое -> Правое
           " 3. Postorder Traversal    \n" //Левое -> Правое -> вершина
           " Put the number: ");
}

//Работа с высотой, работает и с нулевыми указателями
//т.е с нулевыми деревьями
unch height(avl_tree_t *head)
{
    return head ? head->height : 0;
}

//вычисляет balance factor заданного узла
//принимает только ненулевые указатели
int bfactor(avl_tree_t *head)
{
    return height(head->right) - height(head->left);
}

//Восстанавливает корректное значение поля height
//заданного узла, при условии, что оба поля !NULL
void fixheight(avl_tree_t *head)
{
    unch height_left = height(head->left);
    unch height_right = height(head->right);

    head->height = (height_left > height_right ? height_left : height_right) + 1;
}

//правый поворот
avl_tree_t *rotate_right(avl_tree_t *head)
{
    avl_tree_t *q = head->left;
    head->left = q->right;
    q->right = head;

    fixheight(head);
    fixheight(q);

    return q;
}
//левый поворот
avl_tree_t *rotate_left(avl_tree_t *head)
{
    avl_tree_t *p = head->right;
    head->right = p->left;
    p->left = head;

    fixheight(head);
    fixheight(p);

    return p;
}
//балансировка
avl_tree_t *balance(avl_tree_t *head)
{
    fixheight(head);
    if (bfactor(head) == 2)
    {
        if (bfactor(head->right) < 0)
            head->right = rotate_right(head->right);
        return rotate_left(head);
    }
    if (bfactor(head) == -2)
    {
        if (bfactor(head->left) > 0)
            head->left = rotate_left(head->left);
        return rotate_right(head);
    }
    return head;
}
//добавление элемента
avl_tree_t *add_avl_element(avl_tree_t *head, avl_tree_t *node)
{
    if (!head)
        return node;
    if (node->key < head->key)
        head->left = add_avl_element(head->left, node);
    else
        head->right = add_avl_element(head->right, node);
    return balance(head);
}

//Удаление
avl_tree_t *avl_minimun(avl_tree_t *head)
{
    return head->left ? avl_minimun(head->left) : head;
}

//Удаление минимального элемента на поддереве
avl_tree_t *avl_delete_min(avl_tree_t *head)
{
    if (!(head->left))
        return head->right;
    head->left = avl_delete_min(head->left);
    return balance(head);

}

avl_tree_t *avl_delete_node(avl_tree_t *head, int key)
{
    if (!head)
        return NULL;
    if (key < head->key)
        head->left = avl_delete_node(head->left, key);
    else if (key > head->key)
        head->right = avl_delete_node(head->right, key);
    else
    {
        avl_tree_t *left = head->left;
        avl_tree_t *right = head->right;

        free(head);

        if (!right)
            return left;

        avl_tree_t *minimum = avl_minimun(right);
        minimum->right = avl_delete_min(right);
        minimum->left = left;
        return balance(minimum);
    }
    return balance(head);
}

void read_avl_tree(avl_tree_t **head)
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
            avl_tree_t *node = avl_tree_init(value);
            (*head) = add_avl_element(*head, node);
            result = fscanf(file, "%d", &value);
        }
        if (!(*head))
            code = empty_file;
    }
    else
        code = open_file_error;
    show_result(code);
}

avl_tree_t *avl_tree_init(int value)
{
    avl_tree_t *node = malloc(sizeof(avl_tree_t));

    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    node->key = value;

    return node;
}

void do_addition_avl(avl_tree_t **head)
{
    //show_headline(1, "== Addition ==");

    int value;
    printf(" Input value: ");
    check_input(&value);

    avl_tree_t *node = avl_tree_init(value);
    (*head) = add_avl_element(*head, node);

    printf(" The node with value %d was added.\n", value);
}

void do_delete_avl_element(avl_tree_t **head)
{
    //show_headline(1, "== Delete ==");

    int element = get_element();
    avl_tree_t *copy = avl_delete_node(*head, element);
    if(!copy)
        show_result(find_error);
    else
        show_result(success);
}

void do_find_element_avl(avl_tree_t *tree)
{
    //show_headline(1, "== Find ==");

    int element = get_element();
    int comparison = 0;
    avl_tree_t *node = find_element_avl(tree, element, &comparison);

    if (!node)
        show_result(find_error);
    else
        show_node_avl(node, comparison);
}

void show_node_avl(avl_tree_t *tree, int comparison)
{
    printf(" Founded value: \n"
           " key: %-40d              \n"
           " comparison counted:  %d\n",
           tree->key, comparison);
}

void do_traversal_avl(avl_tree_t *head)
{
    int inp_result;

    //show_headline(1, "== Traversal ==");
    show_traversal_menu();
    check_input(&inp_result);

    switch (inp_result)
    {
    case 1:
        do_order_avl(head, "In", inorder_traversal_avl);
        break;

    case 2:
        do_order_avl(head, "Pre", preorder_traversal_avl);
        break;

    case 3:
        do_order_avl(head, "Post", postorder_traversal_avl);
        break;
    }
}

avl_tree_t *find_element_avl(avl_tree_t *head, int key, int *comparison)
{
    (*comparison)++;
    if (!head || key == head->key)
        return head;
    else
    {
        if (key > head->key)
            return find_element_avl(head->right, key, comparison);
        else
            return find_element_avl(head->left, key, comparison);
    }
}

//функция для использования в меню.
void do_show_avl(avl_tree_t *head)
{
    //show_headline(1, "== Show tree ==");
    show_avl(head, 0);
}

//показывает дерево.
void show_avl(avl_tree_t *head, int level)
{
    if (head)
    {
        show_avl(head->right, level + 1);

        for (int i = 0; i < level; i++)
            printf("  ");

        printf("% d\n", head->key);
        show_avl(head->left, level + 1);
    }
}

void do_order_avl(avl_tree_t *tree, const char *name, void (*traversal)(avl_tree_t *tree))
{
    printf(" _______________________________________________________\n");
    printf(" %sorder traversal result: ", name);

    traversal(tree);

    printf("\n");
}

void inorder_traversal_avl(avl_tree_t *tree)
{
    if (tree)
    {
        inorder_traversal_avl(tree->left);
        printf("%d ", tree->key);
        inorder_traversal_avl(tree->right);
    }
}

void preorder_traversal_avl(avl_tree_t *tree)
{
    if (tree)
    {
        printf("%d ", tree->key);
        preorder_traversal_avl(tree->left);
        preorder_traversal_avl(tree->right);
    }
}

void postorder_traversal_avl(avl_tree_t *tree)
{
    if (tree)
    {
        postorder_traversal_avl(tree->left);
        postorder_traversal_avl(tree->right);
        printf("%d ", tree->key);
    }
}
