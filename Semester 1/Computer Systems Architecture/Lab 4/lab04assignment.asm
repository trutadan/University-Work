bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; A - word, B - doubleword
    A dw 0111011101010111b
    B dd 0

; our code starts here
segment code use32 class=code
    start:
        ; 19th exercise
    
        ; compute the result in ebx
        mov ebx, 0
        
        ; the bits 28-31 of B have the value 1
        or ebx, 11110000000000000000000000000000b
        
        ; the bits 24-25 and 26-27 of B are the same as the bits 8-9 of A
        mov eax, 0 ; eax = 0
        mov ax, [A] ; ax = A
        and ax, 0000001100000000b ; isolate the bits 8-9 of A          
        mov cl, 16 ; 24 - 8 = 16
        rol eax, cl ; rotate 16 positions to the left (to the bits 24-25)
        or ebx, eax
        
        mov cl, 2
        rol eax, cl ; we rotate 2 more positions to the left (to the 26-27 bits)
        or ebx, eax
        
        ; the bits 20-23 of B are the invert of the bits 0-3 of A
        mov eax, 0 ; eax = 0
        mov ax, [A] ; ax = A
        not ax ; invert the bits of A
        and ax, 0000000000000111b ; isolate the bits 0-3 of A
        mov cl, 20 ; 20 - 0 = 20
        rol eax, cl
        or ebx, eax
        
        ; the bits 16-19 of B have the value 0
        and ebx, 11111111111100001111111111111111b
        
        ; the bits 0-15 of B are the same as the bits 16-31 of B
        mov eax, ebx
        mov cl, 16 ; 16 - 0 = 16
        ror eax, cl ; eax = the bits 16-31 of B
        or ebx, eax
        
        ; move the result from the register to the result variable
        mov  [B], ebx
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
