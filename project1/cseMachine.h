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
    void CtoS(stack<cseNode*> csest);
    void print(stack<cseNode*> csest);

    
    
};