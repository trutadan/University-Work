;15. Read two numbers a and b (in base 10) from the keyboard and calculate a+b. Display the result in base 16

bits 32

global start        

extern exit, printf, scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data
    a_message db "a = ", 0
    b_message db "b = ", 0
    output_message db "a + b = ", 0
    a dd 0
    b dd 0
    result dd 0
    read_format db "%d", 0
    write_format db "%x", 0

segment code use32 class=code
    start:
    
    push dword a_message
    call [printf]
    add esp, 4
    
    push dword a
    push dword read_format
    call [scanf]
    add esp, 4 * 2
    
    push dword b_message
    call [printf]
    add esp, 4
    
    push dword b
    push dword read_format
    call [scanf]
    add esp, 4 * 2
    
    mov eax, dword [a]
    mov ebx, dword [b]
    
    add eax, ebx
    
    mov dword [result], eax
        
    push dword output_message
    call [printf]
    add esp, 4
    
    push dword [result]
    push dword write_format
    call [printf]
    add esp, 4 * 2
    
    push dword 0
    call [exit]
