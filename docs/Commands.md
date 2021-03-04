# Commands

## A
### add
Add adds 2 args and saves the result in 2nd one.
Syntax:
```asm
add value, variable
```
Where `value` can be variable or value or register and `variable` can be variable or register.
Example:
```asm
add 1, ax
add ax, bx
add 4, variable
# but not:
add 1, 4 # ERROR: LINE 2: ADD: WRONG_TYPE: Field "1" has the wrong type!
        # ERROR: LINE 2: ADD: XYZ_NOT_FOUND: Variable/Register "4" doesn't 
        # exist!
```
### aga
Aga is abbreviation from "Array Get value At"
Syntax:
```asm
aga array, idx, variable
```
`array` is array, `idx` index and `variable` is variable or register in which will be value of expression `array[idx]`.
Examples:
```asm
aga array, 0, myvar
aga list, x, x
# but not:
aga array, 0, 1 # ERROR: LINE 4: AGA: VARIABLE(2)_NOT_FOUND: 1
```
### ags
Ags is abbreviation from "Array Get Size"
Syntax:
```asm
ags array, variable
```
`array` is array and `variable` is variable or register in which will be stored size of array `array`.
Examples:
```asm
ags list, list_size
# but not:
ags array, 10 # ERROR: LINE: 3: AGS: INVALID_VALUE: 10
```
### arl
Arl possibly is abbreviation from "Array Remove eLements".
Syntax:
```asm
arl array, val
```
`arr` is array and `val` is number of times we want to remove end of `arr`.
Examples:
```asm
arl array, 10 # Removes 10 last elements from array array
ags list, cx # Copies list's size to CX register
arl list, cx # Removes all of elements from array list
# but not:
arl 10, 3 # ERROR: LINE 5: ARL: ARRAY_NOT_FOUND: 10
```
### arr
Arr command creates array with given name.
Syntax:
```asm
arr array
``
Examples:
```asm
arr array
# but not:
arr ax # ERROR: LINE 3: INVALID_VARIABLE_NAME: "ax": Variable/Register 
       # already exists!
```
Be careful with creating array with name which is a number! It is __UB__!
### asa
Asa is abbreviation from Set Array to Array. However, this is heavily stretched.
Syntax:
```asm
asa array1, array2
```
Examples:
```asm
asa array, list
# but not:
asa ax, 1 # ERROR: LINE 3: ASA: ARRAY_NOT_FOUND: ax
          # ERROR: LINE 3: ASA: ARRAY_NOT_FOUND: 1
asa 1, array # ERROR: LINE 5: ASA: ARRAY_NOT_FOUND: 1