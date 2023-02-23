/**--------------------------------------
文件名: experiment_5_1
创建人: 宗晴
学号：200110513
日 期: 2021.5.21.
描述：排序、查找及其应用
主要功能：查找“中位数”母牛的产奶量
----------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#define N 10000

int a[N]; // 用于存储奶牛产奶量

int solve1(int *a, int n);
void my_QSort(int *a, int low, int high);
int Partition(int *a, int low, int high);
void test1();

//Todo
//需要返回中位数奶牛产奶量。
//可以自行添加其他辅助函数,可以修改传参的数量

/**
 * 查找“中位数”母牛的产奶量
 * @param a 存储各母牛产奶量的数组
 * @param n 奶牛数量
 * @return 返回“中位数”母牛的产奶量
 */
int solve1(int *a, int n){
    my_QSort(a, 0, n - 1);//将数组进行快排
    return a[n / 2];
}


/**
 * 对数组进行快速排序
 * @param a 待排序数组
 * @param low 待排序数组的起始位置
 * @param high 待排序数组的终止位置
 */
void my_QSort(int *a, int low, int high){
    int p;//枢轴
    if(low < high){//长度大于1
        p = Partition(a, low, high);//进行一次划分
        if(p == N / 2) return;/**增加了对枢轴位置的判断，减少排序次数*/
        else{
            my_QSort(a, low, p - 1);
            my_QSort(a, p + 1, high);//对左右两侧的数据依次进行递归快排
        }
    }
}


/**
 * 对待排序数组进行一次划分
 * @param a 待排序数组
 * @param low 待排序数组的起始位置
 * @param high 待排序数组的终止位置
 * @return 返回枢轴位置
 */
int Partition(int *a, int low, int high){
    int key = a[low];//存储枢轴的关键字
    int temp;
    while(low < high){
        while((low < high) && a[high] >= key) high--;
        temp = a[high];
        a[high] = a[low];
        a[low] = temp;//保证右侧的数均比枢轴大，否则与左侧数进行交换
        while((low < high) && a[low] <= key) low++;
        temp = a[high];
        a[high] = a[low];
        a[low] = temp;//保证左侧的数均比枢轴小，否则与右侧数进行交换
    }
    return low;//low和high均表示枢轴位置
}


void test1(){
    int caseNum; //表示测试轮数
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

        if(!(n % 2) || n < 1 || n >= 10000){/**增加了对奶牛数奇偶性以及范围的判断，增强健壮性*/
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
