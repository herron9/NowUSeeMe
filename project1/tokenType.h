//
//  Token.h
//  project1
//
//  Created by rr on 2/28/16.
//  Copyright © 2016 rr. All rights reserved.
//

#ifndef tokenType_h
#define tokenType_h
#include<vector>
using namespace std;

enum tokenType{
    UNDEF,		// undefined 0
    IDENTIFIER,//1
    INTEGER,//2
    OPERATOR,//3
    OP_plus=300,
    OP_minus,
    OP_multi,
    OP_ls,
    OP_le,
    OP_gr,//305
    OP_ge,
    OP_ampersand,//&
    OP_dot,//308
    OP_at,
    OP_slash,//310
    OP_eq,//
    OP_ne,
    OP_bar,//313
    OP_square,
    OP_arror,//315
    STRING=4,
    PUNCTION,//5
    PU_open=500,
    PU_close,
    PU_semicolon,
    PU_commma,
    PU_double,
    fn_form,//505
    KEYWORD,//506
    tau,//506
    KW_let=600,
    KW_in,
    KW_fn,
    KW_where,//603
    KW_aug,
    KW_or,//605
    KW_not,
    //---
    KW_gr,
    KW_ge,
    KW_ls,
    KW_le,//610
    KW_eq,
    KW_neg,
    //----
    KW_true,
    KW_false,
    KW_nil,//615
    KW_dummy,
    KW_within,//617
    KW_and,
    KW_rec,
    KW_list,//620
    ERRORINPUT=7,      //1
    EOT, 		//8
    GAMMA,
    LAMBDA,
    Ystar,//11
    
    
};

const string keyword[22]={"let","in","fn","where","aug","or","not",
                          "gr","ge","ls","le","eq","ne","true","false",
                          "nil","dummy","within","and","rec","list"};
const vector<char> Operator={'+','-','*','<','>','&','.',
                                 '@','/',':','=','~','|','$',
                                 '!','#','%','^','_','[',']',
                                 '{','}','"','`','?',};
const vector<char>SetString={'\t','\n','\\','(',')',';',',',' '};
const vector<char> Punction={',',';','(',')'};
const vector<char> ESeq={'\n',' ','\t','\\'};


#endif /* Token_h */
