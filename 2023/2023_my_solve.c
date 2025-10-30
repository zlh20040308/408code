#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXV 100
/*
2023年真题：
41.已知有向图G采用邻接矩阵存储，类型定义如下：(写在注释的下面了)
将图中出度大于入度的顶点称为K顶点。例如下图中顶点a和b为K顶点
    请设计算法：int printVertices(MGraph G),对给定的任意非空有向图G，输出G中所有的K顶点，返回K顶点的个数，要求：
    1)给出算法的基本设计思想      
    2)根据设计思想，采用C或C++语言描述算法，关键之处给出注释
*/
/*
阿B注：大家直接把代码最末尾的printVertices函数内容更改成自己的即可(函数名别改)，默认答案为真题ppt上的版本
*/

typedef struct  // 图的类型定义
{
    int numVertices, numEdges;  // 图的顶点数和有向边数
    char VerticesList[MAXV];    // 顶点表，MAXV为已定义常量
    int Edge[MAXV][MAXV];       // 邻接矩阵
} MGraph;
//题目中给出的类型定义





// 初始化有向图
void initGraph(MGraph *G, int numV) {
    G->numVertices = numV;
    G->numEdges = 0;
    memset(G->Edge, 0, sizeof(G->Edge));
    for (int i = 0; i < numV; i++) {
        G->VerticesList[i] = 'A' + i; // 设定顶点名称为 A, B, C, ...
    }
}
int printVertices(MGraph G);
// 添加有向边 u -> v
void addEdge(MGraph *G, int u, int v) {
    if (G->Edge[u][v] == 0) {
        G->Edge[u][v] = 1;
        G->numEdges++;
    }
}

// 打印邻接矩阵
void printAdjacencyMatrix(MGraph G) {
    printf("邻接矩阵:\n");
    for (int i = 0; i < G.numVertices; i++) {
        for (int j = 0; j < G.numVertices; j++) {
            printf("%d ", G.Edge[i][j]);
        }
        printf("\n");
    }
}

// 记录所有的测试是否通过
int allTestsPassed = 1; // 默认所有测试通过
// 打印测试结果
void testGraph(MGraph G, const char *desc, int expected_result) {
    printf("%s:", desc);
    int result = printVertices(G);
    
    // 比较实际结果与预期结果
    if (result == expected_result) {
        printf("\n通过测试\n");
    } else {
        printf("\n未通过测试: ");
        printAdjacencyMatrix(G); // 打印邻接矩阵
        allTestsPassed = 0; // 标记为未通过
    }
}


int main() {
    MGraph G;

    // 测试1: 1个K顶点
    initGraph(&G, 4);
    addEdge(&G, 0, 1);
    addEdge(&G, 1, 2);
    addEdge(&G, 2, 3);
    testGraph(G, "测试1:0个k顶点", 1); // 期望结果有1个K顶点

    // 测试2: 单一顶点图，没有K顶点
    initGraph(&G, 1);
    testGraph(G, "测试2:0个k顶点", 0); // 期望结果为1个K顶点

    // 测试3: 1个K顶点
    initGraph(&G, 4);
    addEdge(&G, 0, 1);
    addEdge(&G, 1, 2);
    addEdge(&G, 1, 3);
    addEdge(&G, 2, 0);
    testGraph(G, "测试3:1个k顶点", 1); // 期望结果为1个K顶点

    // 测试4: 1个K顶点
    addEdge(&G, 0, 1);
    addEdge(&G, 1, 2);
    testGraph(G, "测试4:1个k顶点", 1); // 期望结果为1个K顶点

    // 测试5: 有多个孤立的K顶点
    initGraph(&G, 6);
    addEdge(&G, 0, 1);
    addEdge(&G, 2, 3);
    addEdge(&G, 4, 5);
    testGraph(G, "测试5:3个k顶点", 3); // 期望结果为3个K顶点

    // 测试6: 一个K顶点指向多个其他节点，其他顶点的出度小于入度
    initGraph(&G, 4);
    addEdge(&G, 0, 1);
    addEdge(&G, 0, 2);
    addEdge(&G, 0, 3);
    testGraph(G, "测试6:1个k顶点", 1); // 期望结果为1个K顶点

    // 测试7: 图中所有节点没有边，0个K顶点
    initGraph(&G, 3);
    testGraph(G, "测试7:0个k顶点", 0); // 期望结果为0个K顶点

    // 测试8: 2个K顶点
    initGraph(&G, 4);
    addEdge(&G, 0, 1);
    addEdge(&G, 1, 2);
    addEdge(&G, 2, 3);
    addEdge(&G, 1, 3);
    testGraph(G, "测试8:2个k顶点", 2); // 期望结果为2个K顶点

    // 测试9: 0个K顶点
    initGraph(&G, 3);
    addEdge(&G, 0, 1);
    addEdge(&G, 1, 2);
    addEdge(&G, 2, 0);
    addEdge(&G, 0, 2);
    addEdge(&G, 1, 0);
    addEdge(&G, 2, 1);
    testGraph(G, "测试9:0个k顶点", 0); // 期望结果为0个K顶点

    // 测试10: 图包含多个孤立的K顶点
    initGraph(&G, 6);
    addEdge(&G, 0, 1);
    addEdge(&G, 2, 3);
    addEdge(&G, 4, 5);
    testGraph(G, "测试10:3个k顶点", 3); // 期望结果为3个K顶点

    // 汇总所有测试结果
    if (allTestsPassed) {
        printf("\n========================================\n");
        printf("✅所有测试通过！代码没有问题。\n");
        printf("========================================\n");
    } else {
        printf("\n========================================\n");
        printf("❌有测试未通过，请检查相应的输出。\n");
        printf("========================================\n");
    }

    return 0;
}


//===========================================================================================
//以下代码是ppt中的标准答案，你可以修改成你自己的，但是printVertices函数的名字和参数不要改
//===========================================================================================
int printVertices(MGraph G){
    int num = 0;
    int out[G.numVertices];//记录每个顶点的出度
    int in[G.numVertices];//记录每个顶点的入度
    for(int i = 0; i < G.numVertices; ++i) {
        out[i] = 0;
        in[i] = 0;
    }
    for(int i = 0; i < G.numVertices; ++i) {
        for(int j = 0; j < G.numVertices; ++j) {
            if(G.Edge[i][j] == 1){
                out[i]++;
                in[j]++;
            }
        }
    }
    for(int i = 0; i < G.numVertices; ++i) {
        if(out[i] > in[i]) {
            printf("%c ", G.VerticesList[i]);
            num++;
        }
    }
    printf("\n");
    return num;
}

