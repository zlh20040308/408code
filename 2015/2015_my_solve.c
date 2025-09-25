#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unordered_set>
#define MAX_SIZE 10000
#define true 1
#define false 0
/*
2015年真题：
41.用单链表保存m个整数，结点的结构为[data][link]，且|data|<=n(n为正整数）。
现要求设计一个时间复杂度尽可能高效的算法，对于链表中 data 的绝对值相等的结点，仅保留第一次出现的结点而删除其余绝对值相等的结点。
例如，若给定的单链表 HEAD 如下：
HEAD → |2| → |1| → |-15| → |15| → |-7| → |15|
则删除结点后的 HEAD 为：
HEAD → |2| → |1| → |-15| → |-7|
要求：
1)给出算法的基本设计思想。
2)使用 C 或 C++ 语言，给出单链表结点的数据类型定义。
3)根据设计思想，采用 C 或 C++ 语言描述算法，关键之处给出注释。
4)说明你所设计算法的时间复杂度和空间复杂度。
*/
/*
阿B注：大家直接把代码最末尾的func函数内容更改成自己的即可(函数名别改)
第二问的结构体在下方已给出，如果需要修改的话那测试代码中的data和node也要随之修改
*/
typedef struct node {
    int data;
    struct node *link;
} NODE;
typedef NODE *PNODE;
//第二问的结构体






// 函数声明
void func(PNODE h, int n);
int allTestsPassed = 1;
int compareLinkedLists(PNODE head1, PNODE head2);

// 创建新的节点
PNODE createNode(int data) {
    PNODE newNode = (PNODE)malloc(sizeof(NODE));
    newNode->data = data;
    newNode->link = NULL;
    return newNode;
}

// 创建带头结点的链表，头结点不存数据
PNODE createLinkedListWithHead(int data[], int n) {
    PNODE head = createNode(0); // 头结点不存数据，仅作为链表的起点
    PNODE curr = head;
    for (int i = 0; i < n; i++) {
        PNODE newNode = createNode(data[i]);
        curr->link = newNode;
        curr = newNode;
    }
    return head;
}

// 打印链表
void printList(PNODE head) {
    PNODE temp = head->link; // 从头结点后面的第一个节点开始打印
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->link;
    }
    printf("NULL\n");
}

// 比较两个链表是否相同
int compareLinkedLists(PNODE head1, PNODE head2) {
    PNODE temp1 = head1->link;
    PNODE temp2 = head2->link;
    while (temp1 && temp2) {
        if (temp1->data != temp2->data) return 0;
        temp1 = temp1->link;
        temp2 = temp2->link;
    }
    return temp1 == NULL && temp2 == NULL;
}

// 测试函数
void testFunc(PNODE h, int n, PNODE expected, const char *desc) {
    printf("%s: \n", desc);
    printf("输入链表：");
    printList(h);

    // 调用 func 函数
    func(h, n);

    // 打印修改后的链表
    printf("修改后的链表：");
    printList(h);

    // 比较修改后的链表与期望的链表是否相同
    if (compareLinkedLists(h, expected)) {
        printf("✅ 通过测试\n");
    } else {
        printf("❌ 未通过测试\n");
        allTestsPassed = 0;
    }
}

// 主函数
int main() {
    // 测试1: 输入链表为 {1, 2, 2, 3, 4, 5}
    int case1[] = {1, 2, 2, 3, 4, 5};
    PNODE head1 = createLinkedListWithHead(case1, 6);
    // 预期结果链表 {1, 2, 3, 4, 5}
    int expected1[] = {1, 2, 3, 4, 5};
    PNODE expectedLinkedList1 = createLinkedListWithHead(expected1, 5);
    testFunc(head1, 5, expectedLinkedList1, "测试1: 输入链表 {1, 2, 2, 3, 4, 5}");

    // 测试2: 输入链表为 {7, 3, 9, 1, 6, 4}
    int case2[] = {7, 3, 9, 1, 6, 4};
    PNODE head2 = createLinkedListWithHead(case2, 6);
    // 预期结果链表 {7, 3, 9, 1, 6, 4}
    int expected2[] = {7, 3, 9, 1, 6, 4};
    PNODE expectedLinkedList2 = createLinkedListWithHead(expected2, 6);
    testFunc(head2, 9, expectedLinkedList2, "测试2: 输入链表 {7, 3, 9, 1, 6, 4}");

    // 测试3: 输入链表为 {5, 5, 5, 5, 5}
    int case3[] = {5, 5, 5, 5, 5};
    PNODE head3 = createLinkedListWithHead(case3, 5);
    // 预期结果链表 {5}
    int expected3[] = {5};
    PNODE expectedLinkedList3 = createLinkedListWithHead(expected3, 1);
    testFunc(head3, 5, expectedLinkedList3, "测试3: 输入链表 {5, 5, 5, 5, 5}");

    // 测试4: 输入链表为 {10, 10, 10, 10, 10}
    int case4[] = {10, 10, 10, 10, 10};
    PNODE head4 = createLinkedListWithHead(case4, 5);
    // 预期结果链表 {NULL}
    int expected4[] = {10};
    PNODE expectedLinkedList4 = createLinkedListWithHead(expected4, 1);
    testFunc(head4, 10, expectedLinkedList4, "测试4: 输入链表 {10, 10, 10, 10, 10}");

    // 测试5: 输入链表为 {1, 1, 1, 1, 1}
    int case5[] = {1, 1, 1, 1, 1};
    PNODE head5 = createLinkedListWithHead(case5, 5);
    // 预期结果链表 {1}
    int expected5[] = {1};
    PNODE expectedLinkedList5 = createLinkedListWithHead(expected5, 1);
    testFunc(head5, 5, expectedLinkedList5, "测试5: 输入链表 {1, 1, 1, 1, 1}");

    // 测试6: 输入链表为 {2, 4, 6, 8, 10}
    int case6[] = {2, 4, 6, 8, 10};
    PNODE head6 = createLinkedListWithHead(case6, 5);
    // 预期结果链表 {2, 4, 6, 8, 10}
    int expected6[] = {2, 4, 6, 8, 10};
    PNODE expectedLinkedList6 = createLinkedListWithHead(expected6, 5);
    testFunc(head6, 10, expectedLinkedList6, "测试6: 输入链表 {2, 4, 6, 8, 10}");

    // 测试7: 输入链表为 {0, 0, 0, 0, 0, 0}
    int case7[] = {0, 0, 0, 0, 0, 0};
    PNODE head7 = createLinkedListWithHead(case7, 6);
    // 预期结果链表 {0}
    int expected7[] = {0};
    PNODE expectedLinkedList7 = createLinkedListWithHead(expected7, 1);
    testFunc(head7, 6, expectedLinkedList7, "测试7: 输入链表 {0, 0, 0, 0, 0, 0}");

    // 测试8: 输入链表为 {1, 2, 3, 4, 5, 6, 6, 5, 4, 3, 2, 1}
    int case8[] = {1, 2, 3, 4, 5, 6, 6, 5, 4, 3, 2, 1};
    PNODE head8 = createLinkedListWithHead(case8, 12);
    // 预期结果链表 {1, 2, 3, 4, 5, 6}
    int expected8[] = {1, 2, 3, 4, 5, 6};
    PNODE expectedLinkedList8 = createLinkedListWithHead(expected8, 6);
    testFunc(head8, 12, expectedLinkedList8, "测试8: 输入链表 {1, 2, 3, 4, 5, 6, 6, 5, 4, 3, 2, 1}");

    // 测试9: 输入链表为 {-1, -2, -3, -4, -5}
    int case9[] = {-1, -2, -3, -4, -5};
    PNODE head9 = createLinkedListWithHead(case9, 5);
    // 预期结果链表 {-1, -2, -3, -4, -5}
    int expected9[] = {-1, -2, -3, -4, -5};
    PNODE expectedLinkedList9 = createLinkedListWithHead(expected9, 5);
    testFunc(head9, 5, expectedLinkedList9, "测试9: 输入链表 {-1, -2, -3, -4, -5}");

    // 测试10: 输入链表为 {9, 8, 7, 7, 6, 6, 5, 5}
    int case10[] = {9, 8, 7, 7, 6, 6, 5, 5};
    PNODE head10 = createLinkedListWithHead(case10, 8);
    // 预期结果链表 {9, 8, 7, 6, 5}
    int expected10[] = {9, 8, 7, 6, 5};
    PNODE expectedLinkedList10 = createLinkedListWithHead(expected10, 5);
    testFunc(head10, 9, expectedLinkedList10, "测试10: 输入链表 {9, 8, 7, 7, 6, 6, 5, 5}");

    // 测试11: 输入链表为 {9, 8, 7, 7, 0, 6, 0, 0}
    int case11[] = {9, 8, 7, 7, 0, 6, 0, 0};
    PNODE head11 = createLinkedListWithHead(case11, 8);
    // 预期结果链表 {9, 8, 7, 6, 0}
    int expected11[] = {9, 8, 7, 0, 6};
    PNODE expectedLinkedList11 = createLinkedListWithHead(expected11, 5);
    testFunc(head11, 9, expectedLinkedList11, "测试11: 输入链表 {9, 8, 7, 7, 0, 6, 0, 0}");

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
以下代码是默认答案，你可以修改成你自己的，但是func函数的名字和参数不要改
只需要修改链表即可，上面的代码会检测修改后的链表对不对劲
===========================================================================================
*/

void func (PNODE h, int n) {
    std::unordered_set<int> Nset;
    if(h->link == NULL){
        return;
    }
    PNODE pre = NULL;
    PNODE cur = h->link;
    while(cur != NULL){
        int abs_data = abs(cur->data);
        if(Nset.find(abs_data) != Nset.end()){
            PNODE temp = cur;
            cur = cur->link;
            pre->link = cur;
            free(temp);
        }else{
            Nset.insert(abs_data);
            pre = cur;
            cur = cur->link;
        }
    }
}

