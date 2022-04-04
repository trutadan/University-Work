bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data

    ; 28. Being given a string of bytes and a substring of this string, eliminate all occurrences of this substring from the initial string.
    ; input: 1, 5, 2, 9, 11, 5, 7, 5, 2, 9, 9, 4, 6
    ; output: 1, 11, 5, 7, 9, 4, 6
    
    ; the given string
    string db 1, 5, 2, 9, 11, 5, 7, 5, 2, 9, 9, 4, 6
    stringlength equ $-string
    
    ; the given substring
    substring  db 5, 2, 9
    substringlength equ $-substring
    
    ; the newly formed string
    newstring db stringlength
    
    ; C++ variant
    
    ; char string[], substring[], newstring[];
    ; for(i=0; i<len(string)-len(substring); i++){
    ;       int auxi=i, auxj=0, contor=len(substring);
    ;       while(string[auxi]==substring[auxj]){
    ;           contor--;
    ;           auxi++; auxj++;
    ;           }
    ;       if (contor!=0)
    ;           newstring[] += string[auxi]
    ; }
    ; for(i; i<len(string); i++)
    ;        newstring[] += string[i]

; our code starts here
segment code use32 class=code
    start:
        ; NASM implementation
        
        mov edx, 0 ; length of the new string
        
        mov esi, string  ; store the FAR address of the string
        mov ecx, stringlength  ; store the length of the given string in ecx

        sub ecx, substringlength ; subtract substring length to prevent looking beyond the string length
        cmp ecx, 0 ; check if the substring fits in the string
        jl exitProgram ; if not, the substring can never be a part of the string
        
        repeatProcess:
            mov edi, substring  ; store the FAR address of the substring
            mov ebx, esi ; make a copy of the FAR address of the substring
            ; because we are using it later to copy each byte from the old string to the new one
            
            push ecx ; we need one register free, in order to check if the actual sequence is a substring
            mov ecx, substringlength ; we check if the substring matches the current sequence 
            
            cld ; clear the direction flag in order to be sure the string is being parsed the right way
            
            repe cmpsb ; compare substring at edi, with the string in esi
            jz substringFound ; if ZF = 1 then substring is found within string
            
            ; code to be executed if the sequence checked is not a substring 
            pop ecx ; get back the length of the given string from the stack
            dec ecx ; we just checked one element, so we decrement the step counter
            
            mov esi, ebx ; we get the address of the byte we just checked(the first of the sequence)
            lodsb ; we have now the byte from the old string in AL
            inc ebx ; we get the address of the next byte we want to check
            
            mov esi, newstring ; store the FAR address of the new string
            mov byte [esi+edx], al ; store the byte from AL in the new string on a new position
            inc edx ; increment the length of the new string
            
            mov esi, ebx ; we get the address of the next byte we want to check
            
            jmp substringNotFound

            substringFound:
            pop ecx ; get back the length of the given string from the stack
            sub ecx, substringlength ;  we just checked substringlength elements, so we subtract substringlength value from the step counter
            
            substringNotFound:

        cmp ecx, 0 ; check how many steps have been done
        jnl repeatProcess ; if there are more steps to be done
        
        ; we are checking only stringlength-substringlength elements of the string, so there remain
        ; substringlength bytes to be copied in the end of the string
        
        mov ecx, substring 
        sub ecx, esi ; see how many elements to be checked are left
        
        cmp ecx, 0 ; check if the substring fits in the string
        jle exitProgram ; if not, the substring can never be a part of the string
        
        mov ebx, esi ; in ebx we have the address of the first byte left to be copied
        
        repeatLastProcess:
            mov esi, ebx ; copy the address of the byte to be copied from the old string
            lodsb ; we have now the byte from the old string in AL
            mov esi, newstring ; store the FAR address of the newstring in esi
            mov byte [esi+edx], al ; store the byte from AL in the new string
            inc edx ; increment the length of the new string
            dec ecx ; we just checked one element, so we decrement the step counter
            inc ebx ; we get the address of the next byte we want to check
            
            cmp ecx, 0 ; check how many steps have been done
            jnle repeatLastProcess  ; if there are more steps to be done
        
        exitProgram:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
