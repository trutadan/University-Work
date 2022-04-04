;14. A file name and a text (defined in the data segment) are given. The text contains lowercase letters, uppercase letters, digits and special characters. Transform all the uppercase letters from the given text in lowercase. Create a file with the given name and write the generated text to file.

bits 32

global start        

extern exit
extern fopen, fread, fprintf, fclose
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll

segment data use32 class=data
    input_file_name db 'input.txt', 0
    input_file_format db 'r', 0
    input_file_descriptor dd -1
    
    output_file_name db 'output.txt', 0
    output_file_format db 'w', 0
    output_file_descriptor dd -1
    
    text_length equ 100
    text times text_length db 0
    
    new_text db 0

segment code use32 class=code
    start:
    
    push dword input_file_format
    push dword input_file_name
    call [fopen]
    add esp, 4 * 2
    
    mov [input_file_descriptor], eax

    cmp eax, 0
    je endProgram
    
    push dword output_file_format
    push dword output_file_name
    call [fopen]
    add esp, 4 * 2
    
    mov [output_file_descriptor], eax
    
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
    mov edi, new_text
    mov ecx, text_length
    
    cld
    
    nextCharacter:
    lodsb
    
    cmp al, 0x0
    je endString
    
    cmp al, 'A'
    jb notUppercase
    
    cmp al, 'Z'
    ja notUppercase
    
    add al, 32
    
    notUppercase:
    
    stosb
    
    loop nextCharacter
    
    endString:
    
    push dword new_text    
    push dword [output_file_descriptor]
    call [fprintf]
    add esp, 4 * 2
    
    push dword [output_file_descriptor]
    call [fclose]
    add esp, 4
    
    endProgram:

    push dword 0
    call [exit]
