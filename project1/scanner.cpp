//
//  scanner.cpp
//  project1
//
//  Created by rr on 2/28/16.
//  Copyright © 2016 rr. All rights reserved.
//
#include <iostream>
#include <stdio.h>
#include <string>
#include "scanner.h"



Token scanner(FILE *fPtr){
    char ch= fgetc(fPtr);
    char nextchar;
    string outputStr;
    Token readtoken=Token(" ", UNDEF);
    while (ch!= EOF) {
        switch (ch) {
            case ' ': ch=fgetc(fPtr); break;
            case '\t':ch=fgetc(fPtr); break;
            case '\n':ch=fgetc(fPtr); break;
            case '\r':ch=fgetc(fPtr); break;
            case '/':
                if ((nextchar=fgetc(fPtr)) == '/') {
                    while ((ch = fgetc(fPtr)) != '\n') {;}
                    break;
                }
                else{
                    fseek(fPtr, -1, SEEK_CUR);
                    ch=fgetc(fPtr);
                    if (isOperator(ch)) {
                        errorOperator();
                        readtoken.setValue("errorInput");
                        readtoken.setType(ERRORINPUT);
                        return readtoken;
                    }
                    else {// operator '/'
                        fseek(fPtr, -2, SEEK_CUR);
                        ch=fgetc(fPtr);
                        outputStr=conc(ch, outputStr);
                        readtoken.setValue(outputStr);
                        readtoken.setType(OP_slash);
                        return readtoken;
                    }
                }
            case '(':outputStr=conc(ch, outputStr); readtoken.setValue(outputStr);
                     readtoken.setType(PU_open);  return readtoken;
            case ')':outputStr=conc(ch, outputStr); readtoken.setValue(outputStr);
                     readtoken.setType(PU_close); return readtoken;
            case ',':outputStr=conc(ch, outputStr); readtoken.setValue(outputStr);
                     readtoken.setType(PU_commma);return readtoken;
            case ';':outputStr=conc(ch, outputStr); readtoken.setValue(outputStr);
                     readtoken.setType(PU_semicolon);return readtoken;
            default: break;
        }
        if (ch=='/') {;}else if(ch=='\''||isdigit(ch)||isOperator(ch)||isLetter(ch)) break;

    }//end while
    
    if (isdigit(ch)) {//if is a Integer
        while (isdigit(ch)) {
            outputStr=conc(ch, outputStr);
            ch=fgetc(fPtr);
        }
        if (ch != EOF) {
            fseek(fPtr, -1, SEEK_CUR);
        }
        readtoken.setValue(outputStr);
        readtoken.setType(INTEGER);
        return readtoken;
    }
    else if(isOperator(ch)){
        while (isOperator(ch)) {
            outputStr=conc(ch, outputStr);
            ch=getc(fPtr);
        }
        if (ch != EOF) {
            fseek(fPtr, -1, SEEK_CUR);
        }
        readtoken.setValue(outputStr);
        readtoken.setType(toSpecOp(outputStr));
        return readtoken;
    }//end isOp
    else if (isLetter(ch)){
        outputStr=conc(ch, outputStr);
        ch=fgetc(fPtr);
        while (isLetter(ch)||isdigit(ch)||ch=='_') {
            outputStr=conc(ch, outputStr);
            ch=getc(fPtr);
        }
        if (ch != EOF) {
            fseek(fPtr, -1, SEEK_CUR);
        }
        readtoken.setValue(outputStr);
        readtoken.setType(IDENTIFIER);
        if(isKeyword(outputStr)){
            readtoken.setType(toSpecKW(outputStr));
        }
        return readtoken;
    }//end isID
    else if (ch=='\''){
        ch=fgetc(fPtr);
        while (ch!='\'') {
            outputStr=conc(ch, outputStr);
            ch=getc(fPtr);
        }
        ch=fgetc(fPtr);
        if(isPunction(ch)||isOperator(ch)||ch=='\''||ch=='\n'||ch=='\t'||ch==' '||ch=='\r'){
            fseek(fPtr, -1, SEEK_CUR);
            readtoken.setValue(outputStr);
            readtoken.setType(STRING);
            return readtoken;//read a string successfully
        }else {
            readtoken.setValue("errorInput");
            readtoken.setType(ERRORINPUT);
            return readtoken;
        }
    }
    readtoken.setValue("endREAD");
    readtoken.setType(EOT);
    return readtoken;
    
}




Token::Token(string value,int type){
    _value=value;
    _type=type;
    
}

string Token::getStrValue(){
    return _value;
}

int Token::getIntType(){
    return _type;
}

void Token::setValue(string value){
    _value=value;
}

void Token::setType(int type){
    _type=type;
}





