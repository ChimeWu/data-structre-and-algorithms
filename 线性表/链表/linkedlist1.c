//构造一个双链表，实现插入、删除、查找等操作

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int data;
    struct node *prev;
    struct node *next;
} Node;

typedef struct linkedlist
{
    Node *head;
    Node *tail;
    int size;
} LinkedList;

void init(LinkedList *list)
{
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void add(LinkedList *list, int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    if (list->head == NULL)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
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
    node->prev = NULL;
    node->next = NULL;
    if (index == 0)
    {
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
    else if (index == list->size)
    {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
    }
    else
    {
        Node *temp = list->head;
        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }
        node->next = temp->next;
        node->prev = temp;
        temp->next->prev = node;
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
    if (index == 0)
    {
        Node *temp = list->head;
        list->head = list->head->next;
        list->head->prev = NULL;
        free(temp);
    }
    else if (index == list->size - 1)
    {
        Node *temp = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        free(temp);
    }
    else
    {
        Node *temp = list->head;
        for (int i = 0; i < index; i++)
        {
            temp = temp->next;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        free(temp);
    }
    list->size--;
}

int search(LinkedList *list, int data)
{
    Node *temp = list->head;
    for (int i = 0; i < list->size; i++)
    {
        if (temp->data == data)
        {
            return i;
        }
        temp = temp->next;
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


