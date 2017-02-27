main:
	var x
	ptr ax, x		# Pointer to x
	mov 100, ax		# 100 -> ax -> x
	pushv x			# push x to stack
	outl
	ptr ax, ax		# Pointer to ax (ax -> ax)

	mov 300, ax		# 300 -> ax
	pushv x			# push x to stack (100)
	outl
	pop
	push ax			# push ax to stack (300)
	outl

	mov 400, ax
	mvv ax, x
	pushv x
	outl

	mov 1, ax
	mov 2, bx
	eqi ax, bx
	rts hx
	outl
	pop

	push "Input: "
	mov 7, hx;
	jmp write_string
	inp
	mov hx, gx

	push "Your input was: "
	mov 17, hx
	jmp write_string

	mov gx, hx
	jmp write_string
	push 10

	ptc
	ptc
	pop

	arr a
	ata a, "Hello World!"
	pushv a
	ags a, hx
	jmp write_string

	push 10
	ptc
	hlt

write_string:
	.beg:
		ptc
		pop
		sub 1, hx

	ggn beg
	return
