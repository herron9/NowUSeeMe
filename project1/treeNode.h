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
using namespace std;

class TreeNode{
public:
    TreeNode(string value,int type,TreeNode* leftc,TreeNode* rights);
    TreeNode();
    ~TreeNode();
    void setValue(string value);
    void setType(int type);
    string getStrValue();
    int getIntType();
    void addChild(TreeNode* child);
    void preOrder(int root);
    void buildTree(stack<TreeNode*> &ast, int num);
    
private:
    string TN_value;
    int TN_type;
    TreeNode* LeftC;
    TreeNode* RightS;
};

static stack<TreeNode*> AST;


void parser(FILE *fptr);

void E(FILE *fptr);
void Ew(FILE *fptr);

void T(FILE *fptr);
void Ta(FILE *fptr);
void Tc(FILE *fptr);

void B(FILE *fptr);
void Bt(FILE *fptr);
void Bs(FILE *fptr);
void Bp(FILE *fptr);

void A(FILE *fptr);
void At(FILE *fptr);
void Af(FILE *fptr);
void Ap(FILE *fptr);

void R(FILE *fptr);
void Rn(FILE *fptr);

void D(FILE *fptr);
void Da(FILE *fptr);
void Dr(FILE *fptr);
void Db(FILE *fptr);

void Vb(FILE *fptr);
void Vl(FILE *fptr);



void read(FILE *fPtr);
void readENXT(FILE *fPtr);
void read(FILE *fPtr,int type);
void readNEXT(FILE *fPtr,int type);




#endif /* parser_h */
