;8. A text file is given. Read the content of the file, determine the uppercase letter with the highest frequency and display the letter along with its frequency on the screen. The name of text file is defined in the data segment.

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
    
    write_format db '%s %d ', 0
    
    char dd 0
    counter dd 0
    
    uppercase_letters db 0
    
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
    mov edi, uppercase_letters
    mov ecx, text_length
    
    nextChar:
    mov eax, 0
    lodsb
    
    cmp al, 0x0
    je endOfText
    
    cmp al, 'A'
    jb notUppercase
    
    cmp al, 'Z'
    ja notUppercase
    
    sub eax, 'A'
    add [edi+eax], byte 1 
    
    notUppercase:
    
    loop nextChar
    
    endOfText:
    
    mov esi, uppercase_letters
    mov ecx, 26
    mov edx, 0
    
    nextLetter:
    
    mov eax, 0
    lodsb
    
    cmp eax, edx
    jna notBigger
    
    mov edx, eax
    
    notBigger:
    
    loop nextLetter
    
    mov esi, uppercase_letters
    mov ecx, 26
    mov ebx, 0
    
    next:
    
    mov eax, 0
    lodsb
    
    cmp eax, edx
    jne isNotBiggest
    
    mov eax, 'A'
    add eax, ebx
        
    mov [counter], dword edx
    mov [char], dword eax
    
    pushad
    
    push dword [counter]
    push dword char
    push dword write_format
    call [printf]
    add esp, 4 * 3

    popad
    
    isNotBiggest:
    inc ebx
    loop next
    
    endProgram:

    push dword 0
    call [exit]
