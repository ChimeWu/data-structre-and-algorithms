//构建一个循环双向链表，实现其基本操作

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
        temp->next->prev = node;
        temp->next = node;
        node->prev = temp;
    }
    list->size++;
}

void removeAt(LinkedList *list, int index)
{
    if (index < 0 || index >= list->size)
    {
        printf("index error\n");
        return;
    }
    Node *temp = list->head;
    if (index == 0)
    {
        list->head = list->head->next;
        list->head->prev = NULL;
    }
    else if (index == list->size - 1)
    {
        temp = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }
    else
    {
        for (int i = 0; i < index; i++)
        {
            temp = temp->next;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
    }
    free(temp);
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

int main()
{
    LinkedList list;
    init(&list);
    add(&list, 1);
    add(&list, 2);
    add(&list, 3);
    add(&list, 4);
    add(&list, 5);
    insert(&list, 0, 6);
    insert(&list, 6, 7);
    insert(&list, 3, 8);
    print(&list);
    removeAt(&list, 0);
    removeAt(&list, 5);
    removeAt(&list, 2);
    print(&list);
    printf("%d\n", search(&list, 3));
    printf("%d\n", search(&list, 8));
    printf("%d\n", search(&list, 9));
    return 0;
}
