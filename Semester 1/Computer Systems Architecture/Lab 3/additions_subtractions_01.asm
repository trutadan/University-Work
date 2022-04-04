bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a - byte, b - word, c - double word, d - qword - Unsigned representation
    a db 106
    b dw 32687
    c dd 4297296
    d dq 51327357

; our code starts here
segment code use32 class=code
    start:
        ; d-(a+b)+(c+c)

        ; a <- bx
        mov ebx, 0
        mov bl, [a]
        mov bh, 0
        
        ; b <- ax
        mov ecx, 0
        mov cx, [b]
        
        ; a+b <- cx
        add cx, bx
        
        ; d <- edx:eax
        mov eax, 0
        mov edx, 0
        mov eax, dword [d+0]
        mov edx, dword [d+4]
        
        ; d-(a+b) <- edx:eax
        sub eax, ecx
        sbb edx, 0
        
        ; c+c <- ecx:ebx
        mov ebx, [c]
        mov ecx, 0
        add ebx, [c]
        adc ecx, ecx
        
        ; d-(a+b)+(c+c) <- edx:eax
        add eax, ebx
        adc edx, ecx
            
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
