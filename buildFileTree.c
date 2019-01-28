/*
 * Filename: buildFileTree.c
 * Author: Yingjian Pei
 * Userid: A13595990
 * Description: This function builds the file tree and returns 
 * the pointer to the struct fileInfo that represents the file
 * of name filename,notice that this file may be a directory. 
 * In this case, we need to recursively call buildFileTree to
 * allocate for subfiles.
 * Date: Dec 01, 2018
 * Sources of Help: Tutor
 */

/*
 * Function Header: buildFileTree()
 * Function Prototype: struct fileInfo * buildFileTree (const char * filename, 
 SortBy sortby, int rev); 
 * Description: This function builds the file tree and returns 
 * the pointer to the struct fileInfo that represents the file
 * of name filename,notice that this file may be a directory. 
 * In this case, we need to recursively call buildFileTree to
 * allocate for subfiles.
 * Side Effects: none
 * parameters: filename: the name of the file
 *             sortby: which order the file is sorted by
 *             rev: boolean indicating if it is in rev order
 * Return values: void
 */
#include <sys/stat.h> // for struct stat definition
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "pa4.h"
#include <dirent.h>
#include "pa4Strings.h"

struct fileInfo *buildFileTree(const char *filename, SortBy sortby, 
        int rev){
    //buildFileTree dynamically allocates memory for 1 struct fileInfo
    struct fileInfo *file = calloc(1, sizeof(struct fileInfo));
    //if allocation fails, print an error 
    if(file == NULL){
        perror(__func__);
        return NULL;
    }
    //call getFileInfo on this struct to fill in the vars
    getFileInfo(file, filename);
    //check if the file is a directory 
    DIR *currentFile = opendir(filename);
    if(currentFile == NULL){
        return file;
    }
    file -> isDir = 1;
    struct dirent *subFile;
    //use readdir to read the next subfile
    while((subFile = readdir(currentFile)) != NULL){
        //If this subfile name is this directory (".") or the up directory
        //(".."), skip
        if(strcmp(subFile->d_name, STR_THIS) == 0 || 
                strcmp(subFile->d_name, STR_UP) == 0){
            continue;
        }
        char buffer[MAXLEN];
        snprintf(buffer, MAXLEN, FILE_CONCAT_FORMAT, file -> filename, 
                subFile -> d_name);
        /////Compare childrenSize and childrenCapacity////
        if(file->childrenSize >= file->childrenCapacity){
            //call realloc to expand the children array 
            struct fileInfo **temp = realloc(file->children ,
                    (file->childrenSize + CHILDREN_INCREMENT) 
                    * sizeof(struct fileInfo));
            if(temp == NULL){
                perror(__func__);
                if(file->children != NULL){
                    free(file->children);
                    free(file);
                }
                else{
                    free(file);
                }
                return NULL;

            }
            //otherwise, update the capacity
            else{
                file->childrenCapacity += CHILDREN_INCREMENT; 
            }
            file->children = temp;
        }
        ////recursively call buildFileTree///
        file->children[file -> childrenSize] = buildFileTree(buffer, 
                sortby, rev);
        //Increment childrenSize//
        file -> childrenSize++;
    }
    /////now close the directory////
    closedir(currentFile);
    ////use qsort to sort these cases////

    if(sortby == NAME && rev == 0){
        qsort(file->children, file->childrenSize, sizeof(struct fileInfo *), 
                nameCompare);
    }
    else if(sortby == NAME && rev == 1){
        qsort(file->children, file->childrenSize, sizeof(struct fileInfo *), 
                nameCompareRev);
    }
    else if(sortby == TIME && rev == 0){
        qsort(file->children, file->childrenSize, sizeof(struct fileInfo *),
                timeCompare);
    }
    else if(sortby == TIME && rev == 1){
        qsort(file->children, file->childrenSize, sizeof(struct fileInfo *),
                timeCompareRev);
    }
   /* 
    int i;
    for(i = 0; i < file -> childrenSize; i++){
        printf("%s\n", file->children[i]);
    }*/
    return file;
}


