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

int main(int argc, char **argv) {
    char *fileName = argv[argc - 1];
    FILE *fPtr = fopen(fileName, "r");
    fseek(fPtr, 0, SEEK_END);//check if input file is empty
    if (ftell(fPtr) == 0) {
        printf("File is empty.\n");
        exit(1);
    } else {
        rewind(fPtr);
    }
    
    string comm[4];
    for(int i=1;i<argc-1;i++){
       comm[i]=*argv[i];
    }
    for (int i=1; i<argc-1;) {
        if ("-ast"==comm[i]) {parser(fPtr);}
        if ("-nonout"==comm[i]) {parser(fPtr);}
        parser(fPtr);
        i++;
    }
       fclose(fPtr);
    return 0;
}

