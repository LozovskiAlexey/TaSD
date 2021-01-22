//������ � �������, �������� � � �������� �����������
//�.� � �������� ���������
unch height(avl_tree_t *head)
{
    return head ? head->height : 0;
}

//��������� balance factor ��������� ����
//��������� ������ ��������� ���������
int bfactor(avl_tree_t *head)
{
    return height(head->right) - height(head->left);
}

//��������������� ���������� �������� ���� height
//��������� ����, ��� �������, ��� ��� ���� !NULL
void fixheight(avl_tree_t *head)
{
    unch height_left = height(head->left);
    unch height_right = height(head->right);

    head->height = (height_left > height_right ? height_left : height_right) + 1;
}

//������ �������
avl_tree_t *rotate_right(avl_tree_t *head)
{
    avl_tree_t *q = head->left;
    head->left = q->right;
    q->right = head;

    fixheight(head);
    fixheight(q);

    return q;
}
//����� �������
avl_tree_t *rotate_left(avl_tree_t *head)
{
    avl_tree_t *p = head->right;
    head->right = p->left;
    p->left = head;

    fixheight(head);
    fixheight(p);

    return p;
}
//������������
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