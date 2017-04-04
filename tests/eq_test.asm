print_eq: <2>
	out
	pop

	push 61
	ptc
	pop

	outl
	pop

main:
	print_eq hx, 0
	eqi hx, 0
	push hx
	outl
	pop

	print_eq hx, hx
	eqi hx, hx
	push hx
	outl
	pop

	print_eq 0, hx
	eqi 0, hx
	push hx
	outl
	pop
	hlt
