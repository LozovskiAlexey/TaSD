#include "funcs.h"

#define TEST_SIZE 100
void test_avl_traversal(avl_tree_t *tree)
{
    if (tree)
    {
        test_avl_traversal(tree->left);
        test_avl_traversal(tree->right);
    }
}

void test_tree_traversal(tree_t *tree)
{
    if (tree)
    {
        test_tree_traversal(tree->left);
        test_tree_traversal(tree->right);
    }
}

int comp (const int *i, const int *j)
{
    return *i - *j;
}

void test1()
{
    int element;
    int values[TEST_SIZE];

    tree_t *head = NULL;
    avl_tree_t *avl_head = NULL;
    wrap_t *wrap = init_wrap(103);

    unsigned long long start1, finish1, result1;
    unsigned long long start2, finish2, result2;
    unsigned long long start3, finish3, result3;

    for (int i = 0; i < TEST_SIZE; i++)
    {
        element = rand() % 100 + 1;
        values[i] = element;
    }

    start1 = tick();
    for (int i = 0; i < TEST_SIZE; i++)
    {
        tree_t *node = tree_init(values[i]);
        add_tree_element(&head, node);
    }
    finish1 = tick();
    result1 = (finish1 - start1) / TEST_SIZE;


    start2 = tick();
    for (int i = 0; i < TEST_SIZE; i++)
    {
        avl_tree_t *avl_node = avl_tree_init(values[i]);
        avl_head = add_avl_element(avl_head, avl_node);
    }
    finish2 = tick();
    result2 = (finish2 - start2) / TEST_SIZE;


    start3 = tick();
    for (int i = 0; i < TEST_SIZE; i++)
        add_hash(wrap, values[i]);
    finish3 = tick();
    result3 = (finish3 - start3) / TEST_SIZE;

    printf(" Среднее время запонления элемента: \n");

    const char *tree = "Tree";
    const char *AVL = "AVL-Tree";
    const char *Hash = "Hash-table";

    const char *time = "Time";

    printf(" %15s %17s %18s\n"
           " %s %10d %15d %16d\n",
           tree, AVL, Hash, time,
           (int)result1, (int)result2,(int)result3);
}

void test2()
{
    int element;
    int values[TEST_SIZE];

    tree_t *tree = NULL;
    avl_tree_t *avl_head = NULL;
    wrap_t *wrap = init_wrap(103);

    unsigned long long start1, finish1, result1;
    unsigned long long start2, finish2, result2;
    unsigned long long start3, finish3, result3;

    for (int i = 0; i < TEST_SIZE; i++)
    {
        element = rand() % 100 + 1;
        values[i] = element;
    }
    //заполнение
    for (int i = 0; i < TEST_SIZE; i++)
    {
        tree_t *node = tree_init(values[i]);
        add_tree_element(&tree, node);

        avl_tree_t *avl_node = avl_tree_init(values[i]);
        avl_head = add_avl_element(avl_head, avl_node);

        add_hash(wrap, values[i]);
    }

    //поиск

    int comparison_tree = 0;
    start1 = tick();
    for (int i = 0; i < TEST_SIZE; i++)
    {
        int c = 0;
        element = values[i];
        find_element_trew(tree, element, &c);
        comparison_tree += c;
    }
    finish1 = tick();
    result1 = (finish1 - start1) / TEST_SIZE;
    comparison_tree /= TEST_SIZE;

    int comparison_avl = 0;
    start2 = tick();
    for (int i = 0; i < TEST_SIZE; i++)
    {
        int c = 0;
        element = values[i];
        find_element_avl(avl_head, element, &c);
        comparison_avl += c;
    }
    finish2 = tick();
    result2 = (finish2 - start2) / TEST_SIZE;
    comparison_avl /= TEST_SIZE;

    int comparison_hash = 0;
    start3 = tick();
    for (int i = 0; i < TEST_SIZE; i++)
    {
        int c = 0;
        element = values[i];
        find_hash(wrap, element, &c);
        comparison_avl += c;
    }
    finish3 = tick();
    result3 = (finish3 - start3) / TEST_SIZE;
    comparison_hash /= TEST_SIZE;

    const char *Tree = "Tree";
    const char *AVL = "AVL-Tree";
    const char *Hash = "Hash-table";

    const char *compare = "Compared";
    const char *time = "Time";

    printf("Поиск в несортированных элементах\n");
    printf(" %15s %17s %18s\n"
           " %s %10d %15d %16d\n"
           " %s %4d %15d %16d\n",
           Tree, AVL, Hash,
           time,    (int)result1, (int)result2,(int)result3,
           compare, comparison_tree, comparison_avl, comparison_hash);
}

void test4()
{
    int element;
    int values[TEST_SIZE];

    tree_t *tree = NULL;
    avl_tree_t *avl_head = NULL;
    wrap_t *wrap = init_wrap(103);

    unsigned long long start1, finish1, result1;
    unsigned long long start2, finish2, result2;
    unsigned long long start3, finish3, result3;

    for (int i = 0; i < TEST_SIZE; i++)
    {
        element = rand() % 100 + 1;
        values[i] = element;
    }

    qsort(values, TEST_SIZE, sizeof (int), (int(*) (const void *, const void *)) comp);

    //заполнение
    for (int i = 0; i < TEST_SIZE; i++)
    {
        tree_t *node = tree_init(values[i]);
        add_tree_element(&tree, node);

        avl_tree_t *avl_node = avl_tree_init(values[i]);
        avl_head = add_avl_element(avl_head, avl_node);

        add_hash(wrap, values[i]);
    }

    //поиск

    int comparison_tree = 0;
    start1 = tick();
    for (int i = 0; i < TEST_SIZE; i++)
    {
        int c = 0;
        element = values[i];
        find_element_trew(tree, element, &c);
        comparison_tree += c;
    }
    finish1 = tick();
    result1 = (finish1 - start1) / TEST_SIZE;
    comparison_tree /= TEST_SIZE;

    int comparison_avl = 0;
    start2 = tick();
    for (int i = 0; i < TEST_SIZE; i++)
    {
        int c = 0;
        element = values[i];
        find_element_avl(avl_head, element, &c);
        comparison_avl += c;
    }
    finish2 = tick();
    result2 = (finish2 - start2) / TEST_SIZE;
    comparison_avl /= TEST_SIZE;

    int comparison_hash = 0;
    start3 = tick();
    for (int i = 0; i < TEST_SIZE; i++)
    {
        int c = 0;
        element = values[i];
        find_hash(wrap, element, &c);
        comparison_avl += c;
    }
    finish3 = tick();
    result3 = (finish3 - start3) / TEST_SIZE;
    comparison_hash /= TEST_SIZE;

    const char *Tree = "Tree";
    const char *AVL = "AVL-Tree";
    const char *Hash = "Hash-table";

    const char *compare = "Compared";
    const char *time = "Time";

    printf("Поиск в отсортированных элементах\n");
    printf(" %15s %17s %18s\n"
           " %s %10d %15d %16d\n"
           " %s %4d %15d %16d\n",
           Tree, AVL, Hash,
           time,    (int)result1, (int)result2,(int)result3,
           compare, comparison_tree, comparison_avl, comparison_hash);
}

void test5()
{
    int element;
    int values[TEST_SIZE];

    tree_t *tree = NULL;
    avl_tree_t *avl_head = NULL;
    wrap_t *wrap = init_wrap(103);

    unsigned long long start1, finish1, result1;
    unsigned long long start2, finish2, result2;
    unsigned long long start3, finish3, result3;

    for (int i = 0; i < TEST_SIZE; i++)
    {
        element = rand() % 100 + 1;
        values[i] = element;
    }

    qsort(values, TEST_SIZE, sizeof (int), (int(*) (const void *, const void *)) comp);
    int N = TEST_SIZE;

    for(int i = 0; i < TEST_SIZE / 2; i++)
    {
        int tmp = values[i];
        values[i] = values[N-i-1];
        values[N-i-1] = tmp;
    }

    //заполнение
    for (int i = 0; i < TEST_SIZE; i++)
    {
        tree_t *node = tree_init(values[i]);
        add_tree_element(&tree, node);

        avl_tree_t *avl_node = avl_tree_init(values[i]);
        avl_head = add_avl_element(avl_head, avl_node);

        add_hash(wrap, values[i]);
    }

    //поиск

    int comparison_tree = 0;
    start1 = tick();
    for (int i = 0; i < TEST_SIZE; i++)
    {
        int c = 0;
        element = values[i];
        find_element_trew(tree, element, &c);
        comparison_tree += c;
    }
    finish1 = tick();
    result1 = (finish1 - start1) / TEST_SIZE;
    comparison_tree /= TEST_SIZE;

    int comparison_avl = 0;
    start2 = tick();
    for (int i = 0; i < TEST_SIZE; i++)
    {
        int c = 0;
        element = values[i];
        find_element_avl(avl_head, element, &c);
        comparison_avl += c;
    }
    finish2 = tick();
    result2 = (finish2 - start2) / TEST_SIZE;
    comparison_avl /= TEST_SIZE;

    int comparison_hash = 0;
    start3 = tick();
    for (int i = 0; i < TEST_SIZE; i++)
    {
        int c = 0;
        element = values[i];
        find_hash(wrap, element, &c);
        comparison_avl += c;
    }
    finish3 = tick();
    result3 = (finish3 - start3) / TEST_SIZE;
    comparison_hash /= TEST_SIZE;

    const char *Tree = "Tree";
    const char *AVL = "AVL-Tree";
    const char *Hash = "Hash-table";

    const char *compare = "Compared";
    const char *time = "Time";

    printf("Поиск в обратно-отсортированных элементах\n");
    printf(" %15s %17s %18s\n"
           " %s %10d %15d %16d\n"
           " %s %4d %15d %16d\n",
           Tree, AVL, Hash,
           time,    (int)result1, (int)result2,(int)result3,
           compare, comparison_tree, comparison_avl, comparison_hash);
}

void test3()
{
    int element;
    int values[TEST_SIZE];

    tree_t *head = NULL;
    avl_tree_t *avl_head = NULL;

    unsigned long long start1, finish1, result1;
    unsigned long long start2, finish2, result2;

    for (int i = 0; i < TEST_SIZE; i++)
    {
        element = rand() % 100 + 1;
        values[i] = element;
    }

    for (int i = 0; i < TEST_SIZE; i++)
    {
        tree_t *node = tree_init(values[i]);
        add_tree_element(&head, node);

        avl_tree_t *avl_node = avl_tree_init(values[i]);
        avl_head = add_avl_element(avl_head, avl_node);
    }

    start1 = tick();
    for (int i = 0; i < TEST_SIZE; i++)
    {
        test_tree_traversal(head);
    }
    finish1 = tick();
    result1 = (finish1 - start1);


    start2 = tick();
    for (int i = 0; i < TEST_SIZE; i++)
    {
        test_avl_traversal(avl_head);
    }
    finish2 = tick();
    result2 = (finish2 - start2);

    const char *Tree = "Tree";
    const char *AVL = "AVL-Tree";

    const char *time = "Time";

    printf("Обход несортированном массиве.\n");
    printf(" %15s %17s\n"
           " %s %10d %15d\n",
           Tree, AVL,
           time,    (int)result1, (int)result2);
}

void test6()
{
    int element;
    int values[TEST_SIZE];

    tree_t *head = NULL;
    avl_tree_t *avl_head = NULL;

    for (int i = 0; i < TEST_SIZE; i++)
    {
        element = rand() % 100 + 1;
        values[i] = element;
    }

    qsort(values, TEST_SIZE, sizeof (int), (int(*) (const void *, const void *)) comp);

    for (int i = 0; i < TEST_SIZE; i++)
    {
        tree_t *node = tree_init(values[i]);
        add_tree_element(&head, node);

        avl_tree_t *avl_node = avl_tree_init(values[i]);
        avl_head = add_avl_element(avl_head, avl_node);
    }

    unsigned long long start1, finish1, result1;
    unsigned long long start2, finish2, result2;

    start1 = tick();
    for (int i = 0; i < TEST_SIZE; i++)
    {
        test_tree_traversal(head);
    }
    finish1 = tick();
    result1 = (finish1 - start1);


    start2 = tick();
    for (int i = 0; i < TEST_SIZE; i++)
    {
        test_avl_traversal(avl_head);
    }
    finish2 = tick();
    result2 = (finish2 - start2);

    const char *Tree = "Tree";
    const char *AVL = "AVL-Tree";

    const char *time = "Time";

    printf("Обход сортированном массиве.\n");
    printf(" %15s %17s\n"
           " %s %10d %15d\n",
           Tree, AVL,
           time,    (int)result1, (int)result2);
}

void test7()
{
    int element;
    int values[TEST_SIZE];

    tree_t *head = NULL;
    avl_tree_t *avl_head = NULL;

    for (int i = 0; i < TEST_SIZE; i++)
    {
        element = rand() % 100 + 1;
        values[i] = element;
    }

    qsort(values, TEST_SIZE, sizeof (int), (int(*) (const void *, const void *)) comp);
    int N = TEST_SIZE;

    for(int i = 0; i < TEST_SIZE / 2; i++)
    {
        int tmp = values[i];
        values[i] = values[N-i-1];
        values[N-i-1] = tmp;
    }

    for (int i = 0; i < TEST_SIZE; i++)
    {
        tree_t *node = tree_init(values[i]);
        add_tree_element(&head, node);

        avl_tree_t *avl_node = avl_tree_init(values[i]);
        avl_head = add_avl_element(avl_head, avl_node);
    }

    unsigned long long start1, finish1, result1;
    unsigned long long start2, finish2, result2;

    start1 = tick();
    for (int i = 0; i < TEST_SIZE; i++)
    {
        test_tree_traversal(head);
    }
    finish1 = tick();
    result1 = (finish1 - start1);


    start2 = tick();
    for (int i = 0; i < TEST_SIZE; i++)
    {
        test_avl_traversal(avl_head);
    }
    finish2 = tick();
    result2 = (finish2 - start2);

    const char *Tree = "Tree";
    const char *AVL = "AVL-Tree";

    const char *time = "Time";

    printf("Обход обратно отсортированном массиве.\n");
    printf(" %15s %17s\n"
           " %s %10d %15d\n",
           Tree, AVL,
           time,    (int)result1, (int)result2);
}



void test()
{
    int element;
    int values[TEST_SIZE];

    for (int i = 0; i < TEST_SIZE; i++)
    {
        element = rand() % 100 + 1;
        values[i] = element;
    }

    //заполнить структуры
    tree_t *head = NULL;
    avl_tree_t *avl_head = NULL;
    wrap_t *wrap = init_wrap(103);
    for (int i = 0; i < TEST_SIZE; i++)
    {
        tree_t *node = tree_init(values[i]);
        add_tree_element(&head, node);

        avl_tree_t *avl_node = avl_tree_init(values[i]);
        avl_head = add_avl_element(avl_head, avl_node);

        add_hash(wrap, values[i]);
    }

    test1();
    printf("\n");
    test2();
    printf("\n");
    test3();
    printf("\n");
    test4();
    printf("\n");
    test5();
    printf("\n");
    test6();
    printf("\n");
    test7();
    printf("\n");

    int memory1 = sizeof(tree_t) * TEST_SIZE;
    int memory2 = sizeof(avl_tree_t) * TEST_SIZE;;
    int memory3 = sizeof(hash_t) * TEST_SIZE;

    ////show_headline(1, "== Test ==");

    const char *tree = "Tree";
    const char *AVL = "AVL-Tree";
    const char *Hash = "Hash-table";
    const char *memory = "Memory";


    printf(" %15s %17s %18s\n"
           " %s %4d %15d %16d\n",
           tree, AVL, Hash,
           memory, memory1, memory2, memory3);
}

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}
