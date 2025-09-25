#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MaxSize 500
#define true 1
#define false 0
typedef int bool;
/*
2010年真题：
42.设将 n（n > 1）个整数存放到一维数组 R 中。试设计一个在时间和空间两方面都尽可能高效的算法。
将 R 中保存的序列循环左移 p（0 < p < n）个位置，
即将 R 中的数据由 (X0, X1, ..., Xn-1) 变换为 (Xp, Xp+1, ..., Xn-1, X0, X1, ..., Xp-1)。
要求：
    （1）给出算法的基本设计思想。
    （2）根据设计思想，采用 C、C++ 或 Java 语言描述算法，关键之处给出注释。
    （3）说明你所设计算法的时间复杂度和空间复杂度。
*/
/*
阿B注：大家直接把代码最末尾的Converse函数内容更改成自己的即可(函数名别改)
*/







// 函数声明
int allTestsPassed = 1;
void Reverse(int R[], int from, int to);
void Converse(int R[], int n, int p);


// 测试函数
void testConverse(int R[], int n, int p, int expected[], const char* desc) {
    // 执行左移操作
    Converse(R, n, p);

    // 检查结果是否正确
    int isPassed = 1;
    for (int i = 0; i < n; i++) {
        if (R[i] != expected[i]) {
            isPassed = 0;
            break;
        }
    }

    // 输出测试结果
    printf("%s: \n", desc);
    if (isPassed) {
        printf("✅ 通过测试\n");
    } else {
        printf("❌ 未通过测试\n");
        printf("  期望输出: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", expected[i]);
        }
        printf("\n  实际输出: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", R[i]);
        }
        printf("\n");
        allTestsPassed = 0;
    }
}

// 主函数
int main() {

    // 测试1: 左移 2 个位置
    int case1[] = {1, 2, 3, 4, 5};
    int expected1[] = {3, 4, 5, 1, 2};
    testConverse(case1, 5, 2, expected1, "测试1: 输入 {1, 2, 3, 4, 5}, 左移 2");

    // 测试2: 左移 1 个位置
    int case2[] = {1, 2, 3, 4, 5};
    int expected2[] = {2, 3, 4, 5, 1};
    testConverse(case2, 5, 1, expected2, "测试2: 输入 {1, 2, 3, 4, 5}, 左移 1");

    // 测试3: 左移 3 个位置
    int case3[] = {10, 20, 30, 40, 50};
    int expected3[] = {40, 50, 10, 20, 30};
    testConverse(case3, 5, 3, expected3, "测试3: 输入 {10, 20, 30, 40, 50}, 左移 3");

    // 测试4: 左移 4 个位置
    int case4[] = {1, 2, 3, 4};
    int expected4[] = {1, 2, 3, 4};
    testConverse(case4, 4, 4, expected4, "测试4: 输入 {1, 2, 3, 4}, 左移 4");

    // 测试5: 序列中只有一个元素
    int case5[] = {1};
    int expected5[] = {1};
    testConverse(case5, 1, 1, expected5, "测试5: 输入 {1}, 左移 1");

    // 测试6: 左移 2 个位置
    int case6[] = {10, 20, 30, 40, 50, 60};
    int expected6[] = {30, 40, 50, 60, 10, 20};
    testConverse(case6, 6, 2, expected6, "测试6: 输入 {10, 20, 30, 40, 50, 60}, 左移 2");

    // 测试7: 输入序列是递增的
    int case7[] = {1, 2, 3, 4, 5, 6, 7};
    int expected7[] = {4, 5, 6, 7, 1, 2, 3};
    testConverse(case7, 7, 3, expected7, "测试7: 输入 {1, 2, 3, 4, 5, 6, 7}, 左移 3");

    // 测试8: 左移 3 个位置
    int case8[] = {1, 3, 5, 7, 9};
    int expected8[] = {7, 9, 1, 3, 5};
    testConverse(case8, 5, 3, expected8, "测试8: 输入 {1, 3, 5, 7, 9}, 左移 3");

    // 测试9: 数字从 1 到 10
    int case9[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int expected9[] = {6, 7, 8, 9, 10, 1, 2, 3, 4, 5};
    testConverse(case9, 10, 5, expected9, "测试9: 输入 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 左移 5");

    // 测试10: 数字从 100 到 150
    int case10[] = {100, 110, 120, 130, 140, 150};
    int expected10[] = {130, 140, 150, 100, 110, 120};
    testConverse(case10, 6, 3, expected10, "测试10: 输入 {100, 110, 120, 130, 140, 150}, 左移 3");

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
以下代码是默认答案，你可以修改成你自己的，但是 Converse 函数的名字和参数不要改
===========================================================================================
*/

void Converse(int R[], int n, int p) {
    while(p--){
        int temp = R[0];
        for(int i = 0; i < n - 1; ++i)
            R[i] = R[i+1];
        R[n-1] = temp;
    }
}
