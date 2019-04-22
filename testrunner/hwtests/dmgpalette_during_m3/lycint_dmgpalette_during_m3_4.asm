.size 8000

.code@48
	jp l1000

.code@100
	jp l150

.code@150
l150:
	ld c, 44
	ld b, 97
l154:
	ldff a, (c)
	nop
	cmp a, b
	jpnz l154
	ld c, 41
	ld a, 40
	ldff(c), a
	ld a, 02
	ldff(ff), a
	xor a, a
	ldff(0f), a
	ldff(45), a
	ld c, 47
	ld a, ff
	ldff(c), a
	inc a
	ld b, 90
	ei

.code@1000
l1000:
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	ldff(c), a
	dec a

.code@1030
	ldff(c), a
	pop hl
	ldff a, (45)
	inc a
	cmp a, b
	jrnz l1039
	xor a, a
l1039:
	ldff(45), a
	ld a, 00
	ei

