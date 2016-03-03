//
//  parser.h
//  project1
//
//  Created by rr on 3/2/16.
//  Copyright © 2016 rr. All rights reserved.
//

#ifndef parser_h
#define parser_h
#include <string>
#include<stack>
using namespace std;

class TreeNode{
public:
    TreeNode(string value,int tyoe,TreeNode* leftc,TreeNode* rights);
    void setValue(string value);
    void setType(int type);
    string getStrValue();
    int getIntType();
    void addChild(TreeNode* child);
    void preOrder();
    void buildTree(string TkValue,int TkType,int num);
//    TreeNode* getLeftC();
//    TreeNode* getRightS();
    
private:
    string TN_value;
    int TN_type;
    TreeNode* LeftC;
    TreeNode* RightS;
};

stack<TreeNode> AST;

#endif /* parser_h */
