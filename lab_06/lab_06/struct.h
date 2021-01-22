enum result
{
    open_file_error = -7,
    restructurisation_error,
    empty_data,
    empty_file,
    inv_input,
    find_error,
    success = 0
};

typedef struct tree tree_t;
typedef struct avl_tree avl_tree_t;
typedef struct hash_table hash_t;
typedef struct wrap wrap_t;

typedef unsigned char unch;
typedef unsigned long ulong;

struct tree
{
    int key;

    tree_t *left;
    tree_t *right;
};

struct avl_tree
{
    int key;
    unsigned char height;

    avl_tree_t *left;
    avl_tree_t *right;
};

struct hash_table
{
    int key;

    hash_t *next;
};

struct wrap
{
    hash_t **array;

    int max;
    int status;
    int hash_func;
};
