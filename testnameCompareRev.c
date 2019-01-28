/*
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: Unit test program to test the function nameCompareRev.s
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

/*
 * Unit Test for nameCompareRev.s
 *
 * int nameCompareRevRev (const void * p1, const void * p2)*
 * This function will be used with qsort() to sort on the names of two struct 
 * fileInfo in reverse alphabetical order. 
 *
 * Purpose: Tests our nameCompareRev implementation by passing a variety of values
 * in as test cases for our function. Tests edge cases like 0:0:0 times, larger
 * times, and others.
 */
void testnameCompareRev() {
    struct fileInfo *file1 = malloc(sizeof(struct fileInfo));
    struct fileInfo *file2 = malloc(sizeof(struct fileInfo));
    
    /////////////////////Normal cases///////////////////////
    //case 1: 
    file1->filename[0] = 'a';
    file2->filename[0] = 'b';
    TEST(nameCompareRev(&file1, &file2) == 1);
  
    //case 2:
    file1->filename[0]= '1';
    file2->filename[0] = '2';
    TEST(nameCompareRev(&file1, &file2) == 1);

    //case 3: 
    file1->filename[0]= 'a';
    file2->filename[0] = 'p';
    TEST(nameCompareRev(&file1, &file2) == 1);

    ////////////////////edge cases/////////////////////
    //case 4:
    file1->filename[0]= '0';
    file2->filename[0] = '0';
    TEST(nameCompareRev(&file1, &file2) == 0);

    //case 5: 
    file1->filename[0]= '~';
    file2->filename[0] = '~';
    TEST(nameCompareRev(&file1, &file2) == 0);

    //case 6:
    file1->filename[0]= '\0';
    file2->filename[0] = '\0';
    TEST(nameCompareRev(&file1, &file2) == 0);
    
    ////////////////////bigger cases/////////////////////
    //case 4:
    file1->filename[0]= '1';
    file2->filename[0] = '0';
    TEST(nameCompareRev(&file1, &file2) == -1);

    //case 5: 
    file1->filename[0]= 'b';
    file2->filename[0] = 'a';
    TEST(nameCompareRev(&file1, &file2) == -1);

    //case 6:
    file1->filename[0]= 'l';
    file2->filename[0] = 'a';
    TEST(nameCompareRev(&file1, &file2) == -1);

    free(file1);
    free(file2);
}

int main( void ) {

  fprintf(stderr, "Running tests for nameCompareRev...\n");
  testnameCompareRev();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
