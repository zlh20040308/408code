#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MaxSize 500
#define true 1
#define false 0
typedef int bool;
/*
2014年真题：
41. 二叉树的带权路径长度（WPL）是二叉树中所有叶结点的带权路径长度之和。
给定一棵二叉树 T，采用二叉链表存储，结点结构如下：
   left    weight    right
其中叶结点的 weight 域保存该结点的非负权值。设 root 为指向 T 的根结点的指针，请设计求 T 的 WPL 的算法
要求：
    1）给出算法的基本设计思想。
    2）使用 C 或 C++ 语言，给出二叉树结点的数据类型定义。
    3）根据设计思想，采用 C 或 C++ 语言描述算法，关键之处给出注释。
*/
/*
阿B注：大家直接把代码最末尾的WPL函数内容更改成自己的即可(函数名别改)
第二问的结构体在下方已给出，如果需要修改的话那测试代码中的weight和lchild & rchild也要随之修改
*/
typedef struct BiTNode {
    int weight;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;
//第二问的结构体






// 函数声明
int allTestsPassed = 1;
int wpl_LevelOrder(BiTree root);
int wpl_PreOrder(BiTree root, int deep);
int WPL(BiTree root);

// 创建二叉树节点
BiTree createBiTreeNode(int weight) {
    BiTree newNode = (BiTree)malloc(sizeof(BiTNode));
    newNode->weight = weight;
    newNode->lchild = NULL;
    newNode->rchild = NULL;
    return newNode;
}
// 测试函数
void testWPL(BiTree root, int expected, const char* desc) {
    printf("%s: \n", desc);
    int result = WPL(root);
    if (result == expected) {
        printf("✅ 通过测试\n");
    } else {
        printf("❌ 未通过测试\n");
        printf("  期望输出: %d\n", expected);
        printf("  实际输出: %d\n", result);
        allTestsPassed = 0;
    }
}

// 主函数
int main() {
    // 测试1: 树结构如下，期望WPL = 14
    //        5
    //       / \
    //      3   6
    //     / \   \
    //    1   2   4
    BiTree root1 = createBiTreeNode(5);
    root1->lchild = createBiTreeNode(3);
    root1->rchild = createBiTreeNode(6);
    root1->lchild->lchild = createBiTreeNode(1);
    root1->lchild->rchild = createBiTreeNode(2);
    root1->rchild->rchild = createBiTreeNode(4);
    testWPL(root1, 14, "测试1: 树结构 {5, 3, 6, 1, 2, x, 4}");


    // 测试2: 树结构如下，期望WPL = 60
    //        10
    //       /  \
    //      5    15
    //     / \     \
    //    3   7     20
    BiTree root2 = createBiTreeNode(10);
    root2->lchild = createBiTreeNode(5);
    root2->rchild = createBiTreeNode(15);
    root2->lchild->lchild = createBiTreeNode(3);
    root2->lchild->rchild = createBiTreeNode(7);
    root2->rchild->rchild = createBiTreeNode(20);
    testWPL(root2, 60, "测试2: 树结构 {10, 5, 15, 3, 7, x, 20}");
    //
    // 测试3: 树结构如下，期望WPL = 26
    //        8
    //       / \
    //      4   7
    //     / \   \
    //    2   5   6
    BiTree root3 = createBiTreeNode(8);
    root3->lchild = createBiTreeNode(4);
    root3->rchild = createBiTreeNode(7);
    root3->lchild->lchild = createBiTreeNode(2);
    root3->lchild->rchild = createBiTreeNode(5);
    root3->rchild->rchild = createBiTreeNode(6);
    testWPL(root3, 26, "测试3: 树结构 {8, 4, 7, 2, 5, x, 6}");
    // 10 + 12 + 16
    // 测试4: 树结构如下，期望WPL = 75
    //        12
    //       /  \
    //      7    9
    //     / \    \
    //    5   6    8
    BiTree root4 = createBiTreeNode(12);
    root4->lchild = createBiTreeNode(7);
    root4->rchild = createBiTreeNode(9);
    root4->lchild->lchild = createBiTreeNode(5);
    root4->lchild->rchild = createBiTreeNode(6);
    root4->rchild->rchild = createBiTreeNode(8);
    testWPL(root4, 38, "测试4: 树结构 {12, 7, 9, 5, 6, x, 8}");

    // 测试5: 树结构如下，期望WPL = 40
    //        20
    //       /  \
    //      10   30
    //     /  \
    //    5    8
    BiTree root5 = createBiTreeNode(20);
    root5->lchild = createBiTreeNode(10);
    root5->rchild = createBiTreeNode(30);
    root5->lchild->lchild = createBiTreeNode(5);
    root5->lchild->rchild = createBiTreeNode(8);
    testWPL(root5, 56, "测试5: 树结构 {20, 10, 30, 5, 8}");



    // 测试6: 树结构如下，期望WPL = 142
    //          20
    //        /    \
    //      10      1
    //     /  \    /  \
    //    5    8  14  44
    BiTree root6 = createBiTreeNode(20);
    root6->lchild = createBiTreeNode(10);
    root6->rchild = createBiTreeNode(1);
    root6->lchild->lchild = createBiTreeNode(5);
    root6->lchild->rchild = createBiTreeNode(8);
    root6->rchild->lchild = createBiTreeNode(14);
    root6->rchild->rchild = createBiTreeNode(44);
    testWPL(root6, 142, "测试6: 树结构 {20, 10, 1, 5, 8, 14, 44}");

    // 测试7: 树结构如下，期望WPL = 88
    //          20
    //             \
    //               1
    //                \
    //                 44
    BiTree root7 = createBiTreeNode(20);
    root7->rchild = createBiTreeNode(1);
    root7->rchild->rchild = createBiTreeNode(44);
    testWPL(root7, 88, "测试7: 树结构 {20, x, 1, x, x, x, 44}");

    // 测试8: 树结构如下，期望WPL = 90
    //          20
    //        /    \
    //       2      1
    //                \
    //                 44
    BiTree root8 = createBiTreeNode(20);
    root8->lchild = createBiTreeNode(2);
    root8->rchild = createBiTreeNode(1);
    root8->rchild->rchild = createBiTreeNode(44);
    testWPL(root8, 90, "测试8: 树结构 {20, 2, 1, x, x, x, 44}");

    // 测试9: 树结构如下，期望WPL = 268
    //          20
    //        /    \
    //       2      1
    //      /        \
    //     90        44
    BiTree root9 = createBiTreeNode(20);
    root9->lchild = createBiTreeNode(2);
    root9->rchild = createBiTreeNode(1);
    root9->lchild->lchild = createBiTreeNode(90);
    root9->rchild->rchild = createBiTreeNode(44);
    testWPL(root9, 268, "测试9: 树结构 {20, 2, 1, 90, x, x, 44}");

    // 测试10: 树结构如下，期望WPL = 268
    //          20
    //        /    \
    //       2      1
    //      /        \
    //     90        44
    //    /         /  \
    //   11        4    6
    BiTree root10 = createBiTreeNode(20);
    root10->lchild = createBiTreeNode(2);
    root10->rchild = createBiTreeNode(1);
    root10->lchild->lchild = createBiTreeNode(90);
    root10->rchild->rchild = createBiTreeNode(44);
    root10->lchild->lchild->lchild = createBiTreeNode(11);
    root10->rchild->rchild->lchild = createBiTreeNode(4);
    root10->rchild->rchild->rchild = createBiTreeNode(6);
    testWPL(root10, 63, "测试10: 树结构 {20, 2, 1, 90, x, x, 44, 11, x, x, x, x, x, 4, 6}");

    // 总结测试结果
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


/*
===========================================================================================
以下代码是默认答案，你可以修改成你自己的，但是WPL函数的名字和参数不要改
最后返回wpl的值即可
===========================================================================================
*/
//基于先序遍历的算法
int WPL(BiTree root) {
    return WPL_Deep(root, 0);
}
int WPL_Deep(BiTree root, int deep) {
    if(!root->lchild && !root->rchild)
        return root->weight * deep;
    return (root->lchild ? WPL_Deep(root->lchild, deep + 1) : 0) + (root->rchild ? WPL_Deep(root->rchild, deep + 1) : 0);
}