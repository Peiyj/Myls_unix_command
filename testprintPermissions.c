/*
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: Unit test program to test the function printPermissions.c
 * Date: Nov 30, 2018
 * Sources of Help: worksheet, slides
 */ 

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/stat.h> // for struct stat definition
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "pa4.h"
#include "test.h"
#include "getFileInfo.c"

/*
 * Unit Test for printPermissions.c
 * void printPermissions (const mode_t mode);*
 * 
 * This function will be used with qsort() to sort on the names of two struct 
 * fileInfo in reverse alphabetical order. 
 *
 * Purpose: Tests our printPermissions implementation by passing a variety of values
 * in as test cases for our function. Tests edge cases like 0:0:0 times, larger
 * times, and others.
 */
void testprintPermissions() {
    struct fileInfo *file1 = malloc(sizeof(struct fileInfo));
    //case 1: 
    getFileInfo(file1, "Makefile");
    printPermissions(file1->mode);
    printf("\n");
    //case 2: 
    getFileInfo(file1, "testnameCompareRev");
    printPermissions(file1->mode);
    printf("\n");

    //case 3: 
    getFileInfo(file1, ".");
    printPermissions(file1->mode);
    printf("\n");

    //case 4: 
    getFileInfo(file1, "..");
    printPermissions(file1->mode);
    printf("\n");
    
    free(file1);
}

int main( void ) {

    fprintf(stderr, "Running tests for printPermissions...\n");
    testprintPermissions();
    fprintf(stderr, "Done running tests!\n");

    return 0;
}
