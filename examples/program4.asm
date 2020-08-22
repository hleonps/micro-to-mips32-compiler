.text
.globl main
main:
li $v0, 5
syscall
sw $v0, var1
lw $t1, var1
li $t2, 50
add $t0, $t1, $t2
sw $t0, var2
lw $t5, var2
li $t6, 30
sub $t4, $t5, $t6
move $t3, $t4
li $v0, 1
move $a0, $t3
syscall
li $a0, 10
li $v0, 11
syscall
lw $t9, var1
li $t0, 40
add $t8, $t9, $t0
move $t7, $t8
li $v0, 1
move $a0, $t7
syscall
li $a0, 10
li $v0, 11
syscall
li $v0, 10
syscall

.data
var1: .word 0
var2: .space 4

