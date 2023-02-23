/**--------------------------------------
�ļ���: experiment_5_2
������: ����
ѧ�ţ�200110513
�� ��: 2021.5.21.
���������򡢲��Ҽ���Ӧ��
��Ҫ���ܣ���������������k��Ԫ��
----------------------------------------*/

#include<stdio.h>
#include<stdlib.h>

#define MAX 1000

int *solve2(int *arr, int n, int k);
void HeapSort(int *arr, int n, int k);
void HeapAdjust(int *arr, int s, int m);
void test2();


//Todo
//��Ҫ����һ�����飬����Ԫ����ԭʼ����������k����
//ע�ⰴ�մ�С�����˳������
//�����������������������,���Ը���ʵ����Ҫ�޸ĺ�������

/**
 * ��������������k��Ԫ��
 * @param arr ����������
 * @param n ������Ԫ�ظ���
 * @param k ��������k��Ԫ�ص�kֵ
 * @return ���ذ���С�����˳��洢��k�����Ԫ�ص�����
 */
int *solve2(int *arr, int n, int k){
    HeapSort(arr, n, k);
    int *res = (int *)malloc(k * sizeof(int));
    for(int i = 0; i < k; i++){
        res[i] = arr[n - k + i + 1];
    }
    return res;
}

/**
 * ��������ж����򣨴���ѣ�
 * @param arr ����������
 * @param n �����е�Ԫ�ظ���
 */
void HeapSort(int *arr, int n, int k){
    int i, temp;
    for(i = n / 2; i > 0; i--) HeapAdjust(arr, i, n);//����
    for(i = n; i > n - k; i--){
        temp = arr[i];
        arr[i] = arr[1];
        arr[1] = temp;//���Ѷ�Ԫ�������һ��Ԫ�ؽ���
        HeapAdjust(arr, 1, i - 1);
    }
}


/**
 * ����ĳ������λ��
 * @param arr ����������,��λ��s��mֻ��s��Ҫ������sΪ���Ӵ���ѵĶѶ�Ԫ�أ�
 * @param s �������Ĵ���ѵĸ����λ��
 * @param m �������Ĵ���ѵ���ֹλ��
 */
void HeapAdjust(int *arr, int s, int m){
    int i;
    int rc = arr[s];//�洢������������
    for(i = 2 * s; i <= m; i *= 2){//�ؽϴ�ĺ��ӽ������ɸѡ
        if(i < m && arr[i] < arr[i + 1]) i++;//�ҵ��ϴ�ĺ��ӽ��
        if(rc >= arr[i]) break;//���ҵ��������λ��
        arr[s] = arr[i];
        s = i;
    }
    arr[s] = rc;//���Ѷ�Ԫ�ز�����ʵ�λ��
}

void test2(){
	int caseNum; //��ʾ��������
	if (freopen("5_2_input_5.in", "r", stdin) == NULL) {
		printf("There is an error in reading file 5_2_input_5.in");
    }
	scanf("%d", &caseNum);
    int case1 = 0;
    for (; case1 < caseNum; case1++) {
		int k, N;
        scanf("%d%d", &k, &N);
        int arr[MAX + 1];
        int i = 1;
        for (; i <= N; i++) {
            scanf("%d", &arr[i]);
        }
        if(k < 1 || k > N || N > 1000){
            printf("error!\n");
            continue;
        }
        int *res;
		res = solve2(arr, N, k);
        for (i = 0; i < k; i++) {
            printf("%d ",res[i]);
        }
        printf("\n");
    }
	fclose(stdin);
}


int main(void) {
    test2();
    return 0;
}
