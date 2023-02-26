#include <stdio.h>
#include <stdlib.h>
#define MAXLENGTH 100

typedef struct
{
    int data[MAXLENGTH];
    int last;//��
}Sqlist;

/*La��LbΪ�����ȳ��������У��������������е���λ��*/
int Median_Sq(Sqlist *La, Sqlist *Lb){
    int sa, sb, ea, eb, ma, mb;//s��start��e��end��m��middle���ֱ���sa��sb��ea��eb�Լ�ma��mb����ʾ��ǰ���������±����ʼ�ͽ����Լ��м�λ��

    if(La->last != Lb->last){
        printf("������");
        exit(0);
    }

    sa = sb = 0;
    ea = eb = La->last - 1;
    while(sa != ea || sb != eb){//��ʾ���������о���ֹһ��Ԫ��
        ma = (sa + ea)/2;
        mb = (sb + eb)/2;
        if(La->data[ma] == Lb->data[mb]) return La->data[ma];
        if(La->data[ma] > Lb->data[mb]){
            if((sa + ea)%2){//ÿ�����е�ǰԪ�ظ���Ϊż��
                ea = ma;
                sb = mb + 1;
            }
            else {//ÿ�����е�ǰԪ�ظ���Ϊ����
                ea = ma;
                sb = mb;
            }
        }
        else{
            if((sa + ea)%2){//ÿ�����е�ǰԪ�ظ���Ϊż��
                sa = ma + 1;
                eb = mb;
            }
            else {//ÿ�����е�ǰԪ�ظ���Ϊ����
                sa = ma;
                eb = mb;
            }
        }
    }//�Ƚ�����������λ���Ĵ�С������ȥ�ϴ��ߵĺ�벿�����С�ߵ�ǰ�벿��
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
