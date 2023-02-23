/*----------------------------------------------------------------------------
�ļ���: experiment4_2
������: ����
ѧ�ţ�200110513
�� ��: 2021.5.1.
������ͼ�ͽṹ��Ӧ��
��Ҫ���ܣ��������ڵ�����·ͼ��ͼ�����жϸ���·ͼ�Ƿ���ͨ��
          �����·ͼ�л�����·����վ�㣬������任����·����
          �����վ��֮�����������ʱ�䣬����ӡ�Ƽ�·���ϵ�վ�����ƣ�
          �������·ͼ��ֱ���Ͱ뾶
------------------------------------------------------------------------------*/

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
int maxLineDegree(Graph g, int *line_degree, int *flag);
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
 * ����ÿ����Ļ�����·���������ػ�����·�����Ķ�����
 * @param g ͼ
 * @param node_degree ��ÿ����Ķ�д�����������
 * @param flag �洢վ��Ϊ�˵�վ��Ĵ���������
 * @return ������·�����Ķ�����
 */
int maxLineDegree(Graph g, int *line_degree, int *flag){
    int i, j, max_degree, node;//max_degree�洢��󻻳���·��, nodeΪ������·�����Ķ���
    for(i = 0; i < g.N; i++){//��ÿ������Ķ�
        line_degree[i] = 0;//��ÿ������Ķȳ�ʼ��Ϊ0
        for(j = 0; j < g.N; j++){
            if(g.matrix[i][j] != max_dis && i != j) line_degree[i]++;//�����������֮��ľ��벻������󣬲��������ǲ�ͬ�Ķ��㣬�����ǵĶȼ�һ
        }
    }
    for(i = 0; i < g.N; i++){//����վ��Ϊ�˵�վ������
        line_degree[i] += flag[i];
        line_degree[i] /= 2;//�󾭹�����·��
    }
    max_degree = -1;
    for(i = 0; i < g.N; i++){//Ѱ�һ�����·�����Ķ���
        if(line_degree[i] > max_degree){
            max_degree = line_degree[i];
            node = i;
        }
    }
    return node;//���ػ�����·�����Ķ���
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
    }//�����ж϶����Ƿ����

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
    path[0] = start;

    //��ȡ���·��
    while(fixed != end){
        min_len = max_dis;
        for(i=0; i<g.N; i++){//�������·������
            if(!S[i]){//����Դ�㼯��
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
}

int main() {
    int node_num, line_num, n, num;//node_numΪ������,line_numΪ������·��,nΪ������,numΪÿ����·��վ����
    if (freopen("no2metro.txt", "r", stdin) == NULL) {
        printf("There is an error in reading file no2metro.txt");
    }
    scanf("%d\n", &node_num);
    int start_idx, end_idx, time;//��ʼվ�㣬��ֹվ�㣬��վ��֮���ʱ��
    int *flag = (int *)malloc(node_num * sizeof(int));//���վ���Ƕ˵�վ��Ĵ���
    for(int i = 0; i < node_num; i++){
        flag[i] = 0;
    }
    Graph g = createGraph(node_num);
    for(int i = 0; i < node_num; i++){
        scanf("%d", &n);
        scanf("%s", &g.vertex[n]);
    }//�洢վ���ż�����
    if (freopen("metro.txt", "r", stdin) == NULL) {
        printf("There is an error in reading file metro.txt");
    }
    scanf("%d\n%d", &node_num, &line_num);
    for (int i = 0; i < line_num; i++){
        scanf("%d", &num);
        scanf("%d %d", &start_idx, &time);
        flag[start_idx]++;//�����ʼվ��
        for(int j = 1; j < num; j++){
            scanf("%d %d", &end_idx, &time);
            g.matrix[start_idx][end_idx] = time;
            g.matrix[end_idx][start_idx] = time;
            start_idx = end_idx;
        }
        flag[end_idx]++;//�����ֹվ��
    }//�洢ÿ����·����Ϣ

    if(isConnected(g)) printf("����·ͼ��ͨ\n");//�жϸ���·ͼ�Ƿ���ͨ
    else printf("����·ͼ����ͨ\n");

    int *degree = (int *)malloc(sizeof(int) * g.N);
    int max_node;//�洢�Ȼ�����·�����Ķ���
    max_node = maxLineDegree(g, degree, flag);
    printf("��·ͼ�л�����·����վ���ǣ�%s������%d����·ͨ��\n", g.vertex[max_node], degree[max_node]);
    free(degree);

    if(isConnected(g))
    {
        int *short_path = (int *)malloc(sizeof(int) * g.N);
        int start, end;//�洢��ʼվ��
        for(int i = 0; i < g.N; i++){//�ҵ�����ѧ�ǡ��͡�������վ��ı��
            if(strcmp(g.vertex[i], "��ѧ��") == 0) start = i;
            if(strcmp(g.vertex[i], "����") == 0) end = i;
        }
        int dis = dijkstra(g, start, end, short_path);
        printf("�Ӵ�ѧ��վ������վ������Ҫ%d����\n�Ƽ�·����", dis);
        printPath(dis, short_path, g);//Ѱ�����·�����ȣ�����ӡ���·���ϵ�վ������
        free(short_path);

        int diameter, radius;
        computeEcc(g, &diameter, &radius);//����ͼ��ֱ���Ͱ뾶
        printf("diameter:%d\n", diameter);
        printf("radius:%d\n", radius);
    }

    return 0;
}
