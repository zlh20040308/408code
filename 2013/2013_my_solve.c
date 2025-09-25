#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unordered_map>
#define MaxSize 500
#define true 1
#define false 0
/*
2013年真题：
已知一个整数序列 A = (a0, a1, ..., an-1)，其中 0 <= ai < n (0 <= i < n)。
若存在 ap1 = ap2 = ... = apm = x 且 m > n/2 (0 <= pk < n, 1 <= k <= m)，
则称 x 为 A 的主元素。例如 A = (0, 5, 5, 3, 5, 7, 5, 5)，则 5 为主元素；
又如 A = (0, 5, 5, 3, 5, 1, 5, 7)，则 A 中没有主元素。
假设 A 中的 n 个元素保存在一个一维数组中，请设计一个尽可能高效的算法，找出 A 的主元素。
若存在主元素，则输出该元素；否则输出-1。要求：
    （1）给出算法的基本设计思想。
    （2）根据设计思想，采用 C、C+++或 Java 语言描述算法，关键之处给出注释。
    （3）说明你所设计算法的时间复杂度和空间复杂度。
*/
/*
阿B注：大家直接把代码最末尾的Majority函数内容更改成自己的即可(函数名别改)
*/







// 函数声明
int allTestsPassed = 1;
int Majority(int A[], int n);


// 测试函数
void testMajority(int A[], int n, int expected, const char *desc) {
    printf("%s: \n", desc);
    int result = Majority(A, n);
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

    // 测试1: 主元素为 5
    int case1[] = {0, 5, 5, 3, 5, 7, 5, 5};
    testMajority(case1, 8, 5, "测试1: 输入 {0, 5, 5, 3, 5, 7, 5, 5}");

    // 测试2: 没有主元素
    int case2[] = {0, 5, 5, 3, 5, 1, 5, 7};
    testMajority(case2, 8, -1, "测试2: 输入 {0, 5, 5, 3, 5, 1, 5, 7}");

    // 测试3: 主元素为 1
    int case3[] = {1, 1, 1, 1, 1, 1, 1, 1};
    testMajority(case3, 8, 1, "测试3: 输入 {1, 1, 1, 1, 1, 1, 1, 1}");

    // 测试4: 无主元素
    int case4[] = {1, 2, 2, 2, 3, 4, 5, 2};
    testMajority(case4, 8, -1, "测试4: 输入 {1, 2, 2, 2, 3, 4, 5, 2}");

    // 测试5: 没有主元素
    int case5[] = {1, 2, 3, 4, 5};
    testMajority(case5, 5, -1, "测试5: 输入 {1, 2, 3, 4, 5}");

    // 测试6: 无主元素
    int case6[] = {3, 3, 3, 3, 4, 5, 6, 7};
    testMajority(case6, 8, -1, "测试6: 输入 {3, 3, 3, 3, 4, 5, 6, 7}");

    // 测试7: 输入为一长串相同数字，主元素为 9
    int case7[] = {9, 9, 9, 9, 9, 9, 9, 9, 9, 9};
    testMajority(case7, 10, 9, "测试7: 输入 {9, 9, 9, 9, 9, 9, 9, 9, 9, 9}");

    // 测试8: 没有主元素
    int case8[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    testMajority(case8, 9, -1, "测试8: 输入 {1, 2, 3, 4, 5, 6, 7, 8, 9}");

    // 测试9: 主元素为 3
    int case9[] = {1, 2, 3, 3, 3, 2, 3, 3};
    testMajority(case9, 8, 3, "测试9: 输入 {1, 2, 3, 3, 3, 2, 3, 3}");

    // 测试10: 输入全是零，主元素为 0
    int case10[] = {0, 0, 0, 0, 0};
    testMajority(case10, 5, 0, "测试10: 输入 {0, 0, 0, 0, 0}");

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
以下代码是默认答案，你可以修改成你自己的，但是Majority函数的名字和参数不要改
按照题目要求把值给返回即可
===========================================================================================
*/

// int Majority(int A[], int n) {
//     std::unordered_map<int, int> mp; // 用于记录每个元素出现了几次
//     for(int i = 0; i < n; ++i){ // 逐个统计
//         if(mp.find(A[i]) == mp.end()){
//             mp[A[i]] = 1;
//         }else{
//             mp[A[i]]++;
//         }
//         if(mp[A[i]] > n/2){ // 如果已经满足条件就直接返回
//             return A[i];
//         }
//     }
//     return -1; // 遍历完如果都没找到那就说明不存在
// }


int Majority(int A[], int n) {
    if(n == 0){
        return -1;
    }
    int life = 1;
    int cnt = 0;
    int major = A[0];

    int i = 1;
    while(i < n){
       if(A[i]==major){
        life++;
        i++;
       }else{
        if(life > 1){
            life--;
        }else{
            life=1;
            i+=2;
            if(i>=n){
                return -1;
            }else{
                major=A[i];
            }
        }
       }
    }
    for(int i = 1; i < n; i++){
       if(A[i]==major){
        cnt++;
       }
    }
    if(cnt>n/2){
        return major;
    }
    return -1;
}