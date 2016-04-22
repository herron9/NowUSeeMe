//
//  parser.cpp
//  project1
//
//  Created by rr on 3/2/16.
//  Copyright © 2016 rr. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "cseNode.h"
#include "scanner.h"

static Token symbol=Token("",0);
static Token NEXTsymbol=Token("",0);

TreeNode* CreateNode(Token token){
    TreeNode* node= new TreeNode(token.getStrValue(), token.getIntType(), nullptr, nullptr);
    return node;
}

TreeNode* CreateNode(string value,int type){
    TreeNode* node= new TreeNode(value, type, nullptr, nullptr);
    return node;
}

void read(FILE *fPtr){
    switch (symbol.getIntType()) {
        case 8: break;
        default:
            Token token=scanner(fPtr);
            switch (token.getIntType()) {
                case 7: cerr<<"unexpectedToken "<<token.getStrValue()<<endl;  exit(1); break;
                default: symbol=token; break;
            }
             break;
    }
}

void readNEXT(FILE *fPtr){
    switch (symbol.getIntType()) {
        case 8: break;
        default:
            Token token=scanner(fPtr);
            switch (token.getIntType()) {
                case 7: cerr<<"unexpected token"<<token.getStrValue()<<endl;  exit(1); break;
                default: NEXTsymbol=token; break;
                    
            }
            break;
    }
}
void read(FILE *fPtr,int type){
    switch (symbol.getIntType()) {
        case 8: break;
        default:
            Token token=scanner(fPtr);
            tokenType x=tokenType(type);
            if ("errorInput"==token.getStrValue()||type!=token.getIntType()) {
                cerr<<"unexpected token"<<token.getStrValue()<<" expected "<<x<<endl;
                exit(1);
            }else symbol=token;
            break;
    }
}

void rollBack(FILE *fPtr,Token bin){
    int temp=int(bin.getStrValue().size());
    if (4!=bin.getIntType()&&8!=bin.getIntType()) {
        fseek(fPtr, -temp, SEEK_CUR);
    }else if(4==bin.getIntType()&&8!=bin.getIntType()){
        temp=(int(bin.getStrValue().size())+2);
        fseek(fPtr, -temp, SEEK_CUR);
    }
    if(8==bin.getIntType()){;}
    
}


void E(FILE *fPtr){
    read(fPtr);
    if(600==symbol.getIntType()){//let
        D(fPtr);
        read(fPtr, 601);
        E(fPtr);
        CreateNode("let",600)->buildTree(AST, 2);
    }else if(602==symbol.getIntType()){//fn
        int num=0;
        read(fPtr);
        while (1==symbol.getIntType()||500==symbol.getIntType()) {
            rollBack(fPtr, symbol);
            Vb(fPtr);
            num++;
            read(fPtr);
        }
        rollBack(fPtr,symbol);
        read(fPtr, 308);
        E(fPtr);
        CreateNode("lambda",10)->buildTree(AST, num+1);
        
    }else {
        rollBack(fPtr, symbol);
        Ew(fPtr);
    }
}

void Ew(FILE *fPtr){
    T(fPtr);
    read(fPtr);
    Token temp = symbol;
    switch (temp.getIntType()) {
        case 603: Dr(fPtr); CreateNode(temp)->buildTree(AST, 2); break;
        default:  rollBack(fPtr, symbol); break;
    }
}

void T(FILE *fPtr){
    Ta(fPtr);
    read(fPtr);
    if(503==symbol.getIntType()){
        int num=0;
        while (503==symbol.getIntType()) {
            Ta(fPtr);
            num++;
            read(fPtr);
        }
        CreateNode("tau",506)->buildTree(AST, num+1);
        rollBack(fPtr, symbol);
    }else rollBack(fPtr, symbol);
}

void Ta(FILE *fPtr){
    Tc(fPtr);
    read(fPtr);
    while (604==symbol.getIntType()) {
        Token temp=symbol;
        Tc(fPtr);
        CreateNode(temp)->buildTree(AST, 2);
        read(fPtr);
    }
    rollBack(fPtr,symbol);
}

void Tc(FILE *fPtr){
    B(fPtr);
    read(fPtr);
    Token temp = symbol;
    switch (temp.getIntType()) {
        case 315: Tc(fPtr); read(fPtr,313); Tc(fPtr); CreateNode(temp)->buildTree(AST, 3); break;
        default:  rollBack(fPtr,symbol); break;
    }
}

void B(FILE *fPtr){
    Bt(fPtr);
    read(fPtr);
    while (605==symbol.getIntType()) {
        Token temp=symbol;
        Bt(fPtr);
        CreateNode(temp)->buildTree(AST, 2);
        read(fPtr);
    }
    rollBack(fPtr,symbol);
    
}

void Bt(FILE *fPtr){
    Bs(fPtr);
    read(fPtr);
    while (307==symbol.getIntType()) {
        Token temp=symbol;
        Bs(fPtr);
        CreateNode(temp)->buildTree(AST, 2);
        read(fPtr);
    }
    rollBack(fPtr,symbol);
}

void Bs(FILE *fPtr){
    read(fPtr);
    if (606==symbol.getIntType()) { Bp(fPtr); CreateNode("not",606)->buildTree(AST, 1);}//???
    else{
        rollBack(fPtr,symbol);
        Bp(fPtr);
    }
}

void Bp(FILE *fPtr){
    A(fPtr);
    read(fPtr);
    Token temp = symbol;
    switch (temp.getIntType()) {
        case 305: A(fPtr); CreateNode("gr",305)->buildTree(AST, 2); break;
        case 306: A(fPtr); CreateNode("ge",306)->buildTree(AST, 2); break;
        case 303: A(fPtr); CreateNode("ls",303)->buildTree(AST, 2); break;
        case 304: A(fPtr); CreateNode("le",304)->buildTree(AST, 2); break;
        case 311: A(fPtr); CreateNode(temp)->buildTree(AST, 2); break;
        case 312: A(fPtr); CreateNode(temp)->buildTree(AST, 2); break;
        default: rollBack(fPtr, symbol); break;
    }
}

void A(FILE *fPtr){
    read(fPtr);
    if (300==symbol.getIntType()) {At(fPtr);} else
    if (301==symbol.getIntType()) {At(fPtr);CreateNode("neg", KW_neg)->buildTree(AST, 1);}
    else {
        rollBack(fPtr, symbol);
        At(fPtr);}
    read(fPtr);
    while (300==symbol.getIntType()||301==symbol.getIntType()) {
        Token temp=symbol;
        At(fPtr);
        CreateNode(temp)->buildTree(AST, 2);
        read(fPtr);
    }
    rollBack(fPtr,symbol);
    
}

void At(FILE *fPtr){
    Af(fPtr);
    read(fPtr);
    while (302==symbol.getIntType()||310==symbol.getIntType()) {
        Token temp=symbol;
        Af(fPtr);
        CreateNode(temp)->buildTree(AST, 2);
        read(fPtr);
    }
    rollBack(fPtr,symbol);
}

void Af(FILE *fPtr){
    Ap(fPtr);
    read(fPtr);
    switch (symbol.getIntType()) {
        case 504:  Af(fPtr); CreateNode("**",504)->buildTree(AST,2); break;//**  ????
        default: rollBack(fPtr, symbol);
    }
}
void Ap(FILE *fPtr){
    R(fPtr);
    read(fPtr);
    while (309==symbol.getIntType()) {
        read(fPtr, 1);
        CreateNode(symbol)->buildTree(AST, 0);//?????
        R(fPtr);
        CreateNode("@",309)->buildTree(AST, 3);
        read(fPtr);
    }
    rollBack(fPtr,symbol);
}

void R(FILE *fPtr){//?
    Rn(fPtr);
    read(fPtr);
    while (1==symbol.getIntType()||2==symbol.getIntType()||
           4==symbol.getIntType()||613==symbol.getIntType()||
           614==symbol.getIntType()||615==symbol.getIntType()||
           500==symbol.getIntType()||616==symbol.getIntType())
    {
        rollBack(fPtr,symbol);
        Rn(fPtr);
        CreateNode("gamma",9)->buildTree(AST, 2);
        read(fPtr);}
    rollBack(fPtr, symbol);
}

void Rn(FILE *fPtr){
    read(fPtr);
    switch (symbol.getIntType()) {
        case 1:  CreateNode(symbol)->buildTree(AST, 0); break;
        case 2:  CreateNode(symbol)->buildTree(AST, 0); break;
        case 4:  CreateNode(symbol)->buildTree(AST, 0); break;
        case 613:  CreateNode(symbol)->buildTree(AST, 0); break;
        case 614:  CreateNode(symbol)->buildTree(AST, 0); break;
        case 615:  CreateNode(symbol)->buildTree(AST, 0); break;
        case 500:  E(fPtr); read(fPtr, 501); break;
        case 616:  CreateNode(symbol)->buildTree(AST, 0); break;
        default: cerr<<"Unexpected token "<<symbol.getStrValue()<<endl; break;
    }
}

void Db(FILE *fPtr){
    read(fPtr);
    if (500==symbol.getIntType()) {//( D )
        D(fPtr);
        read(fPtr,501);
    }else{// <ID> Vb+ = E
        long temp=ftell(fPtr);
        readNEXT(fPtr);
        long tempnext=ftell(fPtr);
        if (1==symbol.getIntType()&&(500==NEXTsymbol.getIntType()||1==NEXTsymbol.getIntType())) {
            CreateNode(symbol)->buildTree(AST, 0);//first ID
            rollBack(fPtr,NEXTsymbol);
            read(fPtr);
            int N=0;
            while (1==symbol.getIntType()||500==symbol.getIntType()) {
                rollBack(fPtr, symbol);
                Vb(fPtr);
                N++;
                read(fPtr);
            }
            rollBack(fPtr, symbol);
            read(fPtr, 311);
            E(fPtr);
            CreateNode("function_form", 505)->buildTree(AST, N+2);
        }else{
            fseek(fPtr, (temp-tempnext), SEEK_CUR);
            rollBack(fPtr, symbol);
            Vl(fPtr);
            read(fPtr,311);
            E(fPtr);
            CreateNode("=", 311)->buildTree(AST,2);//????
        }
    }
    
}

void Dr(FILE *fPtr){
    read(fPtr);
    if (619==symbol.getIntType()) {
        Db(fPtr);
        CreateNode("rec", 619)->buildTree(AST, 1);//?????
    }else{
        rollBack(fPtr,symbol);
        Db(fPtr);
    }
}

void Da(FILE *fPtr){
    Dr(fPtr);
    read(fPtr);
    if (618==symbol.getIntType()) {//and
        int num=0;
        while (618==symbol.getIntType()) {
            Dr(fPtr);
            num++;
            read(fPtr);
        }
        CreateNode("and",618)->buildTree(AST, num+1);
    }
    rollBack(fPtr,symbol);
}

void D(FILE *fPtr){
    Da(fPtr);
    read(fPtr);
    switch (symbol.getIntType()) {
        case 617: D(fPtr); CreateNode("within",617)->buildTree(AST, 2); break;//????
        default:rollBack(fPtr, symbol); break;
    }
}


void Vb(FILE *fPtr){
        read(fPtr);
    if (500==symbol.getIntType()) {
        read(fPtr);
        if (501==symbol.getIntType()) {//'('')'
            CreateNode("()", 504)->buildTree(AST, 0);
        }else {//( vl )
            rollBack(fPtr, symbol);
            Vl(fPtr);
            read(fPtr,501);
        }
    }else{//<ID>
        CreateNode(symbol)->buildTree(AST, 0);
    }
}

void Vl(FILE *fPtr){
    read(fPtr);
    if (1==symbol.getIntType()) {//ID
        CreateNode(symbol)->buildTree(AST, 0);
    }else{cerr<<"vl crashed"<<endl;}
    read(fPtr);
    int num=0;
    if(503==symbol.getIntType()){
        while (503==symbol.getIntType()) {
            read(fPtr,1);
            CreateNode(symbol)->buildTree(AST, 0);
            read(fPtr);
            num++;
        }
        rollBack(fPtr, symbol);
        CreateNode(",",503)->buildTree(AST, num+1);
        
    }else{
        rollBack(fPtr, symbol);
    }
    
}
　　

void parserast(FILE *fPtr){
    E(fPtr);
    ST=AST;
    AST.top()->preOrder(0);
}

void parserst(FILE *fPtr){
    E(fPtr);
    ST=AST;
    ST.top()->standardizer();
    ST.top()->preOrder(0);

}
void flattentest(FILE *fPtr){
    E(fPtr);
    ST=AST;
    ST.top()->standardizer();
    ST.top()->preOrder(0);
    ST.top()->flatten();
    CtoS(CONTROL);
    print(STACK);
    
}
