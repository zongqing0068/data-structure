#include <stdio.h>
#include <stdlib.h>
#define Max_Vertex_Num 100//图中顶点数目最大值
#define false 0
#define true 1

typedef int DataType;

typedef struct
{
    DataType data[Max_Vertex_Num];
    int top; // 栈顶指针
} Stack;//用来辅助遍历的栈


typedef struct ArcNode{
    int adjvex;//该边所指向的结点
    struct ArcNode *nextarc;//指向下一条边的指针
}ArcNode;//边结点

typedef struct VNode{
    int data;//顶点信息
    ArcNode *firstarc;//指向依附于该顶点的第一条边的指针
}VNode, AdjList[Max_Vertex_Num];//顶点结点，顶点表

typedef struct{
    AdjList vertices;//邻接表
    int vexnum, arcnum;//顶点数，边数
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
 * 初始化一个栈
 * @param S
 */
void InitStack(Stack *s)
{
    s->top = -1;
}

/**
 * 判断栈是否空，为空返回1，否则返回0
 * @param S
 * @return
 */
int StackEmpty(Stack S)
{
    if(S.top == -1) return 1;
    else return 0;
}

/**
 * 向栈插入一个元素
 * @param S 操作栈
 * @param e 操作数
 * @return 成功返回1，否则返回0
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
 * 从栈中弹出一个元素
 * @param S 操作栈
 * @param e 接受栈弹出的值
 * @return 成功返回1，否则返回0
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
 * 访问当前顶点
 * @param v 当前顶点
 * @return void
 */
void Visit(ALGraph g, int v){
     printf("%d ", g.vertices[v].data);
     return;
 }

/**
 * 用邻接表构造图
 * @param g 指向图的指针
 * @return void
 */
void CreatGraph(ALGraph *g){
     int i, j, k;
     ArcNode *s;
     scanf("%d %d\n", &g->vexnum, &g->arcnum);//读入顶点数，边数
     for(i=0; i<g->vexnum; i++){//存储顶点表信息
        scanf("%d", &g->vertices[i].data);
        g->vertices[i].firstarc = NULL;
     }
     for(i=0; i<g->arcnum; i++){//建立边表
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
 * 深度优先遍历的非递归实现
 * @param g 图
 * @param v 起始顶点
 * @return void
 */
void DFS(ALGraph g, int v){
    Stack S;
    InitStack(&S);//用栈辅助实现
    int visited[Max_Vertex_Num];//标记顶点是否已经被访问过
    int i, j;//i为循环变量,j存储当前访问顶点
    ArcNode *k;//k用来将当前顶点的邻接顶点入栈
    for(i=0; i<g.vexnum; i++) visited[i] = false;//初始化标记数组

    Push(&S, v);
    visited[v] = true;//将顶点v入栈，并标记已访问
    while(!StackEmpty(S)){
        Pop(&S, &j);
        Visit(g, j);//若栈非空，则将栈顶元素出栈并访问
        k = g.vertices[j].firstarc;
        while(k){//将与当前顶点邻接并且还未被访问过的顶点入栈
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
 * 判断顶点u与顶点v之间是否有简单路径
 * @param g 图
 * @param u v 待判断的两顶点
 */
void FindSimplePath_u_v(ALGraph g, int u, int v){
    int i;
    int path[Max_Vertex_Num];//用来存储u到v之间的简单路径
    int visited[Max_Vertex_Num];//用来标记当前顶点是否被访问过
    for(i=0; i<g.vexnum; i++) visited[i] = false;//初始化标记数组

    if(!FindSimplePath_w_v(g, path, visited, u, v, -1)) printf("u和v之间不存在简单路径");
}

/**
 * 判断当前顶点w与顶点v之间是否有简单路径
 * @param g 图
 * @param path 用来存储u到v之间的简单路径
 * @param visited 用来标记当前顶点是否被访问过
 * @param w v 待判断的两顶点
 * @param len 当前路径长度（初始值为-1）
 * @return 有简单路径，则返回1；没有，则返回0
 */
int FindSimplePath_w_v(ALGraph g, int path[], int visited[], int w, int v, int len){
    int i, t, flag;//flag用来标记是否找到简单路径
    ArcNode *p;
    path[++len] = w;
    visited[w] = true;//将当前顶点存入路径中，并标志为已访问
    flag = 0;

    if(w == v){
        for(i=0; i<=len; i++) printf("%d ", path[i]);
        return 1;
    }//w和v相同时，意味着找到简单路径，输出路径上的顶点

    p = g.vertices[w].firstarc;
    while(p){
        t = p->adjvex;
        if(!visited[t] && !flag)
            flag = FindSimplePath_w_v(g, path, visited, t, v, len);
        p = p->nextarc;
    }//递归寻找与当前顶点相邻且未被访问过的顶点到顶点v的简单路径
    visited[w] = false;//当前循环结束，重新将w标记为未访问过，以便其在其它路径中被访问
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
