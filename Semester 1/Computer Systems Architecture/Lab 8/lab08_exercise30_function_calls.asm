; 30. Read numbers (in base 10) in a loop until the digit '0' is read from the keyboard. 
; Determine and display the smallest number from those that have been read.

bits 32 

global start        
extern exit, printf, scanf
import exit msvcrt.dll   
import printf msvcrt.dll 
import scanf msvcrt.dll  
                    
segment data use32 class=data

    n dq 0
    min dq 0
    msg_n db "n=", 0
    readformat db "%lld", 0
    writeformat db "%lld", 0 ; %lld is a placeholder for the long long int data type from C, represented on 8 bytes
    
segment code use32 class=code
start:
    ; printf("n=");
    push dword msg_n
    call [printf]
    add esp, 4

    ; %lld -> 8 bytes, n is a qword
    push dword n
    push dword readformat
    call [scanf]
    add esp, 4 * 2
        
    ; in ecx:eax it is stored n
    mov eax, dword [n] ; low part of n
    mov ecx, dword [n+4] ; high part of n
        
    ; consider the first number introduced as being the minim
    mov dword [min], eax
    mov dword [min + 4], ecx
    
    ; check if the high part of n is 0
    cmp eax, 0
    jne keepLooping
    
    ; check if the low part of n is 0 too
    cmp ecx, 0
    je inputZero ; if low and high part of n are 0 that means the program needs to stop
    
    ; ecx is being pushed here because of the first pop from the loop
    push ecx
    
    keepLooping:
    
        ; after the ecx is modified on the last step, get the value before that
        pop ecx
        
        ; the registers may be modified during the reading
        push ecx
        push eax
        
        ; printf("n=");
        push dword msg_n
        call [printf]
        add esp, 4

        ; we have to ensure that we allocate enough space for the defined variable in accordance to the used placeholder
        ; %lld -> 8 bytes, n is a qword so we're good
        push dword n
        push dword readformat
        call [scanf]
        add esp, 4 * 2
            
        ; edx:ebx = n
        mov ebx, dword [n] ; low part of n
        mov edx, dword [n+4] ; high part of n
        
        cmp edx, 0
        jne inputNotZero
          
        cmp ebx, 0
        je inputZero
            
        inputNotZero:
        
        ; we get back the values of the registers that are modified during the reading
        pop eax
        pop ecx
        
        ; see if the high part of the new introduced number is lower than the high part of minimum number stored
        cmp edx, ecx
        jl foundSmaller
        je highPartsEqual
        jmp notBelow
        
        ; if the high part of the new introduced number is equal with the high part of minimum number stored
        ; see if the low part of the new introduced number is lower than the low part of minimum number stored
        highPartsEqual:
        cmp ebx, eax
        jl foundSmaller
        
        ; the number introduced is not lower than the one stored
        jmp notBelow
        
        foundSmaller:
            
        ; store the new minimum value
        mov dword [min], ebx
        mov dword [min + 4], edx
        
        mov eax, dword [min] ; low part of n
        mov ecx, dword [min+4] ; high part of n
            
        notBelow:
        
        ; push the value of ecx and pop it again in the beginning of the loop
        push ecx
        
        ; after the whole loop runs, the ecx becomes 2 and at the end of the loop it is decremented
        mov ecx, 2
        ; so now ecx is 1, not 0, so the loop keeps running
        
    loop keepLooping
        
    inputZero:
    
    ; to print a qword on the screen, first push its high part then its low part so that the high dword is at the higher address
    push dword [min + 4]
    push dword [min]
    push dword writeformat
    call [printf]
    add esp, 4 * 3
    
	push dword 0
	call [exit]