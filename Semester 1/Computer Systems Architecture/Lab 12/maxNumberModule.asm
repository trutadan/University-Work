; nasm maxNumberModule.asm -fwin32 -o maxNumberModule.obj
; cl maxNumberMain.c /link maxNumberModule.obj
; maxNumberMain.exe

; 25. Read a string of signed numbers in base 10 from keyboard. Determine the maximum value of the string and write it in the file max.txt (it will be created) in 16  base.

bits 32

global _read_numbers, _get_maximum_number
extern _scanf, _printf

segment data use32 class=data public

    read_integer_format db '%d', 0
    string_format db '%s', 0
    ask_for_number_message db 'Enter a number: ', 0


segment code use32 class=code public
        
    _read_numbers:
        push ebp
        mov ebp, esp
        
        pushad
        
        mov edi, [ebp + 12]
        mov edx, 0
        
        read:
            pushad
            
            push dword string_format
            push dword ask_for_number_message
            call _printf
            add esp, 4 * 2
            
            popad
            
            pushad
            pushfd
            
            lea eax, [edi + edx * 4]
            
            push dword eax
            push dword read_integer_format
            call _scanf
            add esp, 4 * 2
            
            popfd
            popad
            
            inc edx
            
            cmp edx, [ebp + 8]
            jne read
        
        popad
        
        mov esp, ebp
        pop ebp
        
        ret
    
    
    _get_maximum_number:
        push ebp
        
        mov ebp, esp
        sub esp, 4
        
        pushad
        pushfd
        
        mov eax, 80000000h
        mov edi, [ebp + 12]
        
        cld
        mov edx, 0
        
        compare_numbers:
            scasd
            
            jg continue
                mov eax, [edi - 4]
                
            continue:
            
            inc edx
            cmp edx, [ebp + 8]
            jne compare_numbers
            
        mov [ebp - 4], eax
        
        popfd
        popad
        
        mov eax, [ebp - 4]
        mov esp, ebp
        pop ebp
        
        ret
