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

int isKeyword(string Kw)
{
    for (string str:keyword)
        if (str.compare(Kw) == 0) {
            return 1;
        }
    return 0;
}
tokenType toTokenType(string str){
    if (str=="let")  return KW_let;//600
    if (str=="in")  return KW_in;
    if (str=="fn")  return KW_fn;
    if (str=="where")  return KW_where;
    if (str=="aug")  return KW_aug;
    if (str=="or")  return KW_or;//605
    if (str=="not")  return KW_not;
    if (str=="gr")  return KW_gr;
    if (str=="ge")  return KW_ge;
    if (str=="ls")  return KW_ls;
    if (str=="le")  return KW_le;//610
    if (str=="eq")  return KW_eq;
    if (str=="ne")  return KW_ne;
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
                        readtoken.setValue("errorInput");
                        readtoken.setType(ERROR);
                        return readtoken;
//                        return  "errorInput";
                    }
                    else {// operator '/'
                        fseek(fPtr, -2, SEEK_CUR);
                        ch=fgetc(fPtr);
                        outputStr=conc(ch, outputStr);
                        readtoken.setValue(outputStr);
                        readtoken.setType(OPERATOR);
                        return readtoken;
                    }
                }
            case '(':
                outputStr=conc(ch, outputStr);
                readtoken.setValue(outputStr);
                readtoken.setType(PUNCTION);
                return readtoken;
            case ')':
                outputStr=conc(ch, outputStr);
                readtoken.setValue(outputStr);
                readtoken.setType(PUNCTION);
                return readtoken;
            case ',':
                outputStr=conc(ch, outputStr);
                readtoken.setValue(outputStr);
                readtoken.setType(PUNCTION);
                return readtoken;
            case ';':
                outputStr=conc(ch, outputStr);
                readtoken.setValue(outputStr);
                readtoken.setType(PUNCTION);
                return readtoken;
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
        readtoken.setType(OPERATOR);
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
            readtoken.setType(toTokenType(outputStr));
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
        if(isPunction(ch)||isOperator(ch)||ch=='\''||ch=='\n'||ch=='\t'||ch==' '){
            fseek(fPtr, -1, SEEK_CUR);
            readtoken.setValue(outputStr);
            readtoken.setType(STRING);
            return readtoken;//read a string successfully
        }else {
            readtoken.setValue("errorInput");
            readtoken.setType(ERROR);
            return readtoken;
        }
    }
//    }
    
    readtoken.setValue("end");
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






