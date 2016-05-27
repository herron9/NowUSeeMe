//
//  standardizer.cpp
//  project1
//
//  Created by RR on 4/17/16.
//  Copyright © 2016 rr. All rights reserved.
//

#include <stdio.h>
#include <string>
#include "treeNode.h"
#include <iostream>

void TreeNode::standardizer(){
    if (TN_value.length()==0&&TN_type!=4){///????
        return;
    }
    if (LeftC!=NULL) {
        LeftC->standardizer();
    }
    if (RightS!=NULL) {
        RightS->standardizer();
    }
    switch (TN_type) {
        case 600: this->stdlet(); break;//let
        case 603: this->stdwhere(); break;//where
        case 617: this->stdwithin(); break;//within
        case 619: this->stdrec(); break;
        case 505: this->stdfcn(); break;
        case 10 : this->stdlambda(); break;
        case 618: this->stdand(); break;
        case 309: this->stdinfix(); break;
//        default: cout<<TN_type<<endl;
    }
}

void TreeNode::stdlet(){
    setVT("gamma", 9);
    TreeNode* eq=LeftC;
    TreeNode* p=eq->RightS;
    TreeNode* x=eq->LeftC;
    TreeNode* e=x->RightS;
    eq->setVT("lambda", 10);
    eq->RightS=e;
    x->RightS=p;
}

void TreeNode::stdwhere(){
    setVT("gamma", 9);
    TreeNode* p=LeftC;
    TreeNode* eq=p->RightS;
    TreeNode* x=eq->LeftC;
    TreeNode* e=x->RightS;
    eq->setVT("lambda", 10);
    LeftC=eq;
    eq->RightS=e;
    x->RightS=p;
    p->RightS=nullptr;
    
}

void TreeNode::stdwithin(){
    setVT("=", 311);
    TreeNode* eqL=LeftC;
    TreeNode* eqR=eqL->RightS;
    TreeNode* x1=eqL->LeftC;
    TreeNode* e1=x1->RightS;
    TreeNode* x2=eqR->LeftC;
    TreeNode* e2=x2->RightS;
    LeftC=x2;
    eqL->setVT("lambda", 10);
    eqR->setVT("gamma", 9);
    x2->RightS=eqR;
    eqR->LeftC=eqL;
    eqL->RightS=e1;
    x1->RightS=e2;
    
}

void TreeNode::stdrec(){
    setVT("=", 311);
//    TreeNode* x= LeftC->LeftC;
//    delete LeftC;
//    LeftC= new TreeNode(x->TN_value,x->TN_type,x->LeftC,x->RightS);
//    
//    TreeNode* G= new TreeNode("gamma",9,nullptr,nullptr);
//    LeftC->RightS=G;
//    TreeNode* Y= new TreeNode("Y*",11,nullptr,nullptr);
//    G->LeftC=Y;
//    TreeNode* L= new TreeNode("lambda",10,x,nullptr);
//    Y->RightS=L;
//    G->LeftC->RightS=L;
    
    TreeNode* x= LeftC->LeftC;
//    delete LeftC;
    LeftC= new TreeNode(x->TN_value,x->TN_type,nullptr,nullptr);
    TreeNode* Y= new TreeNode("Y*",11,nullptr,nullptr);
    TreeNode* G= new TreeNode("gamma",9,Y,nullptr);
    LeftC->RightS=G;
    TreeNode* L= new TreeNode("lambda",10,x,nullptr);
    G->LeftC->RightS=L;
    
//    eq->setVT("lambda", 10);
//    TreeNode* x=eq->LeftC;
//    TreeNode* xup=new TreeNode(x->TN_value,x->TN_type,nullptr,nullptr);
//    eq->LeftC=x;
//    TreeNode* Y= new TreeNode("Y*",11,nullptr,eq);
//    TreeNode* G= new TreeNode("gamma",9,Y,nullptr);
//    LeftC=xup;
//    xup->RightS=G;
//    xup->LeftC=nullptr;
}

void TreeNode::stdfcn(){
    setVT("=", 311);
    TreeNode* p=LeftC;
    TreeNode* v=p->RightS;
    TreeNode* L= new TreeNode("lambda",10,v,nullptr);
//    L->LeftC=v;
    p->RightS=L;
    TreeNode* temp=v->RightS;//the next V or E(when ->rightS=nulllptr)
    while (temp->RightS!=nullptr) {
        TreeNode* L= new TreeNode("lambda",10,nullptr,nullptr);
        v->RightS=L;
        L->LeftC=temp;
        v=temp;
        temp=v->RightS;
    }
}

void TreeNode::stdlambda(){
    TreeNode* v=LeftC;
    TreeNode* temp=v->RightS;
    while (temp->RightS!=nullptr) {
        TreeNode* L= new TreeNode("lambda",10,temp,nullptr);
        v->RightS=L;
//        L->LeftC=temp;
        v=temp;
        temp=v->RightS;
    }

}

void  TreeNode::stdand(){
    setVT("=", 311);
    TreeNode* eq=LeftC;
    TreeNode* x=eq->LeftC;
    TreeNode* e=x->RightS;
    TreeNode* temp =eq->RightS;
    TreeNode* tau= new TreeNode("tau",506,e,nullptr);
    TreeNode* comma= new TreeNode(",",503,x,tau);
    LeftC=comma;
    while (temp!=nullptr) {
        x->RightS=temp->LeftC;
        x=x->RightS;
        e->RightS=temp->LeftC->RightS;
        e=e->RightS;
        temp=temp->RightS;
    }
    x->RightS=nullptr;
    
}

void TreeNode::stdinfix(){
    setVT("gamma", 9);
    TreeNode* e1=LeftC;
    TreeNode* n=e1->RightS;
    TreeNode* e2=n->RightS;
    TreeNode* G= new TreeNode("gamma",9,n,e2);
    LeftC=G;
    n->RightS=e1;
    e1->RightS=nullptr;
}





