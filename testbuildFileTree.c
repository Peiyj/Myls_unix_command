/*
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: Unit test program to test the function buildFileTree.c
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
 * Unit Test for buildFileTree.c
 * void buildFileTree (const mode_t mode);
 * 
 * This function will be used with qsort() to sort on the names of two struct 
 * fileInfo in reverse alphabetical order. 
 *
 * Purpose: Tests our buildFileTree implementation by passing a variety of values
 * in as test cases for our function. Tests edge cases like 0:0:0 times, larger
 * times, and others.
 */
void testbuildFileTree() {
    //case 1: name 
    buildFileTree(".", NAME, 0);
    printf("\n\n\n\n");
/*
    //case 2: name reverse
    buildFileTree("Test", NAME, 1);
    printf("\n\n\n\n");

    //case 3: time
    buildFileTree("Test", TIME, 0);
    printf("\n\n\n\n");

    //case 4: time reverse
    buildFileTree("Test", TIME, 1);
    printf("\n\n\n\n");*/


}

int main( void ) {

    fprintf(stderr, "Running tests for buildFileTree...\n");
    testbuildFileTree();
    fprintf(stderr, "Done running tests!\n");

    return 0;
}
