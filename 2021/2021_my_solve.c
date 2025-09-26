#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAXV 50
/*
2021年真题：
41.已知无向连通图G由顶点集V和边集E组成,|E|>0,当G中度为奇数的顶点个数为不大于2的偶数时(有0或2个度为奇数的顶点时),
G存在包含所有边且长度为|E|的路径(称为EL路径)。
设图G采用邻接矩阵存储,类型定义如下：（写在注释下方第一部分代码中了）
请设计算法 int IsExistEL(MGraph G),判断 是否存在EL路径,若存在,则返回1,否则返回0。要求：
1)给出算法的基本设计思想。
2)根据设计思想,采用C或C++语言描述算法,关键之处给出注释。
3)说明你所设计算法的时间复杂度和空间复杂度。
*/
/*
阿B注：大家直接把代码最末尾的IsExistEL(MGraph G)函数内容更改成自己的即可(函数名别改),默认答案为真题ppt上的版本
*/

typedef struct{
    //图的定义
    int numVertices,numEdges;
    //图中实际的顶点数和边数
    char VerticesList[MAXV];
    //顶点表。MAXV为已定义常量
    int Edge[MAXV][MAXV];
    //邻接矩阵
    }MGraph;
//题目中给出的类型定义







// 函数声明
int IsExistEL(MGraph G);
void initGraph(MGraph *G, int numVertices, int numEdges, int edges[][2]);
void testGraph(MGraph *G, const char *desc, int expected);

int allTestsPassed = 1; // 默认所有测试通过


// 初始化图
void initGraph(MGraph *G, int numVertices, int numEdges, int edges[][2]) {
    G->numVertices = numVertices;
    G->numEdges = numEdges;
    
    // 初始化邻接矩阵
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            G->Edge[i][j] = 0;
        }
    }
    
    // 填充邻接矩阵
    for (int i = 0; i < numEdges; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        G->Edge[u][v] = 1;
        G->Edge[v][u] = 1;  // 无向图，对称添加边
    }
}

// 测试函数
void testGraph(MGraph *G, const char *desc, int expected) {
    printf("%s: ", desc);
    int result = IsExistEL(*G);  // 判断是否存在EL路径
    if (result == expected) {
        printf("通过测试\n");
    } else {
        printf("未通过测试\n");
        // 如果测试失败,打印出图的邻接矩阵
        printf("当前图的邻接矩阵:\n");
        for (int i = 0; i < G->numVertices; i++) {
            for (int j = 0; j < G->numVertices; j++) {
                printf("%d ", G->Edge[i][j]);
            }
            printf("\n");
        }
        allTestsPassed = 0;  // 记录有测试未通过
    }
}

// 主函数
int main() {
    MGraph G;

    // 测试1: 度数为奇数的顶点个数为2
    int edges1[][2] = {{0, 1}, {1, 2}, {2, 0}};
    initGraph(&G, 3, 3, edges1);
    testGraph(&G, "测试1: 度数为奇数的顶点个数为0", 1);

    // 测试2: 度数为奇数的顶点个数为2
    int edges2[][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {1, 3}};
    initGraph(&G, 4, 5, edges2);
    testGraph(&G, "测试2: 度数为奇数的顶点个数为2", 1);

    // 测试3: 度数为奇数的顶点个数为0（满足条件）
    int edges3[][2] = {{0, 1}, {1, 2}, {2, 3}};
    initGraph(&G, 4, 3, edges3);
    testGraph(&G, "测试3: 度数为奇数的顶点个数为0", 1);

    // 测试4: 度数为奇数的顶点个数为2
    int edges4[][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}};
    initGraph(&G, 5, 4, edges4);
    testGraph(&G, "测试4: 度数为奇数的顶点个数为2", 1);

    // 测试5: 度数为奇数的顶点个数为2（符合条件）
    int edges5[][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {4, 0}};
    initGraph(&G, 5, 5, edges5);
    testGraph(&G, "测试5: 度数为奇数的顶点个数为2", 1);

    // 测试6: 图为树,度数为奇数的顶点个数为3
    int edges6[][2] = {{0, 1}, {1, 2}, {2, 3}, {2, 4}};
    initGraph(&G, 5, 4, edges6);
    testGraph(&G, "测试6: 图为树,度数为奇数的顶点个数为3", 0);

    // 测试7: 完全图,度数为奇数的顶点个数为奇数,应该返回0
    int edges7[][2] = {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 3}};
    initGraph(&G, 4, 6, edges7);
    testGraph(&G, "测试7: 完全图,度数为奇数的顶点个数为奇数", 0);

    // 测试8: 度数为奇数的顶点0个
    int edges8[][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}, {1, 4}};
    initGraph(&G, 5, 6, edges8);
    testGraph(&G, "测试8: 0个度数为奇数的顶点", 1);

    // 测试9: 单一顶点,度数为0,符合条件
    int edges9[][2] = {};
    initGraph(&G, 1, 0, edges9);
    testGraph(&G, "测试9: 单一顶点,度数为0", 1);

    // 测试10: 边数为偶数,且度数为奇数的顶点个数为0,符合条件
    int edges10[][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 0}};
    initGraph(&G, 4, 4, edges10);
    testGraph(&G, "测试10: 边数为偶数,度数为奇数的顶点个数为0", 1);

    if (allTestsPassed) {
        printf("\n========================================\n");
        printf("✅所有测试通过！代码没有问题。\n");
        printf("========================================\n");
    } else {
        printf("\n========================================\n");
        printf("❌有测试未通过,请检查相应的输出。\n");
        printf("========================================\n");
    }

    return 0;
}

//===========================================================================================
//以下代码是ppt中的标准答案，你可以修改成你自己的，但是IsExistEL函数的名字和参数不要改
//===========================================================================================
int IsExistEL(MGraph G) {
    // 1. 统计每个点的度
    int degree[G.numVertices];
    for(int i = 0; i < G.numVertices; ++i){
        degree[i] = 0;
    }
    for(int i = 0; i < G.numVertices; ++i){
        for(int j = i + 1; j < G.numVertices; ++j){
            if(G.Edge[i][j] == 1){
                degree[i]++;
                degree[j]++;
            }
        }
    }
    // 2. 统计度为奇数的点的个数
    int num = 0;
    for(int i = 0; i < G.numVertices; ++i){
        if(degree[i] % 2 == 1){
            num++;
        }
    }
    // 3. 如果度为奇数的点的个数为0or2则符合条件
    if(num==0||num==2){
        return 1;
    }
    return 0;
}

