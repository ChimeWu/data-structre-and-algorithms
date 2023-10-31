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

int hash(int data)
{
    return data % HASHSIZE;
}

void add(Hashmap *hashmap, int data)
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

void insert(Hashmap *hashmap, int index, int data)
{
    if (index < 0 || index > hashmap->size)
    {
        printf("index error\n");
        return;
    }
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    if (index == 0)
    {
        node->next = hashmap->nodes[index];
        hashmap->nodes[index] = node;
    }
    else
    {
        Node *temp = hashmap->nodes[index - 1];
        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }
        node->next = temp->next;
        temp->next = node;
    }
    hashmap->size++;
}

void remove_node(Hashmap *hashmap, int data)
{
    int index = hash(data);
    Node *temp = hashmap->nodes[index];
    if (temp == NULL)
    {
        printf("data not found\n");
        return;
    }
    if (temp->data == data)
    {
        hashmap->nodes[index] = temp->next;
        free(temp);
        hashmap->size--;
        return;
    }
    while (temp->next != NULL && temp->next->data != data)
    {
        temp = temp->next;
    }
    if (temp->next == NULL)
    {
        printf("data not found\n");
        return;
    }
    Node *node = temp->next;
    temp->next = node->next;
    free(node);
    hashmap->size--;
}

void print(Hashmap *hashmap)
{
    for (int i = 0; i < HASHSIZE; i++)
    {
        Node *temp = hashmap->nodes[i];
        printf("index %d: ", i);
        while (temp != NULL)
        {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

