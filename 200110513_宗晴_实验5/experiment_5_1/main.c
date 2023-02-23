/**--------------------------------------
�ļ���: experiment_5_1
������: ����
ѧ�ţ�200110513
�� ��: 2021.5.21.
���������򡢲��Ҽ���Ӧ��
��Ҫ���ܣ����ҡ���λ����ĸţ�Ĳ�����
----------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#define N 10000

int a[N]; // ���ڴ洢��ţ������

int solve1(int *a, int n);
void my_QSort(int *a, int low, int high);
int Partition(int *a, int low, int high);
void test1();

//Todo
//��Ҫ������λ����ţ��������
//�����������������������,�����޸Ĵ��ε�����

/**
 * ���ҡ���λ����ĸţ�Ĳ�����
 * @param a �洢��ĸţ������������
 * @param n ��ţ����
 * @return ���ء���λ����ĸţ�Ĳ�����
 */
int solve1(int *a, int n){
    my_QSort(a, 0, n - 1);//��������п���
    return a[n / 2];
}


/**
 * ��������п�������
 * @param a ����������
 * @param low �������������ʼλ��
 * @param high �������������ֹλ��
 */
void my_QSort(int *a, int low, int high){
    int p;//����
    if(low < high){//���ȴ���1
        p = Partition(a, low, high);//����һ�λ���
        if(p == N / 2) return;/**�����˶�����λ�õ��жϣ������������*/
        else{
            my_QSort(a, low, p - 1);
            my_QSort(a, p + 1, high);//������������������ν��еݹ����
        }
    }
}


/**
 * �Դ������������һ�λ���
 * @param a ����������
 * @param low �������������ʼλ��
 * @param high �������������ֹλ��
 * @return ��������λ��
 */
int Partition(int *a, int low, int high){
    int key = a[low];//�洢����Ĺؼ���
    int temp;
    while(low < high){
        while((low < high) && a[high] >= key) high--;
        temp = a[high];
        a[high] = a[low];
        a[low] = temp;//��֤�Ҳ������������󣬷�������������н���
        while((low < high) && a[low] <= key) low++;
        temp = a[high];
        a[high] = a[low];
        a[low] = temp;//��֤��������������С���������Ҳ������н���
    }
    return low;//low��high����ʾ����λ��
}


void test1(){
    int caseNum; //��ʾ��������
    int n;
    int ans[N];
    if (freopen("5_1_input_5.in", "r", stdin) == NULL) {
		printf("There is an error in reading file 5_1_input_5.in");
    }
    scanf("%d", &caseNum);
    for (int case1 = 0; case1 < caseNum; case1++) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++){
            scanf("%d", &a[i]);
        }

        if(!(n % 2) || n < 1 || n >= 10000){/**�����˶���ţ����ż���Լ���Χ���жϣ���ǿ��׳��*/
            printf("error!\n");
            continue;
        }

        ans[case1] = solve1(a, n);
        printf("%d\n", ans[case1]);
    }
    fclose(stdin);
}

int main() {
    test1();
    return 0;
}
