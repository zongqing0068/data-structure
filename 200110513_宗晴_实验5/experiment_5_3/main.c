/**--------------------------------------
文件名: experiment_5_3
创建人: 宗晴
学号：200110513
日 期: 2021.5.21.
描述：排序、查找及其应用
主要功能：查找空闲人数最多的时间段
----------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

void sort(int *start, int *end, int M);
void MergeSort(int *a, int n);
void Mpass(int *a, int *b, int n, int len);
void Merge(int *a, int *b, int min, int m, int max);
void findPeriod(int *start, int *end, int M);

/**
 * 对起始时间与终止时间数组进行排序
 * @param start 起始时间数组
 * @param end 终止时间数组
 * @param M 学生人数
 */
void sort(int *start, int *end, int M){
    MergeSort(start, M);
    MergeSort(end, M);
}


/**
 * 归并排序
 * @param a 待排序数组
 * @param n 数组元素个数
 */
void MergeSort(int *a, int n){
    int len = 1;
    int *t = (int *)malloc(n * sizeof(int));
    while(len < n){
        Mpass(a, t, n, len);
        len *= 2;
        Mpass(t, a, n, len);
        len *= 2;
    }
}


/**
 * 对数组进行一趟归并排序
 * @param a 待排序数组
 * @param b 辅助数组，存储排序后的数组
 * @param len 每段待归并段的长度
 */
void Mpass(int *a, int *b, int n, int len){
    int i, j;
    i = 0;
    while(i+2*len <= n){
        Merge(a, b, i, i+len-1, i+2*len-1);
        i += 2 * len;
    }
    if(i+len < n) Merge(a, b, i, i+len-1, n-1);
    else{
        for(j = i; j <= n - 1; j++) b[j] = a[j];
    }
}

/**
 * 将两个有序序列归并
 * @param a 待归并数组
 * @param b 辅助数组，存储归并后的数组
 * @param min 第一段序列的起始位置
 * @param m 第一段序列的终止位置
 * @param max 第二段序列的终止位置
 */
void Merge(int *a, int *b, int min, int m, int max){
        int i, j, k;
        i = min;
        j = m + 1;
        k = min;
        while(i <= m && j <= max){
            if(a[i] <= a[j]){
                b[k++] = a[i++];
            }
            else{
                b[k++] = a[j++];
            }
        }
        while(i <= m) b[k++] = a[i++];
        while(j <= max) b[k++] = a[j++];
}


//计算空闲人数最多的起始时间和终止时间，参数可自行填写
/**
 * 查找空闲人数最多的时间段的起始时间和终止时间
 * @param start 起始时间数组
 * @param end 终止时间数组
 * @param M 学生人数
 */
void findPeriod(int *start, int *end, int M){
    int i, j, last_s, last_e, maxnum, people_num, time_num;//maxnum为空闲人数最大值，people_num为每段时间的人数，time_num为空闲人数最多的时间段数
    i = j = maxnum = 0;
    last_e = time_num = -1;
    int *maxtime_s = (int *)malloc(M * sizeof(int));//存储空闲人数最多的起始时间
    int *maxtime_e = (int *)malloc(M * sizeof(int));//存储空闲人数最多的终止时间

    while(i < M && j < M){//空闲人数最多的时间段的始末位置只可能是在start和end数组中出现的时间点
        while(j < M && end[j] == end[last_e]) j++;//j指向下一个结束时间
        if(j == M) break;
        while(i < M && start[i] <= end[j]){//对每一个终止时间，起始时间指针不用回溯，因为起始时间指针越靠后，人数越多
            last_s = i;
            while(start[i] <= end[j] && i < M - 1 && start[i + 1] == start[last_s]) i++;
            people_num = i + 1 - j;//计算每个时间段的人数：起始时间（相同则取最后一个）的下标与结束时间（相同则取第一个）的下标之差再加一
            if(people_num == maxnum){//该时间段人数和当前最大人数相等，计数器加一，将起始和终止时间点存入数组的下一个位置
                time_num++;
                maxtime_s[time_num] = start[i];
                maxtime_e[time_num] = end[j];
            }
            else if(people_num > maxnum){//该时间段人数更大，将最大人数更新为该人数，计数器置为初始值，并将起始和终止时间点存入数组的第一个位置
                maxnum = people_num;
                time_num = 0;
                maxtime_s[time_num] = start[i];
                maxtime_e[time_num] = end[j];
            }
            i++;
        }
        last_e = j;
    }

    printf("%d %d", maxtime_s[0], maxtime_e[0]);
    for(i = 1; i <= time_num; i++) printf(",%d %d", maxtime_s[i], maxtime_e[i]);
    printf("\n");//输出空闲人数最多的时间段

    free(maxtime_s);
    free(maxtime_e);
    return;
}

int main()
{
   int N, M; //分别存储时间的段数和学生的个数
   int caseNum = 0;
   int start[1002];
   int end[1002];

   if (freopen("5_3_input.in", "r", stdin) == NULL) {
		printf("There is an error in reading file 5_3_input.in");
    }

   while(scanf("%d %d",&N,&M)!=EOF){
       caseNum++;
       printf("==== Case %d ====\n",caseNum);
       for(int i = 0; i < M;i++){
           scanf("%d %d",&start[i],&end[i]);
       }
       sort(start, end, M);
       findPeriod(start, end, M);
   }
   fclose(stdin);

   /* 终端输入
   while(scanf("%d %d",&N,&M)!=EOF){
       caseNum++;
       printf("==== Case %d ====\n",caseNum);
       for(int i = 0; i < M;i++){
           scanf("%d %d",&start[i],&end[i]);
       }
       sort(start, end, M);
       findPeriod(start, end, M, N);
   }
   */
}

