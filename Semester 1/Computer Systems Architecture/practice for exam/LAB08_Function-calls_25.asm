;25. Read two numbers a and b (in base 10) from the keyboard and determine the order relation between them (either a < b, or a = b, or a > b). Display the result in the following format: "<a> < <b>, <a> = <b> or <a> > <b>".

bits 32

global start        

extern exit
extern scanf, printf
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    a dd 0
    b dd 0
    a_message db "a = ", 0
    b_message db "b = ", 0
    read_format db "%d", 0
    write_format db "%d", 0
    lower_message db "%d < %d", 0
    equal_message db "%d = %d", 0
    greater_message db "%d > %d", 0


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
    
    cmp eax, ebx
    jl lowerBranch
    je equalBranch
    
    greaterBranch:
    push dword [b]
    push dword [a]
    push dword greater_message
    call [printf]
    add esp, 4 * 3
    jmp stopProgram
    
    lowerBranch:
    push dword [b]
    push dword [a]
    push dword lower_message
    call [printf]
    add esp, 4 * 3
    jmp stopProgram
    
    equalBranch:
    push dword [b]
    push dword [a]
    push dword equal_message
    call [printf]
    add esp, 4 * 3
    
    stopProgram:
    
    push dword 0
    call [exit]
