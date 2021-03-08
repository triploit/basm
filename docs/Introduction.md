# BASM - Binary Assembly

When other Assemblies are assembled directly to machine code or compiled to architecure-specific Assemblies, BASM is translated to higher-order language -- C++.
This is why BASM is an uncustomary language. You do not very often see language which translation process looks like BASM's one.

# Basics

In BASM you have access to 8 32-bit registers: AX, BX, CX, DX, EX, FX, GX, HX. In other Assemblies you have 8 8-bit registers, 4 16-bit, 4 32-bit and 4 64-bit registers. And Instruction Pointers, Stack Pointers, Base Pointers and Segment registers, of course.

> *__IMPORTANT:__ When other Assemblies have following syntax:
> `command destination, source`, in BASM positions of destination and 
> source are swapped.*
## Registers in detail
- 'a' in AX stands for *__accumulator__*
- 'b' in BX stands for *__base__*
- 'c' in CX stands for *__counter__*
- 'd' in DX stands for *__data__*
<!-- - 'e' in EX stands for *____* -->
- 'f' in FX stands for *__function__*