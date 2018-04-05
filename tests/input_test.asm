main:
	push "> "
	write_string 2
	inp
	gen number
	ggn str

	.number:
		push "Thats a number!"
		write_string 15
		jmp pnl
		push gx
		outl
		hlt

	.str:
		push "Thats a string!"
		write_string 15
		jmp pnl
		add 1, hx
		write_string hx
		hlt

	return

pnl:
	push 10
	ptc
	pop
	return

write_string: <1> # String value on Stack, String length as argument
	var x
	ptr hx, x
	str hx
	pop
	.beg:
		sub 1, hx
		ptc
		pop
	gnn beg
	ptr hx, hx
	return
