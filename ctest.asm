command: <1> # name: <argcount>
	outl # write top value of stack to console, that's 13
	return

main:
 	push 12 # push 12 onto stack
 	pop # remove top element of stack, that's 12
	command 13 # call label command and push 13 to stack
	hlt
