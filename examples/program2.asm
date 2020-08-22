.text
.globl main
main:
li $v0, 5
syscall
sw $v0, var1
lw $t1, var1
li $v0, 1
move $a0, $t1
syscall
li $a0, 10
li $v0, 11
syscall
li $v0, 10
syscall

.data
var1: .word 0

