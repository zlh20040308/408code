#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MaxSize 500
#define true 1
#define false 0
typedef int bool;
/*
2012年真题：
42. 假定采用带头结点的单链表保存单词，当两个单词有相同的后缀时，则可共享相同的后缀存储空间，
例如，“loading”和“being”的存储映像如下图所示。
str1: "loading" -> 头 -> "l" -> "o" -> "a" -> "d" -> "i" -> "n" -> "g"
str2: "being"   -> 头 -> "b" -> "e" -> "i" -> "n" -> "g"
设 str1 和 str2 分别指向两个单词所在单链表的头结点，
链表结点结构为 [data | next]，
请设计一个时间上尽可能高效的算法，找出由 str1 和 str2 所指向两个链表共同后缀的起始位置（如图中字符 i 所在结点的位置 p）。
要求：
    1）给出算法的基本设计思想。
    2）根据设计思想，采用 C 或 C++ 或 Java 语言描述算法，关键之处给出注释。
    3）说明你所设计算法的时间复杂度。
*/
/*
阿B注：大家直接把代码最末尾的Find_1st_Common函数内容更改成自己的即可(函数名别改)
结构体最好按照已给出的形式，不然测试代码也需要修改
*/
//结构体
typedef struct LinkNode {
    char data;
    struct LinkNode *next;
} LinkNode, *LinkList;






// 函数声明
int allTestsPassed = 1;
LinkNode *Find_1st_Common(LinkList str1, LinkList str2);
int Length(LinkList head);

// 创建带头结点的单链表
LinkList createLinkedList(char *str) {
    LinkList head = (LinkList)malloc(sizeof(LinkNode));
    head->next = NULL;
    LinkNode *tail = head;
    for (int i = 0; str[i] != '\0'; i++) {
        LinkNode *newNode = (LinkNode *)malloc(sizeof(LinkNode));
        newNode->data = str[i];
        newNode->next = NULL;
        tail->next = newNode;
        tail = newNode;
    }
    return head;
}

// 在链表末尾连接另一个链表
void appendList(LinkList head, LinkList suffix) {
    while (head->next) head = head->next;
    head->next = suffix->next;
}

// 计算链表长度
int Length(LinkList head) {
    int len = 0;
    while (head->next) {
        head = head->next;
        len++;
    }
    return len;
}

// 打印链表
void printList(LinkList head) {
    while (head->next) {
        head = head->next;
        printf("%c -> ", head->data);
    }
    printf("NULL\n");
}

// 测试函数
void testFind1stCommon(char *str1, char *str2, char *commonSuffix, const char *desc) {
    printf("%s: \n", desc);

    // 创建两个单词的链表
    LinkList list1 = createLinkedList(str1);
    LinkList list2 = createLinkedList(str2);
    LinkList suffix = createLinkedList(commonSuffix);

    // 连接共同后缀
    appendList(list1, suffix);
    appendList(list2, suffix);

    // 计算预期结果
    LinkNode *expectedCommon = suffix->next;

    // 查找共同后缀起始位置
    LinkNode *result = Find_1st_Common(list1, list2);

    // 打印测试信息
    if (result == expectedCommon) {
        printf("✅ 通过测试\n");
    } else {
        printf("❌ 未通过测试\n");
        printf("  期望输出: %c\n", expectedCommon ? expectedCommon->data : 'N');
        printf("  实际输出: %c\n", result ? result->data : 'N');
        allTestsPassed = 0;
    }
}

// 主函数
int main() {
    // 测试1: "loading" 和 "being" 的共同后缀是 "ing"
    testFind1stCommon("load", "be", "ing", "测试1: loading & being");

    // 测试2: "running" 和 "swimming" 的共同后缀是 "ing"
    testFind1stCommon("runn", "swimm", "ing", "测试2: running & swimming");

    // 测试3: "workship" 和 "friendship" 的共同后缀是 "ship"
    testFind1stCommon("work", "friend", "ship", "测试3: workship & friendship");

    // 测试4: "nation" 和 "station" 的共同后缀是 "tion"
    testFind1stCommon("na", "sta", "tion", "测试4: nation & station");

    // 测试5: "leader" 和 "rider" 的共同后缀是 "der"
    testFind1stCommon("lea", "ri", "der", "测试5: leader & rider");

    // 测试6: "apple" 和 "maple" 的共同后缀是 "ple"
    testFind1stCommon("ap", "ma", "ple", "测试6: apple & maple");

    // 测试7: "hello" 和 "world" 没有共同后缀
    testFind1stCommon("hello", "world", "", "测试7: 无共同后缀");

    // 测试8: "school" 和 "fool" 的共同后缀是 "ool"
    testFind1stCommon("sch", "f", "ool", "测试8: school & fool");

    // 测试9: "running" 和 "ring" 的共同后缀是 "ing"
    testFind1stCommon("runn", "r", "ing", "测试9: running & ring");

    // 测试10: "dancing" 和 "singing" 的共同后缀是 "ing"
    testFind1stCommon("danc", "sing", "ing", "测试10: dancing & singing");

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
以下代码是默认答案，你可以修改成你自己的，但是Find_1st_Common函数的名字和参数不要改
最后返回共同后缀起始结点即可
===========================================================================================
*/

LinkNode *Find_1st_Common(LinkList str1, LinkList str2) {
    int len1 = Length(str1), len2 = Length(str2);
    LinkNode *p, *q;
    for (p = str1; len1 > len2; len1--) // 使 p 指向的链表与 q 指向的链表等长
        p = p->next;
    for (q = str2; len1 < len2; len2--) // 使 q 指向的链表与 p 指向的链表等长
        q = q->next;
    while (p->next != NULL && p->next != q->next) { // 查找共同后缀起始点
        p = p->next; // 两个指针同步向后移动
        q = q->next;
    }
    return p->next; // 返回共同后缀的起始点
}

