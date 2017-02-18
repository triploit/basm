main:                   # there must be a main function
    push "Hello World!" # Put "Hello World!" on the stack
    mov 12, hx          # load length of "Hello World!" (11) in HX
    jmp write_string    # write the string on the console
    push 10             # push new line character
    ptc                 # convert ascii-number (10) to character and write it on the console
    pop                 # delete last element (10) from stack
    hlt                 # stop program

write_string:           # Needs the size of the string in HX and the string on the Stack
    ptc                 # convert ascii-number to character and write it on the console
    pop                 # delete last element from stack
    sub 1, hx           # decrement hx (hx = hx - 1)
    jgn write_string    # if HX is greater than null (Jump if Greater Null), repeat the function
    return              # if HX is 0 or is less 0, then it doesn't make a loop and it returns from this function to main
