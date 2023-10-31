//构造一棵红黑树，并实现其插入、删除、查找、打印等操作

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int data;
    bool color;
    struct node *left;
    struct node *right;
    struct node *parent;
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

Node *grandparent(Node *node)
{
    if ((node != NULL) && (node->parent != NULL))
    {
        return node->parent->parent;
    }
    else
    {
        return NULL;
    }
}

Node *uncle(Node *node)
{
    Node *g = grandparent(node);
    if (g == NULL)
    {
        return NULL;
    }
    if (node->parent == g->left)
    {
        return g->right;
    }
    else
    {
        return g->left;
    }
}

void rotate_left(Tree *tree, Node *node)
{
    Node *right = node->right;
    node->right = right->left;
    if (right->left != NULL)
    {
        right->left->parent = node;
    }
    right->parent = node->parent;
    if (node->parent == NULL)
    {
        tree->root = right;
    }
    else if (node == node->parent->left)
    {
        node->parent->left = right;
    }
    else
    {
        node->parent->right = right;
    }
    right->left = node;
    node->parent = right;
}

void rotate_right(Tree *tree, Node *node)
{
    Node *left = node->left;
    node->left = left->right;
    if (left->right != NULL)
    {
        left->right->parent = node;
    }
    left->parent = node->parent;
    if (node->parent == NULL)
    {
        tree->root = left;
    }
    else if (node == node->parent->right)
    {
        node->parent->right = left;
    }
    else
    {
        node->parent->left = left;
    }
    left->right = node;
    node->parent = left;
}

void insert(Tree *tree, int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->color = true;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
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
                    node->parent = temp;
                    break;
                }
                temp = temp->left;
            }
            else
            {
                if (temp->right == NULL)
                {
                    temp->right = node;
                    node->parent = temp;
                    break;
                }
                temp = temp->right;
            }
        }
    }
    tree->size++;
    //插入修复
    Node *current = node;
    while ((current != NULL) && (current->parent != NULL) && (current->parent->color == true))
    {
        Node *u = uncle(current);
        Node *g = grandparent(current);
        if (u != NULL && u->color == true)
        {
            current->parent->color = false;
            u->color = false;
            g->color = true;
            current = g;
        }
        else
        {
            if (current->parent == g->left)
            {
                if (current == current->parent->right)
                {
                    rotate_left(tree, current->parent);
                    current = current->left;
                }
                rotate_right(tree, g);
                current->parent->color = false;
                current->parent->right->color = true;
            }
            else
            {
                if (current == current->parent->left)
                {
                    rotate_right(tree, current->parent);
                    current = current->right;
                }
                rotate_left(tree, g);
                current->parent->color = false;
                current->parent->left->color = true;
            }
        }
    }
    tree->root->color = false;
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
    if (data < node->data)
    {
        return contains(node->left, data);
    }
    else if (data > node->data)
    {
        return contains(node->right, data);
    }
    else
    {
        return true;
    }
}

Node *search(Tree *tree, int data)
{
    Node *temp = tree->root;
    while (temp != NULL)
    {
        if (data < temp->data)
        {
            temp = temp->left;
        }
        else if (data > temp->data)
        {
            temp = temp->right;
        }
        else
        {
            return temp;
        }
    }
    return NULL;
}

void removeNode(Tree *tree, Node *node)
{
    if (node == NULL)
    {
        return;
    }
    if (node->left == NULL && node->right == NULL)
    {
        if (node == tree->root)
        {
            tree->root = NULL;
        }
        else
        {
            if (node == node->parent->left)
            {
                node->parent->left = NULL;
            }
            else
            {
                node->parent->right = NULL;
            }
        }
        free(node);
    }
    else if (node->left != NULL && node->right != NULL)
    {
        Node *temp = node->right;
        while (temp->left != NULL)
        {
            temp = temp->left;
        }
        node->data = temp->data;
        removeNode(tree, temp);
    }
    else
    {
        Node *child = (node->left != NULL) ? node->left : node->right;
        if (node == tree->root)
        {
            tree->root = child;
        }
        else
        {
            if (node == node->parent->left)
            {
                node->parent->left = child;
            }
            else
            {
                node->parent->right = child;
            }
        }
        child->parent = node->parent;
        free(node);
    }
}

void remove(Tree *tree, int data)
{
    Node *node = search(tree, data);
    removeNode(tree, node);
}

