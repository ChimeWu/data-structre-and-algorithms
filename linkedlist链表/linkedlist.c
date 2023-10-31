//creat a linkedlist
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node
{
    int data;
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
    node->next = NULL;
    if (list->head == NULL)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        list->tail->next = node;
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
    node->next = NULL;
    if (index == 0)
    {
        node->next = list->head;
        list->head = node;
    }
    else if (index == list->size)
    {
        list->tail->next = node;
        list->tail = node;
    }
    else
    {
        Node *current = list->head;
        for (int i = 0; i < index - 1; i++)
        {
            current = current->next;
        }
        node->next = current->next;
        current->next = node;
    }
    list->size++;
}

void removeNode(LinkedList *list, int index)
{
    if (index < 0 || index >= list->size)
    {
        printf("index error\n");
        return;
    }
    Node *current = list->head;
    if (index == 0)
    {
        list->head = current->next;
        free(current);
    }
    else if (index == list->size - 1)
    {
        for (int i = 0; i < index - 1; i++)
        {
            current = current->next;
        }
        current->next = NULL;
        free(list->tail);
        list->tail = current;
    }
    else
    {
        for (int i = 0; i < index - 1; i++)
        {
            current = current->next;
        }
        Node *temp = current->next;
        current->next = temp->next;
        free(temp);
    }
    list->size--;
}

void print(LinkedList *list)
{
    Node *current = list->head;
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

