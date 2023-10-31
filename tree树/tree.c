//定义一棵二叉树，实现二叉树的创建、遍历、查找、插入、删除等操作
// Created by Administrator on 2021/3/7.
//定义一棵二叉树，实现二叉树的创建、遍历、查找、插入、删除等操作

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
        while (true)
        {
            if (data < temp->data)
            {
                if (temp->left == NULL)
                {
                    temp->left = node;
                    break;
                }
                temp = temp->left;
            }
            else
            {
                if (temp->right == NULL)
                {
                    temp->right = node;
                    break;
                }
                temp = temp->right;
            }
        }
    }
    tree->size++;
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

bool contains(Node *node, int data)
{
    if (node == NULL)
    {
        return false;
    }
    if (node->data == data)
    {
        return true;
    }
    else if (data < node->data)
    {
        return contains(node->left, data);
    }
    else
    {
        return contains(node->right, data);
    }
}

int main()
{
    Tree tree;
    init(&tree);
    add(&tree, 5);
    add(&tree, 3);
    add(&tree, 7);
    add(&tree, 2);
    add(&tree, 4);
    add(&tree, 6);
    add(&tree, 8);
    printf("preOrder: ");
    preOrder(tree.root);
    printf("\n");
    printf("inOrder: ");
    inOrder(tree.root);
    printf("\n");
    printf("postOrder: ");
    postOrder(tree.root);
    printf("\n");
    printf("contains 3: %d\n", contains(tree.root, 3));
    printf("contains 9: %d\n", contains(tree.root, 9));
    return 0;
}
