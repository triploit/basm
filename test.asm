
main:
	mov 1000000, hx		# Discription of this programm in speedtest.asm
	.main:
		# add 1, ax
		# rts ax
		# outl
		# pop

		sub 1, hx;
		rts hx
		outl
		pop

	ggn main
	hlt
