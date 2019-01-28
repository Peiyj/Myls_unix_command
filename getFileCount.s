/*
 * Filename: getFileCount.s
 * Author: Yingjian Pei
 * Userid: A13595990
 * Description: defines the getFileCount funtion is a function that
 * counts the number of files.
 * Date: Dec 01, 2018
 * Sources of Help: Tutor
 */

.syntax unified

.equ FP_OFFSET, 4
.equ PARAM_SPACE, 8
.equ File_OFFSET, -8

.equ LOCAL_SPACE, 16
.equ temp_OFFSET, -16
.equ index_OFFSET, -20
.equ number_OFFSET, -24
@ useful constants
.text
.align 2
.global getFileCount

.equ shiftInt, 2

/*
 * Function name: getFileCount()
 * Function prototype: int getFileCount (const struct fileInfo * fi)
 * Description: This function is in charge of counting the total 
 * number of files in a tree of files. 
 * Parameters: const struct fileInfo * fi: fileInfo pointer to the root
 * Side Effects: None.  
 * Error Conditions: None.
 * Return Value: the number of files
 * Registers Used: 
 * r0: parameter 1: fileInfo pointer 
 * r1: n: the number of files
 * r2: i: index
 * r3: intermiediary values
 */
getFileCount:
    @ Save caller's registers on the stack
    push {fp, lr}                @ save registers
    add fp, sp, FP_OFFSET        @ set fp to the base
    sub sp, sp, PARAM_SPACE      @ push parameter space
    sub sp, sp, LOCAL_SPACE      @ push local space

    str r0, [fp, File_OFFSET]    @ store the first parameter
    //////////////////////int n = 1///////////////////////// 
    mov r1, 1                    @ n = 1
    str r1, [fp, number_OFFSET]  @ store it to number offset

    mov r2, 0                    @ index = 0
    str r2, [fp, index_OFFSET]   @ store it to index offset

/////////for(int i = 0; i < fi->childrenSize; i++)///////
    ldr r2, [fp, index_OFFSET]   @ get i
    ldr r3, =offset_childrenSize @ get the address
    ldr r3, [r3]                 @ get the actually offset

    ldr r0, [fp, File_OFFSET]    @ load the file pointer
    ldr r0, [r0, r3]             @ get the fi->childrenSize
    cmp r2, r0                   @ i < fi->childrenSize
    bge end_loop                 @ opposite logic to branch to end
loop:
    //////////////////n += getFileCount(fi->children[i])/////
    
    ldr r1, [fp, number_OFFSET]  @ load number offset 
    ldr r0, [fp, File_OFFSET]    @ load file pointer
    ldr r3, =offset_children     @ load children array address
    ldr r3, [r3]                 @ load the actual offset
    ldr r3, [r0, r3]             @ fi -> children[0]

    ldr r1, [fp, index_OFFSET]   @ get i
    lsl r1, r1, shiftInt         @ lsl 2 to add index for type int
    ldr r0, [r3, r1]             @ r0: fi -> children[i]
    //ldr r0, [r0]

    //str r0, [fp, File_OFFSET]    @ store the pointer
    bl  getFileCount             @ call the function recursively
    ldr r1, [fp, number_OFFSET]  @ load number offset 
    add r1, r1, r0               @ n += getFileCount
    str r1, [fp, number_OFFSET]  @ store it back to number
    

end_if:
    ////////////////////////i++//////////////////////////////////
    ldr r2, [fp, index_OFFSET]   @ load the index
    add r2, r2, 1                @ index ++
    str r2, [fp, index_OFFSET]   @ store back to the index offset

    ldr r0, [fp, File_OFFSET]    @ load the file pointer
    ldr r3, =offset_childrenSize @ load the offset address

    ldr r3, [r3]                 @ load the actual pointer
    ldr r0, [r0, r3]             @ get the fi->childrenSize
    
    cmp r2, r0                   @ compare 
    blt loop                     @ branch
   
end_loop:
    //////////////////////return n////////////////////////
    ldr r0, [fp, number_OFFSET]  @ get the value of n
    sub sp, fp, FP_OFFSET        @ deallocate vars
    @ Restore caller's registers 
    pop {fp, pc}                 @ restore caller's fp
