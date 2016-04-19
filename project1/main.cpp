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
#include "treeNode.h"

using namespace std;

//int main(int argc, char **argv) {
int main() {
//    char *fileName = argv[argc - 1];
//    FILE *fPtr = fopen(fileName, "r");
      FILE *fPtr = fopen("/Users/herron/Documents/PLPproj/project1/tests/pairs1", "r");
//    FILE *fPtr = fopen("/Users/herron/Documents/PLPproj/project1/test1", "r");

    fseek(fPtr, 0, SEEK_END);//check if input file is empty
    if (ftell(fPtr) == 0) {
        printf("File is empty.\n");
        exit(1);
    } else {
        rewind(fPtr);
    }
    
    parserst(fPtr);
//    string x= argv[argc-2];
//    if(x=="-ast"){parserast(fPtr);}
//    if(x=="-st"){parserst(fPtr);}
    
//    string comm[4];
//    for(int i=1;i<argc-1;i++){
//       comm[i]=argv[i];
//    }
//    for (int i=1; i<argc-1;) {
//        
////        if ("-ast"==comm[i]) {parser(fPtr);}// cout<<comm[i];
//        if ("-st"==comm[i]) {parser(fPtr); break;}
//        i++;
//    }
       fclose(fPtr);
    return 0;
}

