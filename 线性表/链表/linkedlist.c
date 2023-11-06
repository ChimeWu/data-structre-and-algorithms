//构造一个单链表，并实现插入、删除、查找等操作

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int data;
    struct node *next;
} Node;

typedef struct linkedlist
{
    Node *head;
    int size;
} LinkedList;

void init(LinkedList *list)
{
    list->head = NULL;
    list->size = 0;
}

void add(LinkedList *list, int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    if (list->head == NULL)
    {
        list->head = node;
    }
    else
    {
        Node *temp = list->head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = node;
    }
    list->size++;
}

//采用头插法建立链表
void addHead(LinkedList *list, int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = list->head;
    list->head = node;
    list->size++;
}

//采用尾插法建立链表
void addTail(LinkedList *list, int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    if (list->head == NULL)
    {
        list->head = node;
    }
    else
    {
        Node *temp = list->head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = node;
    }
    list->size++;
}

void insert(LinkedList *list, int index, int data)
{
    if (index < 0 || index > list->size)
    {
        printf("index error\n");
        return;
    }
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    if (index == 0)
    {
        node->next = list->head;
        list->head = node;
    }
    else
    {
        Node *temp = list->head;
        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }
        node->next = temp->next;
        temp->next = node;
    }
    list->size++;
}

void delete(LinkedList *list, int index)
{
    if (index < 0 || index >= list->size)
    {
        printf("index error\n");
        return;
    }
    Node *node = NULL;
    if (index == 0)
    {
        node = list->head;
        list->head = list->head->next;
    }
    else
    {
        Node *temp = list->head;
        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }
        node = temp->next;
        temp->next = temp->next->next;
    }
    free(node);
    list->size--;
}

//删除给定节点
void deleteNode(LinkedList *list, Node *node)
{
    if (node == NULL)
    {
        return;
    }
    if (node == list->head)
    {
        list->head = list->head->next;
    }
    else
    {
        Node *temp = list->head;
        while (temp != NULL && temp->next != node)
        {
            temp = temp->next;
        }
        if (temp != NULL)
        {
            temp->next = temp->next->next;
        }
    }
    free(node);
    list->size--;
}

int search(LinkedList *list, int data)
{
    Node *temp = list->head;
    int index = 0;
    while (temp != NULL)
    {
        if (temp->data == data)
        {
            return index;
        }
        temp = temp->next;
        index++;
    }
    return -1;
}

void print(LinkedList *list)
{
    Node *temp = list->head;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

//顺序查找
Node *searchNode(LinkedList *list, int data)
{
    Node *temp = list->head;
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

//折半查找
Node *searchNode2(LinkedList *list, int data)
{
    Node *temp = list->head;
    int low = 0;
    int high = list->size - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        for (int i = 0; i < mid; i++)
        {
            temp = temp->next;
        }
        if (temp->data == data)
        {
            return temp;
        }
        else if (temp->data > data)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
        temp = list->head;
    }
    return NULL;
}

//分块查找
Node *searchNode3(LinkedList *list, int data)
{
    Node *temp = list->head;
    int low = 0;
    int high = list->size - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        for (int i = 0; i < mid; i++)
        {
            temp = temp->next;
        }
        if (temp->data == data)
        {
            return temp;
        }
        else if (temp->data > data)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
        temp = list->head;
    }
    return NULL;
}

