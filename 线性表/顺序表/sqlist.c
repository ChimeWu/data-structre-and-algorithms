#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAXSIZE 50

typedef struct
{
    int data[MAXSIZE];
    int length;
} SqList;

void init(SqList *L)
{
    L->length = 0;
}
/*
动态分配内存的方式
void init(Sqlist *list)
{
    list->data = (int *)malloc(sizeof(int) * MAXSIZE);
    list->length = 0;
}
对应的销毁函数
void destroy(Sqlist *list)
{
    free(list->data);
    list->length = 0;
}
在程序结束前应调用销毁函数，释放内存
*/


bool insert(SqList *list, int index, int value)
{
    if (index < 0 || index > list->length || list->length == MAXSIZE)
    {
        return false;
    }
    for (int i = list->length - 1; i >= index; i--)
    {
        list->data[i + 1] = list->data[i];
    }
    list->data[index] = value;
    list->length++;
    return true;
}

bool delete(SqList *list, int index)
{
    if (index < 0 || index >= list->length)
    {
        return false;
    }
    for (int i = index; i < list->length - 1; i++)
    {
        list->data[i] = list->data[i + 1];
    }
    list->length--;
    return true;
}

int search(SqList *list, int value)
{
    for (int i = 0; i < list->length; i++)
    {
        if (list->data[i] == value)
        {
            return i;
        }
    }
    return -1;
}

void CreateList(SqList *L, int n)
{
    int i;
    srand(time(0));
    for (i = 0; i < n; i++)
    {
        L->data[i] = rand() % 100 + 1;
        L->length++;
    }
}

void print(SqList L)
{
    int i;
    for (i = 0; i < L.length; i++)
    {
        printf("%d ", L.data[i]);
    }
    printf("\n");
}

//以下为练习

//从顺序表中删除具有最小值的元素（假设唯一），并由函数返回被删除元素的值，空出的位置由最后一个元素填补，
//若顺序表为空，则显示出错信息并退出运行。

int DeleteMin(SqList *L)
{
    int i, min, pos;
    if (L->length == 0)
    {
        printf("顺序表为空，删除失败！\n");
        return 0;
    }
    min = L->data[0];
    pos = 0;
    for (i = 1; i < L->length; i++)
    {
        if (L->data[i] < min)
        {
            min = L->data[i];
            pos = i;
        }
    }
    L->data[pos] = L->data[L->length - 1];
    L->length--;
    return min;
}

//设计一个高效算法，将顺序表的所有元素逆置，要求算法的空间复杂度为O(1)。

void Reverse(SqList *L)
{
    int i, temp;
    for (i = 0; i < L->length / 2; i++)
    {
        temp = L->data[i];
        L->data[i] = L->data[L->length - 1 - i];
        L->data[L->length - 1 - i] = temp;
    }
}

//编写一个时间复杂度为O(n)，空间复杂度为O(1)的算法，该算法删除一个顺序表中所有值为x的元素。

void DeleteX(SqList *L, int x)
{
    int i, k = 0;
    for (i = 0; i < L->length; i++)
    {
        if (L->data[i] != x)
        {
            L->data[k] = L->data[i];
            k++;
        }
    }
    L->length = k;
}

//从有序顺序表中删除其值在给定值s与t之间（要求s<t）的所有元素，如果s或t不合理或顺序表为空，则显示出错信息并退出运行。

void DeleteST(SqList *L, int s, int t)
{
    int i, j;
    if (s >= t || L->length == 0)
    {
        printf("参数错误或顺序表为空，删除失败！\n");
        return;
    }
    for (i = 0; i < L->length && L->data[i] < s; i++)
        ;
    if (i >= L->length)
    {
        printf("参数错误，删除失败！\n");
        return;
    }
    for (j = i; j < L->length && L->data[j] <= t; j++)
        ;
    for (; j < L->length; i++, j++)
    {
        L->data[i] = L->data[j];
    }
    L->length = i;
}

//从顺序表中删除其值在给定值s与t之间（包含s和t，要求s<t）的所有元素，如果s或t不合理或顺序表为空，则显示出错信息并退出运行。

void DeleteST2(SqList *L, int s, int t)
{
    int i, j;
    if (s >= t || L->length == 0)
    {
        printf("参数错误或顺序表为空，删除失败！\n");
        return;
    }
    for (i = 0; i < L->length && L->data[i] < s; i++)
        ;
    if (i >= L->length)
    {
        printf("参数错误，删除失败！\n");
        return;
    }
    for (j = i; j < L->length && L->data[j] <= t; j++)
        ;
    for (; j < L->length; i++, j++)
    {
        L->data[i] = L->data[j];
    }
    L->length = i;
}

//从有序顺序表中删除所有其值重复的元素，使表中所有元素的值均不同。

void DeleteSame(SqList *L)
{
    int i, j;
    if (L->length == 0)
    {
        printf("顺序表为空，删除失败！\n");
        return;
    }
    for (i = 0, j = 1; j < L->length; j++)
    {
        if (L->data[i] != L->data[j])
        {
            L->data[++i] = L->data[j];
        }
    }
    L->length = i + 1;
}

//将两个有序顺序表合并为一个新的有序顺序表，并由函数返回结果顺序表。

void Merge(SqList La, SqList Lb, SqList *Lc)
{
    int i = 0, j = 0, k = 0;
    while (i < La.length && j < Lb.length)
    {
        if (La.data[i] < Lb.data[j])
        {
            Lc->data[k] = La.data[i];
            i++;
            k++;
        }
        else
        {
            Lc->data[k] = Lb.data[j];
            j++;
            k++;
        }
    }
    while (i < La.length)
    {
        Lc->data[k] = La.data[i];
        i++;
        k++;
    }
    while (j < Lb.length)
    {
        Lc->data[k] = Lb.data[j];
        j++;
        k++;
    }
    Lc->length = k;
}

//已知在一维数组A[m+n]中依次存放两个线性表(a1,a2,...,am)和(b1,b2,...,bn)。
//试编写一个函数，将数组中两个顺序表的位置互换，即将(b1,b2,...,bn)放在(a1,a2,...,am)的前面。

void ReverseList(int A[], int left, int right)
{
    int i, temp;
    for (i = 0; i < (right - left + 1) / 2; i++)
    {
        temp = A[left + i];
        A[left + i] = A[right - i];
        A[right - i] = temp;
    }
}

void Exchange(int A[], int m, int n)
{
    ReverseList(A, 0, m + n - 1);
    ReverseList(A, 0, n - 1);
    ReverseList(A, n, m + n - 1);
}

//线性表(a1,a2,...,an)中的元素递增有序且按顺序存储于计算机内。要求设计一算法，完成用最少时间在表中查找数值为x的元素，
//若找到则将其与后继元素位置相交换，若找不到则将其插入表中并使表中元素仍递增有序。

int SearchExchangeInsert(int A[], int n, int x)
{
    int low = 0, high = n - 1, mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (A[mid] == x)
        {
            if (mid != n - 1)
            {
                int temp = A[mid];
                A[mid] = A[mid + 1];
                A[mid + 1] = temp;
                return mid + 1;
            }
            else
            {
                return -1;
            }
        }
        else if (A[mid] > x)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    for (int i = n - 1; i >= high + 1; i--)
    {
        A[i + 1] = A[i];
    }
    A[high + 1] = x;
    return high + 1;
}

//设将n(n>1)个整数存放到一维数组R中。设计一个在时间和空间两方面都尽可能高效的算法。将R中保存的序列循环左移p(0<p<n)个位置，

void Reverse1(int A[], int left, int right)
{
    int i, temp;
    for (i = 0; i < (right - left + 1) / 2; i++)
    {
        temp = A[left + i];
        A[left + i] = A[right - i];
        A[right - i] = temp;
    }
}

void Converse(int A[], int n, int p)
{
    Reverse1(A, 0, p - 1);
    Reverse1(A, p, n - 1);
    Reverse1(A, 0, n - 1);
}

//一个长度为L(L>=1)的升序序列S，处在第[L/2]个位置的数称为S的中位数。例如，若序列S1=(11,13,15,17,19)，则S1的中位数是15，
//两个序列的中位数是含它们所有元素的升序序列的中位数。例如，若S2=(2,4,6,8,20)，则S1和S2的中位数是11。
//现在有两个等长升序序列A和B，试设计一个在时间和空间两方面都尽可能高效的算法，找出两个序列A和B的中位数。
//要求：算法的时间复杂度为O(logn)，空间复杂度为O(1)。

int M_Search(int A[], int B[], int n)
{
    int s1 = 0, d1 = n - 1, m1, s2 = 0, d2 = n - 1, m2;
    while (s1 != d1 || s2 != d2)
    {
        m1 = (s1 + d1) / 2;
        m2 = (s2 + d2) / 2;
        if (A[m1] == B[m2])
        {
            return A[m1];
        }
        if (A[m1] < B[m2])
        {
            if ((s1 + d1) % 2 == 0)
            {
                s1 = m1;
                d2 = m2;
            }
            else
            {
                s1 = m1 + 1;
                d2 = m2;
            }
        }
        else
        {
            if ((s2 + d2) % 2 == 0)
            {
                d1 = m1;
                s2 = m2;
            }
            else
            {
                d1 = m1;
                s2 = m2 + 1;
            }
        }
    }
    return A[s1] < B[s2] ? A[s1] : B[s2];
}

//已知一个整数序列A=(a0,a1,...,an-1),其中0<=ai<n(0<=i<n)。若存在ap1=ap2=...=apm=x且m>n/2(0<=pk<n,1<=k<=m)，
//则称x为A的主元素。例如A=(0,5,5,3,5,7,5,5)，则5为主元素；又如A=(0,5,5,3,5,1,5,7)，则A中没有主元素。
//假设A中的n个元素保存在一个一维数组中，请设计一个尽可能高效的算法，找出A的主元素。若存在主元素，则输出该元素；否则输出-1。

int Majority(int A[], int n)
{
    int i, c, count = 1;
    c = A[0];
    for (i = 1; i < n; i++)
    {
        if (A[i] == c)
        {
            count++;
        }
        else
        {
            if (count > 0)
            {
                count--;
            }
            else
            {
                c = A[i];
                count = 1;
            }
        }
    }
    if (count > 0)
    {
        for (i = count = 0; i < n; i++)
        {
            if (A[i] == c)
            {
                count++;
            }
        }
    }
    if (count > n / 2)
    {
        return c;
    }
    else
    {
        return -1;
    }
}

//给定一个含n(n>1)个整数的数组，请设计一个在时间上尽可能高效的算法，找出数组中未出现的最小正整数。
//例如，数组{-5,3,2,3}中未出现的最小正整数是1；数组{1,2,3}中未出现的最小正整数是4。

int FindMissMin(int A[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        while (A[i] != i + 1)
        {
            if (A[i] <= 0 || A[i] > n || A[i] == A[A[i] - 1])
            {
                break;
            }
            int temp = A[i];
            A[i] = A[temp - 1];
            A[temp - 1] = temp;
        }
    }
    for (i = 0; i < n; i++)
    {
        if (A[i] != i + 1)
        {
            return i + 1;
        }
    }
    return n + 1;
}

//定义三元组(a,b,c)的距离D=|a-b|+|a-c|+|b-c|。给定3个非空整数集合S1、S2和S3，按升序分别存储在3个数组中。
//请设计一个尽可能高效的算法，计算并输出所有可能的三元组(a,b,c)（a来自S1，b来自S2，c来自S3）的距离D的最小值。

int MinDistance(int A[], int B[], int C[], int n)
{
    int i = 0, j = 0, k = 0, min, max, mid, distance, minDistance;
    min = A[0] < B[0] ? A[0] : B[0];
    min = min < C[0] ? min : C[0];
    max = A[n - 1] > B[n - 1] ? A[n - 1] : B[n - 1];
    max = max > C[n - 1] ? max : C[n - 1];
    while (min < max)
    {
        mid = (min + max) / 2;
        i = 0;
        while (A[i] <= mid)
        {
            i++;
        }
        j = 0;
        while (B[j] <= mid)
        {
            j++;
        }
        k = 0;
        while (C[k] <= mid)
        {
            k++;
        }
        distance = abs(A[i - 1] - B[j - 1]) + abs(A[i - 1] - C[k - 1]) + abs(B[j - 1] - C[k - 1]);
        minDistance = minDistance < distance ? minDistance : distance;
        distance = abs(A[i] - B[j - 1]) + abs(A[i] - C[k - 1]) + abs(B[j - 1] - C[k - 1]);
        minDistance = minDistance < distance ? minDistance : distance;
        distance = abs(A[i - 1] - B[j]) + abs(A[i - 1] - C[k - 1]) + abs(B[j] - C[k - 1]);
        minDistance = minDistance < distance ? minDistance : distance;
        distance = abs(A[i - 1] - B[j - 1]) + abs(A[i - 1] - C[k]) + abs(B[j - 1] - C[k]);
        minDistance = minDistance < distance ? minDistance : distance;
        distance = abs(A[i] - B[j]) + abs(A[i] - C[k - 1]) + abs(B[j] - C[k - 1]);
        minDistance = minDistance < distance ? minDistance : distance;
        distance = abs(A[i] - B[j - 1]) + abs(A[i] - C[k]) + abs(B[j - 1] - C[k]);
        minDistance = minDistance < distance ? minDistance : distance;
        distance = abs(A[i - 1] - B[j]) + abs(A[i - 1] - C[k]) + abs(B[j] - C[k]);
        minDistance = minDistance < distance ? minDistance : distance;
        distance = abs(A[i] - B[j]) + abs(A[i] - C[k]) + abs(B[j] - C[k]);
        minDistance = minDistance < distance ? minDistance : distance;
        if (i == 0)
        {
            min = B[j - 1] < C[k - 1] ? B[j - 1] : C[k - 1];
        }
        else if (j == 0)
        {
            min = A[i - 1] < C[k - 1] ? A[i - 1] : C[k - 1];
        }
        else if (k == 0)
        {
            min = A[i - 1] < B[j - 1] ? A[i - 1] : B[j - 1];
        }
        else
        {
            min = A[i - 1] < B[j - 1] ? A[i - 1] : B[j - 1];
            min = min < C[k - 1] ? min : C[k - 1];
        }
        if (i == n)
        {
            max = B[j] > C[k] ? B[j] : C[k];
        }
        else if (j == n)
        {
            max = A[i] > C[k] ? A[i] : C[k];
        }
        else if (k == n)
        {
            max = A[i] > B[j] ? A[i] : B[j];
        }
        else
        {
            max = A[i] > B[j] ? A[i] : B[j];
            max = max > C[k] ? max : C[k];
        }
    }
    return minDistance;
}


