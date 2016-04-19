//
//  cseNode.h
//  project1
//
//  Created by RR on 4/18/16.
//  Copyright © 2016 rr. All rights reserved.
//

#ifndef cseNode_h
#define cseNode_h
#include<vector>
enum CseType{
    UNDEF,//0
    ID,
    INT,
    OP,//3
    STR,
    PU,//5 non sense
    KW,
    EORROR,
    EOT,
    GAMMA,
    LAMBDA,//10
    Ystar,
};
class cseNode{
    int cse_Type;
    
};
class idf: public cseNode{
    
};
class lambda: public cseNode{
    
    TreeNode* index;
    vector<cseNode> vb;
    int env;
    
};


#endif /* cseNode_h */
