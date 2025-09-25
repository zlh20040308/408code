#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAX_SIZE 10000
#define true 1
#define false 0
typedef int bool;
/*
2018年真题：
41.给定一个含n（n≥1个整数的数组，请设计一个在时间上尽可能高效的算法，找出数组中未出现的最小正整数。
例如，数组{-5, 3, 2, 3}中未出现的最小正整数是 1；数组{1, 2, 3}中未出现的最小正整数是 4。
要求：
    （1）给出算法的基本设计思想。
    （2）根据设计思想，采用 C 或 C++ 语言描述算法，关键之处给出注释。
    （3）说明你所设计算法的时间复杂度和空间复杂度。
*/
/*
阿B注：大家直接把代码最末尾的findMissingPositive函数内容更改成自己的即可(函数名别改)
*/
typedef struct node{
    int data;
    struct node *next;
    }node;
//题目所给出结构体





// 函数声明
int findMissingPositive(int arr[], int n);
void testFindMissingPositive(int arr[], int n, int expected, const char *desc);

int allTestsPassed = 1; // 默认所有测试通过

// 测试函数
void testFindMissingPositive(int arr[], int n, int expected, const char *desc) {
    printf("%s: ", desc);
    int result = findMissingPositive(arr, n);
    if (result == expected) {
        printf("通过测试\n");
    } else {
        printf("未通过测试, 期望值: %d, 实际值: %d\n", expected, result);
        allTestsPassed = 0; // 标记有错误
    }
}

// 主函数
int main() {
    // 测试1: 基本测试
    int case1[] = {-5, 3, 2, 3};
    testFindMissingPositive(case1, 4, 1, "测试1: 最小未出现正整数是 1");

    // 测试2: 1,2,3 递增
    int case2[] = {1, 2, 3};
    testFindMissingPositive(case2, 3, 4, "测试2: 1,2,3 递增, 结果是 4");

    // 测试3: 乱序的正数
    int case3[] = {3, 4, -1, 1};
    testFindMissingPositive(case3, 4, 2, "测试3: 乱序, 结果是 2");

    // 测试4: 只有负数
    int case4[] = {-1, -2, -3, -4};
    testFindMissingPositive(case4, 4, 1, "测试4: 只有负数, 结果是 1");

    // 测试5: 只有大数
    int case5[] = {100, 101, 102};
    testFindMissingPositive(case5, 3, 1, "测试5: 只有大数, 结果是 1");

    // 测试6: 无序数组
    int case6[] = {7, 8, 9, 11, 12};
    testFindMissingPositive(case6, 5, 1, "测试6: 无序数组, 结果是 1");

    // 测试7: 单个元素
    int case7[] = {1};
    testFindMissingPositive(case7, 1, 2, "测试7: 单个元素, 结果是 2");

    // 测试8: 多个相同数字
    int case8[] = {1, 1, 1, 2, 2, 3, 3, 4};
    testFindMissingPositive(case8, 8, 5, "测试8: 有重复元素, 结果是 5");

    // 测试9: 无序大数据
    int case9[] = {10, 7, 6, 1, 5, 2, 4, 3};
    testFindMissingPositive(case9, 8, 8, "测试9: 无序大数据, 结果是 8");

    // 测试10: 空数组
    int case10[] = {};
    testFindMissingPositive(case10, 0, 1, "测试10: 空数组, 结果是 1");

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
以下代码是默认答案，你可以修改成你自己的，但是findMissingPositive函数的名字和参数不要改
===========================================================================================
*/
int findMissingPositive(int A[], int n) {
    int i, j , a;
    int B[n];
    // 手动初始化数组
    for (j = 0; j < n; j++) {
        B[j] = 0;    
    }    // 标记存在的正整数
    for (i = 0; i < n; i++) {
        if (A[i] > 0 && A[i] <= n) {
            a=A[i];
            B[a-1] = 1;
        }
    }    // 寻找第一个未标记的位置
    for (i = 0; i < n; i++) {
        if (B[i] == 0) break;
    }
    return i + 1;
}
