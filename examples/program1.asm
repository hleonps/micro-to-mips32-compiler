.text
.globl main
main:
lw $t1, var1
lw $t2, var1
add $t0, $t1, $t2
sw $t0, var1
lw $t4, var1
li $v0, 1
move $a0, $t4
syscall
li $a0, 10
li $v0, 11
syscall
li $v0, 10
syscall

.data
var1: .word -2

