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
#include "Token.h"

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

Token scanner(FILE *fPtr){
    char ch= fgetc(fPtr);
    char nextchar;
    string outputStr;
    Token readtoken=Token(" ", UNDEF);
    while (ch!= EOF) {
        switch (ch) {
            case ' ':
                ch=fgetc(fPtr);
                break;
            case '\t':
                ch=fgetc(fPtr);
                break;
            case '\n':
                ch=fgetc(fPtr);
                break;
            case '\r':
                ch=fgetc(fPtr);
                break;
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
                        readtoken.setValue
                        return  "errorInput";
                    }
                    else {// operator '/'
                        fseek(fPtr, -2, SEEK_CUR);
                        ch=fgetc(fPtr);
                        outputStr=conc(ch, outputStr);
                        return outputStr;
                    }
                }
            case '(':
                outputStr=conc(ch, outputStr);
//                ch=fgetc(fPtr);
//                scanStr.setStr(outputStr, PUNCTION);
                return outputStr;
            case ')':
                outputStr=conc(ch, outputStr);
//                ch=fgetc(fPtr);
//                scanStr.setStr(outputStr, PUNCTION);
                return outputStr;
            case ',':
                outputStr=conc(ch, outputStr);
//                ch=fgetc(fPtr);
//                scanStr.setStr(outputStr, PUNCTION);
                return outputStr;
            case ';':
                outputStr=conc(ch, outputStr);
//                ch=fgetc(fPtr);
//                scanStr.setStr(outputStr, PUNCTION);
                return outputStr;
            default:
                break;
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
        return outputStr;
    }
    else if(isOperator(ch)){
        while (isOperator(ch)) {
            outputStr=conc(ch, outputStr);
            ch=getc(fPtr);
        }
        if (ch != EOF) {
            fseek(fPtr, -1, SEEK_CUR);
        }
        return outputStr;
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
        return outputStr;
    }//end isID
    else if (ch=='\''){
        ch=fgetc(fPtr);
        while (ch!='\'') {
            outputStr=conc(ch, outputStr);
            ch=getc(fPtr);
        }
        ch=fgetc(fPtr);
        if(isPunction(ch)||isOperator(ch)||ch=='\''||ch=='\n'||ch=='\t'||ch==' '){
            fseek(fPtr, -1, SEEK_CUR);
            return outputStr;//read a string successfully
        }else return "errorInput";
    }
//    }
    
    return "end";
    
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






