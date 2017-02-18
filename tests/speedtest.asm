mov 1000000, hx		# move 1000000 to HX

main:			# basm needs a main function
	add 1, ax	# add 1 to register AX
	rts ax		# put register AX to stack
	outl		# write last number of the stack and write a new line character
	sub 1, hx	# decrement HX (hx = hx - 1)
	jgn main	# jump to main if HX is greater than 0 (Jump if Greater Null)
	hlt		# terminate the program when HX is equal to zero, or less than zero, because the loop stops
