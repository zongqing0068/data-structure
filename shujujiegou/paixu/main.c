#include <stdio.h>
#include <stdlib.h>

/**
 * 将所有负值的关键字放在所有非负值的关键字之前
 * @param a 存储数据的一维数组
 * @param n 数据的数量
 */
void my_Sort(int *a, int n){
    int i, j, temp;//i和j为两个指针，temp用来交换数据
    i = 0;
    j = n - 1;
    while(i < j){//i和j分别从两段移向中间，两指针相遇时，循环停止
        while(i < j && a[i] < 0) i++;
        while(i < j && a[j] >= 0) j--;//找到左侧非负值的关键字和右侧负值的关键字
        if(i < j){
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }//将两者交换
    }
}

int main()
{
    int i, a[5];
    for(i = 0; i < 5; i++){
        scanf("%d", &a[i]);
    }
    my_Sort(a, 5);
    for(i = 0; i < 5; i++){
        printf("%d ", a[i]);
    }

    return 0;
}
