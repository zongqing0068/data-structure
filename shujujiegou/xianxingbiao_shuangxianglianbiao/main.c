#include <stdio.h>
#include <stdlib.h>

//---------线性表的双向链表存储结构--------------
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

/*建立双向循环链表的空表*/
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


/*建立双向循环链表的空表*/
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


/*L为带头结点的双向链表的头指针
若L存在，则销毁线性表*/
void DestoryList_D(DLinkList L){
    if(!L){
        printf("L不存在");
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


/*L为带头结点的双向链表的头指针
若L存在，则销毁线性表*/
void DestoryList_Dul(DulLinkList L){
    if(!L){
        printf("L不存在");
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


/*L为带头结点的双链循环线性表
在第i个位置前插入元素e，成功则返回1，否则返回0*/
int ListInsert_D(DLinkList *L, int i, int e){

}


/*使链表中元素值为x的结点中freq域的值加1,同时使链表按访问频度的递减序排列*/
void LocateNode(DulLinkList L, int x){
    DulNode *p, *q;
    p = L->next;
    while(p){//依次访问每个节点，同时按要求改变freq以及p节点的位置
        if(p->data == x) p->freq++;//元素值为x的结点中freq域的值加1
        q = p->pred;
        if(p != L->next && q->freq < p->freq){//p不是第一个节点且p节点需要前移
            while(q != L && q->freq < p->freq) q = q->pred;//q指向p节点需要插入的位置的前一个节点
            p->pred->next = p->next;
            if(p->next)p->next->pred = p->pred;//p为最后一个节点时要特殊讨论
            p->next = q->next;
            p->pred = q;
            q->next = p;
            p->next->pred = p;//将p插入q之后
        }
        p = p->next;
    }
}


/*L为带头结点的双向链表的头指针
从表头到表尾正向建立双向链表*/
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


/*L为带头结点的双向链表的头指针
打印出L中所有数据元素*/
void Visit_Dul(DulLinkList L){
    if(!L){
        printf("L不存在");
        exit(0);
    }
    DulNode *p = L->next;
    if(!p) printf("L为空表");
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
