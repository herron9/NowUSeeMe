//
//  treeNode.h
//  project1
//
//  Created by rr on 3/2/16.
//  Copyright © 2016 rr. All rights reserved.
//

#ifndef treeNode_h
#define treeNode_h
#include<stack>
#include <string>
using namespace std;

class TreeNode{
public:
    TreeNode(string value,int type,TreeNode* leftc,TreeNode* rights);
    TreeNode();
    ~TreeNode();
    void setValue(string value);
    void setType(int type);
    void setVT(string value,int type);
    string getStrValue();
    int getIntType();
    TreeNode* getRS(){return RightS;}
    TreeNode* getLC(){return LeftC;}
    void setRSnull(){RightS=nullptr;}
    void setRS(TreeNode* x){RightS=x;}
    void addChild(TreeNode* child);
    void preOrder(int root);
    void buildTree(stack<TreeNode*> &ast, int num);
    
    void standardizer();

    
private:
    string TN_value;
    int TN_type;
    TreeNode* LeftC;
    TreeNode* RightS;
    
    void stdlet();
    void stdwhere();
    void stdwithin();
    void stdrec();
    void stdfcn();
    void stdlambda();
    void stdand();
    void stdinfix();
};






#endif /* parser_h */
