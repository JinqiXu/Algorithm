#include "Algorithm.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void initRandomArray(int *array, int m)
{
    srand((unsigned)time(0));
    int temp = 0;

    for (int i = 0; i < m; i++)
    {
        array[i] = rand() % 180 + 20;
    }
}

void Print(int array_Track[], int m)
{
    for (int i = 0; i < m; i++)
        printf("%d ", array_Track[i]);
    printf("\n");
}
void FCFS(int array_Track[], int m)
{
    Print(array_Track, m);
    float sum = 0, avg;
    int cur;
    printf("输入当前磁道号：\n");
    scanf("%d", &cur);
    sum = abs(cur - array_Track[0]);
    printf("寻道序列：\n%d ", array_Track[0]);

    for (int i = 0, j = 1; j < m; i++, j++)
    {
        sum += abs(array_Track[j] - array_Track[i]);
        printf("%d ", array_Track[j]);
    }
    avg = sum / m;
    printf("\n平均寻道长度：%.3f\n\n", avg);
}

void SSTF(int array_Track[], int m)
{
    Print(array_Track, m);

    int i, j;
    float sum = 0, avg = 0;
    int cur, minj, min, Dcount = 0;
    int Disk[MaxTrack], Track[MaxTrack];
    memset(Disk, 0, MaxTrack);
    memset(Track, 0, MaxTrack);
    printf("请输入当前磁道号：\n");
    scanf("%d", &cur);
    for (j = 0; j < m; j++)
    {
        for (i = 0; i < m; i++)
        {
            if (Track[i] == -1)
            {
                continue;
            }
            else
            {
                Track[i] = abs(array_Track[i] - cur);
            }
        }
        min = 200;
        minj = 0;
        for (i = 0; i < m; i++)
        {
            if (Track[i] == -1)
                continue;
            else
            {
                if (Track[i] < min)
                {
                    min = Track[i];
                    minj = i;
                }
            }
        }
        cur = array_Track[minj];
        Disk[Dcount++] = cur;
        sum += Track[minj];
        Track[minj] = -1;
    }
    avg = sum / m;
    printf("寻道序列：\n");
    for (i = 0; i < m; i++)
        printf("%d ", Disk[i]);
    printf("\n平均寻道长度：%.2f\n\n", avg);
}

void SCAN(int array_Track[], int m)
{
    Print(array_Track, m);

    int i, j, k = 0, r = 0, l = 0, cur, count;
    int temp[MaxTrack];
    float sum = 0, avg = 0;
    printf("请输入当前磁道号：\n");
    scanf("%d", &cur);
    for (i = 0; i < m; i++)
    {
        temp[i] = array_Track[i];
    }
    sort(temp, m);
    while (temp[k] < cur)
    {
        k++;
    }
    l = k - 1;
    r = k;
    printf("请输入移动臂移动方向：\n1：磁道号增加方向\n2：磁道号减小方向\n");
    scanf("%d", &count);
    if (count == 2)
    {
        printf("磁道访问序列：\n");
        for (j = l; j >= 0; j--)
        {
            printf("%d ", temp[j]);
        }
        for (int j = r; j < m; j++)
        {
            printf("%d ", temp[j]);
        }
        sum = abs(cur - 2 * temp[0] + temp[m - 1]);
    }
    else
    {
        printf("磁道访问序列：\n");
        for (int j = r; j < m; j++)
        {
            printf("%d ", temp[j]);
        }
        for (j = l; j >= 0; j--)
        {
            printf("%d ", temp[j]);
        }
        sum = abs(cur - temp[0] + 2 * temp[m - 1]);
    }
    avg = sum / m;
    printf("\n平均寻道长度：%.3f\n\n", avg);
}

void CSCAN(int array_Track[], int m)
{
    Print(array_Track, m);

    int i, j, k = 0, r = 0, l = 0, cur;
    float sum = 0, avg = 0;
    int temp[MaxTrack];
    for (i = 0; i < m; i++)
    {
        temp[i] = array_Track[i];
    }
    sort(temp, m);
    printf("请输入当前磁道号：\n");
    scanf("%d", &cur);
    printf("磁道访问序列：\n");
    while (temp[k] < cur)
    {
        k++;
    }
    l = k - 1;
    r = k;
    for (j = r; j < m; j++)
    {
        printf("%d ", temp[j]);
    }
    for (j = 0; j < r; j++)
    {
        printf("%d ", temp[j]);
    }

    sum = abs(2 * temp[m - 1] + temp[l] - cur - 2 * temp[0]);
    avg = sum / m;
    printf("\n平均寻道长度：%.3f\n\n", avg);
}
void FSCAN(int array_Track[], int m)
{
    Print(array_Track, m);

    int i, j, k, cur;
    float sum = 0, avg = 0;
    int temp1[MaxTrack], temp2[MaxTrack];
    for (i = 0; i < m / 2; i++)
        temp1[i] = array_Track[i];
    for (i = m / 2; i < m; i++)
        temp2[i - (m / 2)] = array_Track[i];
    sort(temp1, m / 2);
    printf("请输入第一段磁道初始地址：\n");
    scanf("%d", &cur);
    k = 0;
    while (temp1[k] < cur)
    {
        k++;
    }
    sum += abs(temp1[k] - cur);
    printf("磁道访问序列：\n");
    printf("%d ", temp1[k]);
    for (j = k; j < (m / 2) - 1; j++)
    {
        sum += abs(temp1[j + 1] - temp1[j]);
        printf("%d ", temp1[j + 1]);
    }
    printf("%d ", temp1[0]);
    for (j = 0; j < k - 1; j++)
    {
        sum += abs(temp1[j + 1] - temp1[j]);
        printf("%d ", temp1[j + 1]);
    }
    printf("\n");
    sort(temp2, m / 2);
    printf("请输入第二段磁道初始地址：\n");
    scanf("%d", &cur);
    k = 0;
    while (temp2[k] < cur)
    {
        k++;
    }
    sum += abs(temp2[k] - cur);
    printf("磁道访问序列：\n%d ", temp2[k]);
    for (j = k; j < m / 2 - 1; j++)
    {
        sum += abs(temp2[j + 1] - temp2[j]);
        printf("%d ", temp2[j + 1]);
    }
    for (j = 0; j < k; j++)
    {
        sum += abs(temp2[j + 1] - temp2[j]);
        printf("%d ", temp2[j]);
    }
    avg = sum / m;
    printf("\n平均寻道长度：%.3f\n\n", avg);
}

void sort(int aray[], int m)
{
    int temp, flag = 1;
    while ((m > 1) && flag)
    {
        flag = 0;
        for (int i = 0; i < m - 1; i++)
        {
            if (aray[i] > aray[i + 1])
            {
                temp = aray[i];
                aray[i] = aray[i + 1];
                aray[i + 1] = temp;
                flag = 1;
            }
        }
        m--;
    }
}