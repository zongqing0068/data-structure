/**--------------------------------------
�ļ���: experiment_5_3
������: ����
ѧ�ţ�200110513
�� ��: 2021.5.21.
���������򡢲��Ҽ���Ӧ��
��Ҫ���ܣ����ҿ�����������ʱ���
----------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

void sort(int *start, int *end, int M);
void MergeSort(int *a, int n);
void Mpass(int *a, int *b, int n, int len);
void Merge(int *a, int *b, int min, int m, int max);
void findPeriod(int *start, int *end, int M);

/**
 * ����ʼʱ������ֹʱ�������������
 * @param start ��ʼʱ������
 * @param end ��ֹʱ������
 * @param M ѧ������
 */
void sort(int *start, int *end, int M){
    MergeSort(start, M);
    MergeSort(end, M);
}


/**
 * �鲢����
 * @param a ����������
 * @param n ����Ԫ�ظ���
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
 * ���������һ�˹鲢����
 * @param a ����������
 * @param b �������飬�洢����������
 * @param len ÿ�δ��鲢�εĳ���
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
 * �������������й鲢
 * @param a ���鲢����
 * @param b �������飬�洢�鲢�������
 * @param min ��һ�����е���ʼλ��
 * @param m ��һ�����е���ֹλ��
 * @param max �ڶ������е���ֹλ��
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


//�����������������ʼʱ�����ֹʱ�䣬������������д
/**
 * ���ҿ�����������ʱ��ε���ʼʱ�����ֹʱ��
 * @param start ��ʼʱ������
 * @param end ��ֹʱ������
 * @param M ѧ������
 */
void findPeriod(int *start, int *end, int M){
    int i, j, last_s, last_e, maxnum, people_num, time_num;//maxnumΪ�����������ֵ��people_numΪÿ��ʱ���������time_numΪ������������ʱ�����
    i = j = maxnum = 0;
    last_e = time_num = -1;
    int *maxtime_s = (int *)malloc(M * sizeof(int));//�洢��������������ʼʱ��
    int *maxtime_e = (int *)malloc(M * sizeof(int));//�洢��������������ֹʱ��

    while(i < M && j < M){//������������ʱ��ε�ʼĩλ��ֻ��������start��end�����г��ֵ�ʱ���
        while(j < M && end[j] == end[last_e]) j++;//jָ����һ������ʱ��
        if(j == M) break;
        while(i < M && start[i] <= end[j]){//��ÿһ����ֹʱ�䣬��ʼʱ��ָ�벻�û��ݣ���Ϊ��ʼʱ��ָ��Խ��������Խ��
            last_s = i;
            while(start[i] <= end[j] && i < M - 1 && start[i + 1] == start[last_s]) i++;
            people_num = i + 1 - j;//����ÿ��ʱ��ε���������ʼʱ�䣨��ͬ��ȡ���һ�������±������ʱ�䣨��ͬ��ȡ��һ�������±�֮���ټ�һ
            if(people_num == maxnum){//��ʱ��������͵�ǰ���������ȣ���������һ������ʼ����ֹʱ�������������һ��λ��
                time_num++;
                maxtime_s[time_num] = start[i];
                maxtime_e[time_num] = end[j];
            }
            else if(people_num > maxnum){//��ʱ����������󣬽������������Ϊ����������������Ϊ��ʼֵ��������ʼ����ֹʱ����������ĵ�һ��λ��
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
    printf("\n");//���������������ʱ���

    free(maxtime_s);
    free(maxtime_e);
    return;
}

int main()
{
   int N, M; //�ֱ�洢ʱ��Ķ�����ѧ���ĸ���
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

   /* �ն�����
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

