; 30. A file name (defined in data segment) is given. 
; Create a file with the given name, then read words from the keyboard until character '$' is read from the keyboard. 
; Write only the words that contain at least one digit to file.

bits 32

global start        
extern exit, fopen, fprintf, scanf, fclose, printf
import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import scanf msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    
    new_line dd 0xA ; the ascii code of a new line in hexadecimal is A
    output_file_name db "output.txt", 0 ; the name of the output file
    open_file_mode db "w", 0 ; the output file will be opened in the "write" mode
    identifier dd 0 ; variable to hold the file descriptor
    string_maximum_length equ 100 ; maximum number of characters to read from keyboard
    string times string_maximum_length db 0 ; here you can find the string read from the keyboard
    print db "Enter a new string(maximum 100 characters accepted): ", 0
    format_scan db "%100s", 0

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
    
    keepLooping:
        ; display the prompt
        push print
        call [printf] 
        add esp, 4*1
        
        ; read the string from the keyboard
        push string
        push format_scan
        call [scanf] 
        add esp, 4*2
        
        ; store in esi the address of the first character from the string
        mov esi, string
        
        ; clear the direction flag to be sure the string is being parsed from left to right
        cld
        
        ; dl acts as a switch, when dl becomes 1 that means a digit has been found in the string 
        mov dl, 0
        
        char:
            ; the byte from the address <DS:ESI> is loaded in al
            lodsb 
            
            ; if the end of the string has been reached, go to the file output algorithm
            cmp al, 0
            je fileOutput
            
            ; if the actual character is '$', the program will stop running after the output file is closed
            cmp al, 24h
            je closeOutputFile              
       
            ; check if the actual character's ascii code is bigger or equal to the 0's ascii code
            ; if not, jump over the next check related to this one
            cmp al, 30h
            jae biggerThan0
            jb nextCharacterFromString
            
            ; if the character's ascii code was bigger or equal to the 0's ascii code
            ; check now if also the character's ascii code is smaller or equal to the 9's ascii code
            ; if both conditions are satisfied, that means the character is a digit
            biggerThan0:
            cmp al, 39h                 
            jbe isDigit
                       
            jmp nextCharacterFromString
            
            isDigit:
                ; the character that has just been checked is a digit
                mov dl, 1 
                ; here we could've added a jump in order to stop validation of all other characters, but we still need to watch out for '$' in order to stop the 
                
            nextCharacterFromString:
                jmp char
            
        fileOutput:
        ; if the string had a digit, write it in the file, otherwise jump over that step
        cmp dl, 1 
        jne final
        
        ; write the string in the output file
        push dword string
        push dword [identifier]
        call [fprintf]
        add esp, 4*2
        
        ; in order to display the output nicely, write a newline after each string
        push dword new_line
        push dword [identifier]
        call [fprintf]
        add esp, 4*2
        
        final:
            jmp keepLooping
            
closeOutputFile:
    ; close the output file
    push dword [identifier]
    call [fclose] 
    add esp, 4*1

programStop:    

push    dword 0      ; push the parameter for exit onto the stack
call    [exit]       ; call exit to terminate the program
