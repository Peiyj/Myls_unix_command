/*
 * Filename: main.c
 * Author: Yingjian Pei
 * Userid: A13595990
 * Description: This is the main function of your program. Inside this
 * function, you should parse command line arguments, handle errors 
 * (if any), and call the corresponding functions based on the arguments. 
 * Date: Dec 01, 2018
 * Sources of Help: Tutor
 */

/*
 * Function Header: main()
 * Function Prototype: int main (int argc, char * argv[])
 * void freeFileTree (struct fileInfo * fi, const char * filename);
 * Description: This is the main function of your program. Inside 
 * this function, you should parse command line arguments, handle 
 * errors (if any), and call the corresponding functions based 
 * on the arguments. 
 * Side Effects: none
 * parameters:
 *          int argc: number of arguments 
 *          char * argv[]: argument array
 *        
 * Return values: int exit success or failure
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
#include "pa4.h"
#include <unistd.h>
#include "pa4Strings.h"
#include <dirent.h>
#include <ctype.h>
int main (int argc, char * argv[]){ 
    int opt;
    int hidden = 0;
    int fileCount = 0;
    int longCheck = 0;
    int reverse = 0;
    int sortTime = 0;
    char * fileName = STR_THIS;
    struct fileInfo *fi; 
    ////////////nothing entered//////////
    if(argc == 1){
        fi = buildFileTree(STR_THIS, NAME, reverse);
        printFiles(fi, hidden, longCheck, 0);
        freeFileTree(fi);
        return EXIT_SUCCESS;
    }
    ////////////if there are more arguments/////////
    while((opt = getopt(argc, argv, FLAGS)) != -1){
        switch(opt){
            case FLAG_SHOWHIDDEN:
                hidden = 1;
                break;
            case FLAG_COUNT:
                fileCount = 1;
                break;
            case FLAG_LONGFMT:
                longCheck = 1;
                break;
            case FLAG_REVERSE:
                reverse = 1;
                break;
            case FLAG_TIME:
                sortTime = 1;
                break;
            case FLAG_FILENAME:
                if(optarg == NULL){
                    fileName = STR_THIS;
                }
                else{
                    fileName = optarg;
                }
                break;
            case FLAG_HELP:
                fprintf(stdout, STR_USAGE, argv[0]);
                return EXIT_SUCCESS;
            case FLAG_UNKNOWN:
                fprintf(stderr, STR_USAGE, argv[0]);
                return EXIT_FAILURE;
        }
    }
    ///////////Check for extraneous arguments////////
    if(optind != argc){
        fprintf(stderr, STR_EXTRA_ARG, argv[optind]);
        fprintf(stdout, STR_USAGE, argv[0]);
        return EXIT_FAILURE;
    }
    ///if the file-to-list exists using standard C library function///
    if(access(fileName, F_OK) != 0){
        ////if not, print the error message to stderr and return from main///
        fprintf(stderr, ERR_DNE, fileName);
        return EXIT_FAILURE;
    }
    if(sortTime == 0){
        fi = buildFileTree(fileName, NAME, reverse);
        if(fi == NULL){
            return EXIT_FAILURE;
        }
    }
    else{
        fi = buildFileTree(fileName, TIME, reverse);
        if(fi == NULL){
            return EXIT_FAILURE;
        }
    }
    if(fileCount == 1){
        fprintf(stdout, STR_COUNT, fileName, getFileCount(fi));
    }
    printFiles(fi, hidden, longCheck, 0);
    freeFileTree(fi);
    return EXIT_SUCCESS;
}

