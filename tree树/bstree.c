//构造一棵二叉排序树，实现插入、删除、查找等操作

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int data;
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

void add(Tree *tree, int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    if (tree->root == NULL)
    {
        tree->root = node;
    }
    else
    {
        Node *temp = tree->root;
        while (temp!=NULL && data!=temp->data)
        {
            if (data < temp->data)
            {
                temp = temp->left;
            }
            else
            {
                temp = temp->right;
            }
        }
        
    }
    tree->size++;
}

//定义一个插入节点的函数，要求使用递归
Node *insertNode(Node *node, int data)
{
    if (node == NULL)
    {
        Node *temp = (Node *)malloc(sizeof(Node));
        temp->data = data;
        temp->left = NULL;
        temp->right = NULL;
        return temp;
    }
    if (data < node->data)
    {
        node->left = insertNode(node->left, data);
    }
    else if (data > node->data)
    {
        node->right = insertNode(node->right, data);
    }
    return node;
}

Node *search(Tree *tree, int data)
{
    Node *temp = tree->root;
    while (temp != NULL)
    {
        if (data == temp->data)
        {
            return temp;
        }
        else if (data < temp->data)
        {
            temp = temp->left;
        }
        else
        {
            temp = temp->right;
        }
    }
    return NULL;
}

//定义删除节点的函数
void removeNode(Tree *tree, Node *node)
{
    if (node == NULL)
    {
        return;
    }
    //找到node的父节点
    Node *parent = NULL;
    Node *temp = tree->root;
    while (temp != NULL)
    {
        if (node->data == temp->data)
        {
            break;
        }
        parent = temp;
        if (node->data < temp->data)
        {
            temp = temp->left;
        }
        else
        {
            temp = temp->right;
        }
    }
    //没有找到
    if (temp == NULL)
    {
        return;
    }
    //要删除的节点有两个子节点
    if (node->left != NULL && node->right != NULL)
    {
        //找到右子树中最小的节点
        Node *minP = node->right;
        Node *minPP = node;
        while (minP->left != NULL)
        {
            minPP = minP;
            minP = minP->left;
        }
        //把minP的数据替换到p中
        node->data = minP->data;
        //下面就变成了删除minP了
        node = minP;
        parent = minPP;
    }
    //删除节点是叶子节点或者仅有一个子节点
    Node *child = NULL;
    if (node->left != NULL)
    {
        child = node->left;
    }
    else if (node->right != NULL)
    {
        child = node->right;
    }
    else
    {
        child = NULL;
    }
    if (parent == NULL)
    {
        tree->root = NULL;
    }
    else if (parent->left == node)
    {
        parent->left = child;
    }
    else
    {
        parent->right = child;
    }
    free(node);
    tree->size--;
}

void removeData(Tree *tree, int data)
{
    Node *node = search(tree, data);
    removeNode(tree, node);
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

//层次遍历
void levelOrder(Tree *tree)
{
    if (tree->root == NULL)
    {
        return;
    }
    Node *queue[tree->size];
    int front = 0;
    int rear = 0;
    queue[rear++] = tree->root;
    while (front < rear)
    {
        Node *node = queue[front++];
        printf("%d ", node->data);
        if (node->left != NULL)
        {
            queue[rear++] = node->left;
        }
        if (node->right != NULL)
        {
            queue[rear++] = node->right;
        }
    }
}

void print(Tree *tree)
{
    printf("size: %d\n", tree->size);
    printf("preOrder: ");
    preOrder(tree->root);
    printf("\n");
    printf("inOrder: ");
    inOrder(tree->root);
    printf("\n");
    printf("postOrder: ");
    postOrder(tree->root);
    printf("\n");
}

