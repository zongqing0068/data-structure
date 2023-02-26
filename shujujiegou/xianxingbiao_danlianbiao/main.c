#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//--------���Ա�ĵ�����洢�ṹ----------
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

/*�����ձ���ͷ����ָ����Ϊ��*/
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


/*LΪ��ͷ���ĵ������ͷָ��
��L���ڣ����������Ա�*/
void DestoryList_L(LinkList L){
    if(!L){
        printf("L������");
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


/*LΪ��ͷ���ĵ������ͷָ��
��L���ڣ���L��Ϊ�ձ�*/
void ClearList_L(LinkList L){
    if(!L){
        printf("L������");
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


/*LΪ��ͷ���ĵ������ͷָ��
��LΪ�ձ��򷵻�1�����򷵻�0*/
int ListEmpty_L(LinkList L){
    if(!L){
        printf("L������");
        exit(1);
    }
    else if(!(L->next)) return 1;
    else return 0;//����ǿ�
}


/*LΪ��ͷ���ĵ������ͷָ��
����L������Ԫ�ظ���*/
int ListLength_L(LinkList L){
    if(!L){
        printf("L������");
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


/*LΪ��ͷ���ĵ������ͷָ��
��ӡ��L����������Ԫ��*/
void Visit_L(LinkList L){
    if(!L){
        printf("L������");
        exit(1);
    }
    LNode *p = L->next;
    if(!p) printf("LΪ�ձ�");
    while(p){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

/*LΪ��ͷ���ĵ������ͷָ��
����i��Ԫ�ش���ʱ������ֵ��ֵ��e������1�����򷵻�0*/
int GetElem_L(LinkList L, int i, int *e){
    if(!L){
        printf("L������");
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


/*�������һ���ڵ�*/
LNode *GetLast_L(LinkList L){
    if(!L){
        printf("L������");
        exit(1);
    }
    LNode *p = L->next;
    while(p->next) p = p->next;
    return p;
}


/*LΪ��ͷ���ĵ������ͷָ��
����L�е�һ����e����compare()��ϵ��Ԫ�ص�λ����������Ԫ�ز����ڣ��򷵻�0*/
int LocateElem_L(LinkList L, int e, int(*compare)(int a, int b)){
    if(!L){
        printf("L������");
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


/*�ж����������Ƿ����*/
int Equal(int a, int b){
    return a == b;
}


/*�жϵ�һ�������Ƿ���ڵڶ�������*/
int Descending(int a,int b){
    return a > b;
}


/*�жϵ�һ�������Ƿ�С�ڵڶ�������*/
int Ascending(int a,int b){
    return a < b;
}


/*��e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ�����������ʧ��*/
void PriorElem_L(LinkList L, int e, LNode *pre_e){
    if(!L){
        printf("L������");
        exit(1);
    }
    LNode *p = L->next;
    if(e == p->data){
        printf("eΪ��һ������Ԫ��");
        exit(1);
    }
    while(p->next){
        if(p->next->data == e){
           *pre_e = *p;
           return;
        }
        else p = p->next;
    }
    printf("���Ա��в���������e");
}


/*��e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ�̣��������ʧ��*/
void NextElem_L(LinkList L, int e, LNode *next_e){
    if(!L){
        printf("L������");
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
    if(p->data == e)printf("eΪ���һ������Ԫ��");
    else printf("���Ա��в���������e");
}



/*LΪ��ͷ���ĵ������ͷָ��
������С��i-1ʱ���ڵ�i��λ��֮ǰ����Ԫ��e������1�����򷵻�0*/
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


/*LΪ��ͷ���ĵ������ͷָ��
������С��iʱ��ɾ����i��λ�õ�Ԫ�أ�����e������ֵ������1�����򷵻�0*/
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


/*LΪ��ͷ���ĵ������ͷָ��
�ӱ�β����ͷ������������*/
void CreateList_L_Reversed(LinkList L, int n){
    int i;
    for(i = n; i > 0; i--){
        LNode *p = (LNode *)malloc(sizeof(LNode));
        scanf("%d", &(p->data));
        p->next = L->next;
        L->next = p;
    }
}


/*LΪ��ͷ���ĵ������ͷָ��
�ӱ�ͷ����β������������*/
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


/*LΪ����ͷ���ĵ������ͷָ��
�ӱ�ͷ����β������������*/
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


/*LΪ��ͷ���ĵ������ͷָ��
������������*/
void CreateList_AL(LinkList L){
    LNode *p, *q;
    int x;
    scanf("%d", &x);
    while(x != -9999){
        p = L;
        while(p->next && p->next->data <= x) p = p->next;
        q = (LNode *)malloc(sizeof(LNode));
        if(!q)//�������ڴ��Ƿ�ɹ�
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


/*��ͷ���ĵ������Ա�La��Lb��Ԫ�ذ�ֵ�ǵݼ����У�La��LbΪͷָ��
�鲢La��Lb�õ��µĵ������Ա�Lc��Lc��Ԫ��Ҳ��ֵ�ǵݼ�����*/
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


/*ɾ���ظ����ֹ���Ԫ��*/
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


/*LΪ��ͷ���ĵ������ͷָ�룬�������ݵľ���ֵ��������n��
������һ�γ��ֵĽ���ɾ���������ֵ��ȵĽ��*/
void Delet_L_Same(LinkList L, int n){
    int *flag, i;
    flag = (int *)malloc(sizeof(int)*(n + 1));//��flag����Ǿ���ֵ�Ƿ��Ѿ����ֹ�
    for(i = 0;i <= n + 1; i++) flag[i] = 0;//����Ǿ���ʼ��Ϊ0
    LNode *p, *q;
    q = L;
    p = L->next;
    while(p){
        if(abs(p->data) > n){
            printf("���ݾ���ֵ������Χ");
            exit(1);
        }
        if(flag[abs(p->data)]){
            q->next = p->next;
            free(p);
            p = q->next;//����ֵ��Ӧ��flagֵΪ1��˵���ѳ��ֹ���ɾ���ýڵ�
        }
        else{
            flag[abs(p->data)] = 1;
            q = p;
            p = p->next;//���򽫶�Ӧ��flagֵ��Ϊ1��ָ�����
        }
    }
}


/*����*/
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


/*ɾ������ֵΪd��Ԫ��*/
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


/*LΪͷָ��(��ͷ���)���������*/
void Print_L_Reversed(LinkList L){
    LNode *p = L->next;
    if(p->next) Print_L_Reversed(p);
    printf("%d ", p->data);
}


/*LΪͷָ��(����ͷ���)���������*/
void Print_L1_Reversed(LinkList L){
    if(L->next) Print_L1_Reversed(L->next);
    printf("%d ", L->data);
}


/*��������*/
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


/*LΪ��ͷ���ĵ�������������,min��max�ֱ�Ϊ�������Сֵ�����ֵ
ɾ������ֵ����min��С��max�Ľ��(�������������Ľ��)*/
void Delete_L_min_max(LinkList L, int min, int max){
    LNode *p, *q, *r;
    if(min > max){
        printf("error");
        exit(1);//min����max��error
    }
    p = L->next;
    r = L;
    while(p && p->data <= min){//Ѱ�ҵ�һ������min��Ԫ��
        r = q = p;
        p = p->next;
    }
    if(!p) return;//�������ݾ�С�ڵ���min��ֱ�ӷ���
    while(p && p->data < max){
        q= p->next;
        free(p);
        p = q;
    }//ɾ����min��max֮���Ԫ��
    r->next = p;//��ɾȥ����ǰ�������������
    return;
}


int main()
{
/*(����)    LinkList listhead = NULL;
    LinkList listhead1 = NULL;
    LinkList listhead2 = NULL;
    LNode p;
    int flag, n, e, i;

    //�����ձ�
    listhead = InitList_L();
    listhead1 = InitList_L();
    listhead2 = InitList_L();

    //�п�
    flag = ListEmpty_L(listhead);
    printf("%d\n", flag);

    //����������
    CreateList_L(listhead, 5);
    //����������
    CreateList_L_Reversed(listhead1, 5);

    //��������
    Visit_L(listhead);
    Visit_L(listhead1);

    //��������
    printf("���ʵ�i�����ݣ�");
    scanf("%d", &i);
    GetElem_L(listhead, i, &e);
    printf("%d\n", e);

    //��λ���
    e = LocateElem_L(listhead, 6, Equal);
    printf("locate:%d\n", e);

    //��λ����
    e = LocateElem_L(listhead, 4, Descending);
    printf("locate:%d\n", e);

    //ǰ��
    PriorElem_L(listhead, 2, &p);
    printf("ǰ��%d\n", p.data);

    //���
    NextElem_L(listhead, 5, &p);
    printf("���%d\n", p.data);

    //����
    ListInsert_L(listhead, 6, 999);
    Visit_L(listhead);

    //ɾ��
    ListDelet_L(listhead, 1, &e);
    Visit_L(listhead);
    printf("ɾ��%d\n", e);

    //����
    n = ListLength_L(listhead);
    printf("%d\n", n);

    //�鲢
    MergeList_L(listhead, listhead1, listhead2);
    Visit_L(listhead2);

   /* //�ÿ�
    ClearList_L(listhead);
    ClearList_L(listhead1);
    ClearList_L(listhead2);

    //����
    n = ListLength_L(listhead);
    printf("%d\n", n);

    //�п�
    flag = ListEmpty_L(listhead);
    printf("%d\n", flag);

    //����
    DestoryList_L(listhead);
    DestoryList_L(listhead1);*/
/*    DestoryList_L(listhead2);
    free(listhead);
    free(listhead1);

    listhead = listhead1 =listhead2 = NULL;
*/

/*(ȥ��)    LinkList listhead;
    listhead = InitList_L();
    CreateList_L(listhead, 10);
    Purge_L(listhead);
    Visit_L(listhead);
    DestoryList_L(listhead);
*/

/*(����β���)    LNode *p;
    LinkList listhead;
    listhead = InitList_L();
    CreateList_L(listhead, 3);
    p = GetLast_L(listhead);
    printf("%d", p->data);
    DestoryList_L(listhead);
*/

/*(������    LinkList listheada, listheadb;
    listheada = InitList_L();
    listheadb = InitList_L();
    CreateList_L(listheada, 3);
    CreateList_L(listheadb, 3);
    Union_L(listheada, listheadb);
    Visit_L(listheada);
    DestoryList_L(listheada);
    DestoryList_L(listheadb);
*/

/*(ɾȥ����d)    LinkList listhead;
    listhead = InitList_L();
    CreateList_L(listhead, 10);
    Deleval_L(listhead, 3);
    Visit_L(listhead);
    DestoryList_L(listhead);
*/

/*(��ͷ����������)    LinkList listhead;
    listhead = InitList_L();
    CreateList_L(listhead,5);
    Print_L_Reversed(listhead);
    DestoryList_L(listhead);
*/

/*(��ͷ����������)    LinkList listhead;
    listhead = CreateList_L1(5);
    Print_L1_Reversed(listhead);
    DestoryList_L(listhead);
*/

/*(������������)    LinkList listhead;
    listhead = InitList_L();
    CreateList_AL(listhead);
    Visit_L(listhead);
    DestoryList_L(listhead);
*/

/*(��������)    LinkList listhead;
    listhead = InitList_L();
    CreateList_L(listhead,5);
    Reverse_L(listhead);
    Visit_L(listhead);
    DestoryList_L(listhead);
*/

/*(ɾȥһ����Χ�ڵ���)    LinkList listhead;
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
