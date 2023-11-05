//构造一棵B+树，实现插入、删除、查找等操作

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define M 3

typedef struct node
{
    int data[M - 1];
    struct node *child[M];
    int size;
    bool leaf;
} Node;

typedef struct tree
{
    Node *root;
    int size;
} Tree;

void init(Tree *tree)
{
    tree->root = NULL;
    tree->size = 0;
}

Node *create_node()
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->size = 0;
    node->leaf = true;
    return node;
}

void split_child(Node *parent, int index, Node *child)
{
    Node *node = create_node();
    node->leaf = child->leaf;
    node->size = M / 2 - 1;
    for (int i = 0; i < node->size; i++)
    {
        node->data[i] = child->data[i + M / 2];
    }
    if (!child->leaf)
    {
        for (int i = 0; i < M / 2; i++)
        {
            node->child[i] = child->child[i + M / 2];
        }
    }
    child->size = M / 2 - 1;
    for (int i = parent->size; i > index; i--)
    {
        parent->child[i + 1] = parent->child[i];
    }
    parent->child[index + 1] = node;
    for (int i = parent->size - 1; i >= index; i--)
    {
        parent->data[i + 1] = parent->data[i];
    }
    parent->data[index] = child->data[M / 2 - 1];
    parent->size++;
}

void insert_nonfull(Node *node, int data)
{
    int i = node->size - 1;
    if (node->leaf)
    {
        while (i >= 0 && data < node->data[i])
        {
            node->data[i + 1] = node->data[i];
            i--;
        }
        node->data[i + 1] = data;
        node->size++;
    }
    else
    {
        while (i >= 0 && data < node->data[i])
        {
            i--;
        }
        i++;
        if (node->child[i]->size == M - 1)
        {
            split_child(node, i, node->child[i]);
            if (data > node->data[i])
            {
                i++;
            }
        }
        insert_nonfull(node->child[i], data);
    }
}

void insert(Tree *tree, int data)
{
    if (tree->root == NULL)
    {
        tree->root = create_node();
        tree->root->data[0] = data;
        tree->root->size++;
    }
    else
    {
        if (tree->root->size == M - 1)
        {
            Node *node = create_node();
            node->leaf = false;
            node->child[0] = tree->root;
            split_child(node, 0, tree->root);
            int i = 0;
            if (node->data[0] < data)
            {
                i++;
            }
            insert_nonfull(node->child[i], data);
            tree->root = node;
        }
        else
        {
            insert_nonfull(tree->root, data);
        }
    }
    tree->size++;
}

void print(Node *node)
{
    for (int i = 0; i < node->size; i++)
    {
        printf("%d ", node->data[i]);
    }
    printf("\n");
    if (!node->leaf)
    {
        for (int i = 0; i <= node->size; i++)
        {
            print(node->child[i]);
        }
    }
}

void printTree(Tree *tree)
{
    print(tree->root);
    printf("\n");
}

