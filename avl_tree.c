#include <stdio.h>
#include <malloc.h>

typedef struct tree_node
{
    int value;
    unsigned int height;
    struct tree_node * left;
    struct tree_node * right;

} tree_node_t;

int check(int value, tree_node_t tree)
{
    if (tree.value == value)
    {
        return 1;
    }

    if (tree.value < value)
    {
        if (tree.right == NULL)
        {
            return 0;
        }
        else
        {
            return check(value, *tree.right);
        }
    }

    if (tree.left == NULL)
    {
        return 0;
    }

    return check(value, *tree.left);
}

void tree_count_height(tree_node_t * tree)
{
    unsigned int heightleft = 0;
    if (tree->left != NULL)
    {
        heightleft = (*(*tree).left).height;
    }

    unsigned int heightright = 0;
    if (tree->right != NULL)
    {
        heightright = (*(*tree).right).height;
    }

    if (heightleft > heightright)
    {
        tree->height = heightleft + 1;
    }
    else
    {
        tree->height = heightright + 1;
    }
}

tree_node_t * tree_rotateright(tree_node_t * p)
{
    tree_node_t * q = p->left;
    p->left = q->right;
    q->right = p;
    tree_count_height(p);
    tree_count_height(q);
    return q;
}

tree_node_t * tree_rotateleft(tree_node_t * q)
{
    tree_node_t * p = q->right;
    q->right = p->left;
    p->left = q;
    tree_count_height(q);
    tree_count_height(p);
    return p;
}

int tree_get_balance_factor(tree_node_t * tree)
{
    int heightleft = 0;
    if (tree->left != NULL)
    {
        heightleft = (*(*tree).left).height;
    }

    int heightright = 0;
    if (tree->right != NULL)
    {
        heightright = (*(*tree).right).height;
    }
    return (heightright - heightleft);
}

tree_node_t * tree_balance(tree_node_t * p)
{
    tree_count_height(p);
    if (tree_get_balance_factor(p) == 2)
    {
        if (tree_get_balance_factor(p->right) < 0)
        {
            p->right = tree_rotateright(p->right);
        }
        return tree_rotateleft(p);
    }
    if (tree_get_balance_factor(p) == -2)
    {
        if (tree_get_balance_factor(p->left) > 0)
        {
            p->left = tree_rotateleft(p->left);
        }
        return tree_rotateright(p);
    }
    return p;
}

void delete_tree (tree_node_t *tree)
{
    if (tree == NULL)
        return;
    delete_tree(tree->right);
    delete_tree(tree->left);

    free(tree);
}

tree_node_t * insert(int value, tree_node_t * tree)
{
    if (tree == NULL)
    {
        tree_node_t * new_nod = malloc(sizeof(tree_node_t));

        new_nod->value = value;
        new_nod->right = NULL;
        new_nod->left = NULL;
        new_nod->height = 1;

        return new_nod;
    }

    if (value > tree->value)
    {
        tree->right = insert(value, tree->right);
    }
    else
    {
        tree->left = insert(value, tree->left);
    }

    return tree_balance(tree);
}

int main()
{
    int N;
    scanf("%d", &N);

    if (N == 0)
    {
        printf("0");
    }
    else
    {
        tree_node_t * root = NULL;
        for (size_t i = 0; i < N; i++)
        {
            int a;
            scanf("%d", &a);
            root = insert(a, root);
        }
        printf("%d", root->height);
        delete_tree(root);
    }

    return 0;
}
