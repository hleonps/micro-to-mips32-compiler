.text
.globl main
main:
li $t0, 12
li $t2, 15
move $t3, $t0
sub $t1, $t2, $t3
move $t0, $t1
li $v0, 1
move $a0, $t0
syscall
li $a0, 10
li $v0, 11
syscall
li $t4, 4
li $t6, 6
move $t7, $t4
sub $t5, $t6, $t7
move $t9, $t5
li $t0, 1
sub $t8, $t9, $t0
move $t4, $t8
li $v0, 1
move $a0, $t4
syscall
li $a0, 10
li $v0, 11
syscall
li $v0, 10
syscall

.data

