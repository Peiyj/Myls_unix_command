/*
 * Filename: nameCompare.s
 * Author: Yingjian Pei
 * Userid: A13595990
 * Description: defines the nameCompare funtion that is passed in as
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
.global nameCompare

/*
 * Function name: nameCompare()
 * Function prototype: nameCompare(const void *p1, const void *p2);
 * Description: This function will be used with qsort() to sort on 
 * the names of two struct fileInfo in alphabetical order.  
 * Parameters: p1: a pointer
 *             p2: a pointer 
 * Side Effects: None.  
 * Error Conditions: None.
 * Return Value: -1 if the first name is smaller, 
 * 0 if the names are the same, 
 * +1 if the first name is larger.
 * Registers Used: 
 * r0: void pointer 1: first pointer to struct fileInfo
 * r1: void pointer 2: second pointer to struct fileInfo
 */
nameCompare:
    @ Save caller's registers on the stack
    push {fp, lr}

    .word 0xE28DB004  

    sub sp, sp, PARAM_SPACE

    .word 0xE50B0008 

    str r1, [fp, P2_OFFSET]

if:
    @ Call strcmp on two names

    .word 0xE51B0008  

    ldr r0, [r0]                 @ get 1st name into r0
    ldr r1, [fp, P2_OFFSET]
    ldr r1, [r1]                 @ get 2nd name into r1
    bl strcmp

    @ strcmp returned value < 0, first < second
    cmp r0, 0

    .word 0xAA000001

    @ return -1
    mov r0, -1
    b end_if

else_if:
    @ Call strcmp on two names
    ldr r0, [fp, P1_OFFSET]
    ldr r0, [r0]                 @ get 1st name into r0
    ldr r1, [fp, P2_OFFSET]
    ldr r1, [r1]                 @ get 2nd name into r1
    bl strcmp

    @ strcmp returned value > 0, first > second
    cmp r0, 0


    .word 0xDA000001

    @ return 1
    mov r0, 1
    b end_if

else:
    @ Else, equal, so return 0
    mov r0, 0

end_if:
    .word 0xE24BD004

    @ Restore caller's registers
    pop {fp, pc}
