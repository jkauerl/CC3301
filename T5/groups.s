	.file	"groups.c"
	.option nopic
	.attribute arch, "rv32i2p0_m2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	groups
	.type	groups, @function
groups:
	mv		a5,a0
	slli	a4,a0,1
	beq		a0,zero,.L5
	li		a0,0
	j		.L4
.L3:
	srli	a5,a5,1
	srli	a4,a4,1
	beq		a5,zero,.L7
.L4:
	andi	a3,a5,1
	beq		a3,zero,.L3
	andi	a3,a4,1
	seqz	a3,a3
	add		a0,a0,a3
	j		.L3
.L7:
	ret
.L5:
	li		a0,0
	ret
	.size	groups, .-groups
	.ident	"GCC: (GNU) 11.1.0"
