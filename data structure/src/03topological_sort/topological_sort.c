#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// 邻接表中表对应的链表的顶点
typedef struct edge_node {
    int vertex_num;             // 该边所指向的顶点的位置
    struct edge_node *next;     // 指向下一条弧的指针
} edge_node;

// 邻接表中表的顶点
typedef struct vertex_node {
    int data;                   // 顶点数据
    edge_node *first;           // 指向第一条依附该顶点的弧
} vertex_node;

// 邻接表
typedef struct graph {
    int vertex_number;          // 图的顶点的数目
    int edge_number;            // 图的边的数目
    vertex_node *vex;           // 图的顶点数组
} graph;

/*
 * 返回ch在matrix矩阵中的位置
 */
int get_position(graph *gp, int c) {
    for (int i = 0; i < gp->vertex_number; ++i) {
        if (c == gp->vex[i].data)
            return i;
    }
    return -1;
}

/*
 * 将node链接到list的末尾
 */
void list_last(edge_node *first, edge_node *node) {
    edge_node *tmp = first;
    while (tmp->next) {
        tmp = tmp->next;
    }
    tmp->next = node;
}

/*
 * 创建邻接表对应的图
 */
graph *create() {
    graph *gp = (graph *) malloc(sizeof(graph));

    // 输入"顶点数"和"边数"
    printf("vertex number:");
    scanf("%d", &gp->vertex_number);
    printf("edge number:");
    scanf("%d", &gp->edge_number);
    gp->vex = (vertex_node *) malloc(sizeof(vertex_node) * gp->vertex_number);

    // 初始化"邻接表"的顶点
    for (int i = 0; i < gp->vertex_number; ++i) {
        printf("vertex[%d] data:", i);
        scanf("%d", &gp->vex[i].data);
        gp->vex[i].first = NULL;
    }

    // 初始化"邻接表"的边
    for (int i = 0; i < gp->edge_number; ++i) {
        int c1, c2, p1, p2;
        edge_node *node;

        // 读取边的起始顶点和结束顶点
        printf("edge[%d]:\n", i);
        scanf("%d", &c1);
        scanf("%d", &c2);
        p1 = get_position(gp, c1);
        p2 = get_position(gp, c2);
        node = (edge_node *) malloc(sizeof(edge_node));
        node->vertex_num = p2;
        node->next = NULL;

        // 将node链接到"p1所在链表的末尾"
        if (gp->vex[p1].first == NULL)
            gp->vex[p1].first = node;
        else
            list_last(gp->vex[p1].first, node);
    }
    return gp;
}

/*
 * 打印邻接表图
 */
void print(graph *pg) {
    edge_node *node;
    for (int i = 0; i < pg->edge_number; ++i) {
        printf("[%d]%d: ", i, pg->vex[i].data);
        node = pg->vex[i].first;
        while (node != NULL) {
            printf("[%d]%d ", node->vertex_num, pg->vex[node->vertex_num].data);
            node = node->next;
        }
        printf("\n");
    }
}

/*
 * 拓扑排序
 */
void topological(graph *gp) {
    printf("topological:");
    edge_node *node;
    int index = 0;
    int front = 0, rear = 0;
    int top[gp->vertex_number];
    int queue[gp->vertex_number];
    int insert[gp->vertex_number];
    memset(top, 0, sizeof(top));
    memset(queue, 0, sizeof(queue));
    memset(insert, 0, sizeof(insert));
    for (int i = 0; i < gp->vertex_number; ++i) {
        node = gp->vex[i].first;
        while (node != NULL) {
            insert[node->vertex_num]++;
            node = node->next;
        }
    }
    for (int i = 0; i < gp->vertex_number; ++i) {
        if (insert[i] == 0)
            queue[rear++] = i;
    }
    while (front != rear) {
        int i = queue[front++];
        top[index++] = gp->vex[i].data;
        node = gp->vex[i].first;
        while (node != NULL) {
            insert[node->vertex_num]--;
            if (insert[node->vertex_num] == 0)
                queue[rear++] = node->vertex_num;
            node = node->next;
        }
    }
    if (index != gp->vertex_number) {
        printf("graph has a cycle");
        printf("\n");
        return;
    }
    for (int i = 0; i < gp->vertex_number; ++i) {
        printf("%d ", top[i]);
    }
    printf("\n");
}

int main() {
    graph *pg;
    pg = create();
    print(pg);

    topological(pg);
}
