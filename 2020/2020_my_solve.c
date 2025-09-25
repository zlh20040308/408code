#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAX_SIZE 10000
#define true 1
#define false 0
typedef int bool;
/*
2020年真题：
41.定义三元组(a,b,c)(其中a,b,c均为正数)的距离D=|a-b| + |b-c| + |c-a|。
给定3个非空整数集合S₁、S₂和S₃,按升序分别存储在3个数组中。
设计一个尽可能高效的算法,计算并输出所有可能的三元组(a,b,c)(a∈S₁,b∈S₂,c∈S₃)中的最小距离。
例如S₁={-1,0,9}, S₂= {-25,-10,10,11}, S₃={2,9,17,30,41}, 则最小距离为2, 相应的三元组为(9,10,9)。 
    要求:
    1)给出算法的基本设计思想。
    2)根据设计思想,采用C 或C++语言描述算法,关键之处给出注释。
    3)说明你所设计算法的时间复杂度和空间复杂度。
*/
/*
阿B注：大家直接把代码最末尾的findMin函数内容更改成自己的即可(函数名别改),默认答案为真题ppt上的版本
*/






// 函数声明
int findMin(int A[], int n, int B[], int m, int C[], int p);
int allTestsPassed = 1; // 默认所有测试通过
// 测试函数
void testMinDistance(int A[], int n, int B[], int m, int C[], int p, int expected, const char *desc) {
    printf("%s: ", desc);
    int result = findMin(A, n, B, m, C, p);  // 获取最小距离
    if (result == expected) {
        printf("通过测试\n");
    } else {
        printf("未通过测试, 期望值: %d, 实际值: %d\n", expected, result);
        allTestsPassed = 0;  // 记录有测试未通过
    }
}

// 主函数
int main() {

    // 测试1: 三个集合有重叠的元素
    int A1[] = {1, 5, 10};
    int B1[] = {2, 5, 6, 8};
    int C1[] = {3, 5, 7, 9};
    testMinDistance(A1, 3, B1, 4, C1, 4, 0, "测试1:");

    // 测试2: 负数和正数混合集合
    int A2[] = {-5, 0, 5};
    int B2[] = {-2, 3, 7};
    int C2[] = {-4, 2, 8};
    testMinDistance(A2, 3, B2, 3, C2, 3, 6, "测试2:");

    // 测试3: 集合完全相同
    int A3[] = {1, 2, 3};
    int B3[] = {1, 2, 3};
    int C3[] = {1, 2, 3};
    testMinDistance(A3, 3, B3, 3, C3, 3, 0, "测试3:");

    // 测试4: 集合A和C的元素有差距
    int A4[] = {1, 2, 3};
    int B4[] = {10, 20, 30};
    int C4[] = {100, 200, 300};
    testMinDistance(A4, 3, B4, 3, C4, 3, 194, "测试4:");

    // 测试5: 集合B含有负数
    int A5[] = {1, 2, 3};
    int B5[] = {-1, -2, -3};
    int C5[] = {4, 5, 6};
    testMinDistance(A5, 3, B5, 3, C5, 3, 10, "测试5:");

    // 测试6: 集合B为空
    int A6[] = {1, 2, 3};
    int B6[] = {1};
    int C6[] = {4, 5, 6};
    testMinDistance(A6, 3, B6, 1, C6, 3, 6, "测试6:");

    // 测试7: 集合差距较大
    int A7[] = {1, 100, 1000};
    int B7[] = {10, 100, 1000};
    int C7[] = {100, 1000, 10000};
    testMinDistance(A7, 3, B7, 3, C7, 3, 0, "测试7:");

    // 测试8: 三个集合不重合
    int A8[] = {1, 2, 3};
    int B8[] = {5, 6, 7};
    int C8[] = {9, 10, 11};
    testMinDistance(A8, 3, B8, 3, C8, 3, 12, "测试8:");

    // 测试9: 集合A与B有相同元素
    int A9[] = {5, 10, 15};
    int B9[] = {5, 10, 20};
    int C9[] = {5, 25, 30};
    testMinDistance(A9, 3, B9, 3, C9, 3, 0, "测试9:");

    // 测试10: 较大集合
    int A10[] = {1, 5, 10, 15, 20};
    int B10[] = {2, 6, 11, 16, 21};
    int C10[] = {3, 7, 12, 17, 22};
    testMinDistance(A10, 5, B10, 5, C10, 5, 4, "测试10:");

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
//以下代码是ppt中的标准答案，你可以修改成你自己的，但是findMin函数的名字和参数不要改
//===========================================================================================

int findMin(int A[], int n, int B[], int m, int C[], int p) {

}
