;4. A text file is given. Read the content of the file, count the number of odd digits and display the result on the screen. The name of text file is defined in the data segment.

bits 32

global start        

extern exit
extern fopen, fread, fclose, printf
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    
    input_file_name db 'input.txt', 0
    input_file_open_format db 'r', 0
    input_file_descriptor dd -1
    
    text_length equ 100
    text times text_length db 0
    
    write_format db '%d', 0

    frequency dd 0
    
segment code use32 class=code
    start:
    
    push dword input_file_open_format
    push dword input_file_name
    call [fopen]
    add esp, 4 * 2
    
    mov [input_file_descriptor], eax
    
    cmp eax, 0
    je endProgram
    
    push dword [input_file_descriptor]
    push dword text_length
    push dword 1
    push dword text
    call [fread]
    add esp, 4 * 4
    
    push dword [input_file_descriptor]
    call [fclose]
    add esp, 4
    
    mov esi, text
    mov ecx, text_length
    
    mov ebx, 0
    
    nextCharacter:
    mov eax, 0
    lodsb
    
    cmp al, 0x0
    je endOfString
    
    cmp al, '0'
    jb notDigit
    
    cmp al, '9'
    ja notDigit
    
    sub al, '0'
    shr al, 1
    jnc notDigit
    
    inc ebx
    
    notDigit:
    
    loop nextCharacter
    
    endOfString:
    
    mov [frequency], dword ebx
    
    push dword [frequency]
    push dword write_format
    call [printf]
    add esp, 4 * 2
    
    endProgram:

    push dword 0
    call [exit]
