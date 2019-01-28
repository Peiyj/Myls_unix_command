/*
 * Filename: freeFileTree.c
 * Author: Yingjian Pei
 * Userid: A13595990
 * Description: This function is in charge of freeing the
 * dynamically allocated memory in the program. Note that 
 * struct fileInfo is recursively defined 
 * Date: Dec 01, 2018
 * Sources of Help: Tutor
 */

/*
 * Function Header: freeFileTree()
 * Function Prototype: 
 * void freeFileTree (struct fileInfo * fi, const char * filename);
 * Description: This function is provided for you to get relevant 
 * information about the file. The first argument is a pointer to 
 * struct fileInfo whose member variables will be set by this function.
 * Side Effects: none
 * parameters: 
 *        struct fileInfo * fi: the fileInfo ptr
 * Return values: void
 */
#include <sys/stat.h> // for struct stat definition
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include "pa4.h"
#include <unistd.h>
#include "pa4Strings.h"
#include <dirent.h>
void freeFileTree (struct fileInfo * fi){
    ////this function traverses tree in post order////
    int i;
    if(access(fi->filename, F_OK) != 0) {
        return;
    }
    ///if the children is null////
    if(fi->childrenSize <= 0){
        free(fi);
        return;
    }
    for(i = 0; i < fi->childrenSize; i++){
        if(access(fi->children[i]->filename, F_OK) == 0) {
            freeFileTree(fi->children[i]);
        }
    }
    free(fi->children);
    free(fi);
}

