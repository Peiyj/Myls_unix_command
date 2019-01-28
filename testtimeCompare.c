/*
 * Author: Yingjian Pei
 * Userid: cs30fex
 * Description: Unit test program to test the function timeCompare.s
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
 * Unit Test for timeCompare.s
 *
 * int timeCompare (const void * p1, const void * p2)*
 * This function will be used with qsort() to sort on the times of two struct 
 * fileInfo in reverse alphabetical order. 
 *
 * Purpose: Tests our timeCompare implementation by passing a variety of values
 * in as test cases for our function. Tests edge cases like 0:0:0 times, larger
 * times, and others.
 */
void testtimeCompare() {
    struct fileInfo *file1 = malloc(sizeof(struct fileInfo));
    struct fileInfo *file2 = malloc(sizeof(struct fileInfo));
    
    /////////////////////Normal cases///////////////////////
    //case 1: 
    file1->time = 1;
    file2->time = 2;
    TEST(timeCompare(&file1, &file2) == -1);
  
    //case 2:
    file1->time= 10;
    file2->time = 11;
    TEST(timeCompare(&file1, &file2) == -1);

    //case 3: 
    file1->time= 120;
    file2->time = 12323;
    TEST(timeCompare(&file1, &file2) == -1);

    ////////////////////edge cases/////////////////////
    //case 4:
    file1->time= 0;
    file2->time = 0;
    TEST(timeCompare(&file1, &file2) == 0);

    //case 5: 
    file1->time= 1;
    file2->time = 1;
    TEST(timeCompare(&file1, &file2) == 0);

    //case 6:
    file1->time= 123456789;
    file2->time = 123456789;
    TEST(timeCompare(&file1, &file2) == 0);
    
    ////////////////////bigger cases/////////////////////
    //case 4:
    file1->time= 1;
    file2->time = 0;
    TEST(timeCompare(&file1, &file2) == 1);

    //case 5: 
    file1->time= 19;
    file2->time = 1;
    TEST(timeCompare(&file1, &file2) == 1);

    //case 6:
    file1->time= 10;
    file2->time = 2;
    TEST(timeCompare(&file1, &file2) == 1);

    free(file1);
    free(file2);
}

int main( void ) {

  fprintf(stderr, "Running tests for timeCompare...\n");
  testtimeCompare();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
