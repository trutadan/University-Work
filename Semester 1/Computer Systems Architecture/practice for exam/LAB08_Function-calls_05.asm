;5. Two natural numbers a and b (a, b: dword, defined in the data segment) are given. Calculate a/b and display the quotient and the remainder in the following format: "Quotient = <quotient>, remainder = <remainder>". Example: for a = 23, b = 10 it will display: "Quotient = 2, remainder = 3". The values will be displayed in decimal format (base 10) with sign.

bits 32 

global start        

extern exit
extern printf, scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data
    a dd 0
    b dd 0
    quotient dd 0
    remainder dd 0
    a_message db 'a = ', 0
    b_message db 'b = ', 0
    read_format db '%d', 0
    newline dd 0xA
    quotient_message db 'Quotient = %d', 0
    remainder_message db 'Remainder = %d', 0


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
    cdq
    mov ebx, dword [b]
    
    idiv ebx
    
    mov [quotient], dword eax
    mov [remainder], dword edx
    
    push dword [quotient]
    push dword quotient_message
    call [printf]
    add esp, 4 * 2
    
    push dword newline
    call [printf]
    add esp, 4
    
    push dword [remainder]
    push dword remainder_message
    call [printf]
    add esp, 4 * 2
    
    push dword 0
    call [exit]