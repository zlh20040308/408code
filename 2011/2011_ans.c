#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MaxSize 500
#define true 1
#define false 0
typedef int bool;
/*
2011年真题：
42.一个长度为 L（L>=1）的升序序列 S，处在第 L/2 个位置的数称为 S 的中位数。
例如，若序列 S1 = (11, 13, 15, 17, 19)，则 S1 的中位数是 15，
两个序列的中位数是含它们所有元素的升序序列的中位数。
例如，若 S2 = (2, 4, 6, 8, 20)，则 S1 和 S2 的中位数是 11。
现在有两个等长升序序列 A 和 B，试设计一个在时间和空间两方面都尽可能高效的算法，找出两个序列 A 和 B 的中位数。
要求：
    （1）给出算法的基本设计思想。
    （2）根据设计思想，采用 C、C++或 Java 语言描述算法，关键之处给出注释。
    （3）说明你所设计算法的时间复杂度和空间复杂度。
*/
/*
阿B注：大家直接把代码最末尾的 M_Search 函数内容更改成自己的即可(函数名别改)
*/







// 函数声明
int allTestsPassed = 1;
int M_Search(int A[], int B[], int n);

// 测试函数
void testM_Search(int A[], int B[], int n, int expected, const char *desc) {
    printf("%s: \n", desc);
    int result = M_Search(A, B, n);
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


    // 测试1: 序列 A 和 B 都为 {1, 3, 8}, 中位数为 3
    int case1A[] = {1, 3, 8};
    int case1B[] = {1, 3, 8};
    testM_Search(case1A, case1B, 3, 3, "测试1: 输入 A {1, 3, 8}, B {1, 3, 8}");

    // 测试2: 序列 A 和 B 分别为 {1, 3, 5} 和 {2, 4, 6}, 中位数为 3
    int case2A[] = {1, 3, 5};
    int case2B[] = {2, 4, 6};
    testM_Search(case2A, case2B, 3, 3, "测试2: 输入 A {1, 3, 5}, B {2, 4, 6}");

    // 测试3: 序列 A 为 {1, 2, 5}, B 为 {3, 4, 6}, 中位数为 3
    int case3A[] = {1, 2, 5};
    int case3B[] = {3, 4, 6};
    testM_Search(case3A, case3B, 3, 3, "测试3: 输入 A {1, 2, 5}, B {3, 4, 6}");

    // 测试4: 序列 A 为 {1, 4, 7}, B 为 {2, 5, 8}, 中位数为 4
    int case4A[] = {1, 4, 7};
    int case4B[] = {2, 5, 8};
    testM_Search(case4A, case4B, 3, 4, "测试4: 输入 A {1, 4, 7}, B {2, 5, 8}");

    // 测试5: 序列 A 为 {1, 2, 3}, B 为 {4, 5, 6}, 中位数为 3
    int case5A[] = {1, 2, 3};
    int case5B[] = {4, 5, 6};
    testM_Search(case5A, case5B, 3, 3, "测试5: 输入 A {1, 2, 3}, B {4, 5, 6}");

    // 测试6: 序列 A 为 {3, 5, 7}, B 为 {1, 2, 6}, 中位数为 5
    int case6A[] = {3, 5, 7};
    int case6B[] = {1, 2, 6};
    testM_Search(case6A, case6B, 3, 3, "测试6: 输入 A {3, 5, 7}, B {1, 2, 6}");

    // 测试7: 序列 A 为 {1, 2, 3, 4}, B 为 {3, 4, 5, 6}, 中位数为 3
    int case7A[] = {1, 2, 3, 4};
    int case7B[] = {3, 4, 5, 6};
    testM_Search(case7A, case7B, 4, 3, "测试7: 输入 A {1, 2, 3, 4}, B {3, 4, 5, 6}");

    // 测试8: 序列 A 为 {1, 2, 3, 4}, B 为 {5, 6, 7, 8}, 中位数为 4
    int case8A[] = {1, 2, 3, 4};
    int case8B[] = {5, 6, 7, 8};
    testM_Search(case8A, case8B, 4, 4, "测试8: 输入 A {1, 2, 3, 4}, B {5, 6, 7, 8}");

    // 测试9: 序列 A 为 {1, 2, 3, 6}, B 为 {4, 5, 7, 8}, 中位数为 4
    int case9A[] = {1, 2, 3, 6};
    int case9B[] = {4, 5, 7, 8};
    testM_Search(case9A, case9B, 4, 4, "测试9: 输入 A {1, 2, 3, 6}, B {4, 5, 7, 8}");

    // 测试10: 序列 A 为 {10, 20, 30}, B 为 {15, 25, 35}, 中位数为 20
    int case10A[] = {10, 20, 30};
    int case10B[] = {15, 25, 35};
    testM_Search(case10A, case10B, 3, 20, "测试10: 输入 A {10, 20, 30}, B {15, 25, 35}");

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
以下代码是默认答案，你可以修改成你自己的，但是 M_Search 函数的名字和参数不要改
最后返回中位数即可
===========================================================================================
*/
int M_Search(int A[], int B[], int n) {
    // 分别本轮搜索中A、B的起始位置和结束位置
    int start1 = 0, end1 = n - 1, start2 = 0, end2 = n - 1;
    // 分别本轮搜索中A、B的中位数
    int m1, m2;
    // 直到一个数组被遍历完
    while (start1 != end1 || start2 != end2) {
        m1 = (start1 + end1) / 2;
        m2 = (start2 + end2) / 2;
        // 满足情况(1)
        if (A[m1] == B[m2])
            return A[m1];
        // 满足情况(2)
        if (A[m1] < B[m2]) {
            // 考虑奇偶为保证子数组元素个数相同
            if ((start1 + end1) % 2 == 0) {
                start1 = m1;
                end2 = m2;
            } else {
                start1 = m1 + 1;
                end2 = m2;
            }
        }
        // 满足情况(3)
        if (A[m1] > B[m2]) {
            // 考虑奇偶为保证子数组元素个数相同
            if ((start1 + end1) % 2 == 0) {
                end1 = m1;
                start2 = m2;
            } else {
                end1 = m1;
                start2 = m2 + 1;
            }
        }
        }
    // 返回较小的
    return A[start1] < B[start2] ? A[start1] : B[start2];
}


