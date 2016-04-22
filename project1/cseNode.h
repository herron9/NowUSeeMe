//
//  cseNode.h
//  project1
//
//  Created by RR on 4/18/16.
//  Copyright © 2016 rr. All rights reserved.
//

#ifndef cseNode_h
#define cseNode_h
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "treeNode.h"

using namespace std;

enum CseType{
    ID=1,
    INT,
    OP,//3
    UOP,
    STR,
    GAMMa,//6
    LAMBDa,
    YStar,
    ETA,
    TRUTH,//10
    FALSe,
    DELTA,
    ENV,
    NIL,
    DUMMY,
    TAU,
    TUPLE,
    COND,
    BATA,//19

    
};
class cseNode{
public:
    CseType cse_Type;
//    virtual cseNode(CseType ty);
};

class envC: public cseNode{
public:
    envC* previous;
    int value;
    map<string,int> pairs;
    
};

class idC: public cseNode{
public:
    idC(CseType ty,string val){cse_Type=ty;value=val;}
    string value;
};

class intC: public cseNode{
public:
    intC(CseType ty,string val){cse_Type=ty;value=val;}
    string value;
};

class opC: public cseNode{
public:
    opC(CseType ty,string val){cse_Type=ty;value=val;}
    string value;
};

class UopC: public cseNode{
public:
    UopC(CseType ty,string val){cse_Type=ty;value=val;}
    string value;
};

class strC: public cseNode{
public:
    strC(CseType ty,string val){cse_Type=ty;value=val;}
    string value;
};

class gammaC: public cseNode{
public:
    gammaC(CseType ty){cse_Type=ty;}
    
};

class lambdaC: public cseNode{
public:
    lambdaC(CseType ty,TreeNode* ind){cse_Type=ty;index=ind;env=nullptr;}
    TreeNode* index;
    vector<cseNode*> variable;
    envC* env;
    
};

class YstarC: public cseNode{
public:
    YstarC(CseType ty){cse_Type=ty;}
    
};

class truthvalueC: public cseNode{
public:
    truthvalueC(CseType ty,bool val){cse_Type=ty;value=val;}
    bool value;
    
};

class tauC: public cseNode{
public:
    tauC(CseType ty,int val){cse_Type=ty;value=val;}
    int value;
};

class tupleC: public cseNode{
public:
    tupleC(CseType ty){cse_Type=ty;}
    vector<cseNode*> tuple;
};

class condC: public cseNode{
public:
    condC(CseType ty,TreeNode* thenx,TreeNode* elsEx){cse_Type=ty;then=thenx;elsE=elsEx;}
    TreeNode* then;
    TreeNode* elsE;
    
};

class etaC: public cseNode{
public:
    etaC(CseType ty,TreeNode* ind,envC* envx){cse_Type=ty;index=ind;env=envx;}
    TreeNode* index;
    //    vector<cseNode> vb;
    envC* env;
};

class nilC: public cseNode{
public:
    nilC(CseType ty){cse_Type=ty;}
};

class dummyC: public cseNode{
public:
    
};




#endif /* cseNode_h */
