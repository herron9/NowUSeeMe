//
//  parser.h
//  project1
//
//  Created by RR on 4/22/16.
//  Copyright © 2016 rr. All rights reserved.
//

#ifndef parser_h
#define parser_h
#include"treeNode.h"
#include "scanner.h"


#endif /* parser_h */


class parser{
public:
    stack<TreeNode*> AST;
    stack<TreeNode*> ST;
    
    void parserst(FILE *fptr);
    void parserast(FILE *fptr);
    void flattentest(FILE *fptr);
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
    void readNEXT(FILE *fPtr);
    void read(FILE *fPtr,int type);
    
    void rollBack(FILE *Fptr,Token bin);
};