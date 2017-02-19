main:			# basm needs a main function
    .main:      # create a goto-label named "main"
        push 1	# Push 1 to stack
        outl	# write last number of the stack and write a new line character
        pop		# delete last element from stack
        jmp d_	# run function d_
        gt main	# goto label main (endless loop)
        hlt		# stop programm (will never be execute, due to the endless loop

d_:			    # function d_
    push 2		# push 2 ti stack
    outl		# write last number of the stack and write a new line character
    pop			# delete last element from stack
    jmp e_		# run function e_
    push 4		# push 4 to stack
    outl		# write last element of the stack and write a new line character
    rts fx		# push value of register FX to stack
    outl		# write last number of the stack and write a new line character
    pop			# delete last element of stack

e_:			    # function e_
    push 3		# push 3 to stack
    outl		# write last number of the stack and write a new line character
    pop			# delete last element from stack
    mov 13, gx	# set value of GX to 13
    return		# return to d_ and load the value of GX to FX
