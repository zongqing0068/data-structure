#include <stdio.h>
#include <stdlib.h>

/**
 * �����и�ֵ�Ĺؼ��ַ������зǸ�ֵ�Ĺؼ���֮ǰ
 * @param a �洢���ݵ�һά����
 * @param n ���ݵ�����
 */
void my_Sort(int *a, int n){
    int i, j, temp;//i��jΪ����ָ�룬temp������������
    i = 0;
    j = n - 1;
    while(i < j){//i��j�ֱ�����������м䣬��ָ������ʱ��ѭ��ֹͣ
        while(i < j && a[i] < 0) i++;
        while(i < j && a[j] >= 0) j--;//�ҵ����Ǹ�ֵ�Ĺؼ��ֺ��Ҳฺֵ�Ĺؼ���
        if(i < j){
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }//�����߽���
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
