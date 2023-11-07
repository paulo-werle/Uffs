	.data
A:	.space	4
B:	.space	4
C:	.space	4
S:	.space	4
	.text
main: 
	la    t0, A
	la    t1, B
	la    t2, C
	la    t3, S
	lw    s0, 0 (t0)
	lw    s1, 0 (t1)
	lw    s2, 0 (t2)
	sub   a0, s0, s1
	addi  a1, s2, -5
	add   s3, a0, a1
	sw    s3, 0 (t3)

