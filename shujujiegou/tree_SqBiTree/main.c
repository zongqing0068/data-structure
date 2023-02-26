#include <stdio.h>
#include <stdlib.h>
#define MAX_TREE_SIZE 100

typedef int SqBiTree[MAX_TREE_SIZE];//��0����սڵ�

int find_Comm_Anc(SqBiTree T, int i, int j, int *e, int *anc);

int main()
{
    SqBiTree A;
    int i, j, k, p;
    int anc;
    for(k=1;k<=15;k++){
        scanf("%d", &A[k]);
    }
    scanf("%d %d", &i, &j);
    if (find_Comm_Anc(A, i, j, &p, &anc))
    printf("%d %d", p, anc);
    return 0;
}

/*TΪ˳��洢�Ķ������ĸ���ַ��i��j��ʾ�����ҵ������ڵ���±�
�������ܣ��ҵ�������������Ĺ������Ƚ���λ�ú�ֵ���ֱ���e��anc���أ��ɹ�����1�����򷵻�0*/
int find_Comm_Anc(SqBiTree T, int i, int j, int *e, int *anc){
    if(i == 1 || j == 1){//�����ж������ڵ��Ƿ������Ƚڵ�
        printf("�ڵ���������һ���Ǹ��ڵ㣬�޹�ͬ�����Ƚڵ�");
        return 0;
    }
    if(T[i] != 0 && T[j] != 0){
        int p, q;
        p = i;
        q = j;
        while (p != q){
            if(p > q) p /= 2;//�ҵ��ڵ�i��˫�׽ڵ�
            else q /= 2;//�ҵ��ڵ�j��˫�׽ڵ�
        }
        if(p == i || q == j){//���ڽڵ����������Լ������Ƚڵ㣬��������нڵ��±�δ������ͼ��������ǵ�˫�׽ڵ�
            p /= 2;
        }
        *e = p;
        *anc = T[p];
        return 1;
    }
    printf("�ڵ�Ϊ��");
    return 0;
}
