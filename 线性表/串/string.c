//构造一个串，实现其基本操作，包括串的赋值、串的连接、求子串、串的比较、求串长、清空串、销毁串等。实现一个模式匹配算法，实现模式匹配的基本操作，包括模式匹配、KMP算法等。

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 100

typedef struct string
{
    char data[MAXSIZE];
    int length;
} String;

void init(String *string)
{
    string->length = 0;
}

void assign(String *string, char *chars)
{
    int i = 0;
    while (chars[i] != '\0')
    {
        string->data[i] = chars[i];
        i++;
    }
    string->length = i;
}

void concat(String *string, String *string1, String *string2)
{
    int i = 0;
    while (i < string1->length)
    {
        string->data[i] = string1->data[i];
        i++;
    }
    int j = 0;
    while (j < string2->length)
    {
        string->data[i] = string2->data[j];
        i++;
        j++;
    }
    string->length = i;
}

void substring(String *string, String *string1, int pos, int len)
{
    int i = 0;
    while (i < len)
    {
        string->data[i] = string1->data[pos + i];
        i++;
    }
    string->length = i;
}

// 模式匹配算法
int compare(String *string1, String *string2)
{
    int i = 0;
    while (i < string1->length && i < string2->length)
    {
        if (string1->data[i] != string2->data[i])
        {
            return string1->data[i] - string2->data[i];
        }
        i++;
    }
    return string1->length - string2->length;
}

// KMP算法
int kmp(String *string1, String *string2)
{
    int i = 0;
    int j = 0;
    while (i < string1->length && j < string2->length)
    {
        if (string1->data[i] == string2->data[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j == string2->length)
    {
        return i - j;
    }
    else
    {
        return -1;
    }
}

int length(String *string)
{
    return string->length;
}

void clear(String *string)
{
    string->length = 0;
}

void destroy(String *string)
{
    free(string);
}

int main()
{
    String *string = (String *)malloc(sizeof(String));
    init(string);
    assign(string, "hello");
    printf("%s\n", string->data);
    String *string1 = (String *)malloc(sizeof(String));
    init(string1);
    assign(string1, "world");
    printf("%s\n", string1->data);
    String *string2 = (String *)malloc(sizeof(String));
    init(string2);
    concat(string2, string, string1);
    printf("%s\n", string2->data);
    String *string3 = (String *)malloc(sizeof(String));
    init(string3);
    substring(string3, string2, 1, 3);
    printf("%s\n", string3->data);
    printf("%d\n", compare(string, string1));
    printf("%d\n", length(string));
    clear(string);
    printf("%d\n", length(string));
    destroy(string);
    destroy(string1);
    destroy(string2);
    destroy(string3);
    return 0;
}
