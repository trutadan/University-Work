;18. A text file is given. The text contains letters, spaces and points. Read the content of the file, determine the number of words and display the result on the screen. (A word is a sequence of characters separated by space or point)bits 32 ; assembling for the 32 bits architecture
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
    
    print_format db '%d words found.', 0
    
    counter dd 0

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
    dec ecx
    mov ebx, 0
    mov edx, 0
    
    cld
    lodsb
    
    cmp al, 0x0
    je endOfText
    
    cmp al, 0x20
    je isNotLetter
    
    cmp al, 0x2E
    je isNotLetter
    
    mov ebx, 1
    
    isNotLetter:
    
    nextCharacter:
    lodsb
    
    cmp al, 0x0
    je endOfText
    
    cmp al, 0x20
    je notLetter
    
    cmp al, 0x2E
    je notLetter
    
    mov ebx, 1
    jmp notWord
    
    notLetter:
    cmp ebx, 1
    je wordFound
    
    mov ebx, 0
    jmp notWord
    
    wordFound:
    inc edx
    mov ebx, 0
    
    notWord:
    
    loop nextCharacter
    
    endOfText:
    
    mov [counter], dword edx
    
    push dword [counter]
    push dword print_format
    call [printf]
    add esp, 4 * 2
    
    endProgram:
    
    push dword 0
    call [exit]
    