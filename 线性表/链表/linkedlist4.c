//实现一个静态链表，实现其基本操作

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 100

typedef struct node
{
    int data;
    int next;
} Node;

typedef struct staticlinkedlist
{
    Node data[MAXSIZE];
    int length;
    int head;
} StaticLinkedList;

void init(StaticLinkedList *list)
{
    list->length = 0;
    list->head = -1;
}

bool insert(StaticLinkedList *list, int index, int value)
{
    if (index < 0 || index > list->length || list->length == MAXSIZE)
    {
        return false;
    }
    int temp = list->head;
    for (int i = 0; i < index - 1; i++)
    {
        temp = list->data[temp].next;
    }
    int node = list->data[temp].next;
    list->data[temp].next = list->length;
    list->data[list->length].data = value;
    list->data[list->length].next = node;
    list->length++;
    return true;
}

bool delete(StaticLinkedList *list, int index)
{
    if (index < 0 || index >= list->length)
    {
        return false;
    }
    int temp = list->head;
    for (int i = 0; i < index - 1; i++)
    {
        temp = list->data[temp].next;
    }
    int node = list->data[temp].next;
    list->data[temp].next = list->data[node].next;
    list->length--;
    return true;
}

int search(StaticLinkedList *list, int value)
{
    int temp = list->head;
    for (int i = 0; i < list->length; i++)
    {
        if (list->data[temp].data == value)
        {
            return i;
        }
        temp = list->data[temp].next;
    }
    return -1;
}

void print(StaticLinkedList *list)
{
    int temp = list->head;
    for (int i = 0; i < list->length; i++)
    {
        printf("%d ", list->data[temp].data);
        temp = list->data[temp].next;
    }
    printf("\n");
}

int main()
{
    StaticLinkedList list;
    init(&list);
    for (int i = 0; i < 10; i++)
    {
        insert(&list, i, i + 1);
    }
    delete(&list, 5);
    printf("%d\n", search(&list, 6));
    print(&list);
    return 0;
}
