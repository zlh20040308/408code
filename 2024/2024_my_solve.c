/*
2024年真题：
请设计算法:int uniquely(MGraph G),判定G是否存在唯一的拓扑排序列,若是,则返回1,否则返回0,要求如下：
1)给出算法的基本设计思想.
2)根据设计思想,采用C 或C++语言描述算法,关键之处给出注释.
*/

/*
阿B注：大家直接把代码最末尾的uniquely函数内容更改成自己的即可(函数名别改)，默认答案为真题ppt上的版本
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXV 100


typedef struct // 图的类型定义
{
    int numVertices, numEdges;  // 图的顶点数和有向边数
    char VerticesList[MAXV];    // 顶点表,MAXV 为已定义常量
    int Edge[MAXV][MAXV];       // 邻接矩阵
} MGraph;

// uniquely 函数声明
int uniquely(MGraph G);

// 初始化有向图
void initGraph(MGraph *G, int numV) {
    G->numVertices = numV;
    G->numEdges = 0;
    memset(G->Edge, 0, sizeof(G->Edge));
    for (int i = 0; i < numV; i++) {
        G->VerticesList[i] = 'A' + i; // 设定顶点名称为 A, B, C, ...
    }
}

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
    printf("%s: ", desc);
    int result = uniquely(G);
    
    // 比较实际结果与预期结果
    if (result == expected_result) {
        printf("通过测试\n");
    } else {
        printf("未通过测试: ");
        printAdjacencyMatrix(G); // 打印邻接矩阵
        allTestsPassed = 0; // 标记为未通过
    }
}


int main() {
    MGraph G;

    // 测试1: 只有一种拓扑排序的 DAG
    initGraph(&G, 4);
    addEdge(&G, 0, 1);
    addEdge(&G, 1, 2);
    addEdge(&G, 2, 3);
    testGraph(G, "测试1 (唯一拓扑排序)", 1); // 期望结果为唯一拓扑排序

    // 测试2: 多个拓扑排序的 DAG
    initGraph(&G, 4);
    addEdge(&G, 0, 1);
    addEdge(&G, 0, 2);
    addEdge(&G, 1, 3);
    addEdge(&G, 2, 3);
    testGraph(G, "测试2 (多个拓扑排序)", 0); // 期望结果为多个拓扑排序

    // 测试3: 有环
    initGraph(&G, 3);
    addEdge(&G, 0, 1);
    addEdge(&G, 1, 2);
    addEdge(&G, 2, 0);
    testGraph(G, "测试3 (有环)", 0); // 期望结果为多个拓扑排序序列（有环）

    // 测试4: 孤立点+一个序列=多个拓扑排序
    initGraph(&G, 5);
    addEdge(&G, 0, 1);
    addEdge(&G, 1, 2);
    addEdge(&G, 2, 3);
    testGraph(G, "测试4 (孤立点+一个序列=多个拓扑排序)", 0); // 期望结果为多个拓扑排序

    // 测试5: 只有孤立点
    initGraph(&G, 1);
    testGraph(G, "测试5 (只有孤立点)", 1); // 期望结果为唯一拓扑排序

     // 测试6: 一个有多个环的图
     initGraph(&G, 4);
     addEdge(&G, 0, 1);
     addEdge(&G, 1, 2);
     addEdge(&G, 2, 0);  // 环1
     addEdge(&G, 1, 3);
     addEdge(&G, 3, 1);  // 环2
     testGraph(G, "测试6 (多个环的图)", 0); // 期望结果为有环
 
     // 测试7: 一个节点指向多个节点
     initGraph(&G, 4);
     addEdge(&G, 0, 1);
     addEdge(&G, 0, 2);
     addEdge(&G, 0, 3);
     testGraph(G, "测试7 (一个节点指向多个节点)", 0); // 期望结果为多个拓扑排序
 
     // 测试8: 两个完全独立的子图
     initGraph(&G, 6);
     addEdge(&G, 0, 1);
     addEdge(&G, 1, 2);
     addEdge(&G, 4, 5);
     addEdge(&G, 5, 6);
     testGraph(G, "测试8 (两个完全独立的子图)", 0); // 期望结果为多个拓扑排序
 
     // 测试9: 一个复杂的DAG，且存在多个拓扑排序
     initGraph(&G, 5);
     addEdge(&G, 0, 1);
     addEdge(&G, 0, 2);
     addEdge(&G, 1, 3);
     addEdge(&G, 2, 3);
     addEdge(&G, 3, 4);
     testGraph(G, "测试9 (一个复杂的DAG，多个拓扑排序)", 0); // 期望结果为多个拓扑排序
 
     // 测试10: 一个链式结构的DAG，只有一个拓扑排序
    initGraph(&G, 4);
    addEdge(&G, 0, 1);
    addEdge(&G, 1, 2);
    addEdge(&G, 2, 3);
    testGraph(G, "测试10 (链式结构，唯一拓扑排序)", 1); // 期望结果为唯一拓扑排序
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
//以下代码是ppt中的标准答案，你可以修改成你自己的，但是uniquely函数的名字和参数不要改
//===========================================================================================
int uniquely(MGraph G){
    // 依次寻找是否只存在一个点只有出度没有入度，如果有只有一个，则去除该顶点及其对应边
    int in[G.numVertices];
    int remove[G.numVertices];
    for(int i = 0; i < G.numVertices; ++i){
        in[i] = 0;
        remove[i] = 0;
    }
    for(int k = 0; k < G.numVertices; ++k){
        int num = 0;
        int index = 0;
        for(int i = 0; i < G.numVertices; ++i) {
            for(int j = 0; j < G.numVertices; ++j) {
                if(G.Edge[i][j] == 1){
                    in[j] = 1;
                }

            }
        }
        for(int i = 0; i < G.numVertices; ++i) {
            if(in[i] == 0 && remove[i] == 0) {
                num++;
                index=i;
            }
        }
        if(num > 1 || num == 0) {
            return 0;
        }
        for(int i = 0; i < G.numVertices; ++i) {
            G.Edge[index][i] = 0;
        }
        for(int i = 0; i < G.numVertices; ++i){
            in[i] = 0;
        }
        remove[index] = 1;
    }
    return 1;
}


