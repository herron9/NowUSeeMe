//
//  scanner.h
//  project1
//
//  Created by rr on 2/28/16.
//  Copyright © 2016 rr. All rights reserved.
//

#ifndef scanner_h
#define scanner_h
#include "Token.h"
using namespace std;

//void conc(){}

//string scanner(){}


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

Token scanner(FILE *fPtr);
#endif /* scanner_h */

