//
//  main.cpp
//  proj1
//
//  Created by rr on 2/28/16.
//  Copyright © 2016 rr. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string>
#include "Token.h"
#include "scanner.h"
using namespace std;

int main() {
//    FILE *fPtr =fopen("/Users/herron/Documents/share/rpal/tests/vectorsum","r");
    FILE *fPtr =fopen("/Users/herron/Documents/PLPproj/project1/project1/demo1","r");

    
    fseek(fPtr, 0, SEEK_END);//check if input file is empty
    if (ftell(fPtr) == 0) {
        printf("File is empty.\n");
        exit(1);
    } else {
        rewind(fPtr);
    }
    string outPut="start";
    while (outPut!="end"&&outPut!="errorInput") {
            outPut=scanner(fPtr);
            cout<<"Token= "<<outPut<<endl;
        }
    fclose(fPtr);
    return 0;
}