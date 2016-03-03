//
//  main.cpp
//  proj1
//
//  Created by rr on 2/28/16.
//  Copyright © 2016 rr. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string>
#include "Token.h"
#include "scanner.h"
#include "parser.h"
using namespace std;

stack<TreeNode> AST;

int main() {
//    FILE *fPtr =fopen("/Users/herron/Documents/share/rpal/tests/tiny","r");
////    FILE *fPtr =fopen("/Users/herron/Documents/PLPproj/project1/project1/demo1","r");
//
//    
//    fseek(fPtr, 0, SEEK_END);//check if input file is empty
//    if (ftell(fPtr) == 0) {
//        printf("File is empty.\n");
//        exit(1);
//    } else {
//        rewind(fPtr);
//    }
//    Token outPut=Token("start", UNDEF);
//    while (outPut.getStrValue()!="end"&&outPut.getStrValue()!="errorInput") {
//            outPut=scanner(fPtr);
//        cout<<"TokenV= "<<outPut.getStrValue()<<" TokenT= "<<outPut.getIntType()<<endl;
//        }
//    fclose(fPtr);
    TreeNode x1=TreeNode("111", INTEGER, nullptr, nullptr);
    TreeNode x2=TreeNode("222", INTEGER, nullptr, nullptr);
    TreeNode x3=TreeNode("+", OPERATOR, nullptr, nullptr);
    AST.push(x1);
    AST.push(x2);
    x3.buildTree(2);
//    x3.preOrder();

    return 0;
}

void TreeNode::buildTree(int num){
    TreeNode* temp=nullptr;
    TreeNode* temp1=nullptr;
    while (num>0) {
        temp1=&AST.top();
        temp1->RightS=temp;
        temp=temp1;
        AST.pop();
        num--;
    }
    TreeNode newnode= TreeNode(TN_value,TN_type,nullptr,nullptr);
    newnode.LeftC=temp;
    AST.push(newnode);  
//    newnode.preOrder();
}