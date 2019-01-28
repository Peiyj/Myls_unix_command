/*
 * Filename: printFiles.c
 * Author: Yingjian Pei
 * Userid: A13595990
 * Description: This function does the actual printing to display the 
 * files in the terminal. 
 * Date: Dec 01, 2018
 * Sources of Help: Tutor
 */

/*
 * Function Header: printFiles()
 * Function Prototype: 
 * void printFiles (const struct fileInfo * fi, int showHidden, 
 int showLongFmt, int indent);
 * Description: This function does the actual printing to display 
 * the files in the terminal. 
 * Side Effects: none
 * parameters: 
 *   const struct fileInfo * fi : the root of the file tree to print
 *   int showHidden : flag (TRUE or FALSE) 
 *   int showLongFmt : flag (TRUE or FALSE) 
 *   int indent : number of spaces before a filename for indentation; 
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
#define TrimStart 4
#define TrimEnd 16
#define spacer " "
#define newline '\n'
void printFiles (const struct fileInfo * fi, int showHidden, 
        int showLongFmt, int indent){
    int i;
    int j;
    struct passwd *file;
    struct group *file2;
    struct tm *mytime; 
    char buffer[BUFSIZ]; 
    ///////////////////////base case/////////////////////
    //if we don't have to show hidden files//
    if(showHidden == 0 && isHidden(fi->filename) == 1){
        return;
    }
    //if it is in long format//
    if(showLongFmt == 1){
        file = getpwuid(fi->uid);
        file2 = getgrgid(fi->gid);
        mytime = &(fi->time);
        //populate the owner, group of the file
        //print permission
        printPermissions(fi->mode);
        //print the space
        fprintf(stdout, spacer);
        //print owner of the file
        if(file != NULL){ 
            fprintf(stdout, STR_PWNAME, file->pw_name);
        }
        else{
            fprintf(stdout, STR_PWNAME, spacer);
        }
        //print group of the file
        if(file2!= NULL){
            fprintf(stdout, STR_GNAME, file2->gr_name);
        }
        else{
            fprintf(stdout, STR_GNAME, spacer);
        }
        //print the size
        fprintf(stdout, STR_SIZE, fi->size);
        //print the time
        strcpy(buffer,ctime(mytime));
        //parse the arguments
        for(i = TrimStart; i < TrimEnd; i++){
            fprintf(stdout, "%c", buffer[i]);
        }
        //print the spacer
        fprintf(stdout, spacer);
    }

    for(j = 0; j < indent; j++){
        fprintf(stdout, spacer); 
    }
    //print the content
    printf("%s%c", fi->filename, newline);
    if(fi->isDir == 0){
        return;
    }
    ////////////////////////recursion/////////////////////
    for(i = 0; i < fi -> childrenSize; i++){
        printFiles(fi -> children[i], showHidden, showLongFmt, indent + 1);
    }
}


