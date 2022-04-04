bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data

    ; A byte string S is given. Build the string D whose elements represent the sum of each two consecutive bytes of S.
    
    ; example:
    ; if S: 1, 2, 3, 4, 5, 6
    ; then D: 3, 5, 7, 9, 11
    
    S db 1, 2, 3, 4, 5, 6, 7, 8 ; declare the string of bytes
    len equ $-S-1 ; compute the length of the string in len
    D times len db 0 ; reserve l bytes for the destination string and initialize it 
    
; our code starts here
segment code use32 class=code
    start:
        
        ; we put the length len in ECX in order to make the loop
        mov ecx, len
        
        ; we go through each byte from the string
        mov esi, 0
        
        jecxz EndOfLoop
        
        Looping:
        
            mov al, [S+esi]
            mov bl, [S+esi+1]
            add al, bl
            mov [D+esi], al
            
            inc esi
        loop Looping
        
        ;end of the program
        EndOfLoop: 
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
