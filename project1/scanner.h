//
//  scanner.h
//  project1
//
//  Created by rr on 2/28/16.
//  Copyright © 2016 rr. All rights reserved.
//

#ifndef scanner_h
#define scanner_h
#include "tokenType.h"
using namespace std;



class Token{
public:
    Token (string value,int type);
    void setValue(string value);
    void setType(int type);
    string getStrValue();
    int getIntType();
    
private:
    string _value;
    int _type;
    
};


string conc(char x,string str );
int isOperator(char Op);
int isLetter(char Le);
void errorOperator();
int isSetString(char Str);
int isPunction(char Pu);
int isKeyword(string Kw);
tokenType toSpecKW(string str);
tokenType toSpecOp(string str);
tokenType toSpecPu(string str);

Token scanner(FILE *fPtr);

//===========================for parser=================================


void rollBack(FILE *Fptr,Token bin);
#endif /* scanner_h */

