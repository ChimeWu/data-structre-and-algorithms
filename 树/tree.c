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

//删除节点
Node *delete(Node *node, int data)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (data < node->data)
    {
        node->left = delete(node->left, data);
    }
    else if (data > node->data)
    {
        node->right = delete(node->right, data);
    }
    else
    {
        if (node->left == NULL && node->right == NULL)
        {
            free(node);
            return NULL;
        }
        else if (node->left == NULL)
        {
            Node *temp = node->right;
            free(node);
            return temp;
        }
        else if (node->right == NULL)
        {
            Node *temp = node->left;
            free(node);
            return temp;
        }
        else
        {
            Node *temp = node->right;
            while (temp->left != NULL)
            {
                temp = temp->left;
            }
            node->data = temp->data;
            node->right = delete(node->right, temp->data);
        }
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

//编写一个函数，能动态地将一个数组转换为一棵二叉排序树，在屏幕上将该树打印出来，要求打印成一棵树形
//例如，数组{1,2,3,4,5,6,7,8,9}转换为二叉排序树后，打印结果如下：
//        5
//    3       8
//  2   4   7   9
//1       6
//提示：先将数组中间的元素作为根节点，然后将数组分成左右两部分，分别递归地将左右两部分的元素转换为左右子树
//     递归结束的条件是数组为空

Node *arrayToTree(int *array, int length)
{
    if (length == 0)
    {
        return NULL;
    }
    Node *node = (Node *)malloc(sizeof(Node));
    int middle = length / 2;
    node->data = array[middle];
    node->left = arrayToTree(array, middle);
    node->right = arrayToTree(array + middle + 1, length - middle - 1);
    return node;
}

void printTree(Node *node, int level)
{
    if (node == NULL)
    {
        return;
    }
    printTree(node->right, level + 1);
    for (int i = 0; i < level; i++)
    {
        printf("    ");
    }
    printf("%d\n", node->data);
    printTree(node->left, level + 1);
}

//编写一个函数，从用户获得数据输入，调用以上函数，将输入的数据转换为二叉排序树，然后打印出来

void input(Tree *tree)
{
    int data;
    while (true)
    {
        printf("请输入数据：");
        scanf("%d", &data);
        if (data == 0)
        {
            break;
        }
        add(tree, data);
    }
}

int main()
{
    Tree tree;
    init(&tree);
    input(&tree);
    printTree(tree.root, 0);
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9,10};
    Node *node = arrayToTree(a, 10);
    printTree(node, 0);
    return 0;
}
