//
//  Token.h
//  project1
//
//  Created by rr on 2/28/16.
//  Copyright © 2016 rr. All rights reserved.
//

#ifndef Token_h
#define Token_h
#include<vector>
using namespace std;

//#define MAX 8 // max length of each word string
//#define LIMIT 200 // max number of word strings in an input file

enum tokenType{
    UNDEF,		// undefined 0
    IDENTIFIER,//1
    INTEGER,//2
    OPERATOR,//3
    OP_plus=300,
    OP_minus,
    OP_multi,
    OP_le,
    OP_gr,
    OP_and,//305
    OP_dot,
    OP_at,
    OP_slash,
    OP_colon,//:
    OP_eq,//310
    OP_tilde,//~
    OP_bar,//
    OP_dollar,//
    OP_non,//!
    OP_number,//#315
    OP_percent,//
    OP_caret,//^
    OP_underline,//_
    OP_LeftSquare,//
    OP_RightSquare,//320
    OP_LeftBig,//
    OP_RightBig,//
    OP_Dquote,//
    OP_Squote,//
    OP_question,//325
    STRING=4,
    PUNCTION,//5
    KEYWORD,//6
    KW_let=600,
    KW_in,
    KW_fn,
    KW_where,
    KW_aug,
    KW_or,//605
    KW_not,
    KW_gr,
    KW_ge,
    KW_ls,
    KW_le,//610
    KW_eq,
    KW_ne,
    KW_true,
    KW_false,
    KW_nil,//615
    KW_dummy,
    KW_within,
    KW_and,
    KW_rec,
    KW_list,//620
    ERROR=7,      //1
    EOT, 		//2 end of token
    
//    IDENTIFIER,
//    KEYWORD,
//    NUMBER,
//    REL_OP, 	// such as ==  <  >  =!=    =>  =<
//    OP,			// such as = :  +  -  *  / %
//    DELIM,		// such as . (  ) , { } ; [ ]
    
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
