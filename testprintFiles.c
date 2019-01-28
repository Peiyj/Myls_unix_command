/*
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: Unit test program to test the function printFiles.c
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
#include "isHidden.c"
/*
 * Unit Test for printFiles.c
 * void printFiles (const mode_t mode);
 * 
 * This function will be used with qsort() to sort on the names of two struct 
 * fileInfo in reverse alphabetical order. 
 *
 * Purpose: Tests our printFiles implementation by passing a variety of values
 * in as test cases for our function. Tests edge cases like 0:0:0 times, larger
 * times, and others.
 */
void testprintFiles() {
    //case 1: name 
    struct fileInfo *fi = malloc(sizeof(struct fileInfo));
    getFileInfo(fi, "..");
    fi = buildFileTree("..", NAME, 0);
    printFiles(fi, 0, 1, 1);
    printf("More Tests\n");

}

int main( void ) {

    fprintf(stderr, "Running tests for printFiles...\n");
    testprintFiles();
    fprintf(stderr, "Done running tests!\n");

    return 0;
}
