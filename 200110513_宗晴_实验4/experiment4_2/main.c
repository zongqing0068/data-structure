/*----------------------------------------------------------------------------
文件名: experiment4_2
创建人: 宗晴
学号：200110513
日 期: 2021.5.1.
描述：图型结构的应用
主要功能：根据深圳地铁线路图建图，并判断该线路图是否连通；
          求出线路图中换乘线路最多的站点，并求出其换乘线路数；
          求出两站点之间所需的最少时间，并打印推荐路径上的站点名称；
          求出该线路图的直径和半径
------------------------------------------------------------------------------*/

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
int maxLineDegree(Graph g, int *line_degree, int *flag);
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
 * 计算每个点的换乘线路数，并返回换乘线路数最大的顶点编号
 * @param g 图
 * @param node_degree 将每个点的度写到这个数组中
 * @param flag 存储站点为端点站点的次数的数组
 * @return 换乘线路数最大的顶点编号
 */
int maxLineDegree(Graph g, int *line_degree, int *flag){
    int i, j, max_degree, node;//max_degree存储最大换乘线路数, node为换乘线路数最大的顶点
    for(i = 0; i < g.N; i++){//求每个顶点的度
        line_degree[i] = 0;//将每个顶点的度初始化为0
        for(j = 0; j < g.N; j++){
            if(g.matrix[i][j] != max_dis && i != j) line_degree[i]++;//如果两个顶点之间的距离不是无穷大，并且它们是不同的顶点，则将它们的度加一
        }
    }
    for(i = 0; i < g.N; i++){//考虑站点为端点站点的情况
        line_degree[i] += flag[i];
        line_degree[i] /= 2;//求经过的线路数
    }
    max_degree = -1;
    for(i = 0; i < g.N; i++){//寻找换乘线路数最大的顶点
        if(line_degree[i] > max_degree){
            max_degree = line_degree[i];
            node = i;
        }
    }
    return node;//返回换乘线路数最大的顶点
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
    }//首先判断顶点是否存在

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
    path[0] = start;

    //求取最短路径
    while(fixed != end){
        min_len = max_dis;
        for(i=0; i<g.N; i++){//更新最短路径长度
            if(!S[i]){//不在源点集中
                if((len[fixed_p] + g.matrix[fixed_p][i]) < len[i]){
                   len[i] = len[fixed_p] + g.matrix[fixed_p][i];
                   parent[i] = fixed_p;
                }
                if(len[i] < min_len){
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
}

int main() {
    int node_num, line_num, n, num;//node_num为顶点数,line_num为地铁线路数,n为顶点编号,num为每条线路的站点数
    if (freopen("no2metro.txt", "r", stdin) == NULL) {
        printf("There is an error in reading file no2metro.txt");
    }
    scanf("%d\n", &node_num);
    int start_idx, end_idx, time;//起始站点，终止站点，两站点之间的时间
    int *flag = (int *)malloc(node_num * sizeof(int));//标记站点是端点站点的次数
    for(int i = 0; i < node_num; i++){
        flag[i] = 0;
    }
    Graph g = createGraph(node_num);
    for(int i = 0; i < node_num; i++){
        scanf("%d", &n);
        scanf("%s", &g.vertex[n]);
    }//存储站点编号及名称
    if (freopen("metro.txt", "r", stdin) == NULL) {
        printf("There is an error in reading file metro.txt");
    }
    scanf("%d\n%d", &node_num, &line_num);
    for (int i = 0; i < line_num; i++){
        scanf("%d", &num);
        scanf("%d %d", &start_idx, &time);
        flag[start_idx]++;//标记起始站点
        for(int j = 1; j < num; j++){
            scanf("%d %d", &end_idx, &time);
            g.matrix[start_idx][end_idx] = time;
            g.matrix[end_idx][start_idx] = time;
            start_idx = end_idx;
        }
        flag[end_idx]++;//标记终止站点
    }//存储每条线路的信息

    if(isConnected(g)) printf("该线路图连通\n");//判断该线路图是否连通
    else printf("该线路图不连通\n");

    int *degree = (int *)malloc(sizeof(int) * g.N);
    int max_node;//存储度换乘线路数最大的顶点
    max_node = maxLineDegree(g, degree, flag);
    printf("线路图中换乘线路最多的站点是：%s，共有%d条线路通过\n", g.vertex[max_node], degree[max_node]);
    free(degree);

    if(isConnected(g))
    {
        int *short_path = (int *)malloc(sizeof(int) * g.N);
        int start, end;//存储起始站点
        for(int i = 0; i < g.N; i++){//找到“大学城”和“机场”站点的编号
            if(strcmp(g.vertex[i], "大学城") == 0) start = i;
            if(strcmp(g.vertex[i], "机场") == 0) end = i;
        }
        int dis = dijkstra(g, start, end, short_path);
        printf("从大学城站到机场站最少需要%d分钟\n推荐路径：", dis);
        printPath(dis, short_path, g);//寻找最短路径长度，并打印最短路径上的站点名称
        free(short_path);

        int diameter, radius;
        computeEcc(g, &diameter, &radius);//计算图的直径和半径
        printf("diameter:%d\n", diameter);
        printf("radius:%d\n", radius);
    }

    return 0;
}
