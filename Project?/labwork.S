  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.global delay
.global time2string


.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #

.data
.align 2
mytime:    .word 0x5957
timstr:    .ascii


.text
main:
    # print timstr
    la    $a0,timstr
    li    $v0,4
    syscall
    nop
    # wait a little
    li    $a0,1000
    jal   delay
    nop
    # call tick
    la    $a0,mytime
    jal   tick
    nop

    li    $a0,10
    li    $v0,11
    syscall
    nop

    # call your function time2string
    la    $a0,timstr
    la    $t0,mytime
    lw    $a1,0($t0)
    jal   time2string
    nop
    # print a newline
    li    $a0,10
    li    $v0,11
    syscall
    nop
    # go back and do it all again
    j     main
    nop
# tick: update time pointed to by $a0
tick:
    lw      $t0,0($a0)    # get time
    addiu   $t0,$t0,1    # increase
    andi    $t1,$t0,0xf    # check lowest digit
    sltiu   $t2,$t1,0xa    # if digit < a, okay
    bnez    $t2,tiend
    nop
    addiu   $t0,$t0,0x6    # adjust lowest digit
    andi    $t1,$t0,0xf0    # check next digit
    sltiu   $t2,$t1,0x60    # if digit < 6, okay
    bnez    $t2,tiend
    nop
    addiu   $t0,$t0,0xa0    # adjust digit
    andi    $t1,$t0,0xf00    # check minute digit
    sltiu   $t2,$t1,0xa00    # if digit < a, okay
    bnez    $t2,tiend
    nop
    addiu   $t0,$t0,0x600    # adjust digit
    andi    $t1,$t0,0xf000    # check last digit
    sltiu   $t2,$t1,0x6000    # if digit < 6, okay
    bnez    $t2,tiend
    nop
    addiu   $t0,$t0,0xa000    # adjust last digit
tiend:
    sw      $t0,0($a0)    # save updated result
    jr      $ra        # return
    nop

    # you can write your code for subroutine "hexasc" below this line
    #
time2string:
    PUSH   $ra
    PUSH   $s0      #子方程将之前使用过的s0和s1储存在stack，再将a0和a1的值赋予s0和s1，在这里之前s0和s1未被使用，但为防止在以后的情况中，time2string被作为子方程的子方程
                    #则需要先把之前使用过的s0和s1储存起来，跳回主方程之前再pop出来，将值还给主方程
    PUSH   $s1

    move   $s0,$a0  #a0原来储存的是存时间的address，现在将address赋予s0，a0将可以作为argument被随意改变，从而在function hexasc中作为argument出现
    move   $s1,$a1

    andi   $t0,$s1,0x0000f000
    srl    $a0,$t0,12           #！！！！！切勿将t registers作为一个方程的argument，因为t registers只能在一个方程中得以使用，当call另外一个方程时，t的值容易发生改变
                                #因此不宜使用
    jal    hexasc
    nop
    sb     $v0,0($s0)
    addi   $s0,$s0,1

    andi   $t0,$s1,0x00000f00
    srl    $a0,$t0,8
    jal    hexasc
    nop
    sb     $v0,0($s0)
    addi   $s0,$s0,1

    li     $t0,0x3a
    sb     $t0,0($s0)
    addi   $s0,$s0,1

    andi   $t0,$s1,0x000000f0
    srl    $a0,$t0,4
    jal    hexasc
    nop
    sb     $v0,0($s0)
    addi   $s0,$s0,1

    andi   $a0,$s1,0x0000000f
    li     $t0,2
    beq    $a0,$t0,jerry
    nop

    jal    hexasc
    nop
    sb     $v0,0($s0)
    addi   $s0,$s0,1

    li     $t0,0x00
    sb     $t0,0($s0)

jing:

    POP    $s1
    POP    $s0
    POP    $ra
    jr     $ra
    nop

jerry:
    PUSH  $s0
    li    $t0,84
    sb    $t0,0($s0)
    addi  $s0,$s0,1

    li    $t0,87
    sb    $t0,0($s0)
    addi  $s0,$s0,1

    li    $t0,79
    sb    $t0,0($s0)
    addi  $s0,$s0,1

    li    $t0,0x00
    sb    $t0,0($s0)

    POP   $s0
    j     jing
    nop


hexasc:
    andi   $t0,$a0,0x0f
    li     $t1,0x30
    add    $v0,$t1,$t0
    jr     $ra
    nop

delay:
    li     $t1,65000
    li     $t0,67
    mul    $t1,$t1,$t0
    li     $t0,0
fora:
    beq    $a0,$0,donea
    nop
    addi   $a0,$a0,-1
fort:
    beq    $t0,$t1,donet
    nop
    addi   $t0,$t0,1
    j      fort
    nop
donet:
    j      fora
    nop
donea:
    jr     $ra
    nop

