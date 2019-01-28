/*
 * Filename: nameCompareRev.s
 * Author: Yingjian Pei
 * Userid: A13595990
 * Description: defines the nameCompareRev funtion that is passed in as
 *              parameter for qsort() function used in the PA4 program.
 * Date: Dec 01, 2018
 * Sources of Help: Tutor
 */

.syntax unified

.equ FP_OFFSET, 4
.equ PARAM_SPACE, 16
.equ P1_OFFSET, -8
.equ P2_OFFSET, -12

.text
.align 2
.global nameCompareRev

/*
 * Function name: nameCompareRev()
 * Function prototype: nameCompareRev(const void *p1, const void *p2);
 * Description: This function will be used with qsort() to sort on 
 * the names of two struct fileInfo in alphabetical order.  
 * Parameters: p1: a pointer
 *             p2: a pointer 
 * Side Effects: None.   
 * Error Conditions: None.
 * Return Value: -1 if the first name is big, 
 * 0 if the names are the same, 
 * +1 if the first name is smaller.
 * Registers Used: 
 * r0: void pointer 1: first pointer to struct fileInfo
 * r1: void pointer 2: second pointer to struct fileInfo
 */

nameCompareRev:
    @ Save caller's registers on the stack
    push {fp, lr}                @ save registers
    add fp, sp, FP_OFFSET        @ set fp to the base
    sub sp, sp, PARAM_SPACE      @ push parameter space
    str r0, [fp, P1_OFFSET]      @ store the first parameter
    str r1, [fp, P2_OFFSET]      @ store the second paramter
if:
    @ Call strcmp on two names
    ldr r0, [fp, P1_OFFSET]      @ load the first pointer
    ldr r0, [r0]                 @ get 1st name into r0
    ldr r1, [fp, P2_OFFSET]      @ load the second pointer
    ldr r1, [r1]                 @ get 2nd name into r1
    bl strcmp                    @ call string compare 

    @ strcmp returned value < 0, first < second
    cmp r0, 0                    @ compare the return value to 0
    bge else_if                  @ if the number is greater go to else_if
    @ return 1
    mov r0, 1                    @ if number is smaller, return 1
    b end_if                     @ go to end_if

else_if:
    @ Call strcmp on two names
    ldr r0, [fp, P1_OFFSET]      @ load the 1st pointer
    ldr r0, [r0]                 @ get 1st name into r0
    ldr r1, [fp, P2_OFFSET]      @ load the 2nd pointer
    ldr r1, [r1]                 @ get 2nd name into r1
    bl strcmp                    @ call string compare

    @ strcmp returned value > 0, first > second
    cmp r0, 0                    @ compare to 0
    ble else                     @ branch if numbers are equal
    @ return -1                 
    mov r0, -1                   @ otherwise return -1 
    b end_if                     @ branch to end_if

else:
    @ Else, equal, so return 0
    mov r0, 0                    @ the numbers are equal

end_if:
    sub sp, fp, FP_OFFSET        @ deallocate vars
    @ Restore caller's registers 
    pop {fp, pc}                 @ restore caller's fp
