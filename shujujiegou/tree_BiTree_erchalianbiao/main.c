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

/*先序建立二叉树*/
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

/*先序输出二叉树*/
void PreOrderTraverse_Print(BiTree T){
    printf("%d ", T->data);
    if(T->lchild) PreOrderTraverse_Print(T->lchild);
    if(T->rchild) PreOrderTraverse_Print(T->rchild);
}


/*入队*/
void EnQueue(Queue *Q, BiTNode *bt){
    QNode *p = (QNode*)malloc(sizeof(QNode));
    p->bt = bt;
    p->next = NULL;//申请内存，存入信息并将节点指针域置空

    if(!Q->front){
        Q->front = p;//如果队列为空，则需修改队头指针
        Q->rear = p;
    }
    else{
        Q->rear->next = p;
        Q->rear = p;//修改队尾指针
    }
}

/*出队*/
BiTNode* DeQueue(Queue *Q){
    if(!Q->front){
        printf("队列为空");
        exit(1);
    }
    BiTNode *p = Q->front->bt;
    Q->front = Q->front->next;
    return p;
}

/*判断队列是否为空*/
int QueueEmpty(Queue *Q){
    if(!Q->front)return 1;
    else return 0;
}

/*求树的高度*/
int Depth(BiTree T){
    if(!T) return 0;//终止条件，空指针表示访问到最底层
    int ldepth, rdepth;
    ldepth = Depth(T->lchild);
    rdepth = Depth(T->rchild);//递归求左右子树的高度
    return ldepth > rdepth ? ++ldepth : ++rdepth;//返回较高的子树高度加1
}

/*求二叉树 T 的繁茂度（即二叉树的宽度和高度的乘积）*/
int Flourish(BiTree T){
    if(!T){
        printf("树为空");
        exit(0);
    }
    int maxwidth, width, nextwidth, i;//maxwidth表示最大宽度, width表示当前宽度, nextwidth表示下一层宽度, i用来遍历当前层的所有结点
    maxwidth = width = 1;
    Queue Q;
    Q.front = Q.rear = NULL;//定义并初始化一个队列用来层次遍历树
    BiTNode *p;
    EnQueue(&Q, T);//根结点入队
    i = nextwidth = 0;
    while(Q.front){//队列中有元素
        if(i < width){//不是当前层的最后一个结点
            p = DeQueue(&Q);//该结点出队
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
            }//将左右节点分别入队并相应计入下一层的宽度
        }
        else{//表示当前层的循环已经结束
            maxwidth = (maxwidth > width) ? maxwidth : width;//更新最大宽度的值
            width = nextwidth;//当前宽度设为下一层宽度，准备进行下一层的遍历
            nextwidth = 0;
            i = 0;//其余变量初始化
        }
    }
    return maxwidth * Depth(T);
}

/*删除以T为根的树*/
void Delete_Whole_Tree(BiTree T){
    if(T){//判断T是否为空
        Delete_Whole_Tree(T->lchild);
        Delete_Whole_Tree(T->rchild);//递归删除T的左右子树
        free(T);//释放该节点空间
    }
}

/*对于二叉树 T 中每一个元素值为 x 的结点，删去以它为根的子树，并释放相应的空间*/
BiTNode *Delete_x(BiTree T, int x){
    if(!T){
        printf("树为空");
        exit(0);
    }
    if(T->data == x){
        Delete_Whole_Tree(T);
        return NULL;//如果当前节点的元素为x，则删去以当前节点为根的子树并返回空指针给其父节点
    }
    if(T->lchild) T->lchild = Delete_x(T->lchild, x);
    if(T->rchild) T->rchild = Delete_x(T->rchild, x);//递归处理其左右子树
    return T;//如果当前节点的元素不为x，则将其自身返回给其父节点
}

/*二叉树 bt 中查找值为 x 的结点（不多于一个），打印值为 x 的结点的所有祖先*/
int Search_x(BiTree bt, int x){//返回值为1表示传入节点是值为x的节点或者其祖先，为0表示不是
    if(!bt) return 0;//指针为空，表示已经查找到最底层，返回0
    if(bt->data == x) return 1;//返回1，表示找到值为x的节点
    if(Search_x(bt->lchild,  x)){
        printf("%d ", bt->data);
        return 1;
    }
    if(Search_x(bt->rchild, x)){
        printf("%d ", bt->data);
        return 1;
    }//递归查找其左右子树，如果在左右子树中找到值为x的节点，则当前节点是需要打印的祖先，并且返回1
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
    else printf("树为空");*/
   // Search_x(T, x);

    return 0;
}

