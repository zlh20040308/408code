#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAX_SIZE 10000
#define true 1
#define false 0
typedef int bool;
/*
2016年真题：
43. 已知由 n (n>=2) 个正整数构成的集合 A={a_k|0<=k<n}，将其划分为两个不相交的子集 A1 和 A2，元素个数分别是 n1 和 n2，A1 和 A2 中元素之和分别为 S1 和 S2。
设计一个尽可能高效的划分算法，满足 |n1-n2| 最小且 |S1-S2| 最大。
要求：
    （1）给出算法的基本设计思想。
    （2）根据设计思想，采用 C 或 C++ 语言描述算法，关键之处给出注释。
    （3）说明你所设计算法的平均时间复杂度和空间复杂度。
*/
/*
阿B注：大家直接把代码最末尾的findMin函数内容更改成自己的即可(函数名别改)
本测试代码要求返回|S1-S2| ，根据这个值来判断是否通过测试
*/






// 函数声明
int setPartition(int a[], int n);
int allTestsPassed = 1;

void testSetPartition(int a[], int n, int expected, const char *desc) {
    printf("%s: ", desc);
    int result = setPartition(a, n);
    
    if (result == expected) {
        printf("✅ 通过测试\n");
    } else {
        printf("❌ 未通过测试\n");
        printf("  期望输出: %d\n", expected);
        printf("  实际输出: %d\n", result);
        allTestsPassed = 0;
    }
}

int main() {

    // 测试1: 输入数组为 {1, 2, 3, 4, 5}, 期望返回的结果为相差1的最优划分
    int case1[] = {4, 2, 3, 1, 5};
    testSetPartition(case1, 5, 9, "测试1: 输入数组 {1, 2, 3, 4, 5}");

    // 测试2: 输入数组为 {1, 3, 2, 5, 4}, 期望返回的结果为划分后最优的差
    int case2[] = {1, 3, 2, 5, 4};
    testSetPartition(case2, 5, 9, "测试2: 输入数组 {1, 3, 2, 5, 4}");

    // 测试3: 输入数组为 {30, 20, 50, 40, 10}, 期望返回的最优划分差
    int case3[] = {30, 20, 50, 40, 10};
    testSetPartition(case3, 5, 90, "测试3: 输入数组 {30, 20, 50, 40, 10}");

    // 测试4: 输入数组为 {5, 5, 5, 5, 5}, 期望返回结果为0
    int case4[] = {5, 5, 5, 5, 5};
    testSetPartition(case4, 5, 5, "测试4: 输入数组 {5, 5, 5, 5, 5}");

    // 测试5: 输入数组为 {7, 3, 9, 1, 6, 4}, 期望返回结果为最大的划分差
    int case5[] = {7, 3, 9, 1, 6, 4};
    testSetPartition(case5, 6, 14, "测试5: 输入数组 {7, 3, 9, 1, 6, 4}");

    // 测试6: 输入数组为 {1, 1, 1, 1}, 期望返回结果为0
    int case6[] = {1, 1, 1, 1};
    testSetPartition(case6, 4, 0, "测试6: 输入数组 {1, 1, 1, 1}");

    // 测试7: 输入数组为 {4, 6, 10, 2, 8}, 期望返回结果为0
    int case7[] = {4, 6, 10, 2, 8};
    testSetPartition(case7, 5, 18, "测试7: 输入数组 {4, 6, 10, 2, 8}"); 

    // 测试8: 输入数组为 {5, 7, 9, 1, 3}, 期望返回结果为0
    int case8[] = {5, 7, 9, 1, 3};
    testSetPartition(case8, 5, 17, "测试8: 输入数组 {5, 7, 9, 1, 3}");

    // 测试9: 输入数组为 {1, 5, 9, 14}, 期望返回结果为17
    int case9[] = {1, 5, 9, 14};
    testSetPartition(case9, 4, 17, "测试8: 输入数组 {1, 5, 9, 14}");

    // 测试9: 输入数组为 {1,5,9,16,85,2,7,12,77}, 期望返回结果为184
    int case10[] = {1,5,9,16,85,2,7,12,77};
    testSetPartition(case10, 9, 184, "测试8: 输入数组 {1,5,9,16,85,2,7,12,77}");


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
以下代码是默认答案，你可以修改成你自己的，但是setPartition函数的名字和参数不要改
传入数组和数组长度，最后请返回|s2-s1|
===========================================================================================
*/

int setPartition(int a[], int n) {
    int pivokey = 0, low = 0,low0=0, high = n-1,high0=n-1 , flag = 1, k = n/2, i;
    int s1 = 0, s2 = 0;
    
    while(flag) {
        pivokey = a[low];  // 选择枢纽
        while(low < high) {
            while(low < high && a[high] >= pivokey) --high;
            if(low != high) a[low] = a[high]; // 替换较大的数
            while(low < high && a[low] <= pivokey) ++low;
            if(low != high) a[high] = a[low]; // 替换较小的数
        }  // end of while(low < high)
        
        a[low] = pivokey; // 完成交换枢纽
        if(low == k-1) {  // 如果枢纽是第n/2 小元素，划分成功
            flag = 0;
        }
        else {
            if(low < k-1) { // 向右继续划分
                low0=++low;
                high=high0;
            } else { // 向左继续划分
                high0 = --high;
                low=low0;
            }
        }
    }
    
    for(i=0; i<k; i++) s1 += a[i];
    for(i=k; i<n; i++) s2 += a[i];
    return s2-s1;

}


