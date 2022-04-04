bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; b,c-byte, e,g,h-word
    b db 3
    c db 5
    e dw 0Ah
    g dw 8
    h dw 6
; our code starts here
segment code use32 class=code
    start:
        ; (e+g-h)/3+b*c 
        
         mov ax, [e]
         add ax, [g]
         ; ax = e+g-h
         sub ax, [h]
         
         mov bl, 3
         ; ax = (e+g-h)/3
         div bl
         
         ; bl = (e+g-h)/3 
         mov bl, al
         mov al, [b]
         
         
         mul byte [c]
         mov [b], ax
         mov al, bl
         mov ah, 0
         
         ; bl = low part from b*c
         mov bl, [b]
         
         ; bh = high part from b*c 
         ; bx = b*c
         mov bh, [c]
         
         ; ax = (e+g-h)/3+b*c
         add ax, bx
         
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
