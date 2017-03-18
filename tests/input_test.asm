main:
	inp
	gln number
	ggn str
	gen str
	var x

	.number:
		push "Thats a number!"
		mov 15, hx
		jmp write_string
		hlt

	.str:
		push "Thats a string!"
		mov 15, hx
		jmp write_string
		hlt

write_string: # String value on Stack, Length on String in HX
	var x
	mov hx, x
	ptr hx, x
	.beg:
		sub 1, hx
		ptc
		pop
	ggn beg
	ptr hx, hx
	return
