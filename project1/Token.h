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
    UNDEF,		// undefined
    EOT, 		// end of token
    PUNCTION,
    INTEGER
//    IDENTIFIER,
//    KEYWORD,
//    NUMBER,
//    REL_OP, 	// such as ==  <  >  =!=    =>  =<
//    OP,			// such as = :  +  -  *  / %
//    DELIM,		// such as . (  ) , { } ; [ ]
    
};


const string Type[5]={"IDENTIFIER","INTEGER","OPERATOR","STRING","KEY"};
const string keyword[22]={"let","in","fn","where""aug","or","not",
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
