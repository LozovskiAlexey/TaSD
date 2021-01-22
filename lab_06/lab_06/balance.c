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