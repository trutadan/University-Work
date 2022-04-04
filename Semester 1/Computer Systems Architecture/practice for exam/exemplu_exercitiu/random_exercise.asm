; A name of the input file is defined in the data segment. Replace all the small letters from the file with their ascii code. The result will be saved in an output file.
; Example:
; The text read from the input file: MariaC; the result written in the output file should be: M9711410597C.

bits 32
global start        

extern exit, fopen, fread, fclose, fprintf
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll

segment data use32 class=data
    
    input_file_name db "input.txt", 0
    input_access_mode db "r", 0
    input_file_descriptor dd -1
    len equ 100
    text times len db 0
    
    output_file_name db "output.txt", 0
    output_access_mode db "w", 0
    output_file_descriptor dd -1
    
    small_format db "%d", 0
    not_small_format db "%s", 0
    character dd 0
    
segment code use32 class=code
    start:

    push dword input_access_mode     
    push dword input_file_name
    call [fopen]
    add esp, 4*2

    mov [input_file_descriptor], eax

    cmp eax, 0
    je final
    
    push dword output_access_mode     
    push dword output_file_name
    call [fopen]
    add esp, 4*2

    mov [output_file_descriptor], eax
    
    cmp eax, 0
    je final

    push dword [input_file_descriptor]
    push dword len
    push dword 1
    push dword text        
    call [fread]
    add esp, 4*4

    mov esi, text
    
    mov ecx, eax
    
    next:
    mov eax, 0
    lodsb
    mov dword [character], eax
    
    cmp al, 0x61
    jb notSmall
    
    cmp al, 0x7A
    ja notSmall

    pushad
    push dword eax
    push dword small_format
    push dword [output_file_descriptor]
    call [fprintf]
    add esp, 4*3
    popad
    jmp smallLetter
    
    notSmall:
    pushad
    push dword character
    push dword not_small_format
    push dword [output_file_descriptor]
    call [fprintf]
    add esp, 4*3
    popad
    
    smallLetter:
    loop next
    
    push dword [input_file_descriptor]
    call [fclose]
    add esp, 4
    
    push dword [output_file_descriptor]
    call [fclose]
    add esp, 4
    
    final:
    
    push dword 0
    call [exit]
