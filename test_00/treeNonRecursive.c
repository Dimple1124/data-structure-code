#include <stdio.h>
#include <stdlib.h>

typedef struct treenode
{
    char data;
    struct treenode *lchild;
    struct treenode *rchild;
} treenode;

typedef struct stacknode
{
    treenode *data;
    struct stacknode *next;
} stacknode;

void createtree(treenode **t)
{
    char data;
    scanf(" %c", &data);
    if (data == '#')
        *t = NULL;
    else
    {
        *t = (treenode *)malloc(sizeof(treenode));
        (*t)->data = data;
        // 创建左右子树，逻辑一致，进行递归
        createtree(&((*t)->lchild));
        createtree(&((*t)->rchild));
    }
}

stacknode *initstack()
{
    stacknode *node = (stacknode *)malloc(sizeof(stacknode));
    node->data = NULL;
    node->next = NULL;
    return node;
}

void push(treenode *t, stacknode *s)
{
    stacknode *node = (stacknode *)malloc(sizeof(stacknode));
    node->data = t;
    node->next = s->next;
    s->next = node;
}
int isempty(stacknode *s)
{
    if (s->next == NULL)
        return 1;
    else
        return 0;
}

stacknode *pop(stacknode *s)
{
    if (isempty(s))
        return NULL;
    else
    {
        stacknode *node = s->next;
        s->next = node->next;
        return node;
    }
}

void preorder(treenode *t)
{
    if (t == NULL)
        return;
    else
    {
        treenode *node = t;
        stacknode *s = initstack();
        while (node || !isempty(s))
        {
            if (node)
            {
                printf("%c ", node->data);
                push(node, s);
                node = node->lchild;
            }
            else
            {
                node = pop(s)->data;
                node = node->rchild;
            }
        }
    }
}

void inorder(treenode *t)
{
    if (t == NULL)
        return;
    else
    {
        treenode *node = t;
        stacknode *s = initstack();
        while (node || !isempty(s))
        {
            if (node)
            {
                push(node, s);
                node = node->lchild;
            }
            else
            {
                node = pop(s)->data;
                printf("%c ", node->data);
                node = node->rchild;
            }
        }
    }
}

int main()
{
    treenode *t;
    createtree(&t);
    preorder(t);
    printf("\n");
    inorder(t);
    printf("\n");
    return 0;
}