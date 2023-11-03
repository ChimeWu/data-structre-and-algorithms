//构造一棵平衡二叉树，要求节点中的数据用通用指针表示，且树的结构中要有一个函数指针，用于比较两个节点的数据的大小，还要有一个函数指针，用于销毁节点中的数据

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    void *data;
    int height;
    struct node *left;
    struct node *right;
} Node;

typedef struct tree
{
    Node *root;
    int size;
    int (*compare)(void *, void *);
    void (*destroy)(void *);
} Tree;

void init(Tree *tree, int (*compare)(void *, void *), void (*destroy)(void *))
{
    tree->root = NULL;
    tree->size = 0;
    tree->compare = compare;
    tree->destroy = destroy;
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

Node *insert(Node *node, void *data, int (*compare)(void *, void *))
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
    int result = compare(data, node->data);
    if (result < 0)
    {
        node->left = insert(node->left, data, compare);
        if (height(node->left) - height(node->right) == 2)
        {
            if (compare(data, node->left->data) < 0)
            {
                node = rightRotate(node);
            }
            else
            {
                node = leftRightRotate(node);
            }
        }
    }
    else if (result > 0)
    {
        node->right = insert(node->right, data, compare);
        if (height(node->right) - height(node->left) == 2)
        {
            if (compare(data, node->right->data) > 0)
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

void insertTree(Tree *tree, void *data)
{
    tree->root = insert(tree->root, data, tree->compare);
    tree->size++;
}

void *search(Node *node, void *data, int (*compare)(void *, void *))
{
    if (node == NULL)
    {
        return NULL;
    }
    int result = compare(data, node->data);
    if (result < 0)
    {
        return search(node->left, data, compare);
    }
    else if (result > 0)
    {
        return search(node->right, data, compare);
    }
    return node->data;
}

void *searchTree(Tree *tree, void *data)
{
    return search(tree->root, data, tree->compare);
}

Node *findMin(Node *node)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (node->left == NULL)
    {
        return node;
    }
    return findMin(node->left);
}

Node *removeMin(Node *node)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (node->left == NULL)
    {
        return node->right;
    }
    node->left = removeMin(node->left);
    return node;
}

Node *remove(Node *node, void *data, int (*compare)(void *, void *), void (*destroy)(void *))
{
    if (node == NULL)
    {
        return NULL;
    }
    int result = compare(data, node->data);
    if (result < 0)
    {
        node->left = remove(node->left, data, compare, destroy);
    }
    else if (result > 0)
    {
        node->right = remove(node->right, data, compare, destroy);
    }
    else
    {
        if (node->left == NULL)
        {
            Node *temp = node->right;
            destroy(node->data);
            free(node);
            return temp;
        }
        else if (node->right == NULL)
        {
            Node *temp = node->left;
            destroy(node->data);
            free(node);
            return temp;
        }
        else
        {
            Node *temp = findMin(node->right);
            node->data = temp->data;
            node->right = removeMin(node->right);
        }
    }
    return node;
}

void removeTree(Tree *tree, void *data)
{
    tree->root = remove(tree->root, data, tree->compare, tree->destroy);
    tree->size--;
}

void preOrder(Node *node, void (*traverse)(void *))
{
    if (node == NULL)
    {
        return;
    }
    traverse(node->data);
    preOrder(node->left, traverse);
    preOrder(node->right, traverse);
}

void preOrderTree(Tree *tree, void (*traverse)(void *))
{
    preOrder(tree->root, traverse);
}

void inOrder(Node *node, void (*traverse)(void *))
{
    if (node == NULL)
    {
        return;
    }
    inOrder(node->left, traverse);
    traverse(node->data);
    inOrder(node->right, traverse);
}

void inOrderTree(Tree *tree, void (*traverse)(void *))
{
    inOrder(tree->root, traverse);
}

void postOrder(Node *node, void (*traverse)(void *))
{
    if (node == NULL)
    {
        return;
    }
    postOrder(node->left, traverse);
    postOrder(node->right, traverse);
    traverse(node->data);
}

void postOrderTree(Tree *tree, void (*traverse)(void *))
{
    postOrder(tree->root, traverse);
}

bool contains(Node *node, void *data, int (*compare)(void *, void *))
{
    if (node == NULL)
    {
        return false;
    }
    int result = compare(data, node->data);
    if (result < 0)
    {
        return contains(node->left, data, compare);
    }
    else if (result > 0)
    {
        return contains(node->right, data, compare);
    }
    return true;
}

bool containsTree(Tree *tree, void *data)
{
    return contains(tree->root, data, tree->compare);
}

void print(Node *node, void (*print)(void *))
{
    if (node == NULL)
    {
        return;
    }
    print(node->data);
    print(node->left, print);
    print(node->right, print);
}

void printTree(Tree *tree, void (*print)(void *))
{
    print(tree->root, print);
}

void destroy(Node *node, void (*destroy)(void *))
{
    if (node == NULL)
    {
        return;
    }
    destroy(node->data);
    destroy(node->left, destroy);
    destroy(node->right, destroy);
    free(node);
}

void destroyTree(Tree *tree)
{
    destroy(tree->root, tree->destroy);
    tree->root = NULL;
    tree->size = 0;
}

typedef struct student
{
    char *name;
    int age;
} Student;

int compare(void *a, void *b)
{
    Student *studentA = (Student *)a;
    Student *studentB = (Student *)b;
    return studentA->age - studentB->age;
}

void destroy(void *data)
{
    Student *student = (Student *)data;
    free(student->name);
    free(student);
}

void print(void *data)
{
    Student *student = (Student *)data;
    printf("name = %s, age = %d\n", student->name, student->age);
}
