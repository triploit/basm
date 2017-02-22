main:
	var	x
	ptr	ax, x
	mov	100, ax
	pushv	x
	outl
	ptr	ax, ax

	mov	300, ax
	pushv	x
	outl
	pop
	push	ax
	outl

	mov 	400, ax
	mvv	ax, x
	pushv 	x
	outl
	hlt
