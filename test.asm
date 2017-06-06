stack_to_array:         # needs length of input in hx, output in list_ax; if yout get input with inp,
    var len             # the value is on the stack and the length of the input is in hx,
    mvv hx, len         # so be careful with hx!
    .ar:
        ata list_ax, 0
        sub 1, hx

    ggn ar
    pushv len
    str hx
    pop
    .beg:
        sub 1, hx
        str gx

        asv list_ax, hx, gx
        pop
    ggn beg
    return

# test 1 2 3

array_to_stack:         # needs value in list_ax
    ags list_ax, hx     # "asa your_array, list_ax"
    mov 0, fx           # -> This sets the value of list_ax to your_array
    .beg:
        aga list_ax, fx, gx
        push gx
        sub 1, hx
        add 1, fx
    gnn beg
    return

write_string: # String value on Stack, Length on String in HX
    .beg:
        sub 1, hx
        ptc
        pop
    ggn beg
    return

write_array: # String value in LIST_AX
    ags list_ax, hx
    mov 0, ax
    .beg:
        aga list_ax, ax, bx
        push bx
        ptc
        pop
        add 1, ax
        sub 1, hx
    ggn beg
    return

new_line: # prints new line
    push 10
    ptc
    pop
    return

main:
    var o_in
    inp
    mvv hx, o_in
    jmp stack_to_array
    jmp array_to_stack
    pushv o_in
    str hx
    pop
    jmp write_string
    jmp new_line
    hlt
