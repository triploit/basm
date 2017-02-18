mov 1000000, hx		# Discription of this programm in speedtest.asm

main:
	add 1, ax
	rts ax
	outl
	sub 1, hx
	jgn main
	hlt
