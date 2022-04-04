;17. A file name is given (defined in the data segment). Create a file with the given name, then read numbers from the keyboard and write only the numbers divisible by 7 to file, until the value '0' is read from the keyboard.

bits 32

global start        

extern exit
extern fopen, fprintf, fclose, printf, scanf
import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data
    number dd 0
    read_message db 'number = ', 0
    read_write_format db '%u', 0
    
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
    
    push dword read_message
    call [printf]
    add esp, 4
    
    push dword number
    push dword read_write_format
    call [scanf]
    add esp, 4 * 2
    
    mov eax, dword [number]
    
    cmp eax, 0
    je noMoreNumbers
    
    mov edx, 0
    mov ebx, 7
    
    div ebx
    
    cmp edx, 0
    jne notDivisible
    
    push dword [number]
    push dword read_write_format
    push dword [output_file_descriptor]
    call [fprintf]
    add esp, 4 * 3
    
    push dword newline
    push dword [output_file_descriptor]
    call [fprintf]
    add esp, 4 * 2
    
    notDivisible:
    
    jmp nextNumber
    
    noMoreNumbers:
    
    push dword [output_file_descriptor]
    call [fclose]
    add esp, 4

    endProgram:
    
    push dword 0
    call [exit]
