//
//  scanPre.cpp
//  project1
//
//  Created by rr on 3/5/16.
//  Copyright © 2016 rr. All rights reserved.
//

#include <stdio.h>
#include <string>
#include "tokenType.h"

string conc(char x,string str ){
    
    str.push_back(x);
    return str;
}

int isOperator(char Op)
{
    for (char ch:Operator)
        if(Op==ch)return 1;
    return 0;
}

int isLetter(char Le)
{
    if ((Le>='a'&&Le<='z')||(Le>='A'&&Le<='Z')) {
        return 1;
    }
    return 0;
}

void errorOperator(){
    printf("Wrong Operator!\n");
}

int isSetString(char Str)
{
    for (char ch:SetString)
        if(Str==ch)return 1;
    return 0;
}

int isPunction(char Pu)
{
    for (char ch:Punction)
        if(Pu==ch)return 1;
    return 0;
}

int isKeyword(string Kw)
{
    for (string str:keyword)
        if (str.compare(Kw) == 0) {
            return 1;
        }
    return 0;
}
tokenType toSpecKW(string str){
    if (str=="let")  return KW_let;//600
    if (str=="in")  return KW_in;
    if (str=="fn")  return KW_fn;
    if (str=="where")  return KW_where;
    if (str=="aug")  return KW_aug;
    if (str=="or")  return KW_or;//605
    if (str=="not")  return KW_not;
    if (str=="gr")  return OP_gr;
    if (str=="ge")  return OP_ge;
    if (str=="ls")  return OP_ls;
    if (str=="le")  return OP_le;
    if (str=="eq")  return OP_eq;
    if (str=="ne")  return OP_ne;
    if (str=="true")  return KW_true;
    if (str=="false")  return KW_false;
    if (str=="nil")  return KW_nil;//615
    if (str=="dummy")  return KW_dummy;
    if (str=="within")  return KW_within;
    if (str=="and")  return KW_and;
    if (str=="rec")  return KW_rec;
    if (str=="list")  return KW_list;//620
    return UNDEF;
}

tokenType toSpecOp(string str){
    if (str=="+")  return OP_plus;//300
    if (str=="-")  return OP_minus;
    if (str=="*")  return OP_multi;
    if (str=="<")  return OP_ls;//303
    if (str=="<=")  return OP_le;
    if (str==">")  return OP_gr;//305
    if (str==">=")  return OP_ge;
    if (str=="&")  return OP_ampersand;//
    if (str==".")  return OP_dot;
    if (str=="@")  return OP_at;
    if (str=="/")  return OP_slash;//310
    if (str=="=")  return OP_eq;
    if (str=="|")  return OP_bar;
    if (str=="**")  return OP_square;
    if (str=="->")  return OP_arror;
    return UNDEF;
}

tokenType toSpecPu(string str){
    if (str=="(")  return PU_open;//500
    if (str==")")  return PU_close;
    if (str==";")  return PU_semicolon;
    if (str==",")  return PU_commma;
    
    return UNDEF;
}