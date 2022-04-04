bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a,b,c,d - word
    a dw 3
    b dw 5
    c dw 7
    d dw 0Ah
; our code starts here
segment code use32 class=code
    start:
        ; (d-c)+(b+b-c-a)+d 
        
        mov ax, [d]
        sub ax, [c]
        
        mov bx, [b]
        add bx, [b]
        sub bx, [c]
        sub bx, [a]
        
        add ax, bx
        
        add ax, [d]
        ; ax = (d-c)+(b+b-c-a)+d
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
