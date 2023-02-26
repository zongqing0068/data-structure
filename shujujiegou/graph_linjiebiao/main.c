#include <stdio.h>
#include <stdlib.h>
#define Max_Vertex_Num 100//ͼ�ж�����Ŀ���ֵ
#define false 0
#define true 1

typedef int DataType;

typedef struct
{
    DataType data[Max_Vertex_Num];
    int top; // ջ��ָ��
} Stack;//��������������ջ


typedef struct ArcNode{
    int adjvex;//�ñ���ָ��Ľ��
    struct ArcNode *nextarc;//ָ����һ���ߵ�ָ��
}ArcNode;//�߽��

typedef struct VNode{
    int data;//������Ϣ
    ArcNode *firstarc;//ָ�������ڸö���ĵ�һ���ߵ�ָ��
}VNode, AdjList[Max_Vertex_Num];//�����㣬�����

typedef struct{
    AdjList vertices;//�ڽӱ�
    int vexnum, arcnum;//������������
}ALGraph;


void InitStack(Stack *s);
int StackEmpty(Stack S);
int Push(Stack *s, DataType e);
int Pop(Stack *S, DataType *e);
void Visit(ALGraph g, int v);
void CreatGraph(ALGraph *g);
void DFS(ALGraph g, int v);
void FindSimplePath_u_v(ALGraph g, int u, int v);
int FindSimplePath_w_v(ALGraph g, int path[], int visited[], int w, int v, int len);


/**
 * ��ʼ��һ��ջ
 * @param S
 */
void InitStack(Stack *s)
{
    s->top = -1;
}

/**
 * �ж�ջ�Ƿ�գ�Ϊ�շ���1�����򷵻�0
 * @param S
 * @return
 */
int StackEmpty(Stack S)
{
    if(S.top == -1) return 1;
    else return 0;
}

/**
 * ��ջ����һ��Ԫ��
 * @param S ����ջ
 * @param e ������
 * @return �ɹ�����1�����򷵻�0
 */
int Push(Stack *s, DataType e)
{
    if(s->top == Max_Vertex_Num - 1) return 0;
    else {
        s->top++;
        s->data[s->top] = e;
        return 1;
    }
}

/**
 * ��ջ�е���һ��Ԫ��
 * @param S ����ջ
 * @param e ����ջ������ֵ
 * @return �ɹ�����1�����򷵻�0
 */
int Pop(Stack *S, DataType *e)
{
    if(StackEmpty(*S)) return 0;
    else {
        *e = S->data[S->top];
        S->top--;
        return 1;
    }
}

/**
 * ���ʵ�ǰ����
 * @param v ��ǰ����
 * @return void
 */
void Visit(ALGraph g, int v){
     printf("%d ", g.vertices[v].data);
     return;
 }

/**
 * ���ڽӱ���ͼ
 * @param g ָ��ͼ��ָ��
 * @return void
 */
void CreatGraph(ALGraph *g){
     int i, j, k;
     ArcNode *s;
     scanf("%d %d\n", &g->vexnum, &g->arcnum);//���붥����������
     for(i=0; i<g->vexnum; i++){//�洢�������Ϣ
        scanf("%d", &g->vertices[i].data);
        g->vertices[i].firstarc = NULL;
     }
     for(i=0; i<g->arcnum; i++){//�����߱�
        scanf("%d %d", &j, &k);
        s = (ArcNode *)malloc(sizeof(ArcNode));
        s->adjvex = j;
        s->nextarc = g->vertices[k].firstarc;
        g->vertices[k].firstarc = s;
        s = (ArcNode *)malloc(sizeof(ArcNode));
        s->adjvex = k;
        s->nextarc = g->vertices[j].firstarc;
        g->vertices[j].firstarc = s;
     }
     return;
 }


/**
 * ������ȱ����ķǵݹ�ʵ��
 * @param g ͼ
 * @param v ��ʼ����
 * @return void
 */
void DFS(ALGraph g, int v){
    Stack S;
    InitStack(&S);//��ջ����ʵ��
    int visited[Max_Vertex_Num];//��Ƕ����Ƿ��Ѿ������ʹ�
    int i, j;//iΪѭ������,j�洢��ǰ���ʶ���
    ArcNode *k;//k��������ǰ������ڽӶ�����ջ
    for(i=0; i<g.vexnum; i++) visited[i] = false;//��ʼ���������

    Push(&S, v);
    visited[v] = true;//������v��ջ��������ѷ���
    while(!StackEmpty(S)){
        Pop(&S, &j);
        Visit(g, j);//��ջ�ǿգ���ջ��Ԫ�س�ջ������
        k = g.vertices[j].firstarc;
        while(k){//���뵱ǰ�����ڽӲ��һ�δ�����ʹ��Ķ�����ջ
            if(!visited[k->adjvex]){
                Push(&S, k->adjvex);
                visited[k->adjvex] = true;
            }
            k = k->nextarc;
        }
    }
    return;
}

/**
 * �ж϶���u�붥��v֮���Ƿ��м�·��
 * @param g ͼ
 * @param u v ���жϵ�������
 */
void FindSimplePath_u_v(ALGraph g, int u, int v){
    int i;
    int path[Max_Vertex_Num];//�����洢u��v֮��ļ�·��
    int visited[Max_Vertex_Num];//������ǵ�ǰ�����Ƿ񱻷��ʹ�
    for(i=0; i<g.vexnum; i++) visited[i] = false;//��ʼ���������

    if(!FindSimplePath_w_v(g, path, visited, u, v, -1)) printf("u��v֮�䲻���ڼ�·��");
}

/**
 * �жϵ�ǰ����w�붥��v֮���Ƿ��м�·��
 * @param g ͼ
 * @param path �����洢u��v֮��ļ�·��
 * @param visited ������ǵ�ǰ�����Ƿ񱻷��ʹ�
 * @param w v ���жϵ�������
 * @param len ��ǰ·�����ȣ���ʼֵΪ-1��
 * @return �м�·�����򷵻�1��û�У��򷵻�0
 */
int FindSimplePath_w_v(ALGraph g, int path[], int visited[], int w, int v, int len){
    int i, t, flag;//flag��������Ƿ��ҵ���·��
    ArcNode *p;
    path[++len] = w;
    visited[w] = true;//����ǰ�������·���У�����־Ϊ�ѷ���
    flag = 0;

    if(w == v){
        for(i=0; i<=len; i++) printf("%d ", path[i]);
        return 1;
    }//w��v��ͬʱ����ζ���ҵ���·�������·���ϵĶ���

    p = g.vertices[w].firstarc;
    while(p){
        t = p->adjvex;
        if(!visited[t] && !flag)
            flag = FindSimplePath_w_v(g, path, visited, t, v, len);
        p = p->nextarc;
    }//�ݹ�Ѱ���뵱ǰ����������δ�����ʹ��Ķ��㵽����v�ļ�·��
    visited[w] = false;//��ǰѭ�����������½�w���Ϊδ���ʹ����Ա���������·���б�����
    return flag;
}



int main()
{
    ALGraph g;
    CreatGraph(&g);
   // DFS(g, 0);
    FindSimplePath_u_v(g, 1, 4);
    return 0;
}
