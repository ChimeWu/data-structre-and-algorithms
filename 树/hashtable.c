//构造一个散列表，并且实现插入、查找、删除、销毁等操作，实现一个散列函数，解决冲突的方法采用链地址法。

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define HASHSIZE 10

typedef struct node
{
    int data;
    struct node *next;
} Node;

typedef struct hashmap
{
    Node *nodes[HASHSIZE];
    int size;
} Hashmap;

void init(Hashmap *hashmap)
{
    for (int i = 0; i < HASHSIZE; i++)
    {
        hashmap->nodes[i] = NULL;
    }
    hashmap->size = 0;
}

//除留余数法
int hash(int data)
{
    return data % HASHSIZE;
}

//直接定址法
int hash2(int data)
{
    return data;
}

//平方取中法
int hash3(int data)
{
    int temp = data * data;
    temp = temp / 100 % 10000;
    return temp;
}

//数字分析法
int hash4(int data)
{
    int temp = data;
    int sum = 0;
    while (temp != 0)
    {
        sum += temp % 10;
        temp /= 10;
    }
    return sum % HASHSIZE;
}

//折叠法
int hash5(int data)
{
    int temp = data;
    int sum = 0;
    while (temp != 0)
    {
        sum += temp % 100;
        temp /= 100;
    }
    return sum % HASHSIZE;
}

//开放定址法解决冲突
int hash6(int data, int i)
{
    return (hash(data) + i) % HASHSIZE;
}

//拉链法解决冲突
int hash7(int data)
{
    return hash(data);
}

void insert(Hashmap *hashmap, int data)
{
    int index = hash(data);
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    if (hashmap->nodes[index] == NULL)
    {
        hashmap->nodes[index] = node;
    }
    else
    {
        Node *temp = hashmap->nodes[index];
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = node;
    }
    hashmap->size++;
}

Node *find(Hashmap *hashmap, int data)
{
    int index = hash(data);
    Node *temp = hashmap->nodes[index];
    while (temp != NULL)
    {
        if (temp->data == data)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void delete(Hashmap *hashmap, int data)
{
    int index = hash(data);
    Node *node = NULL;
    if (hashmap->nodes[index] != NULL && hashmap->nodes[index]->data == data)
    {
        node = hashmap->nodes[index];
        hashmap->nodes[index] = hashmap->nodes[index]->next;
    }
    else
    {
        Node *temp = hashmap->nodes[index];
        while (temp->next != NULL)
        {
            if (temp->next->data == data)
            {
                node = temp->next;
                temp->next = temp->next->next;
                break;
            }
            temp = temp->next;
        }
    }
    if (node != NULL)
    {
        free(node);
        hashmap->size--;
    }
}

void destroy(Hashmap *hashmap)
{
    for (int i = 0; i < HASHSIZE; i++)
    {
        Node *temp = hashmap->nodes[i];
        while (temp != NULL)
        {
            Node *node = temp;
            temp = temp->next;
            free(node);
        }
    }
    hashmap->size = 0;
}

void print(Hashmap *hashmap)
{
    for (int i = 0; i < HASHSIZE; i++)
    {
        printf("%d: ", i);
        Node *temp = hashmap->nodes[i];
        while (temp != NULL)
        {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

