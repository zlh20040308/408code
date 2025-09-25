#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAX_SIZE 10000
#define true 1
#define false 0
typedef int bool;
/*
2019年真题：
41.设线性表 采用带头结点的单链表保存，链表中的结点定义如下：（写在了注释下方代码第一部分）
请设计一个空间复杂度为O(1)且时间上尽可能高效的算法，重新排列L 中的各结点，得到线性表L'=(a1, an,a2, an-1,a3, an-2,…)。
要求：
    (1) 给出算法的基本设计思想。
    (2) 根据设计思想，采用C 或C++语言描述算法，关键之处给出注释。
    (3) 说明你所设计的算法的时间复杂度。
*/
/*
阿B注：大家直接把代码最末尾的reorderList函数内容更改成自己的即可(函数名别改),默认答案为真题ppt上的版本
*/
typedef struct node{
    int data;
    struct node *next;
    }node;
//题目所给出结构体





// 函数声明
int setPartition(int a[], int n);
node* createLinkedList(int arr[], int size);
void reorderList(node *h);
int compareLinkedLists(node *head1, node *head2);
void printLinkedList(node *head);
void freeLinkedList(node *head);

int allTestsPassed = 1; // 默认所有测试通过
// 测试函数
void testReorderList(int arr[], int size, int expected[], int expSize, const char *desc) {
    printf("%s: ", desc);
    // 创建链表
    node *head = createLinkedList(arr, size);
    node *expectedHead = createLinkedList(expected, expSize);

    // 调用函数
    reorderList(head);

    // 检查结果
    if (compareLinkedLists(head->next, expectedHead->next)) {
        printf("通过测试\n");
    } else {
        printf("未通过测试，期望输出: ");
        printLinkedList(expectedHead);
        printf("实际输出: ");
        printLinkedList(head);
        allTestsPassed = 0;
    }

    // 释放内存
    freeLinkedList(head);
    freeLinkedList(expectedHead);
}

// **创建带头结点的链表**
node* createLinkedList(int arr[], int size) {
    // **创建头结点**
    node *head = (node*)malloc(sizeof(node));
    head->next = NULL;  // 头结点不存储数据，仅指向第一个元素

    // **若数组为空，则直接返回头结点**
    if (size == 0) return head;

    // **创建数据节点**
    node *curr = head;
    for (int i = 0; i < size; i++) { // **从 i=0 开始，因为 head 只是头结点**
        curr->next = (node*)malloc(sizeof(node));
        curr = curr->next;
        curr->data = arr[i]; // 赋值
        curr->next = NULL;
    }

    return head;  // **返回头结点**
}

// 释放链表
void freeLinkedList(node *head) {
    node *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// 打印链表
void printLinkedList(node *head) {
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// 比较两个链表是否相同
int compareLinkedLists(node *head1, node *head2) {
    while (head1 && head2) {
        if (head1->data != head2->data) return 0;
        head1 = head1->next;
        head2 = head2->next;
    }
    return head1 == NULL && head2 == NULL;
}
// 测试主函数
int main() {
    // 测试1: 长度为5的链表
    int case1[] = {1, 2, 3, 4, 5};
    int expected1[] = {1, 5, 2, 4, 3};
    testReorderList(case1, 5, expected1, 5, "测试1: 长度为5的链表");

    // 测试2: 长度为6的链表
    int case2[] = {1, 2, 3, 4, 5, 6};
    int expected2[] = {1, 6, 2, 5, 3, 4};
    testReorderList(case2, 6, expected2, 6, "测试2: 长度为6的链表");

    // 测试3: 只有1个元素
    int case3[] = {1};
    int expected3[] = {1};
    testReorderList(case3, 1, expected3, 1, "测试3: 只有1个元素");

    // 测试4: 只有2个元素
    int case4[] = {1, 2};
    int expected4[] = {1, 2};
    testReorderList(case4, 2, expected4, 2, "测试4: 只有2个元素");

    // 测试5: 只有3个元素
    int case5[] = {1, 2, 3};
    int expected5[] = {1, 3, 2};
    testReorderList(case5, 3, expected5, 3, "测试5: 只有3个元素");

    // 测试6: 只有4个元素
    int case6[] = {1, 2, 3, 4};
    int expected6[] = {1, 4, 2, 3};
    testReorderList(case6, 4, expected6, 4, "测试6: 只有4个元素");

    // 测试7: 长度为7的链表
    int case7[] = {10, 20, 30, 40, 50, 60, 70};
    int expected7[] = {10, 70, 20, 60, 30, 50, 40};
    testReorderList(case7, 7, expected7, 7, "测试7: 长度为7的链表");

    // 测试8: 链表为空
    int case8[] = {};
    int expected8[] = {};
    testReorderList(case8, 0, expected8, 0, "测试8: 空链表");

    // 测试9: 链表有重复值
    int case9[] = {1, 1, 1, 1, 1, 1};
    int expected9[] = {1, 1, 1, 1, 1, 1};
    testReorderList(case9, 6, expected9, 6, "测试9: 链表有重复值");

    // 测试10: 负数和正数混合
    int case10[] = {-5, -3, -1, 1, 3, 5};
    int expected10[] = {-5, 5, -3, 3, -1, 1};
    testReorderList(case10, 6, expected10, 6, "测试10: 负数和正数混合");

    // 总结测试结果
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

/*
===========================================================================================
以下代码是ppt中的答案，你可以修改成你自己的，但是reorderList函数的名字和参数不要改
空间复杂度O(1)需要自己写代码的时候注意，这里没有写检测的逻辑
===========================================================================================
*/

node *solve(node *head){
    if(head->next == NULL){ // 如果只有一个元素，直接返回
        return head;
    }
    if(head->next->next == NULL){ // 如果只有两个元素，直接返回
        return head;
    }
    node *tail = head;
    node *before_tail = head;
    while(tail->next != NULL){
        tail = tail->next;
    }
    while(before_tail->next != tail){
        before_tail = before_tail->next;
    }
    before_tail->next = NULL;
    node *back = solve(head->next);
    head->next = tail;
    tail->next = back;
    return head;
}

void reorderList(node *h){
    if(h->next == NULL){
        return;
    }
    h->next = solve(h->next);
}


