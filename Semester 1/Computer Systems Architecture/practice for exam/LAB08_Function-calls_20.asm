;20. Read two doublewords a and b in base 16 from the keyboard. Display the sum of the low parts of the two numbers and the difference between the high parts of the two numbers in base 16 Example:
;a = 00101A35h
;b = 00023219h
;sum = 4C4Eh
;difference = Eh

bits 32

global start        

extern exit
extern printf, scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data
    a dd 0
    b dd 0
    a_message db "a = ", 0
    b_message db "b = ", 0
    newline dd 0xA
    sum dd 0
    difference dd 0
    read_format db "%x", 0
    sum_message db "sum = %x", 0
    difference_message db "difference = %x", 0

segment code use32 class=code
    start:
    
    push dword a_message
    call [printf]
    add esp, 4
    
    push dword a
    push dword read_format    
    call [scanf]
    add esp, 4 * 2
    
    push dword b_message
    call [printf]
    add esp, 4
    
    push dword b
    push dword read_format    
    call [scanf]
    add esp, 4 * 2
    
    mov eax, dword [a] ; ax - lower part of a   
    mov ebx, dword [b] ; bx - lower part of b
    mov dx, 0
    
    add ax, bx
    adc dx, 0
    
    mov [sum], word ax
    mov [sum+2], word dx
    
    mov cl, 16
    shr eax, cl ; ax - higher part of a
    shr ebx, cl ; bx - higher part of b
    
    cmp ax, bx
    jb firstSmaller
    
    sub ax, bx
    mov word [difference], ax
    jmp firstBigger
    
    firstSmaller:
    sub bx, ax
    mov word [difference], bx
    
    firstBigger:
    
    push dword [sum]
    push dword sum_message
    call [printf]
    add esp, 4 * 2
    
    push dword newline
    call [printf]
    add esp, 4 
    
    push dword [difference]
    push dword difference_message
    call [printf]
    add esp, 4 * 2
    
    push dword 0
    call [exit]
