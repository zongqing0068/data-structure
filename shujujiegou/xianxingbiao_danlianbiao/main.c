#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//--------线性表的单链表存储结构----------
typedef struct LNode{
int data;
struct LNode *next;
}LNode, *LinkList;

LinkList InitList_L();
void DestoryList_L(LinkList L);
void ClearList_L(LinkList L);
int ListEmpty_L(LinkList L);
int ListLength_L(LinkList L);
void Visit_L(LinkList L);
int GetElem_L(LinkList L, int i, int *e);
LNode *GetLast_L(LinkList L);
int LocateElem_L(LinkList L, int e, int(*compare)(int a, int b));
int Equal(int a, int b);
int Descending(int a,int b);
int Ascending(int a,int b);
void PriorElem_L(LinkList L, int e, LNode *pre_e);
void NextElem_L(LinkList L, int e, LNode *next_e);
int ListInsert_L(LinkList L, int i, int e);
int ListDelet_L(LinkList L, int i, int *e);
void CreateList_L_Reversed(LinkList L, int n);
void CreateList_L(LinkList L, int n);
LinkList CreateList_L1(int n);
void MergeList_L(LinkList La, LinkList Lb, LinkList Lc);
void Purge_L(LinkList L);
void Union_L(LinkList La, LinkList Lb);
void Deleval_L(LinkList L, int d);
void Print_L_Reversed(LinkList L);
void Print_L1_Reversed(LinkList L);
void CreateList_AL(LinkList L);
void Reverse_L (LinkList L);
void Delete_L_min_max (LinkList L, int min, int max);

/*建立空表，即头结点的指针域为空*/
LinkList InitList_L(){
    LNode *p;
    p = (LNode *)malloc(sizeof(LNode));
    if(!p){
        printf("overflow\n");
        exit(1);
    }
    p->next = NULL;
    return p;
}


/*L为带头结点的单链表的头指针
若L存在，则销毁线性表*/
void DestoryList_L(LinkList L){
    if(!L){
        printf("L不存在");
        exit(1);
    }
    else {
        LNode *p, *q;
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


/*L为带头结点的单链表的头指针
若L存在，将L置为空表*/
void ClearList_L(LinkList L){
    if(!L){
        printf("L不存在");
        exit(1);
    }
    else {
        LNode *p;
        p = L->next;
        if(p){
            LNode *q = p->next;
            while(q){
                free(p);
                p = q;
                q = q->next;
                }
                free(p);
                L->next = NULL;
            }
        }
}


/*L为带头结点的单链表的头指针
若L为空表，则返回1，否则返回0*/
int ListEmpty_L(LinkList L){
    if(!L){
        printf("L不存在");
        exit(1);
    }
    else if(!(L->next)) return 1;
    else return 0;//链表非空
}


/*L为带头结点的单链表的头指针
返回L中数据元素个数*/
int ListLength_L(LinkList L){
    if(!L){
        printf("L不存在");
        exit(1);
    }
    int i = 0;
    LNode *p = L->next;
    while(p){
        i++;
        p = p->next;
    }
    return i;
}


/*L为带头结点的单链表的头指针
打印出L中所有数据元素*/
void Visit_L(LinkList L){
    if(!L){
        printf("L不存在");
        exit(1);
    }
    LNode *p = L->next;
    if(!p) printf("L为空表");
    while(p){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

/*L为带头结点的单链表的头指针
当第i个元素存在时，将其值赋值给e并返回1，否则返回0*/
int GetElem_L(LinkList L, int i, int *e){
    if(!L){
        printf("L不存在");
        exit(1);
    }
    LNode *p = L->next;
    int j = 1;
    while(p && j < i){
        p = p->next;
        j++;
    }
    if(!p || j > i) return 0;
    *e = p->data;
    return 1;
}


/*返回最后一个节点*/
LNode *GetLast_L(LinkList L){
    if(!L){
        printf("L不存在");
        exit(1);
    }
    LNode *p = L->next;
    while(p->next) p = p->next;
    return p;
}


/*L为带头结点的单链表的头指针
返回L中第一个与e满足compare()关系的元素的位序，若这样的元素不存在，则返回0*/
int LocateElem_L(LinkList L, int e, int(*compare)(int a, int b)){
    if(!L){
        printf("L不存在");
        exit(1);
    }
    LNode *p = L->next;
    int i = 1;
    while(p){
        if((*compare)(p->data, e)) return i;
        p = p->next;
        i++;
    }
    return 0;
}


/*判断两个数据是否相等*/
int Equal(int a, int b){
    return a == b;
}


/*判断第一个参数是否大于第二个参数*/
int Descending(int a,int b){
    return a > b;
}


/*判断第一个参数是否小于第二个参数*/
int Ascending(int a,int b){
    return a < b;
}


/*若e是L的数据元素，且不是第一个，则用pre_e返回它的前驱，否则操作失败*/
void PriorElem_L(LinkList L, int e, LNode *pre_e){
    if(!L){
        printf("L不存在");
        exit(1);
    }
    LNode *p = L->next;
    if(e == p->data){
        printf("e为第一个数据元素");
        exit(1);
    }
    while(p->next){
        if(p->next->data == e){
           *pre_e = *p;
           return;
        }
        else p = p->next;
    }
    printf("线性表中不存在数据e");
}


/*若e是L的数据元素，且不是最后一个，则用next_e返回它的后继，否则操作失败*/
void NextElem_L(LinkList L, int e, LNode *next_e){
    if(!L){
        printf("L不存在");
        exit(1);
    }
    LNode *p = L->next;
    while(p->next){
        if(p->data == e){
           *next_e = *(p->next);
           return;
        }
        else p = p->next;
    }
    if(p->data == e)printf("e为最后一个数据元素");
    else printf("线性表中不存在数据e");
}



/*L为带头结点的单链表的头指针
当表长不小于i-1时，在第i个位置之前插入元素e并返回1，否则返回0*/
int ListInsert_L(LinkList L, int i, int e){
    LNode *p = L;
    int j = 0;
    while(p && j < i - 1){
        p = p->next;
        j++;
    }
    if(!p || i < 1) return 0;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return 1;
}


/*L为带头结点的单链表的头指针
当表长不小于i时，删除第i个位置的元素，并由e返回其值并返回1，否则返回0*/
int ListDelet_L(LinkList L, int i, int *e){
    LNode *p = L;
    int j = 0;
    while(p->next && j < i - 1){
        p = p->next;
        j++;
    }
    if(!(p->next) || i < 1) return 0;
    *e = p->next->data;
    LNode *q = p->next;
    p->next = q->next;
    free(q);
    return 1;
}


/*L为带头结点的单链表的头指针
从表尾到表头逆向建立单链表*/
void CreateList_L_Reversed(LinkList L, int n){
    int i;
    for(i = n; i > 0; i--){
        LNode *p = (LNode *)malloc(sizeof(LNode));
        scanf("%d", &(p->data));
        p->next = L->next;
        L->next = p;
    }
}


/*L为带头结点的单链表的头指针
从表头到表尾正向建立单链表*/
void CreateList_L(LinkList L, int n){
    int i;
    LNode *p ,*q;
    q = L;
    for(i = 0; i < n; i++){
        p = (LNode *)malloc(sizeof(LNode));
        scanf("%d", &(p->data));
        q->next = p;
        q = p;
    }
    p->next = NULL;
}


/*L为不带头结点的单链表的头指针
从表头到表尾正向建立单链表*/
LinkList CreateList_L1(int n){
    int i;
    LNode *p ,*q;
    LinkList L;
    L = q = (LNode *)malloc(sizeof(LNode));
    scanf("%d", &(q->data));
    for(i = 1; i < n; i++){
        p = (LNode *)malloc(sizeof(LNode));
        scanf("%d", &(p->data));
        q->next = p;
        q = p;
    }
    q->next = NULL;
    return L;
}


/*L为带头结点的单链表的头指针
建立升序单链表*/
void CreateList_AL(LinkList L){
    LNode *p, *q;
    int x;
    scanf("%d", &x);
    while(x != -9999){
        p = L;
        while(p->next && p->next->data <= x) p = p->next;
        q = (LNode *)malloc(sizeof(LNode));
        if(!q)//检查分配内存是否成功
        {
            printf("overflow");
            exit(1);
        }
        q->data = x;
        q->next = p->next;
        p->next = q;
        scanf("%d", &x);
    }
}


/*带头结点的单链线性表La和Lb的元素按值非递减排列，La和Lb为头指针
归并La和Lb得到新的单链线性表Lc，Lc的元素也按值非递减排列*/
void MergeList_L(LinkList La, LinkList Lb, LinkList Lc){
    LNode *pa, *pb, *pc;
    pc = Lc;
    pa = La->next;
    pb = Lb->next;
    while(pa && pb){
        if(pa->data < pb->data){
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        else{
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
        pc->next = pa ? pa : pb;
    }
}


/*删除重复出现过的元素*/
void Purge_L(LinkList L){
    int p = 1;
    int x, y;
    int n = ListLength_L(L);
    while(p < n){
        int q = p + 1;
        while(q <= n){
            GetElem_L(L, p, &x);
            GetElem_L(L, q, &y);
            if(x == y) {
                ListDelet_L(L, q, &y);
                q--;
                n--;
            }
            q++;
        }
        p++;
    }
}


/*L为带头结点的单链表的头指针，表中数据的绝对值均不大于n，
保留第一次出现的结点而删除其余绝对值相等的结点*/
void Delet_L_Same(LinkList L, int n){
    int *flag, i;
    flag = (int *)malloc(sizeof(int)*(n + 1));//用flag来标记绝对值是否已经出现过
    for(i = 0;i <= n + 1; i++) flag[i] = 0;//将标记均初始化为0
    LNode *p, *q;
    q = L;
    p = L->next;
    while(p){
        if(abs(p->data) > n){
            printf("数据绝对值超过范围");
            exit(1);
        }
        if(flag[abs(p->data)]){
            q->next = p->next;
            free(p);
            p = q->next;//绝对值对应的flag值为1，说明已出现过，删除该节点
        }
        else{
            flag[abs(p->data)] = 1;
            q = p;
            p = p->next;//否则将对应的flag值记为1，指针后移
        }
    }
}


/*并集*/
void Union_L(LinkList La, LinkList Lb){
    int p;
    LNode *q;
    p = ListLength_L(La);
    q = Lb->next;
    while(q){
        if(!LocateElem_L(La, q->data, Equal)) ListInsert_L(La, ++p, q->data);
        q = q->next;
    }

}


/*删除所有值为d的元素*/
void Deleval_L(LinkList L, int d){
    int p, e, n;
    p = 1;
    n = ListLength_L(L);
    while(p <= n){
        GetElem_L(L, p, &e);
        if(e == d){
            ListDelet_L(L, p, &e);
            p--;
            n--;
        }
        p++;
    }
}


/*L为头指针(带头结点)，逆序输出*/
void Print_L_Reversed(LinkList L){
    LNode *p = L->next;
    if(p->next) Print_L_Reversed(p);
    printf("%d ", p->data);
}


/*L为头指针(不带头结点)，逆序输出*/
void Print_L1_Reversed(LinkList L){
    if(L->next) Print_L1_Reversed(L->next);
    printf("%d ", L->data);
}


/*单链表反向*/
void Reverse_L (LinkList L){
    LNode *p, *q;
    p = L->next;
    L->next = NULL;
    while(p){
        q = p->next;
        p->next = L->next;
        L->next = p;
        p = q;
    }
}


/*L为带头结点的递增有序单向链表,min和max分别为传入的最小值和最大值
删除表中值大于min且小于max的结点(若表中有这样的结点)*/
void Delete_L_min_max(LinkList L, int min, int max){
    LNode *p, *q, *r;
    if(min > max){
        printf("error");
        exit(1);//min大于max，error
    }
    p = L->next;
    r = L;
    while(p && p->data <= min){//寻找第一个大于min的元素
        r = q = p;
        p = p->next;
    }
    if(!p) return;//表内数据均小于等于min，直接返回
    while(p && p->data < max){
        q= p->next;
        free(p);
        p = q;
    }//删除在min和max之间的元素
    r->next = p;//将删去部分前后的链表连起来
    return;
}


int main()
{
/*(测试)    LinkList listhead = NULL;
    LinkList listhead1 = NULL;
    LinkList listhead2 = NULL;
    LNode p;
    int flag, n, e, i;

    //建立空表
    listhead = InitList_L();
    listhead1 = InitList_L();
    listhead2 = InitList_L();

    //判空
    flag = ListEmpty_L(listhead);
    printf("%d\n", flag);

    //正向建立链表
    CreateList_L(listhead, 5);
    //逆向建立链表
    CreateList_L_Reversed(listhead1, 5);

    //遍历访问
    Visit_L(listhead);
    Visit_L(listhead1);

    //单个访问
    printf("访问第i个数据：");
    scanf("%d", &i);
    GetElem_L(listhead, i, &e);
    printf("%d\n", e);

    //定位相等
    e = LocateElem_L(listhead, 6, Equal);
    printf("locate:%d\n", e);

    //定位大于
    e = LocateElem_L(listhead, 4, Descending);
    printf("locate:%d\n", e);

    //前驱
    PriorElem_L(listhead, 2, &p);
    printf("前驱%d\n", p.data);

    //后继
    NextElem_L(listhead, 5, &p);
    printf("后继%d\n", p.data);

    //插入
    ListInsert_L(listhead, 6, 999);
    Visit_L(listhead);

    //删除
    ListDelet_L(listhead, 1, &e);
    Visit_L(listhead);
    printf("删除%d\n", e);

    //长度
    n = ListLength_L(listhead);
    printf("%d\n", n);

    //归并
    MergeList_L(listhead, listhead1, listhead2);
    Visit_L(listhead2);

   /* //置空
    ClearList_L(listhead);
    ClearList_L(listhead1);
    ClearList_L(listhead2);

    //长度
    n = ListLength_L(listhead);
    printf("%d\n", n);

    //判空
    flag = ListEmpty_L(listhead);
    printf("%d\n", flag);

    //销毁
    DestoryList_L(listhead);
    DestoryList_L(listhead1);*/
/*    DestoryList_L(listhead2);
    free(listhead);
    free(listhead1);

    listhead = listhead1 =listhead2 = NULL;
*/

/*(去重)    LinkList listhead;
    listhead = InitList_L();
    CreateList_L(listhead, 10);
    Purge_L(listhead);
    Visit_L(listhead);
    DestoryList_L(listhead);
*/

/*(返回尾结点)    LNode *p;
    LinkList listhead;
    listhead = InitList_L();
    CreateList_L(listhead, 3);
    p = GetLast_L(listhead);
    printf("%d", p->data);
    DestoryList_L(listhead);
*/

/*(并集）    LinkList listheada, listheadb;
    listheada = InitList_L();
    listheadb = InitList_L();
    CreateList_L(listheada, 3);
    CreateList_L(listheadb, 3);
    Union_L(listheada, listheadb);
    Visit_L(listheada);
    DestoryList_L(listheada);
    DestoryList_L(listheadb);
*/

/*(删去所有d)    LinkList listhead;
    listhead = InitList_L();
    CreateList_L(listhead, 10);
    Deleval_L(listhead, 3);
    Visit_L(listhead);
    DestoryList_L(listhead);
*/

/*(有头结点逆序输出)    LinkList listhead;
    listhead = InitList_L();
    CreateList_L(listhead,5);
    Print_L_Reversed(listhead);
    DestoryList_L(listhead);
*/

/*(无头结点逆序输出)    LinkList listhead;
    listhead = CreateList_L1(5);
    Print_L1_Reversed(listhead);
    DestoryList_L(listhead);
*/

/*(建立升序单链表)    LinkList listhead;
    listhead = InitList_L();
    CreateList_AL(listhead);
    Visit_L(listhead);
    DestoryList_L(listhead);
*/

/*(链表逆序)    LinkList listhead;
    listhead = InitList_L();
    CreateList_L(listhead,5);
    Reverse_L(listhead);
    Visit_L(listhead);
    DestoryList_L(listhead);
*/

/*(删去一个范围内的数)    LinkList listhead;
    listhead = InitList_L();
    CreateList_L(listhead,5);
    Delete_L_min_max(listhead, 6, 6);
    Visit_L(listhead);
    DestoryList_L(listhead);
*/

    LinkList listhead;
    listhead = InitList_L();
    CreateList_L(listhead, 3);
    Delet_L_Same(listhead, 10);
    Visit_L(listhead);
    DestoryList_L(listhead);



    return 0;
}
