_t:
    push    "Works!"
    mov     6, hx;
    jmp     write_string;
    push    10;
    ptc
    pop
    return;

write_string:
	.beg:
	    ptc
	    pop
	    sub 1, hx

    ggn		beg
	mov		0, hx
    return
