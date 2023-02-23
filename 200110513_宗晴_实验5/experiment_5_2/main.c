/**--------------------------------------
文件名: experiment_5_2
创建人: 宗晴
学号：200110513
日 期: 2021.5.21.
描述：排序、查找及其应用
主要功能：查找数组中最大的k个元素
----------------------------------------*/

#include<stdio.h>
#include<stdlib.h>

#define MAX 1000

int *solve2(int *arr, int n, int k);
void HeapSort(int *arr, int n, int k);
void HeapAdjust(int *arr, int s, int m);
void test2();


//Todo
//需要返回一个数组，数组元素是原始数组里最大的k个数
//注意按照从小到大的顺序排序
//可以自行添加其他辅助函数,可以根据实际需要修改函数参数

/**
 * 查找数组中最大的k个元素
 * @param arr 待查找数组
 * @param n 数组中元素个数
 * @param k 查找最大的k个元素的k值
 * @return 返回按从小到大的顺序存储的k个最大元素的数组
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
 * 对数组进行堆排序（大根堆）
 * @param arr 待排序数组
 * @param n 数组中的元素个数
 */
void HeapSort(int *arr, int n, int k){
    int i, temp;
    for(i = n / 2; i > 0; i--) HeapAdjust(arr, i, n);//建堆
    for(i = n; i > n - k; i--){
        temp = arr[i];
        arr[i] = arr[1];
        arr[1] = temp;//将堆顶元素与最后一个元素交换
        HeapAdjust(arr, 1, i - 1);
    }
}


/**
 * 调整某个结点的位置
 * @param arr 待排序数组,从位置s到m只有s需要调整（s为此子大根堆的堆顶元素）
 * @param s 待调整的大根堆的根结点位置
 * @param m 待调整的大根堆的终止位置
 */
void HeapAdjust(int *arr, int s, int m){
    int i;
    int rc = arr[s];//存储待调整的数据
    for(i = 2 * s; i <= m; i *= 2){//沿较大的孩子结点向下筛选
        if(i < m && arr[i] < arr[i + 1]) i++;//找到较大的孩子结点
        if(rc >= arr[i]) break;//已找到待插入的位置
        arr[s] = arr[i];
        s = i;
    }
    arr[s] = rc;//将堆顶元素插入合适的位置
}

void test2(){
	int caseNum; //表示测试轮数
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
