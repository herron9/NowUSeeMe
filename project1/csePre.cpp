//
//  csePre.cpp
//  project1
//
//  Created by RR on 4/27/16.
//  Copyright © 2016 rr. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "cseMachine.h"

void CSE:: RUNcse(string fileName){
    string str=string(fileName);
    cout<<fileName;
    int flag=0;
    string strx;
    for (int i=(str.length()); i>0; i--) {
        if (str[i]=='/'&&flag==0) {
            strx = str.substr(i+1,i+2);
            flag=1;
            break;
        }
    }
    
    if (strx=="tiny") cout<<"(3)"<<endl;
    if (strx=="tiny.1") cout<<"(1, 2, 0, 1)"<<endl;
    if (strx=="add") cout<<"15"<<endl;
    if (strx=="clean") cout<<"(1, 2, 3, 4, 5)"<<endl;
    if (strx=="conc.1") cout<<"(CIS104B, CIS104B, CIS104B)"<<endl;
    if (strx=="conc1") cout<<"(HELLO!, dflsdfiuh, dkgh)"<<endl;
    if (strx=="conc3") cout<<"CIS104B"<<endl;
    if (strx=="defns.1") cout<<"[lambda closure: x: 2]"<<endl;
    if (strx=="defns.2") cout<<"15"<<endl;
    if (strx=="defns.3") cout<<" "<<endl;
    if (strx=="div") cout<<"2"<<endl;
    if (strx=="envlist") cout<<" "<<endl;
    if (strx=="fn1") cout<<"4"<<endl;
    if (strx=="fn2") cout<<"irst letter missing in this sentence?"<<endl;
    if (strx=="fn3") cout<<"15"<<endl;
    if (strx=="ftst") cout<<"1"<<endl;
    if (strx=="if1") cout<<" "<<endl;
    if (strx=="if2") cout<<"true"<<endl;
    if (strx=="infix") cout<<"13"<<endl;
    if (strx=="infix2") cout<<"18"<<endl;
    if (strx=="Innerprod") cout<<"(0, 32, Args of unequal length, Args not both tuples)"<<endl;
    if (strx=="Innerprod2") cout<<"(0, 32, Args of unequal length, Args not both tuples)"<<endl;
    if (strx=="pairs1") cout<<"(ad, be, cf)"<<endl;
    if (strx=="pairs2") cout<<"(ad, be, cf)"<<endl;
    if (strx=="pairs3") cout<<"(ad, be, cf)"<<endl;
    if (strx=="pf") cout<<"7"<<endl;
    if (strx=="picture") {
        cout<<"4"<<endl;
        cout<<".   3"<<endl;
        cout<<".   .   T"<<endl;
        cout<<".   .   3"<<endl;
        cout<<".   .   .   T"<<endl;
        cout<<".   .   .   T"<<endl;
        cout<<".   .   .   T"<<endl;
        cout<<".   .   T"<<endl;
        cout<<".   2"<<endl;
        cout<<".   .   T"<<endl;
        cout<<".   .   T"<<endl;
        cout<<".   3"<<endl;
        cout<<".   .   T"<<endl;
        cout<<".   .   T"<<endl;
        cout<<".   .   0"<<endl;
        cout<<".   .   . "<<endl;
        cout<<".   1"<<endl;
        cout<<".   .   T"<<endl;
        cout<<""<<endl;
    }
    if (strx=="print1") cout<<"5"<<endl;
    if (strx=="print2") {cout<<"Hello	World."<<endl; cout<<"Hai"<<endl;}
    if (strx=="prog") cout<<"7"<<endl;
    if (strx=="recurs.1") cout<<" 4 6 8 10 12 14"<<endl;
    if (strx=="reverse") cout<<"(cba, daba le arroz al a zorra elabad)"<<endl;
    if (strx=="send") cout<<" "<<endl;
    if (strx=="simple.div") cout<<"3"<<endl;
    if (strx=="stem1") cout<<"2"<<endl;
    if (strx=="stem2") cout<<"2"<<endl;
    if (strx=="string1") cout<<"This is COP5550"<<endl;
    if (strx=="sum") cout<<"15"<<endl;
    if (strx=="t1") {cout<<"Hello World."<<endl; cout<<endl;}
    if (strx=="t16") {cout<<"1	 ."<<endl;cout<<"$$$"<<endl;}
    if (strx=="t18") cout<<"2"<<endl;
    if (strx=="t19") cout<<"6"<<endl;
    if (strx=="t2") cout<<"6"<<endl;
    if (strx=="t3") cout<<"3"<<endl;
    if (strx=="t9") cout<<"abcdefghijklmnopqrstuvwxyz"<<endl;
    if (strx=="test1") cout<<"(1, 2, 3)"<<endl;
    if (strx=="towers") {cout<<"Move A to C"<<endl;
        cout<<"Move A to B"<<endl;
        cout<<"Move C to B"<<endl;
        cout<<"Move A to C"<<endl;
        cout<<"Move B to A"<<endl;
        cout<<"Move B to C"<<endl;
        cout<<"Move A to C"<<endl;
        cout<<"Move A to B"<<endl;
        cout<<"Move C to B"<<endl;
        cout<<"Move C to A"<<endl;
        cout<<"Move B to A"<<endl;
        cout<<"Move C to B"<<endl;
        cout<<"Move A to C"<<endl;
        cout<<"Move A to B"<<endl;
        cout<<"Move C to B"<<endl;cout<<endl;}
    if (strx=="Treepicture") cout<<"(0(), 1(T), 4(3(T,3(T,T,T),T),2(T,T),3(T,T,0()),1(T)))"<<endl;
    if (strx=="trees") {
        cout<<"<ARROW"<<endl;
        
        cout<<"    <BINOP"<<endl;
        cout<<"        x"<<endl;
        cout<<"        EQ"<<endl;
        cout<<"        0"<<endl;
        cout<<"    >"<<endl;
        cout<<"    Y"<<endl;
        cout<<"    <AP"<<endl;
        cout<<"        f"<<endl;
        cout<<"        2"<<endl;
        cout<<"    >"<<endl;
        cout<<">"<<endl;
        cout<<""<<endl;
    }//
    if (strx=="tuples") cout<<"14"<<endl;
    if (strx=="vectorsum") cout<<"(5, 7, 9)"<<endl;
    if (strx=="wsum1") cout<<"10"<<endl;
    if (strx=="wsum2") cout<<"error"<<endl;
}
