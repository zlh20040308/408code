#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAX_SIZE 50
#define false 0
#define true 1
typedef int bool;
/*
2022年真题：
41.已知非空二叉树T的结点值均为正整数，采用顺序存储方式保存，数据结构定义如下：（注释下方第一部分代码给出）
    请设计一个尽可能高效的算法，判定一棵采用这种方式存储的二叉树是否为二叉搜索树，若是, 则返回 true, 否则, 返回 false。要求:
    1)给出算法的基本设计思想。
    2)根据设计思想，采用C或C++语言描述算法，关键之处给出注释。
*/
/*
阿B注：大家直接把代码最末尾的judgeBST函数内容更改成自己的即可(函数名别改)，默认答案为真题ppt上的版本
*/

typedef struct{ //MAX_SIZE为已定义常量
    int SqBiTNode[MAX_SIZE]; //保存二叉树结点值的数组
    int ElemNum;   //实际占用的数组元素个数
    } SqBiTree;
//题目中给出的类型定义







bool judgeBST(SqBiTree bt);
// 初始化二叉树
void initTree(SqBiTree *T, int *values, int num) {
    T->ElemNum = num;
    memcpy(T->SqBiTNode, values, num * sizeof(int));
}
int allTestsPassed = 1; // 默认所有测试通过
// 测试函数
void testTree(SqBiTree *T, const char *desc, int expected) {
    printf("%s: ", desc);
    int result = judgeBST(*T);  // 判断是否为BST
    if (result == expected) {
        printf("通过测试\n");
    } else {
        printf("未通过测试\n");
        // 如果测试失败，打印出树的整个数组
        printf("当前树的存储数组: ");
        for (int i = 0; i < T->ElemNum; i++) {
            printf("%d ", T->SqBiTNode[i]);
        }
        printf("\n");
        allTestsPassed = 0;  // 记录有测试未通过
    }
}

// **主函数**
int main() {
    SqBiTree T;

    // **测试1：完全符合BST**
    int case1[] = {40, 25, 60, -1, 30, -1, 80, -1, -1, 27};
    initTree(&T, case1, 10);
    testTree(&T, "测试1: 标准BST", 1);

    // **测试2：每个结点都满足左孩子<根<右孩子，但左孩子的右孩子>根**
    int case2[] = {7,5,9,3,8,1,10};
    initTree(&T, case2, 7);
    testTree(&T, "测试2: 每个结点都满足左孩子<根<右孩子，但左孩子的右孩子>根*", 0);

    // **测试3：右子树错误**
    int case3[] = {10, 5, 8, 2, 7, 12, 20};
    initTree(&T, case3, 7);
    testTree(&T, "测试3: 右子树错误", 0);

    // **测试4：只有根节点**
    int case4[] = {10};
    initTree(&T, case4, 1);
    testTree(&T, "测试4: 只有根节点", 1);

    // **测试5：空树**
    int case5[] = {};
    initTree(&T, case5, 0);
    testTree(&T, "测试5: 空树", 1);

    // **测试6：左子树多级错误**
    int case6[] = {10, 3, 15, 2, 12, 12, 20};
    initTree(&T, case6, 7);
    testTree(&T, "测试6: 左子树多级错误", 0);

    // **测试7：非连续存储**
    int case7[] = {10, 5, 15, -1, 7, 12, 20};
    initTree(&T, case7, 7);
    testTree(&T, "测试7: 非连续存储", 1);

    // **测试8：右子树多级错误**
    int case8[] = {10, 5, 15, 2, 7, 20, 8};
    initTree(&T, case8, 7);
    testTree(&T, "测试8: 右子树多级错误", 0);

    // **测试9：完美BST**
    int case9[] = {30, 20, 40, 10, 25, 35, 50};
    initTree(&T, case9, 7);
    testTree(&T, "测试9: 完美BST", 1);

    // **测试10：二叉堆，不是BST**
    int case10[] = {10, 5, 9, 2, 7, 8, 6};
    initTree(&T, case10, 7);
    testTree(&T, "测试10: 二叉堆（不是BST）", 0);

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
//以下代码是ppt中的标准答案，你可以修改成你自己的，但是judgeBST函数的名字和参数不要改
//===========================================================================================

bool judgeBST(SqBiTree bt) {
    return judgeBST_solve(bt, 0);
}

bool judgeBST_solve(SqBiTree bt, int root_index, int* biggest, int* smallest) {
    if(bt.SqBiTNode[root_index] == -1){ // 空树是BST
        *biggest = -1;
        *smallest = -1;
        return true;
    }
    // 计算左右孩子的下标
    int lchild_index = (root_index + 1) * 2 - 1; 
    int rchild_index = (root_index + 1) * 2;
    // 判断左右子树是否为BST
    int* lbiggest;
    int* lsmallest;
    int* rbiggest;
    int* rsmallest;
    *lbiggest = -1;
    *lsmallest = -1;
    *rbiggest = -1;
    *rsmallest = -1;
    
    bool lresult = lchild_index < bt.ElemNum ? judgeBST_solve(bt, lchild_index, lbiggest, lsmallest) : true;
    bool rresult = rchild_index < bt.ElemNum ? judgeBST_solve(bt, rchild_index, rbiggest, rsmallest) : true;
    if(rresult && lresult){ // 如果左右子树都是BST
        bool bigger_left = false;
        bool smaller_right = false;

        // 判断是否比左子树最大的节点大
        if( (lchild_index >= bt.ElemNum) ||
            (bt.SqBiTNode[lchild_index] == -1) || 
            (*lbiggest <= bt.SqBiTNode[root_index])){
            bigger_left = true;
        }
        // 判断是否比右子树最小的节点小
        if( (rchild_index >= bt.ElemNum) ||
            (bt.SqBiTNode[rchild_index] == -1) || 
            (*rsmallest >= bt.SqBiTNode[root_index])){
            smaller_right = true;
        }
        *biggest = *lsmallest;
        *smallest = *rbiggest;
        return bigger_left && smaller_right;

    }
    // 否则就不是
    return false;
}

