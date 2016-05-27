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
#include "cseMachine.h"
#include "parser.h"

using namespace std;

int main(int argc, char **argv) {
//int main() {
    char *fptr = argv[argc - 1];
    FILE *fPtr = fopen(fptr, "r");
//      FILE *fPtr = fopen("/Users/herron/Documents/PLPproj/project1/project1/tests/tiny.1", "r");
//    FILE *fPtr = fopen("/Users/herron/Documents/PLPproj/project1/te1", "r");

    fseek(fPtr, 0, SEEK_END);//check if input file is empty
    if (ftell(fPtr) == 0) {
        printf("File is empty.\n");
        exit(1);
    } else {
        rewind(fPtr);
    }
        parser* pser=new parser;
        pser->E(fPtr);
        pser->AST.top()->standardizer();
        CSE* cse=new CSE;
        cse->root=pser->AST.top();
        cse->runCSE(cse->root);
    
    fclose(fPtr);
    return 0;
}

