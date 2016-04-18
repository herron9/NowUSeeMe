//
//  treeNode.cpp
//  project1
//
//  Created by rr on 3/4/16.
//  Copyright © 2016 rr. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <iostream>
#include "treeNode.h"
using namespace std;

TreeNode::TreeNode(string value,int type,TreeNode* leftc,TreeNode* rights){
    TN_value=value;
    TN_type=type;
    this->LeftC = leftc;
    this->RightS = rights;
}

TreeNode::TreeNode(){
    this->LeftC = nullptr;
    this->RightS = nullptr;
}

TreeNode::~TreeNode(){
    if (LeftC != nullptr) delete LeftC;
    if (RightS != nullptr) delete RightS;
}

void TreeNode::setValue(string value){
    TN_value=value;
    
}
void TreeNode::setType(int type){
    TN_type=type;
}

void TreeNode::setVT(string value, int type){
    TN_value=value;
    TN_type=type;
}
string TreeNode::getStrValue(){
    return TN_value;
}
int TreeNode::getIntType(){
    return TN_type;
}
void TreeNode::addChild(TreeNode* child){
    if (LeftC==nullptr) {
        LeftC=child;
    }else if (LeftC!=nullptr){
        if (LeftC->RightS==nullptr) {
            LeftC->RightS=child;
        }else {
            TreeNode* temp;
            temp=LeftC->RightS;
            while (temp!=nullptr) {
                temp=temp->RightS;
            }
            temp=child;
        }
    }
}

void TreeNode::preOrder(int root){
    int temp=root;
    string dot="";
    while (temp>0) {
        dot=dot+".";
        temp--;
    }
    switch (TN_type) {
        case 1: cout<<dot<<"<ID:"<<TN_value<<">"<<endl; break;
        case 2: cout<<dot<<"<INT:"<<TN_value<<">"<<endl; break;
        case 4: cout<<dot<<"<STR:'"<<TN_value<<"'>"<<endl; break;
        case 613: cout<<dot<<"<"<<TN_value<<">"<<endl; break;
        case 614: cout<<dot<<"<"<<TN_value<<">"<<endl; break;
        case 615: cout<<dot<<"<"<<TN_value<<">"<<endl; break;
        case 616: cout<<dot<<"<"<<TN_value<<">"<<endl; break;
        case 11: cout<<dot<<"<"<<TN_value<<">"<<endl; break;
        default: cout<<dot<<TN_value<<endl; break;
            
    }
    if (this->LeftC != nullptr) this->LeftC->preOrder(root+1);
    if (this->RightS != nullptr) this->RightS->preOrder(root);
}

void TreeNode::buildTree(stack<TreeNode*> &ast, int num){
    TreeNode* temp=nullptr;
    TreeNode* temp1=nullptr;
    while (num>0) {
        temp1=ast.top();
        temp1->RightS=temp;
        temp=temp1;
        ast.pop();
        num--;
    }
    LeftC=temp;
    ast.push(&(*this));
}
