.686
.MODEL FLAT, C
.STACK
.DATA
.CODE
findNegativeCount PROC len:DWORD, arr:DWORD
    mov esi, arr
    mov eax, len
    shl eax, 2
    add esi, eax
    sub esi, 4
    mov ecx, len
    @c1:
        mov eax, [esi]
        cmp eax, 0
        je @cnt1
        sub esi, 4
    loop @c1
    mov ecx, len
    jmp @else
    @cnt1:
    mov edi, arr
    sub esi, edi
    shr esi, 2
    xor ecx, ecx
    mov ecx, esi
    @else:
    xor edx, edx
    xor eax, eax
    mov esi, arr
    @c2:
        mov edx, [esi]
        cmp edx, 0
        jge @cnt2
        inc eax
    @cnt2:
    add esi, 4
    loop @c2

	ret
findNegativeCount ENDP

findPositiveArithmeticMean PROC len:DWORD, arr:DWORD
    mov ecx, len
    mov esi, arr
    xor edx, edx
    xor ebx, ebx
    @c1:
        mov eax, [esi]
        cmp eax, 0
        jle @cnt1
        inc dh
        add ebx, eax
    @cnt1:
        add esi, 4
    loop @c1
    xchg ebx, eax
    cmp dh, 0
    jne @cnt2
    div dh
    cbw
    cwde 
    @cnt2:
	ret
findPositiveArithmeticMean ENDP

END