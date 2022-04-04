;10. Read a number in base 10 from the keyboard and display the value of that number in base 16 Example: Read: 28; display: 1C

bits 32 

global start        

extern exit
extern printf, scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data
    number dd 0
    number_message db "number in base 10 = ", 0
    read_format db "%d", 0
    output_message db "number in base 16 = %x", 0

segment code use32 class=code
    start:

    push dword number_message
    call [printf]
    add esp, 4
    
    push dword number
    push dword read_format
    call [scanf]
    add esp, 4 * 2
    
    push dword [number]
    push dword output_message
    call [printf]
    add esp, 4 * 2
    
    push dword 0
    call [exit]
