bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a - word, b - byte, c - word, x - qword - Unsigned representation
    a dw 4
    b db 45
    c dw 23
    x dq 15
    
; our code starts here
segment code use32 class=code
    start:
        ; x-(a*100+b)/(b+c-1);
        
        ; edx:eax <- a*100
        mov edx, 0
        mov eax, 0
        mov ax, 100
        
        mov ebx, 0
        mov bx, [a]
        mul word bx
        
        ; ecx <- b
        mov ecx, 0
        mov cl, byte [b]
        
        ; edx:eax <- a*100 + b
        add eax, ecx
        adc edx, 0
        
        ; ebx <- c
        mov ebx, 0
        mov bx, word [c]
        
        ; ecx <- b
        mov ecx, 0
        mov cl, byte [b]
        
        ; ebx <- b+c
        add ebx, ecx
        
        ; ecx <- 1
        mov ecx, 0
        mov cl, 1
        
        ; ebx <- b+c-1
        sub ebx, ecx
        
        ; eax <- (a*100+b)/(b+c-1)
        div ebx
        
        ; ebx:ecx <- x
        mov ecx, 0
        mov ebx, 0
        mov ecx, [x+0]
        mov ebx, [x+4]
        
        ; ebx:ecx <- x-(a*100+b)/(b+c-1)
        sub ecx, eax
        sbb ebx, 0 
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
