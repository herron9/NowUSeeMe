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
    TRUTH,
    FALSe,
    DELTA,
    ENV,
    NIL,
    DUMMY,
    TAU,
    TUPLE,
    COND,

    
};
class cseNode{
public:
    CseType cse_Type;
//    virtual cseNode(CseType ty);
};

class idC: public cseNode{
public:
    string value;
};

class intC: public cseNode{
public:
    int value;
};

class opC: public cseNode{
public:
    string value;
};

class UopC: public cseNode{
public:
    string value;
};

class strC: public cseNode{
public:
    string value;
};

class gammaC: public cseNode{
public:
    
};

class lambdaC: public cseNode{
public:
    TreeNode* index;
    vector<cseNode*> variable;
    int env;
    
};

class YstarC: public cseNode{
public:
    
};

class truthvalueC: public cseNode{
public:
    bool value;
    
};

class tauC: public cseNode{
public:
    int value;
};

class tupleC: public cseNode{
public:
    vector<cseNode*> tuple;
};

class condC: public cseNode{
public:
    TreeNode* then;
    TreeNode* elsE;
    
};

class etaC: public cseNode{
public:
    TreeNode* index;
    //    vector<cseNode> vb;
    int env;
};

class nilC: public cseNode{
public:
    
};

class dummyC: public cseNode{
public:
    
};

class envC: public cseNode{
public:
    envC* previous;
    int value;
    map<string,int> pairs;

};

static stack<cseNode*> CONTROL;
static stack<cseNode*> STACK;


void CtoS(stack<cseNode*> csest);
void print(stack<cseNode*> csest);




#endif /* cseNode_h */
