; Read natural numbers until you reach 0. Write in a file numbers separated by space that are negative and have an odd number of bits set to 1.

bits 32
global start        

extern exit
extern fopen, fprintf, fclose, scanf, printf
import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    number dd 0
    number_message db 'number= ', 0
    read_number_format db '%d', 0
    write_number_format db '%d ', 0
    
    output_file_name db 'output.txt', 0
    output_file_descriptor dd -1
    output_file_open_format db 'w', 0

    newline dd 0xA
    
segment code use32 class=code
    start:
    
    push dword output_file_open_format
    push dword output_file_name
    call [fopen]
    add esp, 4 * 2
    
    mov [output_file_descriptor], eax
    
    cmp eax, 0
    je endProgram
    
    nextNumber:
    
    push dword number_message
    call [printf]
    add esp, 4
    
    push dword number
    push dword read_number_format
    call [scanf]
    add esp, 4 * 2
    
    mov eax, dword [number]
    
    cmp eax, 0
    je stopLoop
    jg isPositive
    
    or eax, eax
    jp isPositive
    
    push dword [number]
    push dword write_number_format
    push dword [output_file_descriptor]
    call [fprintf]
    add esp, 4 * 3
       
    isPositive:
    
    jmp nextNumber
    
    stopLoop:
    
    push dword [output_file_descriptor]
    call [fclose]
    add esp, 4
    
    endProgram:

    push dword 0
    call [exit]