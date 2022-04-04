;27. A text file is given. The text file contains numbers (in base 10) separated by spaces. Read the content of the file, determine the minimum number (from the numbers that have been read) and write the result at the end of file.

bits 32

global start        

extern exit
extern fopen, fread, fclose, fprintf, fscanf
import fscanf msvcrt.dll
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll

segment data use32 class=data
    file_name db 'text.txt', 0
    
    input_file_format db 'r', 0
    input_file_descriptor dd -1

    output_file_format db 'a', 0
    output_file_descriptor dd -1
    
    text_length equ 100
    text times text_length db 0
    
    format db "%d", 0
    newline dd 0xA, 0
    
    w_format db 0xA, "%d", 0
    
    max dd 0
    
segment code use32 class=code
    start:
    
    push dword input_file_format
    push dword file_name
    call [fopen]
    add esp, 4 * 2
    
    mov [input_file_descriptor], eax
    
    cmp eax, 0
    jle endProgram
    
    ;reading number
    push dword text
    push dword format
    push dword [input_file_descriptor]
    call [fscanf]
    add esp, 4 * 3
    
    mov edx, dword [text]
    mov dword [max], edx
    
    main_loop:
    
    push dword text
    push dword format
    push dword [input_file_descriptor]
    call [fscanf]
    add esp, 4 * 3
    
    ;check for error
    cmp eax, 0
    jle end_main_loop
    
    mov edx, dword [max] 
    
    cmp edx, dword [text]
    jnl notBigger
    
    mov edx, dword [text]
    mov dword [max], edx
    
    notBigger:
    
    jmp main_loop
    
    end_main_loop:
    
    push dword [input_file_descriptor]
    call [fclose]
    add esp, 4
    
    push dword output_file_format
    push dword file_name
    call [fopen]
    add esp, 4 * 2
    
    mov [output_file_descriptor], eax
    
    cmp eax, 0
    je endProgram
    
    push dword [max]
    push dword w_format
    push dword [output_file_descriptor]
    call [fprintf]
    add esp, 4 * 3
    
    push dword [output_file_descriptor]
    call [fclose]
    add esp, 4

    endProgram:
    
    push dword 0
    call [exit]
