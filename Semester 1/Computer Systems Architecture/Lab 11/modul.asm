bits 32 ; assembling for the 32 bits architecture


global bigger_number

; our code starts here
segment code use32 class=code public

    bigger_number:
        push ebp
        mov ebp, esp

        mov ebx, dword [ebp + 12]
        mov edx, dword [ebp + 8]

        cmp ebx, edx
        jae skip

        mov ebx, edx

        skip:
        mov esp, ebp
        pop ebp

        ret