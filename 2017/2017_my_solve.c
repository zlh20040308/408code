#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAX_SIZE 10000
#define true 1
#define false 0
typedef int bool;
/*
2017年真题：
41.请设计一个算法，将给定的表达式树（二叉树）转换为等价的中缀表达式（通过括号反映操作符的计算次序）并输出。
例如，当下列两棵表达式树作为算法的输入时，输出的等价中缀表达式分别为(a+b)(c(-d))和(a*b)+(-(c-d))。
要求：
    （1）给出算法的基本设计思想。
    （2）根据设计思想，采用 C 或 C++ 语言描述算法，关键之处给出注释。
*/
/*
阿B注：大家直接把代码最末尾的BtreeToExp函数内容更改成自己的即可(函数名别改)
*/
typedef struct node {
    char data[10]; // 存储操作数或操作符
    struct node *left, *right;
} BTree;
//题目所给出结构体





// 函数声明
void BtreeToExp(BTree *root, int deep); // 这是标准答案
void BtreeToE(BTree *root);
void testBtreeToE(BTree *root, const char *expected, const char *desc);
BTree* createNode(const char *data);
int allTestsPassed = 1;

// 主函数
int main() {
    // 测试1:(a + b) * (c - d)
    BTree *root1 = createNode("*");
    root1->left = createNode("+");
    root1->right = createNode("-");
    root1->left->left = createNode("a");
    root1->left->right = createNode("b");
    root1->right->left = createNode("c");
    root1->right->right = createNode("d");
    testBtreeToE(root1, "(a+b)*(c-d)", "测试1期望结果:(a+b)*(c-d)");

    // 测试2:a * b + -(c - d)
    BTree *root2 = createNode("+");
    root2->left = createNode("*");
    root2->right = createNode("-");
    root2->left->left = createNode("a");
    root2->left->right = createNode("b");
    root2->right->left = createNode("c");
    root2->right->right = createNode("d");
    testBtreeToE(root2, "(a*b)+(c-d)", "测试2期望结果:(a*b)+(c-d)");

    // 测试3:(a+b)*(c*(-d))
    BTree *root3 = createNode("*");
    root3->left = createNode("+");
    root3->right = createNode("*");
    root3->left->left = createNode("a");
    root3->left->right = createNode("b");
    root3->right->left = createNode("c");
    root3->right->right = createNode("-");
    root3->right->right->right = createNode("d");
    testBtreeToE(root3, "(a+b)*(c*(-d))", "测试3期望结果:(a+b)*(c*(-d))");

    // 测试4:(a*b)+(-(c-d))
     BTree *root4 = createNode("+");
     root4->left = createNode("*");
     root4->right = createNode("-");
     root4->left->left = createNode("a");
     root4->left->right = createNode("b");
     root4->right->right = createNode("-");
     root4->right->right->left = createNode("c");
     root4->right->right->right = createNode("d");
     testBtreeToE(root4, "(a*b)+(-(c-d))", "测试4期望结果:(a*b)+(-(c-d))");

    // 测试5:((a+b)*c)-d
    BTree *root5 = createNode("-");
    root5->left = createNode("*");
    root5->right = createNode("d");
    root5->left->left = createNode("+");
    root5->left->right = createNode("c");
    root5->left->left->left = createNode("a");
    root5->left->left->right = createNode("b");
    testBtreeToE(root5, "((a+b)*c)-d", "测试5期望结果:((a+b)*c)-d");

    // 测试6:(a/(b+c))-(d*e)
    BTree *root6 = createNode("-");
    root6->left = createNode("/");
    root6->right = createNode("*");
    root6->left->left = createNode("a");
    root6->left->right = createNode("+");
    root6->left->right->left = createNode("b");
    root6->left->right->right = createNode("c");
    root6->right->left = createNode("d");
    root6->right->right = createNode("e");
    testBtreeToE(root6, "(a/(b+c))-(d*e)", "测试6期望结果:(a/(b+c))-(d*e)");

    // 测试7:a-(b*(c+d))
    BTree *root7 = createNode("-");
    root7->left = createNode("a");
    root7->right = createNode("*");
    root7->right->left = createNode("b");
    root7->right->right = createNode("+");
    root7->right->right->left = createNode("c");
    root7->right->right->right = createNode("d");
    testBtreeToE(root7, "a-(b*(c+d))", "测试7期望结果:a-(b*(c+d))");

    // 测试8:((a+b)*(c+d))-(e/f)
    BTree *root8 = createNode("-");
    root8->left = createNode("*");
    root8->right = createNode("/");
    root8->left->left = createNode("+");
    root8->left->right = createNode("+");
    root8->left->left->left = createNode("a");
    root8->left->left->right = createNode("b");
    root8->left->right->left = createNode("c");
    root8->left->right->right = createNode("d");
    root8->right->left = createNode("e");
    root8->right->right = createNode("f");
    testBtreeToE(root8, "((a+b)*(c+d))-(e/f)", "测试8期望结果:((a+b)*(c+d))-(e/f)");

    // 测试9:-(a+b)*(c-d)
    BTree *root9 = createNode("*");
    root9->left = createNode("-");
    root9->right = createNode("-");
    root9->left->right = createNode("+");
    root9->left->right->left = createNode("a");
    root9->left->right->right = createNode("b");
    root9->right->left = createNode("c");
    root9->right->right = createNode("d");
    testBtreeToE(root9, "-(a+b)*(c-d)", "测试9期望结果:(-(a+b))*(c-d)");

    // 测试10:(((a+b)*c)-d)/e
    BTree *root10 = createNode("/");
    root10->left = createNode("-");
    root10->right = createNode("e");
    root10->left->left = createNode("*");
    root10->left->right = createNode("d");
    root10->left->left->left = createNode("+");
    root10->left->left->right = createNode("c");
    root10->left->left->left->left = createNode("a");
    root10->left->left->left->right = createNode("b");
    testBtreeToE(root10, "(((a+b)*c)-d)/e", "测试10期望结果:(((a+b)*c)-d)/e");

    return 0;
}

// 创建新的节点
BTree* createNode(const char *data) {
    BTree *newNode = (BTree*)malloc(sizeof(BTree));
    strcpy(newNode->data, data);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


// 测试函数
void testBtreeToE(BTree *root, const char *expected, const char *desc) {
    printf("\n%s\n", desc);
    printf("代码实际结果: ");
    // 调用标准答案
    BtreeToE(root);
    printf("\n");
}
/*
===========================================================================================
以下代码是默认答案，你可以修改成你自己的，但是BtreeToExp函数的名字和参数不要改
打印出来的结果需要手动和测试结果对比，如果括号符号字母都没区别就是对啦
===========================================================================================
*/

char *gen_exp(BTree *root){
    if(root == NULL){
        return "";
    }

    if(!strcmp(root->data,"*") && !strcmp(root->data,"/") && !strcmp(root->data,"+") && !strcmp(root->data,"-")){
        return root->data;
    }

    char* lstr = NULL;
    char* rstr = NULL;
    char* exp_str = NULL;

    if(root->left != NULL){
        char* lexp = gen_exp(root->left);
        int lexp_len = strlen(lexp);
        if(lexp_len == 1){
            lstr = lexp;
        }else{
            lstr = malloc(sizeof(char)*lexp_len + 1 + 2);
            strcat(lstr, "(");strcat(lstr, lexp);strcat(lstr, ")");
        }

    }else{
        lstr = "";
    }

    if(root->right != NULL){
        char* rexp = gen_exp(root->right);
        int rexp_len = strlen(rexp);

        if(rexp_len == 1){
            rstr = rexp;
        }else{
            rstr = malloc(sizeof(char)*rexp_len + 1 + 2);
            strcat(rstr, "(");
            strcat(rstr, rexp);
            strcat(rstr, ")");
        }

    }else{
        rstr = "";
    }
    exp_str = malloc(sizeof(char)*strlen(lstr) + sizeof(char)*strlen(rstr) + 1 + 1);
    strcat(exp_str, lstr);
    strcat(exp_str, root->data);
    strcat(exp_str, rstr);
    return exp_str;
}

void BtreeToExp(BTree *root, int deep) {
    printf("%s\n", gen_exp(root));
}

void BtreeToE(BTree *root) {
    BtreeToExp(root, 1); // 根的深度为 1
}
