;23. A file name and a hexadecimal number (on 16 bits) are given. Create a file with the given name and write each nibble composing the hexadecimal number on a different line to file.

bits 32

global start        

extern exit
extern fopen, fclose, fprintf
import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll

segment data use32 class=data
    write_format db '%x', 0
    
    newline dd 0xA
        
    hexadecimal_number dd 0xFFFF
    output_file_name db 'output.txt', 0
    output_file_format db 'w', 0
    output_file_descriptor dd -1
    
    digit dd 0

segment code use32 class=code
    start:
    
    push dword output_file_format
    push dword output_file_name
    call [fopen]
    add esp, 4 * 2
    
    mov [output_file_descriptor], eax
    
    cmp eax, 0
    je endProgram
    
    mov ecx, 4
    mov eax, dword [hexadecimal_number]
    
    nextDigit:
    
    mov ebx, 0xF000
    and bx, ax
    shr ebx, 12
    mov [digit], dword ebx
    
    pushad
    push dword [digit]
    push dword write_format
    push dword [output_file_descriptor]
    call [fprintf]
    add esp, 4 * 3
    
    push dword newline
    push dword [output_file_descriptor]
    call [fprintf]
    add esp, 4 * 2
    popad
    
    shl eax, 4
    
    loop nextDigit
    
    push dword [output_file_descriptor]
    call [fclose]
    add esp, 4
    
    endProgram:

    push dword 0
    call [exit]
