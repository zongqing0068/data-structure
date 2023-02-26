#include <stdio.h>
#include <stdlib.h>
#define TElemType int

typedef struct BiTNode{
    TElemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

typedef struct QNode{
    BiTNode *bt;
    struct QNode *next;
}QNode;

typedef struct Queue{
    QNode *front, *rear;
}Queue;

/*������������*/
BiTree CreateBiTree(){
    int x;
    BiTNode *p;
    scanf("%d", &x);
    if(x == 0) return NULL;
    else {
        p = (BiTNode *)malloc(sizeof(BiTNode));
        p->data = x;
        p->lchild = CreateBiTree();
        p->rchild = CreateBiTree();
    }
    return p;
}

/*�������������*/
void PreOrderTraverse_Print(BiTree T){
    printf("%d ", T->data);
    if(T->lchild) PreOrderTraverse_Print(T->lchild);
    if(T->rchild) PreOrderTraverse_Print(T->rchild);
}


/*���*/
void EnQueue(Queue *Q, BiTNode *bt){
    QNode *p = (QNode*)malloc(sizeof(QNode));
    p->bt = bt;
    p->next = NULL;//�����ڴ棬������Ϣ�����ڵ�ָ�����ÿ�

    if(!Q->front){
        Q->front = p;//�������Ϊ�գ������޸Ķ�ͷָ��
        Q->rear = p;
    }
    else{
        Q->rear->next = p;
        Q->rear = p;//�޸Ķ�βָ��
    }
}

/*����*/
BiTNode* DeQueue(Queue *Q){
    if(!Q->front){
        printf("����Ϊ��");
        exit(1);
    }
    BiTNode *p = Q->front->bt;
    Q->front = Q->front->next;
    return p;
}

/*�ж϶����Ƿ�Ϊ��*/
int QueueEmpty(Queue *Q){
    if(!Q->front)return 1;
    else return 0;
}

/*�����ĸ߶�*/
int Depth(BiTree T){
    if(!T) return 0;//��ֹ��������ָ���ʾ���ʵ���ײ�
    int ldepth, rdepth;
    ldepth = Depth(T->lchild);
    rdepth = Depth(T->rchild);//�ݹ������������ĸ߶�
    return ldepth > rdepth ? ++ldepth : ++rdepth;//���ؽϸߵ������߶ȼ�1
}

/*������� T �ķ�ï�ȣ����������Ŀ�Ⱥ͸߶ȵĳ˻���*/
int Flourish(BiTree T){
    if(!T){
        printf("��Ϊ��");
        exit(0);
    }
    int maxwidth, width, nextwidth, i;//maxwidth��ʾ�����, width��ʾ��ǰ���, nextwidth��ʾ��һ����, i����������ǰ������н��
    maxwidth = width = 1;
    Queue Q;
    Q.front = Q.rear = NULL;//���岢��ʼ��һ������������α�����
    BiTNode *p;
    EnQueue(&Q, T);//��������
    i = nextwidth = 0;
    while(Q.front){//��������Ԫ��
        if(i < width){//���ǵ�ǰ������һ�����
            p = DeQueue(&Q);//�ý�����
            i++;
            if(p->lchild)
            {
                EnQueue(&Q, p->lchild);
                nextwidth++;
            }
            if(p->rchild)
            {
                EnQueue(&Q, p->rchild);
                nextwidth++;
            }//�����ҽڵ�ֱ���Ӳ���Ӧ������һ��Ŀ��
        }
        else{//��ʾ��ǰ���ѭ���Ѿ�����
            maxwidth = (maxwidth > width) ? maxwidth : width;//��������ȵ�ֵ
            width = nextwidth;//��ǰ�����Ϊ��һ���ȣ�׼��������һ��ı���
            nextwidth = 0;
            i = 0;//���������ʼ��
        }
    }
    return maxwidth * Depth(T);
}

/*ɾ����TΪ������*/
void Delete_Whole_Tree(BiTree T){
    if(T){//�ж�T�Ƿ�Ϊ��
        Delete_Whole_Tree(T->lchild);
        Delete_Whole_Tree(T->rchild);//�ݹ�ɾ��T����������
        free(T);//�ͷŸýڵ�ռ�
    }
}

/*���ڶ����� T ��ÿһ��Ԫ��ֵΪ x �Ľ�㣬ɾȥ����Ϊ�������������ͷ���Ӧ�Ŀռ�*/
BiTNode *Delete_x(BiTree T, int x){
    if(!T){
        printf("��Ϊ��");
        exit(0);
    }
    if(T->data == x){
        Delete_Whole_Tree(T);
        return NULL;//�����ǰ�ڵ��Ԫ��Ϊx����ɾȥ�Ե�ǰ�ڵ�Ϊ�������������ؿ�ָ����丸�ڵ�
    }
    if(T->lchild) T->lchild = Delete_x(T->lchild, x);
    if(T->rchild) T->rchild = Delete_x(T->rchild, x);//�ݹ鴦������������
    return T;//�����ǰ�ڵ��Ԫ�ز�Ϊx�����������ظ��丸�ڵ�
}

/*������ bt �в���ֵΪ x �Ľ�㣨������һ��������ӡֵΪ x �Ľ�����������*/
int Search_x(BiTree bt, int x){//����ֵΪ1��ʾ����ڵ���ֵΪx�Ľڵ���������ȣ�Ϊ0��ʾ����
    if(!bt) return 0;//ָ��Ϊ�գ���ʾ�Ѿ����ҵ���ײ㣬����0
    if(bt->data == x) return 1;//����1����ʾ�ҵ�ֵΪx�Ľڵ�
    if(Search_x(bt->lchild,  x)){
        printf("%d ", bt->data);
        return 1;
    }
    if(Search_x(bt->rchild, x)){
        printf("%d ", bt->data);
        return 1;
    }//�ݹ��������������������������������ҵ�ֵΪx�Ľڵ㣬��ǰ�ڵ�����Ҫ��ӡ�����ȣ����ҷ���1
    else return 0;
}



int main()
{
    BiTree T;
    T = CreateBiTree();
    int f = Flourish(T);
    printf("%d", f);
   // int x;
   // scanf("%d", &x);
   /* T = Delete_x(T, x);
    if(T) PreOrderTraverse_Print(T);
    else printf("��Ϊ��");*/
   // Search_x(T, x);

    return 0;
}

