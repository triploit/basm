main:
	jqn	init
	jln init

	add 1, ax
	rts ax
	outl
	pop
	jgn main
	hlt

init:
	mov 1000000, hx		# Discription of this programm in speedtest.asm
	return
