bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a - byte, b - word, c - double word, d - qword - Signed representation
    a db 10
    b dw 32
    c dd 4
    d dq 5

; our code starts here
segment code use32 class=code
    start:
        ; c+d-a-b+(c-a)
        
        ; edx:eax <- c
        mov edx, 0
        mov eax, 0
        mov eax, [c]
        cdq
        
        ; ebx:ecx <- d 
        mov ecx, 0
        mov ebx, 0
        mov ecx, dword [d+0]
        mov ebx, dword [d+4]
        
        ; ebx:ecx <- c+d
        add ecx, eax
        adc ebx, edx
        
        ; edx:eax <- a
        mov eax, 0
        mov al, [a]
        cbw
        cwde
        cdq
        
        ; ebx:ecx <- c+d-a
        sub ecx, eax
        sbb ebx, edx

        ; edx:eax <- b
        mov eax, 0
        mov ax, [b]
        cwde
        cdq
        
        ; ebx:ecx <- c+d-a-b
        sub ecx, eax
        sbb ebx, edx
        
        ; eax <- a
        mov eax, 0
        mov al, byte [a]
        cbw
        cwde
        
        ; edx <- c
        mov edx, 0
        mov edx, dword [c]
        
        ; eax:edx <- c-a
        sub edx, eax
        mov eax, 0
        sbb eax, 0            
        
        ; ebx:ecx <- c+d-a-b+(c-a)
        add ecx, edx
        adc ebx, eax
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
