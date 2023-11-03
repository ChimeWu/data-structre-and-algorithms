//为顺序表实现以下排序函数：直接插入排序、折半插入排序、希尔排序、冒泡排序、快速排序、简单选择排序、堆排序、二路归并排序、基数排序、外部排序等。

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int *data;
    int length;
} List;

void init(List *list, int length)
{
    list->data = (int *)malloc(sizeof(int) * length);
    list->length = length;
}

void print(List *list)
{
    for (int i = 0; i < list->length; i++)
    {
        printf("%d ", list->data[i]);
    }
    printf("\n");
}

void swap(List *list, int i, int j)
{
    int temp = list->data[i];
    list->data[i] = list->data[j];
    list->data[j] = temp;
}

void insertSort(List *list)
{
    for (int i = 1; i < list->length; i++)
    {
        int temp = list->data[i];
        int j = i - 1;
        while (j >= 0 && list->data[j] > temp)
        {
            list->data[j + 1] = list->data[j];
            j--;
        }
        list->data[j + 1] = temp;
    }
}

void binaryInsertSort(List *list)
{
    for (int i = 1; i < list->length; i++)
    {
        int temp = list->data[i];
        int low = 0;
        int high = i - 1;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (list->data[mid] > temp)
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        for (int j = i - 1; j >= low; j--)
        {
            list->data[j + 1] = list->data[j];
        }
        list->data[low] = temp;
    }
}

void shellSort(List *list)
{
    int gap = list->length / 2;
    while (gap > 0)
    {
        for (int i = gap; i < list->length; i++)
        {
            int temp = list->data[i];
            int j = i - gap;
            while (j >= 0 && list->data[j] > temp)
            {
                list->data[j + gap] = list->data[j];
                j -= gap;
            }
            list->data[j + gap] = temp;
        }
        gap /= 2;
    }
}

void bubbleSort(List *list)
{
    for (int i = 0; i < list->length - 1; i++)
    {
        bool flag = false;
        for (int j = 0; j < list->length - 1 - i; j++)
        {
            if (list->data[j] > list->data[j + 1])
            {
                swap(list, j, j + 1);
                flag = true;
            }
        }
        if (!flag)
        {
            break;
        }
    }
}

void quickSort(List *list, int low, int high)
{
    if (low >= high)
    {
        return;
    }
    int i = low;
    int j = high;
    int temp = list->data[i];
    while (i < j)
    {
        while (i < j && list->data[j] >= temp)
        {
            j--;
        }
        if (i < j)
        {
            list->data[i] = list->data[j];
            i++;
        }
        while (i < j && list->data[i] < temp)
        {
            i++;
        }
        if (i < j)
        {
            list->data[j] = list->data[i];
            j--;
        }
    }
    list->data[i] = temp;
    quickSort(list, low, i - 1);
    quickSort(list, i + 1, high);
}

void selectSort(List *list)
{
    for (int i = 0; i < list->length - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < list->length; j++)
        {
            if (list->data[j] < list->data[min])
            {
                min = j;
            }
        }
        if (min != i)
        {
            swap(list, i, min);
        }
    }
}

void heapAdjust(List *list, int i, int length)
{
    int temp = list->data[i];
    for (int k = 2 * i + 1; k < length; k = 2 * k + 1)
    {
        if (k + 1 < length && list->data[k] < list->data[k + 1])
        {
            k++;
        }
        if (list->data[k] > temp)
        {
            list->data[i] = list->data[k];
            i = k;
        }
        else
        {
            break;
        }
    }
    list->data[i] = temp;
}

void heapSort(List *list)
{
    for (int i = list->length / 2 - 1; i >= 0; i--)
    {
        heapAdjust(list, i, list->length);
    }
    for (int i = list->length - 1; i > 0; i--)
    {
        swap(list, 0, i);
        heapAdjust(list, 0, i);
    }
}

void merge(List *list, int low, int mid, int high)
{
    int i = low;
    int j = mid + 1;
    int k = 0;
    int *temp = (int *)malloc(sizeof(int) * (high - low + 1));
    while (i <= mid && j <= high)
    {
        if (list->data[i] < list->data[j])
        {
            temp[k++] = list->data[i++];
        }
        else
        {
            temp[k++] = list->data[j++];
        }
    }
    while (i <= mid)
    {
        temp[k++] = list->data[i++];
    }
    while (j <= high)
    {
        temp[k++] = list->data[j++];
    }
    for (int i = 0; i < k; i++)
    {
        list->data[low + i] = temp[i];
    }
    free(temp);
}

void mergeSort(List *list, int low, int high)
{
    if (low >= high)
    {
        return;
    }
    int mid = (low + high) / 2;
    mergeSort(list, low, mid);
    mergeSort(list, mid + 1, high);
    merge(list, low, mid, high);
}

void radixSort(List *list)
{
    int max = list->data[0];
    for (int i = 1; i < list->length; i++)
    {
        if (list->data[i] > max)
        {
            max = list->data[i];
        }
    }
    int count = 0;
    while (max > 0)
    {
        max /= 10;
        count++;
    }
    int *temp = (int *)malloc(sizeof(int) * list->length);
    int *order = (int *)malloc(sizeof(int) * 10);
    int radix = 1;
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            order[j] = 0;
        }
        for (int j = 0; j < list->length; j++)
        {
            int lsd = (list->data[j] / radix) % 10;
            order[lsd]++;
        }
        for (int j = 1; j < 10; j++)
        {
            order[j] += order[j - 1];
        }
        for (int j = list->length - 1; j >= 0; j--)
        {
            int lsd = (list->data[j] / radix) % 10;
            temp[order[lsd] - 1] = list->
            data[j];
            order[lsd]--;
        }
        for (int j = 0; j < list->length; j++)
        {
            list->data[j] = temp[j];
        }
        radix *= 10;
    }
    free(temp);
    free(order);
}

