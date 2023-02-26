#include <stdio.h>
#include <stdlib.h>

//---------���Ա��˫������洢�ṹ--------------
typedef struct DNode{
    int data;
    struct DNode *prior;
    struct DNode *next;
}DNode, *DLinkList;

typedef struct DulNode{
    int data, freq;
    struct DulNode *pred;
    struct DulNode *next;
}DulNode, *DulLinkList;


DLinkList InitList_D();
void DestoryList_D(DLinkList L);

/*����˫��ѭ������Ŀձ�*/
DLinkList InitList_D(){
    DNode *p;
    p = (DNode *)malloc(sizeof(DNode));
    if(!p){
        printf("overflow\n");
        exit(0);
    }
    p->next = NULL;
    return p;
}


/*����˫��ѭ������Ŀձ�*/
DulLinkList InitList_Dul(){
    DulNode *p;
    p = (DulNode *)malloc(sizeof(DulNode));
    if(!p){
        printf("overflow\n");
        exit(0);
    }
    p->next = NULL;
    return p;
}


/*LΪ��ͷ����˫�������ͷָ��
��L���ڣ����������Ա�*/
void DestoryList_D(DLinkList L){
    if(!L){
        printf("L������");
        exit(0);
    }
    else {
        DNode *p, *q;
        p = L;
        q = p->next;
        while(q){
            free(p);
            p = q;
            q = q->next;
            }
        }
    free(L);
}


/*LΪ��ͷ����˫�������ͷָ��
��L���ڣ����������Ա�*/
void DestoryList_Dul(DulLinkList L){
    if(!L){
        printf("L������");
        exit(0);
    }
    else {
        DulNode *p, *q;
        p = L->next;
        q = p->next;
        while(q){
            free(p);
            p = q;
            q = q->next;
            }
        free(p);
        }
    free(L);
}


/*LΪ��ͷ����˫��ѭ�����Ա�
�ڵ�i��λ��ǰ����Ԫ��e���ɹ��򷵻�1�����򷵻�0*/
int ListInsert_D(DLinkList *L, int i, int e){

}


/*ʹ������Ԫ��ֵΪx�Ľ����freq���ֵ��1,ͬʱʹ��������Ƶ�ȵĵݼ�������*/
void LocateNode(DulLinkList L, int x){
    DulNode *p, *q;
    p = L->next;
    while(p){//���η���ÿ���ڵ㣬ͬʱ��Ҫ��ı�freq�Լ�p�ڵ��λ��
        if(p->data == x) p->freq++;//Ԫ��ֵΪx�Ľ����freq���ֵ��1
        q = p->pred;
        if(p != L->next && q->freq < p->freq){//p���ǵ�һ���ڵ���p�ڵ���Ҫǰ��
            while(q != L && q->freq < p->freq) q = q->pred;//qָ��p�ڵ���Ҫ�����λ�õ�ǰһ���ڵ�
            p->pred->next = p->next;
            if(p->next)p->next->pred = p->pred;//pΪ���һ���ڵ�ʱҪ��������
            p->next = q->next;
            p->pred = q;
            q->next = p;
            p->next->pred = p;//��p����q֮��
        }
        p = p->next;
    }
}


/*LΪ��ͷ����˫�������ͷָ��
�ӱ�ͷ����β������˫������*/
void CreateList_Dul(DulLinkList L, int n){
    int i;
    DulNode *p ,*q;
    q = L;
    for(i = 0; i < n; i++){
        p = (DulNode *)malloc(sizeof(DulNode));
        scanf("%d", &(p->data));
        p->freq = 0;
        q->next = p;
        p->pred = q;
        q = p;
    }
    p->next = NULL;
}


/*LΪ��ͷ����˫�������ͷָ��
��ӡ��L����������Ԫ��*/
void Visit_Dul(DulLinkList L){
    if(!L){
        printf("L������");
        exit(0);
    }
    DulNode *p = L->next;
    if(!p) printf("LΪ�ձ�");
    while(p){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}


int main()
{
    DulLinkList listhead;
    listhead = InitList_Dul();
    CreateList_Dul(listhead, 5);
    LocateNode(listhead, 3);
    Visit_Dul(listhead);
    LocateNode(listhead, 0);
    Visit_Dul(listhead);
    LocateNode(listhead, 4);
    Visit_Dul(listhead);
    DestoryList_Dul(listhead);

    return 0;
}
