.text
.globl main
main:
li $v0, 5
syscall
sw $v0, var1
lw $t0, var1
li $t1, 0
beq $t0, $t1, .label0
li $t0, 0
j .label1
.label0:
li $t0, 1
.label1:
sw $t0, var2
li $t2, 0
lw $t3, var2
beq $t3, $t2, .label2
li $t4, 123
sw $t4, var2
j .label3
.label2:
li $t5, 3
sw $t5, var2
.label3:
lw $t7, var2
li $t8, 600
add $t6, $t7, $t8
move $t0, $t6
li $t1, 60
add $t9, $t0, $t1
move $t3, $t9
li $t4, 6
add $t2, $t3, $t4
sw $t2, var2
lw $t6, var1
li $v0, 1
move $a0, $t6
syscall
li $a0, 10
li $v0, 11
syscall
lw $t8, var2
li $v0, 1
move $a0, $t8
syscall
li $a0, 10
li $v0, 11
syscall
li $v0, 10
syscall

.data
var1: .word 0
var2: .space 4

