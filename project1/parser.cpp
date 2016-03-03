//
//  parser.cpp
//  project1
//
//  Created by rr on 3/2/16.
//  Copyright © 2016 rr. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "parser.h"
#include "Token.h"
//#include "scanner.h"


//    stack<TreeNode> AST;

TreeNode::TreeNode(string value,int type,TreeNode* leftc=nullptr,TreeNode* rights=nullptr){
    TN_value=value;
    TN_type=type;
}
TreeNode::TreeNode(){

}

void TreeNode::setValue(string value){
    TN_value=value;
    
}
void TreeNode::setType(int type){
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

void TreeNode::preOrder(){
    cout<<"TokenValue"<<TN_value<<"  TokenType"<<TN_type<<endl;
    LeftC->preOrder();
    RightS->preOrder();
}

//void TreeNode::buildTree(string TkValue,int TkType,int num){
//    TreeNode* temp=nullptr;
//    TreeNode* temp1=nullptr;
//    for (int i=0; i<num; num++) {
//        temp1=&AST.top();
//        temp1->RightS=temp;
//        temp=temp1;
//        AST.pop();
//    }
//    TreeNode newnode= TreeNode(TkValue,TkType,nullptr,nullptr);
//    newnode.LeftC=temp;
//    AST.push(newnode);
//}



//void ErrorMsg(Token errorToken,string msg){
//    cout<<errorToken.getStrValue()<<" "<<msg<<endl;
//}

//void readToekn(Token token){
//    if(token!=NT) ErrorMsg(token, "error!!");
//        
//    
//}










