main:					# BASM needs a main function
	mov 1000000, hx		# load 1000000 to HX
	.main:				# set goto-label main ( !! this is not a function !! )

		sub 1, hx;		# decrement HX
		rts hx			# push value of HX to stack
		outl			# write last element of stack to screen and write a new line
		pop				# delete last element from stack

	ggn main			#.if HX is greater than zero, jump to goto label "main"
	hlt					# stop programm
