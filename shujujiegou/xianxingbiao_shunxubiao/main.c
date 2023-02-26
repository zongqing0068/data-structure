#include <stdio.h>
#include <stdlib.h>
#define MAXLENGTH 100

typedef struct
{
    int data[MAXLENGTH];
    int last;//表长
}Sqlist;

/*La和Lb为两个等长升序序列，返回这两个序列的中位数*/
int Median_Sq(Sqlist *La, Sqlist *Lb){
    int sa, sb, ea, eb, ma, mb;//s即start，e即end，m即middle，分别用sa，sb和ea，eb以及ma，mb来表示当前两个数组下标的起始和结束以及中间位置

    if(La->last != Lb->last){
        printf("表长不等");
        exit(0);
    }

    sa = sb = 0;
    ea = eb = La->last - 1;
    while(sa != ea || sb != eb){//表示两个序列中均不止一个元素
        ma = (sa + ea)/2;
        mb = (sb + eb)/2;
        if(La->data[ma] == Lb->data[mb]) return La->data[ma];
        if(La->data[ma] > Lb->data[mb]){
            if((sa + ea)%2){//每个序列当前元素个数为偶数
                ea = ma;
                sb = mb + 1;
            }
            else {//每个序列当前元素个数为奇数
                ea = ma;
                sb = mb;
            }
        }
        else{
            if((sa + ea)%2){//每个序列当前元素个数为偶数
                sa = ma + 1;
                eb = mb;
            }
            else {//每个序列当前元素个数为奇数
                sa = ma;
                eb = mb;
            }
        }
    }//比较两个序列中位数的大小，并截去较大者的后半部分与较小者的前半部分
    return La->data[sa] < Lb->data[sb] ? La->data[sa] : Lb->data[sb];
}


void Create_Sq(Sqlist *L){
    int x;
    scanf("%d", &x);
    L->last = 0;
    while(x != -9999){
        L->data[++L->last - 1] = x;
        scanf("%d", &x);
    }
}


int main()
{
    Sqlist La, Lb;
    Create_Sq(&La);
    Create_Sq(&Lb);
    int x;
    x = Median_Sq(&La, &Lb);
    printf("%d\n", x);
    return 0;
}
