//构造一个循环单链表，并实现其基本操作

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
        node->next = list->head;
    }
    else
    {
        Node *temp = list->head;
        while (temp->next != list->head)
        {
            temp = temp->next;
        }
        temp->next = node;
        node->next = list->head;
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
        Node *temp = list->head;
        while (temp->next != list->head)
        {
            temp = temp->next;
        }
        temp->next = list->head;
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

bool delete(LinkedList *list, int index)
{
    if (index < 0 || index >= list->size)
    {
        printf("index error\n");
        return false;
    }
    Node *temp = list->head;
    if (index == 0)
    {
        while (temp->next != list->head)
        {
            temp = temp->next;
        }
        list->head = list->head->next;
        temp->next = list->head;
    }
    else
    {
        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }
        temp->next = temp->next->next;
    }
    list->size--;
    return true;
}

int search(LinkedList *list, int data)
{
    Node *temp = list->head;
    int index = 0;
    while (temp->next != list->head)
    {
        if (temp->data == data)
        {
            return index;
        }
        temp = temp->next;
        index++;
    }
    if (temp->data == data)
    {
        return index;
    }
    return -1;
}

void print(LinkedList *list)
{
    Node *temp = list->head;
    while (temp->next != list->head)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("%d\n", temp->data);
}

int main()
{
    LinkedList list;
    init(&list);
    for (int i = 0; i < 10; i++)
    {
        add(&list, i + 1);
    }
    insert(&list, 0, 0);
    insert(&list, 5, 5);
    insert(&list, 12, 12);
    delete(&list, 0);
    delete(&list, 5);
    delete(&list, 10);
    printf("%d\n", search(&list, 6));
    print(&list);
    return 0;
}
