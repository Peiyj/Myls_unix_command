/*
 * Filename: timeCompare.s
 * Author: Yingjian Pei
 * Userid: A13595990
 * Description: defines the timeCompare funtion that is passed in as
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
.global timeCompareRev

/*
 * Function name: timeCompareRev()
 * Function prototype: timeCompareRev(const void *p1, const void *p2);
 * Description: This function will be used with qsort() to sort on 
 * the names of two struct fileInfo in alphabetical order.  
 * Parameters: p1: a pointer
 *             p2: a pointer 
 * Side Effects: None.  
 * Error Conditions: None.
 * Return Value: -1 if the first time is newer, 0 if they are the same
 * or +1 if the first time is older.
 * Registers Used: 
 * r0: void pointer 1: first pointer to struct fileInfo
 * r1: void pointer 2: second pointer to struct fileInfo
 */
timeCompareRev:
    @ Save caller's registers on the stack
    push {fp, lr}                @ save registers
    add fp, sp, FP_OFFSET        @ set fp to the base
    sub sp, sp, PARAM_SPACE      @ push parameter space
    str r0, [fp, P1_OFFSET]      @ store the first parameter
    str r1, [fp, P2_OFFSET]      @ store the second paramter
if:
    @ Call strcmp on two numbers
    ldr r0, [fp, P1_OFFSET]      @ load the first pointer
    ldr r0, [r0]                 @ load the struct pointer

    ldr r2, =offset_time         @ load the time offset
    ldr r2, [r2]                 @ load the content
    ldr r0, [r0, r2]             @ get 1st name into r0
    
    ldr r1, [fp, P2_OFFSET]      @ load the second pointer
    ldr r1, [r1]                 @ load the struct pointer
    ldr r2, =offset_time         @ load the time offset
    ldr r2, [r2]                 @ load the content
    ldr r1, [r1, r2]             @ get 2nd name into r1

    @ first < second
    cmp r0,r1                    @ compare first and second
    bge else_if                  @ if the first is greater or equal
    @ return 1
    mov r0, 1                    @ if number is smaller, return 1
    b end_if                     @ go to end_if

else_if:
    @ Call strcmp on two names
    ldr r0, [fp, P1_OFFSET]      @ load the 1st pointer
    ldr r0, [r0]                 @ load the struct offset
    ldr r2, =offset_time         @ load the time offset
    ldr r2, [r2]                 @ load the content
    ldr r0, [r0, r2]             @ get 1st name into r0
    ldr r1, [fp, P2_OFFSET]      @ load the 2nd pointer
    ldr r1, [r1]                 @ load the struct offset
    ldr r2, =offset_time         @ load the time offset
    ldr r2, [r2]                 @ load the content
    ldr r1, [r1, r2]             @ get 2nd name into r1

    @ first > second
    cmp r0, r1                   @ compare to 0
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
