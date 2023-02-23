/*--------------------------------------------------------------------------------------
�ļ���: experiment4_1
������: ����
ѧ�ţ�200110513
�� ��: 2021.5.1.
������ͼ�ͽṹ
��Ҫ���ܣ���������ͼ������ͼ�ľ���ϵ�����������֮��ĵ�Դ���·��������ͼ��ֱ���Ͱ뾶
---------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define max_dis 100000

typedef char vextype[20];
typedef struct {
    int N, E;//N�Ƕ�������E�Ǳ���
    int **matrix;//�����ڽӾ���
    vextype *vertex;//�洢�ڵ������
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
 * ����һ���ڵ���Ϊn��ͼ
 * @param n �ڵ����
 * @return �������ͼ
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
 * ���ݾ���d��·������path���·���������Ͳ���Ҫ·���Ľڵ���Ҳ����ȷ���·��
 * @param d ·������
 * @param path ����·��������
 * @param g ͼ
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
 * �ж�ͼ�Ƿ���ͨ
 * @param g ͼ
 * @return ��ͨ����1�����򷵻�0
 */
int isConnected(Graph g) {
    int *visit = (int *)malloc(g.N * sizeof(int));//����visit����������Ƕ����Ƿ��Ѿ������ʹ�
    int i;
    for(i = 0; i < g.N; i++) visit[i] = 0;
    DFS(g, visit, 0);//�ӵ�0�����㿪ʼ������ȱ�����ͼ
    for(i = 0; i < g.N; i++){
        if(visit[i] == 0){
            free(visit);
            return 0;//���������������ж���δ�����ʣ���˵����ͼ����ͨ������0
        }
    }
    free(visit);
    return 1;//����˵����ͼ��ͨ������1
    //TODO
}

/**
 * ������ȱ���
 * @param g ͼ
 * @param visit ����ѷ��ʶ��������
 * @param v ��ǰ����
 */
void DFS(Graph g, int *visit, int v){
    visit[v] = 1;//����ǰ������Ϊ�ѷ���
    int i;
    for(i = 0; i < g.N; i++){
        if(g.matrix[v][i] != max_dis && visit[i] == 0){//����������ȱ������ڶ�����δ�����ʹ��Ķ���
            DFS(g, visit, i);
        }
    }
}

/**
 * ����ÿ����Ķ�
 * @param g ͼ
 * @param node_degree ��ÿ����Ķ�д�����������
 */
void nodeDegree(Graph g, int *node_degree) {
    int i, j;
    for(i = 0; i < g.N; i++){
        node_degree[i] = 0;//��ÿ������Ķȳ�ʼ��Ϊ0
        for(j = 0; j < g.N; j++){
            if(g.matrix[i][j] != max_dis && i != j) node_degree[i]++;//�����������֮��ľ��벻������󣬲��������ǲ�ͬ�Ķ��㣬�����Ķȼ�һ
        }
    }
    //TODO
}

/**
 * ����ͼ�ľ���ϵ��
 * @param g ͼ
 * @return ���ؾ���ϵ��
 */
double clusteringCoefficient(Graph g) {
    double CC = 0;//�洢����ͼ�ľ���ϵ��
    double *LCC = (double *)malloc(g.N * sizeof(double));//�����洢ÿ������ľ���ϵ��
    int *neighbour = (int *)malloc(g.N * sizeof(int));//�����洢�뵱ǰ�������ڵĶ�����
    int counter, pairs;//counter������¼�뵱ǰ�������ڵĶ��������pairs������¼�������ڵĶ���֮�������ı���
    int i, j, m, n;

    for(i=0; i<g.N; i++){
        counter = pairs = 0;
        for(j=0; j<g.N; j++){//���뵱ǰ�������ڵĶ���������������Ǵ洢��neighbour������
            if(g.matrix[i][j] != max_dis && i != j) neighbour[counter++] = j;
        }
        for(m=0; m<counter; m++){//���뵱ǰ�������ڵĶ���֮�������ı���
            for(n=m+1; n<counter; n++){
                if(g.matrix[neighbour[m]][neighbour[n]] != max_dis) pairs++;
            }
        }
        if (counter == 0 || counter == 1) LCC[i] = 0;//��Ϊ0��1ʱ������ϵ����Ϊ0
        else LCC[i] = (double)pairs * 2 / counter / (counter - 1);//���ÿ������ľ���ϵ������Ҫǿת��
    }
    for(i=0; i<g.N; i++) CC += LCC[i];
    CC /= g.N;//��ȡƽ��ֵ��������ͼ�ľ���ϵ��

    free(LCC);
    free(neighbour);

    return CC;
    //TODO
}

/**
 * ʹ��dijkstra�㷨���㵥Դ���·��
 * @param g ͼ
 * @param start ���
 * @param end �յ�
 * @param path ��start��end��·��, [start,...,end]
 * @return ·������
 */
int dijkstra(Graph g, int start, int end, int *path)
{
    if(g.N < start + 1 || g.N < end + 1){
        printf("�����ڸö���");
        exit(0);
    }//�����ж϶����Ƿ���ڣ���ǿ��׳�ԣ�

    int i, fixed, fixed_p, min_len, num;
    //fixed�����̶�ÿ��ѭ��ȷ������С·���Ķ���,fixed_p�洢��һ��ѭ���̶��Ķ���,min_len�洢ÿ��ѭ����õ����·��,num�洢����·���ϵĶ������
    int *S = (int *)malloc(g.N * sizeof(int));//Դ�㼯��ֵΪ1��ʾ��Դ�㼯�У�Ϊ0��ʾ����
    int *len = (int *)malloc(g.N * sizeof(int));//�洢Դ�㵽��������·������
    int *parent = (int *)malloc(g.N * sizeof(int));//�洢���·���иö����ǰһ�����㣬���������Ա��ҵ�·��
    int *temp = (int *)malloc(g.N * sizeof(int));;//��·���ϵĶ���ת�Ƶ�path������

    //��ʼ�����鼰����
    for(i=0; i<g.N; i++){
        S[i] = 0;
        len[i] = max_dis;
    }
    S[start] = 1;
    len[start] = 0;
    fixed = fixed_p = start;

    //��ȡ���·��
    while(fixed != end){
        min_len = max_dis;
        for(i=0; i<g.N; i++){
            if(!S[i]){//����Դ�㼯��
                if((len[fixed_p] + g.matrix[fixed_p][i]) < len[i]){//���ڲ���Դ�㼯�еĶ��㣬��������Դ������·������
                   len[i] = len[fixed_p] + g.matrix[fixed_p][i];
                   parent[i] = fixed_p;//��ǰ������parent������
                }
                if(len[i] < min_len){//�ҳ�����Դ�㼯�еĶ����У���ʼ������·��������̵Ķ���
                    min_len = len[i];
                    fixed = i;
                }
            }
        }
        S[fixed] = 1;
        fixed_p = fixed;
    }

    //ͨ��parent��������ҵ����·��
    num = 1;
    i = end;
    temp[0] = end;
    while(parent[i] != start){
        i = temp[num++] = parent[i];
    }
    temp[num++] = start;

    //�������·������洢��path������
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
 * ����ͼ��ֱ���Ͱ뾶����ʾ: Floyd�㷨
 * @param g ͼ
 * @param diameter ָ��ֱ��������ָ��
 * @param radius ָ��뾶������ָ��
 * @return void
 */
void computeEcc(Graph g, int *diameter, int *radius)
{
    int i, j, k, max_d;//max_d�洢�ڵ��������ֵ
    int *eccentricity = (int *)malloc(g.N * sizeof(int));//�洢ÿ�������������
    int *distance = (int *)malloc(g.N * g.N * sizeof(int));//�洢��������֮������·������
    for(i=0; i<g.N; i++){
        for(j=0; j<g.N; j++) distance[i * g.N + j] = g.matrix[i][j];
    }//��ԭ�����Ƶ����·�����Ⱦ�����

    for(k=0; k<g.N; k++){//������ӿ��������Ķ��㣬�������·������
        for(i=0; i<g.N; i++){
            for(j=0; j<g.N; j++){
                if(distance[i * g.N + k] + distance[k * g.N + j] < distance[i * g.N + j]) distance[i * g.N + j] = distance[i * g.N + k] + distance[k * g.N + j];
            }
        }
    }

    for(i=0; i<g.N; i++){//��ÿ�������������
        max_d = 0;
        for(j=0; j<g.N; j++){
            if(distance[i * g.N + j] > max_d) max_d = distance[i * g.N + j];
        }
        eccentricity[i] = max_d;
    }

    *diameter = 0;
    *radius = max_dis;
    for(i=0; i<g.N; i++){//��ͼ��ֱ���Ͱ뾶
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
