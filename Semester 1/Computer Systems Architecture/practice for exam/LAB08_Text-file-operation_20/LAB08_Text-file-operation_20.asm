;20. A file name and a text (defined in the data segment) are given. The text contains lowercase letters and spaces. Replace all the letters on even positions with their position. Create a file with the given name and write the generated text to file.

bits 32

global start        

extern exit
extern fopen, fprintf, fclose
import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll

segment data use32 class=data

    file_name db 'output.txt', 0
    file_open_format db 'w', 0
    file_descriptor dd -1
    
    string db 'abecedarul meu', 0
    string_length equ $-string
    
    string_format db '%s', 0
    number_format db '%d', 0
    
    character dd 0

    newstring db 0
    
segment code use32 class=code
    start:
    
    push dword file_open_format
    push dword file_name
    call [fopen]
    add esp, 4 * 2
    
    mov [file_descriptor], eax
    
    cmp eax, 0
    je endProgram
    
    mov esi, string
    mov edi, newstring
    mov ecx, string_length
    mov dl, 1
    cld
    
    nextCharacter:
    lodsb
    
    cmp al, 'a'
    jb notLetter
    
    cmp al, 'z'
    ja notLetter
    
    mov bl, dl
    shr bl, 1
    jc notLetter
    
    mov al, dl
    
    notLetter:
    stosb
    inc dl
    
    loop nextCharacter
    
    mov ecx, string_length
    mov esi, newstring
    cld
    
    nextChar:
    mov eax, 0
    lodsb
    
    mov [character], dword eax
    
    cmp al, 0x0
    je endOfString
    
    cmp al, ' '
    je spatiu
    
    cmp al, 'a'
    jb notLett
    
    cmp al, 'z'
    ja notLett

    spatiu:
    
    pushad
    
    push dword character
    push dword string_format
    push dword [file_descriptor]
    call [fprintf]
    add esp, 4 * 3
    
    popad
    
    jmp nextOne
    
    notLett:
    
    pushad
    
    push dword [character]
    push dword number_format
    push dword [file_descriptor]
    call [fprintf]
    add esp, 4 * 3
    
    popad
    
    nextOne:
    
    loop nextChar
    
    endOfString:
    
    push dword [file_descriptor]
    call [fclose]
    add esp, 4
    
    endProgram:

    push dword 0
    call [exit]
