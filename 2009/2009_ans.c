#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MaxSize 500
#define true 1
#define false 0
typedef int bool;
/*
2009年真题：
42. （15 分）已知一个带有表头结点的单链表，结点结构为：
|  data | link  |
假设该链表只给出了头指针 list。在不改变链表的前提下，请设计一个尽可能高效的算法，
查找链表中倒数第 k 个位置上的结点（k 为正整数）。
若查找成功，算法输出该结点的 data 域的值，并返回 1；
否则，只返回 0。
要求：
    1）描述算法的基本设计思想。
    2）描述算法的详细实现步骤。
    3）根据设计思想和实现步骤，采用程序设计语言描述算法（使用 C、C++或 Java 语言实现），关键之处请给出简要注释。
*/
/*
阿B注：大家直接把代码最末尾的 Search_k 函数内容更改成自己的即可(函数名别改)
结构体下方已给出，如果需要更改的话需要连同测试代码一起更改
原题目需要输出值，但是为了检测方便请把值给返回(return)，就不要查找成功返回1了
*/
//结构体定义
typedef int ElemType; // 链表数据的类型定义
typedef struct LNode { // 链表结点的结构定义
    ElemType data; // 结点数据
    struct LNode *link; // 结点链接指针
} *LinkList;







// 函数声明
int allTestsPassed = 1;
int Search_k(LinkList list, int k);

// 创建一个新节点
LinkList CreateNode(ElemType value) {
    LinkList newNode = (LinkList)malloc(sizeof(struct LNode));
    newNode->data = value;
    newNode->link = NULL;
    return newNode;
}

// 创建带头结点的链表
LinkList CreateList(ElemType arr[], int n) {
    LinkList head = CreateNode(0); // 头结点不存数据，仅作链表头标识
    LinkList p = head;
    for (int i = 0; i < n; i++) {
        p->link = CreateNode(arr[i]);
        p = p->link;
    }
    return head;
}

// 测试函数
void testSearch_k(ElemType arr[], int n, int k, int expected, const char* desc) {
    LinkList list = CreateList(arr, n);
    int result = Search_k(list, k);

    printf("%s: \n", desc);
    if (result == expected) {
        printf("✅ 通过测试\n");
    } else {
        printf("❌ 未通过测试\n");
        printf("  期望输出: %d\n", expected);
        printf("  实际输出: %d\n", result);
        allTestsPassed=0;
    }
}

int main() {

    // 测试1: 倒数第 2 个元素为 5
    ElemType case1[] = {1, 2, 3, 4, 5};
    testSearch_k(case1, 5, 2, 4, "测试1: 输入 {1, 2, 3, 4, 5}, 倒数第 2 个元素");

    // 测试2: 倒数第 3 个元素为 30
    ElemType case2[] = {10, 20, 30, 40, 50};
    testSearch_k(case2, 5, 3, 30, "测试2: 输入 {10, 20, 30, 40, 50}, 倒数第 3 个元素");

    // 测试3: 倒数第 1 个元素为 50
    ElemType case3[] = {1, 2, 3, 4, 5};
    testSearch_k(case3, 5, 1, 5, "测试3: 输入 {1, 2, 3, 4, 5}, 倒数第 1 个元素");

    // 测试4: 查找倒数第 6 个元素（不存在）
    ElemType case4[] = {1, 2, 3, 4, 5};
    testSearch_k(case4, 5, 6, 0, "测试4: 输入 {1, 2, 3, 4, 5}, 查找倒数第 6 个元素");

    // 测试5: 倒数第 4 个元素为 2
    ElemType case5[] = {1, 2, 3, 4, 5};
    testSearch_k(case5, 5, 4, 2, "测试5: 输入 {1, 2, 3, 4, 5}, 倒数第 4 个元素");

    // 测试6: 空链表（只有头结点）
    ElemType case6[] = {};
    testSearch_k(case6, 0, 1, 0, "测试6: 空链表");

    // 测试7: 倒数第 3 个元素为 4
    ElemType case7[] = {1, 2, 3, 4, 5, 6};
    testSearch_k(case7, 6, 3, 4, "测试7: 输入 {1, 2, 3, 4, 5, 6}, 倒数第 3 个元素");

    // 测试8: 查找倒数第 5 个元素（不存在）
    ElemType case8[] = {10, 20, 30, 40};
    testSearch_k(case8, 4, 5, 0, "测试8: 输入 {10, 20, 30, 40}, 查找倒数第 5 个元素");

    // 测试9: 倒数第 2 个元素为 50
    ElemType case9[] = {10, 20, 30, 40, 50, 60};
    testSearch_k(case9, 6, 2, 50, "测试9: 输入 {10, 20, 30, 40, 50, 60}, 倒数第 2 个元素");

    // 测试10: 倒数第 5 个元素为 20
    ElemType case10[] = {10, 20, 30, 40, 50, 60};
    testSearch_k(case10, 6, 5, 20, "测试10: 输入 {10, 20, 30, 40, 50, 60}, 倒数第 5 个元素");

    // 总结测试结果
    if (allTestsPassed) {
        printf("\n========================================\n");
        printf("✅ 所有测试通过！代码没有问题。\n");
        printf("========================================\n");
    } else {
        printf("\n========================================\n");
        printf("❌ 有测试未通过, 请检查相应的输出。\n");
        printf("========================================\n");
    }

    return 0;
}
/*
===========================================================================================
以下代码是默认答案，你可以修改成你自己的，但是 Search_k 函数的名字和参数不要改
原题目需要输出值，但是为了检测方便请把值给返回(return)，就不要查找成功返回1了
===========================================================================================
*/
int Search_k(LinkList list, int k) { // 查找链表 list 倒数第 k 个结点，并输出该结点 data 域的值
    LinkList p = list->link, q = list->link; // 指针 p、q 指示第一个结点
    int count = 0;
    while (p != NULL) { // 遍历链表直到最后一个结点
        if (count < k) count++; // 计数，若 count<k 只移动 p
        else q = q->link; p = p->link; // 之后让 p、q 同步移动
    } // while
    if (count < k) // 查找失败返回 0
        return 0; // 查找失败返回 0
    else {
        return q->data;// 否则返回查找到的值
    }
} 
