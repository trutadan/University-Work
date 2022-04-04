;1. Read two numbers a and b (in base 10) from the keyboard and calculate their product. This value will be stored in a variable called "result" (defined in the data segment).


bits 32 

global start        
extern exit
extern printf, scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll


segment data use32 class=data
    ; ...
    a dd 0
    b dd 0
    result dd 0
    message_a db "a = ", 0
    message_b db "b = ", 0
    message_output db "a * b = ", 0
    read_format db "%d", 0
    write_format db "%d", 0

segment code use32 class=code
    start:

        push dword message_a
        call [printf]
        add esp, 4
        
        push dword a
        push dword read_format
        call [scanf]
        add esp, 4 * 2
        
        push dword message_b
        call [printf]
        add esp, 4
        
        push dword b
        push dword read_format
        call [scanf]
        add esp, 4 * 2
              
        mov eax, dword [a]
        mov ebx, dword [b]
        
        imul ebx
        
        mov dword [result], eax
        mov dword [result+4], edx
        
        push dword message_output
        call [printf]
        add esp, 4
        
        push dword [result]
        push dword write_format
        call [printf]
        add esp, 4 * 2
        
        push    dword 0 
        call    [exit]
