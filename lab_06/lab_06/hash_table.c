#include "funcs.h"

void hash_menu()
{
    int inp_result;

    //функция для файлa
    wrap_t *wrap = init_wrap(2);
    fill_hash(wrap);

    //show_headline(2, "== Menu ==", "== Hash-table ==");
    show_hash_menu();
    check_input(&inp_result);

    while (inp_result)
    {
        switch(inp_result)
        {
        case 1:
            do_add_hash(wrap);
            break;

        case 2:
            do_delete_hash(wrap);
            break;

        case 3:
            do_find_hash(wrap);
            break;

        case 4:
            do_fix_collision(wrap);
            break;

        case 5:
            do_show_hash(wrap);
            break;

        case 0:
            return;

        default:
            show_result(inv_input);
            break;
        }

        //show_headline(2, "== Menu ==", "== Hash-table ==");
        show_hash_menu();
        check_input(&inp_result);
    }
}

void show_hash_menu()
{
    printf(" 1. Add element.           \n"
           " 2. Delete element.        \n"
           " 3. Find element.          \n"
           " 4. fix collisions.        \n"
           " 5. Show in console.       \n"
           " 0. Change data structure. \n"
           " Put the number: ");
}

wrap_t *init_wrap(int hash_func)
{
    wrap_t *wrap = malloc(sizeof(wrap_t));
    wrap->hash_func = hash_func;
    wrap->status = 0;
    wrap->max = 0;
    wrap->array = calloc( (ulong)hash_func, sizeof(hash_t *));

    return wrap;
}

hash_t *init_hash(int key)
{
    hash_t *node = malloc(sizeof(hash_t));
    node->key = key;
    node->next = NULL;

    return node;
}

int hash(int key, int m)
{
    return abs(key % m);
}

void add_hash(wrap_t *wrap, int key)
{
    int i = hash(key, wrap->hash_func);
    hash_t *node = init_hash(key);

    if (!((wrap->array)[i]))
        (wrap->array)[i] = node;
    else
    {
        hash_t *tmp = (wrap->array)[i];
        for (; tmp->next != NULL; tmp = tmp->next);
        tmp->next = node;
    }
}


void do_add_hash(wrap_t *wrap)
{
    //show_headline(1, "== Addition ==");

    int value;
    printf(" Input value: ");
    check_input(&value);

    wrap->max += 1;

    wrap->status = 1;
    add_hash(wrap, value);

    printf(" The node with value %d was added.\n", value);
}

void do_show_hash(wrap_t *wrap)
{
    ////show_headline(1, "== Show ==");

    if (!(wrap->status))
        show_result(empty_data);
    else
        show_hash(wrap);
}

void show_hash(wrap_t *wrap)
{
    char *index = "Index";
    char *key = "Key";

    printf("%18s %23s\n", index, key);
    for (int i = 0; i < wrap->hash_func; i++)
    {
        if ((wrap->array)[i])
            print_hash((wrap->array)[i], i);
    }
}

void fill_hash(wrap_t *wrap)
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

            wrap->max += 1;

            add_hash(wrap, value);
            wrap->status = 1;
            result = fscanf(file, "%d", &value);
        }
        if (!(wrap->status))
            code = empty_file;
    }
    else
        code = open_file_error;
    show_result(code);
}

void delete_hash(wrap_t *wrap, int key)
{
    int i = hash(key, wrap->hash_func);
    if (((wrap->array)[i]))
    {
        hash_t *tmp = (wrap->array)[i];
        hash_t *prev = tmp;

        if (tmp->key == key)
        {
            (wrap->array)[i] = tmp->next;
            free(tmp);
            return;
        }

        for (; tmp; tmp = tmp->next)
        {
            if (tmp->key == key)
            {
                prev->next = tmp->next;
                free(tmp);
                break;
            }
            prev = tmp;
        }
    }
}

void do_delete_hash(wrap_t *wrap)
{
    //show_headline(1, "== Delete ==");

    int element = get_element();
    delete_hash(wrap, element);

    show_result(success);
}

hash_t *find_hash(wrap_t *wrap, int key, int *comparison)
{
    int i = hash(key, wrap->hash_func);

    if (((wrap->array)[i]))
    {
        hash_t *tmp = (wrap->array)[i];
        for (; tmp; tmp = tmp->next)
        {
            (*comparison)++;
            if (tmp->key == key)
                return tmp;
        }
    }
    return NULL;
}

int get_simple(int digit)
{
    for (long long i = 2; i <= sqrt(digit); i++)
        if (!(digit % i))
            return get_simple(digit + 1);
    return digit;
}

void do_find_hash(wrap_t *wrap)
{
    int limit = 4;
    int comparison = 0;
    int code;

    //show_headline(1, "== Find ==");
    int key = get_element();

    hash_t *result = find_hash(wrap, key, &comparison);

    if (!result)
        code = find_error;
    else if (comparison > limit)
        code = restructurisation_error;
    else
        code = success;

    if (code != find_error)
        show_find_result(result, comparison);

    show_result(code);
}

void show_find_result(hash_t *head, int comparison)
{
    printf(" Founded value:         \n"
           " key: %-40d             \n"
           " comparison counted:  %d\n",
           head->key, comparison);
}

void do_fix_collision(wrap_t *wrap)
{
    //show_headline(1, "== Fix collisions ==");
    int simple = get_simple(wrap->max);
    int compare = wrap->hash_func;

    wrap->hash_func = simple;

    hash_t **array = calloc( (ulong)simple, sizeof(hash_t *));

    for (int i = 0; i < compare; i++)
    {
        if (wrap->array[i])
        {
            hash_t *tmp = wrap->array[i];
            while (tmp)
            {
                int key = tmp->key;
                int index = hash(key, simple);

                hash_t *node = init_hash(key);
                array[index] = node;

                tmp = tmp->next;
            }
        }
    }
    free(wrap->array);
    wrap->array = array;

    show_new_hash(wrap, compare);
}

void show_new_hash(wrap_t *wrap, int compare)
{
    char *exp_index = " Index before";
    char *index = " Index after";
    char *key = " Key";

    printf("%12s %19s %15s\n", exp_index, index, key);
    for (int i = 0; i < wrap->hash_func; i++)
    {
        if ((wrap->array)[i])
            print_new_hash((wrap->array)[i], i, compare);
    }
}

void print_hash(hash_t *head, int i)
{
    hash_t *tmp = head;
    printf("%16d                      ", i);
    for (; tmp; tmp = tmp->next)
        printf(" %d", tmp->key);
    printf("\n");
}

void print_new_hash(hash_t *head, int i, int j)
{
    hash_t *tmp = head;

    for (; tmp; tmp = tmp->next)
    {
        int index = hash(tmp->key, j);
        printf("%9d %19d %19d\n", index, i, tmp->key);
    }
}
