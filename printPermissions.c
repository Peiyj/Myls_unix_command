/*
 * Filename: printPermissions.c
 * Author: Yingjian Pei
 * Userid: A13595990
 * Description: This function is in charge of printing the 
 * file permission when the -l flag is given
 * Date: Dec 01, 2018
 * Sources of Help: Tutor
 */

/*
 * Function Header: printPermissions()
 * Function Prototype: int printPermissions( const mode_t mode); 
 * Description: This function is in charge of printing the file
 * permission when the -l flag is given
 * Side Effects: none
 * parameters: mode: the mode of the file (rwx)
 * Return values: void
 */
#include <sys/stat.h> // for struct stat definition
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "pa4.h"
#include <unistd.h>
#include "pa4Strings.h"

void printPermissions(const mode_t mode){
    //if it is a directory
    if(S_ISDIR(mode)){
        printf(D_PERMISSION);
    }
    else{
        printf(NO_PERMISSION);
    }
    //////////////////////owner/////////////////////
    //read
    if((mode & S_IRUSR) == 0){
        printf(NO_PERMISSION);
    }
    else{
        printf(R_PERMISSION);
    }
    //write
    if((mode & S_IWUSR) == 0){
        printf(NO_PERMISSION);
    }
    else{
        printf(W_PERMISSION);
    }
    //execution
    if((mode & S_IXUSR) == 0){
        printf(NO_PERMISSION);
    }
    else{
        printf(X_PERMISSION);
    }
    //////////////////////group/////////////////////
    //read
    if((mode & S_IRGRP) == 0){
        printf(NO_PERMISSION);
    }
    else{
        printf(R_PERMISSION);
    }
    //write
    if((mode & S_IWGRP) == 0){
        printf(NO_PERMISSION);
    }
    else{
        printf(W_PERMISSION);
    }
    //execution
    if((mode & S_IXGRP) == 0){
        printf(NO_PERMISSION);
    }
    else{
        printf(X_PERMISSION);
    }
    //////////////////////other/////////////////////
    //read
    if((mode & S_IROTH) == 0){
        printf(NO_PERMISSION);
    }
    else{
        printf(R_PERMISSION);
    }
    //write
    if((mode & S_IWOTH) == 0){
        printf(NO_PERMISSION);
    }
    else{
        printf(W_PERMISSION);
    }
    //execution
    if((mode & S_IXOTH) == 0){
        printf(NO_PERMISSION);
    }
    else{
        printf(X_PERMISSION);
    }
}

