.text
.globl main
main:
li $t1, 5
lw $t2, var1
sub $t0, $t1, $t2
sw $t0, var1
li $v0, 5
syscall
sw $v0, var2
lw $t3, var2
li $t4, 0
beq $t3, $t4, .label0
lw $t6, var1
li $t7, 5
add $t5, $t6, $t7
move $t3, $t5
li $t8, 0
beq $t3, $t8, .label2
li $t3, 4
j .label3
.label2:
li $t3, 5
.label3:
move $t3, $t3
j .label1
.label0:
li $t3, 10
.label1:
sw $t3, var3
lw $t0, var3
li $v0, 1
move $a0, $t0
syscall
li $a0, 10
li $v0, 11
syscall
li $v0, 10
syscall

.data
var1: .word 15
var2: .word 0
var3: .space 4

