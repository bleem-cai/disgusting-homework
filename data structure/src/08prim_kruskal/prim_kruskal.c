#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX         100                 // 矩阵最大容量
#define INF         10000               // 最大值
#define isLetter(a) ((((a)>='a')&&((a)<='z')) || (((a)>='A')&&((a)<='Z')))
#define LENGTH(a)   (sizeof(a)/sizeof(a[0]))

// 邻接矩阵
typedef struct _graph {
    char vexs[MAX];       // 顶点集合
    int vexnum;           // 顶点数
    int edgnum;           // 边数
    int matrix[MAX][MAX]; // 邻接矩阵
} Graph;

// 边的结构体
typedef struct _EdgeData {
    char start; // 边的起点
    char end;   // 边的终点
    int weight; // 边的权重
} EData;


/*
 * 返回ch在matrix矩阵中的位置
 */
static int get_position(Graph G, char ch) {
    int i;
    for (i = 0; i < G.vexnum; i++)
        if (G.vexs[i] == ch)
            return i;
    return -1;
}

/*
 * 读取一个输入字符
 */
static char read_char() {
    char ch;

    do {
        ch = getchar();
    } while (!isLetter(ch));

    return ch;
}

/*
 * 创建图(输入)
 */
Graph *create_graph() {
    char c1, c2;
    int v, e;
    int i, j, weight, p1, p2;
    Graph *pG;

    // 输入"顶点数"和"边数"
    printf("input vertex number: ");
    scanf("%d", &v);
    printf("input edge number: ");
    scanf("%d", &e);
    if (v < 1 || e < 1 || (e > (v * (v - 1)))) {
        printf("input error: invalid parameters!\n");
        return NULL;
    }

    if ((pG = (Graph *) malloc(sizeof(Graph))) == NULL)
        return NULL;
    memset(pG, 0, sizeof(Graph));

    // 初始化"顶点数"和"边数"
    pG->vexnum = v;
    pG->edgnum = e;
    // 初始化"顶点"
    for (i = 0; i < pG->vexnum; i++) {
        printf("vertex(%d): ", i);
        pG->vexs[i] = read_char();
    }

    // 1. 初始化"边"的权值
    for (i = 0; i < pG->vexnum; i++) {
        for (j = 0; j < pG->vexnum; j++) {
            if (i == j)
                pG->matrix[i][j] = 0;
            else
                pG->matrix[i][j] = INF;
        }
    }
    // 2. 初始化"边"的权值: 根据用户的输入进行初始化
    for (i = 0; i < pG->edgnum; i++) {
        // 读取边的起始顶点，结束顶点，权值
        printf("edge(%d):", i);
        c1 = read_char();
        c2 = read_char();
        scanf("%d", &weight);

        p1 = get_position(*pG, c1);
        p2 = get_position(*pG, c2);
        if (p1 == -1 || p2 == -1) {
            printf("input error: invalid edge!\n");
            free(pG);
            return NULL;
        }

        pG->matrix[p1][p2] = weight;
        pG->matrix[p2][p1] = weight;
    }

    return pG;
}

/*
 * 创建图(示例)
 */
Graph *create_example_graph() {
    char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    int matrix[][9] = {
            /*A*//*B*//*C*//*D*//*E*//*F*//*G*/
            /*A*/ {0,   12,  INF, INF, INF, 16, 14},
            /*B*/
                  {12,  0,   10,  INF, INF, 7, INF},
            /*C*/
                  {INF, 10,  0, 3,     5,   6, INF},
            /*D*/
                  {INF, INF, 3, 0,     4, INF, INF},
            /*E*/
                  {INF, INF, 5, 4,     0,   2,  8},
            /*F*/
                  {16,  7,   6,   INF, 2,   0,  9},
            /*G*/
                  {14,  INF, INF, INF, 8,   9,  0}};
    int vlen = LENGTH(vexs);
    int i, j;
    Graph *pG;

    // 输入"顶点数"和"边数"
    if ((pG = (Graph *) malloc(sizeof(Graph))) == NULL)
        return NULL;
    memset(pG, 0, sizeof(Graph));

    // 初始化"顶点数"
    pG->vexnum = vlen;
    // 初始化"顶点"
    for (i = 0; i < pG->vexnum; i++)
        pG->vexs[i] = vexs[i];

    // 初始化"边"
    for (i = 0; i < pG->vexnum; i++)
        for (j = 0; j < pG->vexnum; j++)
            pG->matrix[i][j] = matrix[i][j];

    // 统计边的数目
    for (i = 0; i < pG->vexnum; i++)
        for (j = 0; j < pG->vexnum; j++)
            if (i != j && pG->matrix[i][j] != INF)
                pG->edgnum++;
    pG->edgnum /= 2;

    return pG;
}

/*
 * 打印矩阵队列图
 */
void print_graph(Graph G) {
    int i, j;

    printf("Martix Graph:\n");
    for (i = 0; i < G.vexnum; i++) {
        for (j = 0; j < G.vexnum; j++)
            printf("%10d ", G.matrix[i][j]);
        printf("\n");
    }
}

/*
 * prim最小生成树
 *
 * 参数说明：
 *       G -- 邻接矩阵图
 *   start -- 从图中的第start个元素开始，生成最小树
 */
void prim(Graph G, int start) {
    int min, i, j, k, m, n, sum;
    int index = 0;         // prim最小树的索引，即prims数组的索引
    char prims[MAX];     // prim最小树的结果数组
    int weights[MAX];    // 顶点间边的权值

    // prim最小生成树中第一个数是"图中第start个顶点"，因为是从start开始的。
    prims[index++] = G.vexs[start];

    // 初始化"顶点的权值数组"，
    // 将每个顶点的权值初始化为"第start个顶点"到"该顶点"的权值。
    for (i = 0; i < G.vexnum; i++)
        weights[i] = G.matrix[start][i];
    // 将第start个顶点的权值初始化为0。
    // 可以理解为"第start个顶点到它自身的距离为0"。
    weights[start] = 0;

    for (i = 0; i < G.vexnum; i++) {
        // 由于从start开始的，因此不需要再对第start个顶点进行处理。
        if (start == i)
            continue;

        j = 0;
        k = 0;
        min = INF;
        // 在未被加入到最小生成树的顶点中，找出权值最小的顶点。
        while (j < G.vexnum) {
            // 若weights[j]=0，意味着"第j个节点已经被排序过"(或者说已经加入了最小生成树中)。
            if (weights[j] != 0 && weights[j] < min) {
                min = weights[j];
                k = j;
            }
            j++;
        }

        // 经过上面的处理后，在未被加入到最小生成树的顶点中，权值最小的顶点是第k个顶点。
        // 将第k个顶点加入到最小生成树的结果数组中
        prims[index++] = G.vexs[k];
        // 将"第k个顶点的权值"标记为0，意味着第k个顶点已经排序过了(或者说已经加入了最小树结果中)。
        weights[k] = 0;
        // 当第k个顶点被加入到最小生成树的结果数组中之后，更新其它顶点的权值。
        for (j = 0; j < G.vexnum; j++) {
            // 当第j个节点没有被处理，并且需要更新时才被更新。
            if (weights[j] != 0 && G.matrix[k][j] < weights[j])
                weights[j] = G.matrix[k][j];
        }
    }

    // 计算最小生成树的权值
    sum = 0;
    for (i = 1; i < index; i++) {
        min = INF;
        // 获取prims[i]在G中的位置
        n = get_position(G, prims[i]);
        // 在vexs[0...i]中，找出到j的权值最小的顶点。
        for (j = 0; j < i; j++) {
            m = get_position(G, prims[j]);
            if (G.matrix[m][n] < min)
                min = G.matrix[m][n];
        }
        sum += min;
    }
    // 打印最小生成树
    printf("PRIM(%c)=%d: ", G.vexs[start], sum);
    for (i = 0; i < index; i++)
        printf("%c ", prims[i]);
    printf("\n");
}

/*
 * 获取图中的边
 */
EData *get_edges(Graph G) {
    int i, j;
    int index = 0;
    EData *edges;

    edges = (EData *) malloc(G.edgnum * sizeof(EData));
    for (i = 0; i < G.vexnum; i++) {
        for (j = i + 1; j < G.vexnum; j++) {
            if (G.matrix[i][j] != INF) {
                edges[index].start = G.vexs[i];
                edges[index].end = G.vexs[j];
                edges[index].weight = G.matrix[i][j];
                index++;
            }
        }
    }

    return edges;
}

/*
 * 对边按照权值大小进行排序(由小到大)
 */
void sorted_edges(EData *edges, int elen) {
    int i, j;

    for (i = 0; i < elen; i++) {
        for (j = i + 1; j < elen; j++) {
            if (edges[i].weight > edges[j].weight) {
                // 交换"第i条边"和"第j条边"
                EData tmp = edges[i];
                edges[i] = edges[j];
                edges[j] = tmp;
            }
        }
    }
}

/*
 * 获取i的终点
 */
int get_end(int vends[], int i) {
    while (vends[i] != 0)
        i = vends[i];
    return i;
}

/*
 * 克鲁斯卡尔（Kruskal)最小生成树
 */
void kruskal(Graph G) {
    int i, m, n, p1, p2;
    int length;
    int index = 0;          // rets数组的索引
    int vends[MAX] = {0};     // 用于保存"已有最小生成树"中每个顶点在该最小树中的终点。
    EData rets[MAX];        // 结果数组，保存kruskal最小生成树的边
    EData *edges;           // 图对应的所有边

    // 获取"图中所有的边"
    edges = get_edges(G);
    // 将边按照"权"的大小进行排序(从小到大)
    sorted_edges(edges, G.edgnum);

    for (i = 0; i < G.edgnum; i++) {
        p1 = get_position(G, edges[i].start);   // 获取第i条边的"起点"的序号
        p2 = get_position(G, edges[i].end);     // 获取第i条边的"终点"的序号

        m = get_end(vends, p1);                 // 获取p1在"已有的最小生成树"中的终点
        n = get_end(vends, p2);                 // 获取p2在"已有的最小生成树"中的终点
        // 如果m!=n，意味着"边i"与"已经添加到最小生成树中的顶点"没有形成环路
        if (m != n) {
            vends[m] = n;                       // 设置m在"已有的最小生成树"中的终点为n
            rets[index++] = edges[i];           // 保存结果
        }
    }
    free(edges);

    // 统计并打印"kruskal最小生成树"的信息
    length = 0;
    for (i = 0; i < index; i++)
        length += rets[i].weight;
    printf("Kruskal=%d: ", length);
    for (i = 0; i < index; i++)
        printf("(%c,%c) ", rets[i].start, rets[i].end);
    printf("\n");
}

int main() {
    Graph *pG;
//    pG=create_graph();
    pG = create_example_graph();
    print_graph(*pG);
    prim(*pG, 0);           // prim算法生成最小生成树
    kruskal(*pG);             // kruskal算法生成最小生成树
}