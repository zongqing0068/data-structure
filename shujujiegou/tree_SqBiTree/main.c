#include <stdio.h>
#include <stdlib.h>
#define MAX_TREE_SIZE 100

typedef int SqBiTree[MAX_TREE_SIZE];//用0代表空节点

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

/*T为顺序存储的二叉树的根地址，i和j表示待查找的两个节点的下标
函数功能：找到两个结点的最近的公共祖先结点的位置和值，分别用e和anc带回，成功返回1，否则返回0*/
int find_Comm_Anc(SqBiTree T, int i, int j, int *e, int *anc){
    if(i == 1 || j == 1){//首先判断两个节点是否都有祖先节点
        printf("节点中至少有一个是根节点，无共同的祖先节点");
        return 0;
    }
    if(T[i] != 0 && T[j] != 0){
        int p, q;
        p = i;
        q = j;
        while (p != q){
            if(p > q) p /= 2;//找到节点i的双亲节点
            else q /= 2;//找到节点j的双亲节点
        }
        if(p == i || q == j){//由于节点自身不能是自己的祖先节点，所以如果有节点下标未变过，就继续找它们的双亲节点
            p /= 2;
        }
        *e = p;
        *anc = T[p];
        return 1;
    }
    printf("节点为空");
    return 0;
}
