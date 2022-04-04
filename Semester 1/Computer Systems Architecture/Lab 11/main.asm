; 16. Read a string of unsigned numbers in base 10 from keyboard. Determine the maximum value of the string and write it in the file max.txt (it will be created) in 16  base.

bits 32 

global start        
extern bigger_number      
extern exit, fopen, fprintf, scanf, fclose, printf
import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import scanf msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
                    
segment data use32 class=data

    n dq 0
    identifier dd 0
    max dq 0
    msg_n db "string number: ", 0
    output_file_name db "max.txt", 0
    open_file_mode db "w", 0
    readformat db "%d", 0
    writeformat db "%x", 0
    
segment code use32 class=code
start:
    ; open the file in write mode
    push open_file_mode
    push output_file_name
    call [fopen] 
    add esp, 4*2
    
    ; store the file descriptor returned by fopen
    mov [identifier], eax
    
    ; check if fopen() has successfully created the file (EAX != 0)
    cmp eax, 0
    je programStop
    
    push dword msg_n
    call [printf]
    add esp, 4

    push dword n
    push dword readformat
    call [scanf]
    add esp, 4 * 2
        
    mov ebx, dword [n]
        
    mov dword [max], ebx
    
    keepLooping:
        mov ecx, 2
        
        push ebx
        
        push dword msg_n
        call [printf]
        add esp, 4

        push dword n
        push dword readformat
        call [scanf]
        add esp, 4 * 2
            
        mov edx, dword [n]
        
        cmp edx, 0
        je zeroInput
        
        pop ebx
        
        push dword edx
        push dword ebx
        call bigger_number
        add esp, 4 * 2
        
        mov dword [max], ebx

    loop keepLooping
    
    zeroInput:
    
    ; write the string in the output file
    push dword [max]
    push dword writeformat
    push dword [identifier]
    call [fprintf]
    add esp, 4*3

    closeOutputFile:
    ; close the output file
    push dword [identifier]
    call [fclose] 
    add esp, 4*1
    
    programStop:    
	push dword 0
	call [exit]