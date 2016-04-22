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
#include "cseNode.h"

using namespace std;

//int main(int argc, char **argv) {
int main() {
//    char *fileName = argv[argc - 1];
//    FILE *fPtr = fopen(fileName, "r");
      FILE *fPtr = fopen("/Users/herron/Documents/PLPproj/project1/project1/tests/print1", "r");
//    FILE *fPtr = fopen("/Users/herron/Documents/PLPproj/project1/test1", "r");

    fseek(fPtr, 0, SEEK_END);//check if input file is empty
    if (ftell(fPtr) == 0) {
        printf("File is empty.\n");
        exit(1);
    } else {
        rewind(fPtr);
    }
    
    flattentest(fPtr);
       fclose(fPtr);
    return 0;
}

