/*--------------------------------------------------------------------------------------
文件名: experiment4_1
创建人: 宗晴
学号：200110513
日 期: 2021.5.1.
描述：图型结构
主要功能：构建无向图、计算图的聚类系数、求两结点之间的单源最短路径、计算图的直径和半径
---------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define max_dis 100000

typedef char vextype[20];
typedef struct {
    int N, E;//N是顶点数，E是边数
    int **matrix;//储存邻接矩阵
    vextype *vertex;//存储节点的名字
} Graph;


Graph createGraph(int n);
int isConnected(Graph g);
void nodeDegree(Graph g, int *node_degree);
double clusteringCoefficient(Graph g);
void computeEcc(Graph g, int *diameter, int *radius);
int dijkstra(Graph g, int start, int end, int *path);
void printPath(int d, int *diameter_path, Graph g);
void DFS(Graph g, int *visit, int v);

/**
 * 创建一个节点数为n的图
 * @param n 节点个数
 * @return 返回这个图
 */
Graph createGraph(int n) {
    int i, j;
    Graph g;
    g.N = n;
    g.matrix = (int **) malloc(sizeof(int *) * g.N);
    for (i = 0; i < n; i++) {
        g.matrix[i] = (int *) malloc(sizeof(int) * g.N);
    }
    for (i = 0; i < g.N; i++) {
        for (j = 0; j < g.N; j++) {
            g.matrix[i][j] = max_dis;
        }
    }
    for (i = 0; i < g.N; i++) {
        g.matrix[i][i] = 0;
    }
    g.vertex = (vextype *) malloc(sizeof(vextype) * g.N);
    return g;
}

/**
 * 根据距离d和路径数组path输出路径，这样就不需要路径的节点数也能正确输出路径
 * @param d 路径长度
 * @param path 储存路径的数组
 * @param g 图
 */
void printPath(int d, int *path, Graph g)
{
    int k = 0;
    int path_length = 0;
    printf("Path: ");
    do {
        printf("%s ", g.vertex[path[k]]);
        path_length += g.matrix[path[k]][path[k + 1]];
        k++;
    } while (path_length < d);
    printf("%s\n", g.vertex[path[k]]);
}

/**
 * 判断图是否连通
 * @param g 图
 * @return 连通返回1，否则返回0
 */
int isConnected(Graph g) {
    int *visit = (int *)malloc(g.N * sizeof(int));//申请visit数组用来标记顶点是否已经被访问过
    int i;
    for(i = 0; i < g.N; i++) visit[i] = 0;
    DFS(g, visit, 0);//从第0个顶点开始深度优先遍历该图
    for(i = 0; i < g.N; i++){
        if(visit[i] == 0){
            free(visit);
            return 0;//若遍历结束后仍有顶点未被访问，则说明该图不连通，返回0
        }
    }
    free(visit);
    return 1;//否则说明该图连通，返回1
    //TODO
}

/**
 * 深度优先遍历
 * @param g 图
 * @param visit 标记已访问顶点的数组
 * @param v 当前顶点
 */
void DFS(Graph g, int *visit, int v){
    visit[v] = 1;//将当前顶点标记为已访问
    int i;
    for(i = 0; i < g.N; i++){
        if(g.matrix[v][i] != max_dis && visit[i] == 0){//继续深度优先遍历相邻顶点中未被访问过的顶点
            DFS(g, visit, i);
        }
    }
}

/**
 * 计算每个点的度
 * @param g 图
 * @param node_degree 将每个点的度写到这个数组中
 */
void nodeDegree(Graph g, int *node_degree) {
    int i, j;
    for(i = 0; i < g.N; i++){
        node_degree[i] = 0;//将每个顶点的度初始化为0
        for(j = 0; j < g.N; j++){
            if(g.matrix[i][j] != max_dis && i != j) node_degree[i]++;//如果两个顶点之间的距离不是无穷大，并且它们是不同的顶点，则将它的度加一
        }
    }
    //TODO
}

/**
 * 计算图的聚类系数
 * @param g 图
 * @return 返回聚类系数
 */
double clusteringCoefficient(Graph g) {
    double CC = 0;//存储无向图的聚类系数
    double *LCC = (double *)malloc(g.N * sizeof(double));//用来存储每个顶点的聚类系数
    int *neighbour = (int *)malloc(g.N * sizeof(int));//用来存储与当前顶点相邻的顶点编号
    int counter, pairs;//counter用来记录与当前顶点相邻的顶点个数，pairs用来记录与它相邻的顶点之间所连的边数
    int i, j, m, n;

    for(i=0; i<g.N; i++){
        counter = pairs = 0;
        for(j=0; j<g.N; j++){//求与当前顶点相邻的顶点个数，并把它们存储在neighbour数组中
            if(g.matrix[i][j] != max_dis && i != j) neighbour[counter++] = j;
        }
        for(m=0; m<counter; m++){//求与当前顶点相邻的顶点之间所连的边数
            for(n=m+1; n<counter; n++){
                if(g.matrix[neighbour[m]][neighbour[n]] != max_dis) pairs++;
            }
        }
        if (counter == 0 || counter == 1) LCC[i] = 0;//度为0或1时，聚类系数均为0
        else LCC[i] = (double)pairs * 2 / counter / (counter - 1);//求出每个顶点的聚类系数（需要强转）
    }
    for(i=0; i<g.N; i++) CC += LCC[i];
    CC /= g.N;//求取平均值，得整张图的聚类系数

    free(LCC);
    free(neighbour);

    return CC;
    //TODO
}

/**
 * 使用dijkstra算法计算单源最短路径
 * @param g 图
 * @param start 起点
 * @param end 终点
 * @param path 从start到end的路径, [start,...,end]
 * @return 路径长度
 */
int dijkstra(Graph g, int start, int end, int *path)
{
    if(g.N < start + 1 || g.N < end + 1){
        printf("不存在该顶点");
        exit(0);
    }//首先判断顶点是否存在（增强健壮性）

    int i, fixed, fixed_p, min_len, num;
    //fixed用来固定每轮循环确定的最小路径的顶点,fixed_p存储上一轮循环固定的顶点,min_len存储每轮循环求得的最短路径,num存储所求路径上的顶点个数
    int *S = (int *)malloc(g.N * sizeof(int));//源点集，值为1表示在源点集中，为0表示不在
    int *len = (int *)malloc(g.N * sizeof(int));//存储源点到各点的最短路径长度
    int *parent = (int *)malloc(g.N * sizeof(int));//存储最短路径中该顶点的前一个顶点，用来回溯以便找到路径
    int *temp = (int *)malloc(g.N * sizeof(int));;//将路径上的顶点转移到path数组中

    //初始化数组及变量
    for(i=0; i<g.N; i++){
        S[i] = 0;
        len[i] = max_dis;
    }
    S[start] = 1;
    len[start] = 0;
    fixed = fixed_p = start;

    //求取最短路径
    while(fixed != end){
        min_len = max_dis;
        for(i=0; i<g.N; i++){
            if(!S[i]){//不在源点集中
                if((len[fixed_p] + g.matrix[fixed_p][i]) < len[i]){//对于不在源点集中的顶点，更新它到源点的最短路径长度
                   len[i] = len[fixed_p] + g.matrix[fixed_p][i];
                   parent[i] = fixed_p;//将前驱存入parent数组中
                }
                if(len[i] < min_len){//找出不在源点集中的顶点中，与始点的最短路径长度最短的顶点
                    min_len = len[i];
                    fixed = i;
                }
            }
        }
        S[fixed] = 1;
        fixed_p = fixed;
    }

    //通过parent数组回溯找到最短路径
    num = 1;
    i = end;
    temp[0] = end;
    while(parent[i] != start){
        i = temp[num++] = parent[i];
    }
    temp[num++] = start;

    //将逆序的路径正向存储到path数组中
    for(i=0; i<num; i++){
        path[i] = temp[num - 1 - i];
    }

    free(S);
    free(len);
    free(parent);
    free(temp);

    return len[end];
    //TODO
}

/**
 * 计算图的直径和半径，提示: Floyd算法
 * @param g 图
 * @param diameter 指向直径变量的指针
 * @param radius 指向半径变量的指针
 * @return void
 */
void computeEcc(Graph g, int *diameter, int *radius)
{
    int i, j, k, max_d;//max_d存储节点距离的最大值
    int *eccentricity = (int *)malloc(g.N * sizeof(int));//存储每个顶点的离心率
    int *distance = (int *)malloc(g.N * g.N * sizeof(int));//存储两个顶点之间的最短路径长度
    for(i=0; i<g.N; i++){
        for(j=0; j<g.N; j++) distance[i * g.N + j] = g.matrix[i][j];
    }//将原矩阵复制到最短路径长度矩阵中

    for(k=0; k<g.N; k++){//依次添加可允许经过的顶点，更新最短路径长度
        for(i=0; i<g.N; i++){
            for(j=0; j<g.N; j++){
                if(distance[i * g.N + k] + distance[k * g.N + j] < distance[i * g.N + j]) distance[i * g.N + j] = distance[i * g.N + k] + distance[k * g.N + j];
            }
        }
    }

    for(i=0; i<g.N; i++){//求每个顶点的离心率
        max_d = 0;
        for(j=0; j<g.N; j++){
            if(distance[i * g.N + j] > max_d) max_d = distance[i * g.N + j];
        }
        eccentricity[i] = max_d;
    }

    *diameter = 0;
    *radius = max_dis;
    for(i=0; i<g.N; i++){//求图的直径和半径
        if(eccentricity[i] > *diameter) *diameter = eccentricity[i];
        if(eccentricity[i] < *radius) *radius = eccentricity[i];
    }

    free(eccentricity);
    free(distance);

    //TODO
}

int main() {
    int node_num;
    int edge_num;
    int ca = 1;
    if (freopen("stu.in", "r", stdin) == NULL) {
        printf("There is an error in reading file stu.in");
    }
    while (scanf("%d %d\n", &node_num, &edge_num) != EOF) {
        printf("\ncase %d:\n", ca++);
        int start_idx, end_idx, weight;
        Graph g = createGraph(node_num);
        for(int i = 0; i < node_num; i++) {
            sprintf(g.vertex[i], "%d", i);
        }
        for (int i = 0; i < edge_num; i++) {
            scanf("%d %d %d\n", &start_idx, &end_idx, &weight);
            g.matrix[start_idx][end_idx] = weight;
            g.matrix[end_idx][start_idx] = weight;
        }

        printf("connected: %d\n", isConnected(g));

        int *degree = (int *)malloc(sizeof(int) * g.N);
        nodeDegree(g, degree);
        printf("degree distribution:\n");
        for(int i=0; i<g.N; i++)
        {
            printf("node%s:%d,", g.vertex[i], degree[i]);
        }
        printf("\n");
        free(degree);

        double c = clusteringCoefficient(g);
        printf("clustering coefficient:%f\n", c);

        if(isConnected(g))
        {
            int *short_path = (int *)malloc(sizeof(int) * g.N);
            int dis = dijkstra(g, 1, 3, short_path);
            printf("the shortest path between 1 and 3: %d\n", dis);
            printPath(dis, short_path, g);
            free(short_path);

            int diameter, radius;
            computeEcc(g, &diameter, &radius);
            printf("diameter:%d\n", diameter);
            printf("radius:%d\n", radius);
        }
    }

    return 0;
}
