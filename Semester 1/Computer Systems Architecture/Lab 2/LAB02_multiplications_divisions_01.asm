bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a,b,c - byte, d - word
    a db 4
    b db 6
    c db 5
    d dw 16
; our code starts here
segment code use32 class=code
    start:
        ; d+10*a-b*c 
        
         mov al, 10
         ; ax = al*a
         mul byte [a]
         
         ; d = d+10*a
         add [d], ax
         mov al, [b]
         
         ; ax = b*c
         mul byte [c]
         
         ; d = d+10*a-b*c
         sub [d], ax
         
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
