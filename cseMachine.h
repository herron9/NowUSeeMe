//
//  cseMachine.h
//  project1
//
//  Created by RR on 4/22/16.
//  Copyright © 2016 rr. All rights reserved.
//

#ifndef cseMachine_h
#define cseMachine_h
#include <vector>
#include "cseNode.h"
using namespace std;


#endif /* cseMachine_h */


class CSE{
public:
    TreeNode* root;
    void flatten(TreeNode* node);
    vector<cseNode*> CONTROL;
    vector<cseNode*> STACK;
    
    void print(vector<cseNode*> csev);
    void prints(vector<cseNode*> csev);
    void printenv(vector<cseNode*> csev);
    void printenvs(vector<cseNode*> csev);
    
    void runCSE(TreeNode* node);
    
    cseNode* lookup(cseNode* node,envC* envc);
    cseNode* naryConvert(cseNode* node,cseNode* rand);
    cseNode* binop(cseNode* op,cseNode* rand1,cseNode* rand2);
    cseNode* uop(cseNode* op,cseNode* rand);
    cseNode* maketuple(cseNode* tup);
    void     intrinsicFn(cseNode* intrinsic);
    void     ISintrinsicFn(cseNode* node);
    void     HasTAB(cseNode* node);

    
    
};