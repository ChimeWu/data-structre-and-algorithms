//构建一棵平衡二叉树，实现插入、删除、查找、遍历等操作

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int data;
    int height;
    struct node *left;
    struct node *right;
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

int max(int a, int b)
{
    return a > b ? a : b;
}

int height(Node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return node->height;
}

Node *leftRotate(Node *node)
{
    Node *temp = node->right;
    node->right = temp->left;
    temp->left = node;
    node->height = max(height(node->left), height(node->right)) + 1;
    temp->height = max(height(temp->left), height(temp->right)) + 1;
    return temp;
}

Node *rightRotate(Node *node)
{
    Node *temp = node->left;
    node->left = temp->right;
    temp->right = node;
    node->height = max(height(node->left), height(node->right)) + 1;
    temp->height = max(height(temp->left), height(temp->right)) + 1;
    return temp;
}

Node *leftRightRotate(Node *node)
{
    node->left = leftRotate(node->left);
    return rightRotate(node);
}

Node *rightLeftRotate(Node *node)
{
    node->right = rightRotate(node->right);
    return leftRotate(node);
}

Node *insert(Node *node, int data)
{
    if (node == NULL)
    {
        node = (Node *)malloc(sizeof(Node));
        node->data = data;
        node->height = 1;
        node->left = NULL;
        node->right = NULL;
        return node;
    }
    if (data < node->data)
    {
        node->left = insert(node->left, data);
        if (height(node->left) - height(node->right) == 2)
        {
            if (data < node->left->data)
            {
                node = rightRotate(node);
            }
            else
            {
                node = leftRightRotate(node);
            }
        }
    }
    else if (data > node->data)
    {
        node->right = insert(node->right, data);
        if (height(node->right) - height(node->left) == 2)
        {
            if (data > node->right->data)
            {
                node = leftRotate(node);
            }
            else
            {
                node = rightLeftRotate(node);
            }
        }
    }
    node->height = max(height(node->left), height(node->right)) + 1;
    return node;
}

Node *find(Node *node, int data)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (data < node->data)
    {
        return find(node->left, data);
    }
    else if (data > node->data)
    {
        return find(node->right, data);
    }
    else
    {
        return node;
    }
}

Node *findMin(Node *node)
{
    if (node == NULL)
    {
        return NULL;
    }
    else if (node->left == NULL)
    {
        return node;
    }
    else
    {
        return findMin(node->left);
    }
}

Node *removeNode(Node *node, int data)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (data < node->data)
    {
        node->left = removeNode(node->left, data);
        if (height(node->right) - height(node->left) == 2)
        {
            if (height(node->right->left) > height(node->right->right))
            {
                node = rightLeftRotate(node);
            }
            else
            {
                node = leftRotate(node);
            }
        }
    }
    else if (data > node->data)
    {
        node->right = removeNode(node->right, data);
        if (height(node->left) - height(node->right) == 2)
        {
            if (height(node->left->right) > height(node->left->left))
            {
                node = leftRightRotate(node);
            }
            else
            {
                node = rightRotate(node);
            }
        }
    }
    else
    {
        if (node->left && node->right)
        {
            Node *temp = findMin(node->right);
            node->data = temp->data;
            node->right = removeNode(node->right, temp->data);
        }
        else
        {
            Node *temp = node;
            if (node->left == NULL)
            {
                node = node->right;
            }
            else if (node->right == NULL)
            {
                node = node->left;
            }
            free(temp);
        }
    }
    if (node != NULL)
    {
        node->height = max(height(node->left), height(node->right)) + 1;
    }
    return node;
}

void preOrder(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    printf("%d ", node->data);
    preOrder(node->left);
    preOrder(node->right);
}

void inOrder(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    inOrder(node->left);
    printf("%d ", node->data);
    inOrder(node->right);
}

void postOrder(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    postOrder(node->left);
    postOrder(node->right);
    printf("%d ", node->data);
}

void destroy(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    destroy(node->left);
    destroy(node->right);
    free(node);
}

