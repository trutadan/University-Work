bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a - word, b - byte, c - word, x - qword - Signed representation
    a dw 4
    b db 45
    c dw 23
    x dq 3

; our code starts here
segment code use32 class=code
    start:
        ; x-(a*100+b)/(b+c-1);
        
        ; eax <- 100
        mov eax, 0
        mov ax, 100
        cwde
        
        ; ebx <- a
        
        mov ebx, 0
        mov bx, [a]
        
        ; eax <- a*100
        imul word bx
        
        ; ebx <- a*100
        mov ebx, eax
        
        ; eax <- b
        mov eax, 0
        mov al, byte [b]
        cbw
        cwde
        
        ; ebx <- a*100+b
        add ebx, eax
        
        ; ecx <- b
        mov ecx, eax
        
        ; eax <- c
        mov eax, 0
        mov ax, word [c]
        cwde
        
        ; ecx <- b+c
        add ecx, eax
        
        ; eax <- 1
        mov eax, 0
        mov al, 1
        cbw
        cwde
        
        ; ecx <- b+c-1
        sub ecx, eax
        
        ; edx:eax <- a*100+b
        mov eax, ebx
        mov edx, 0
        
        ; eax <- (a*100+b)/(b+c-1)
        idiv ecx 
        
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
