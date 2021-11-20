.686
.MODEL FLAT, C
.STACK
.DATA
	l	=	20
	arr	dd	l dup (?)
	s1	db	"Original array:", 0Ah,0Dh, 0
	s2	db	"%d ", 0
	s3	db	0Ah, 0Dh, "The number of negative numbers in the array = %d", 0Ah,0Dh, 0
	s4	db	"The number of negative numbers up to the last zero = %d", 0Ah,0Dh, 0
.CODE
findNegativeCount	PROTO len:DWORD, arr:PTR DWORD
findPositiveArithmeticMean	PROTO len:DWORD, arr:PTR DWORD
printf			PROTO arg1:PTR BYTE, printlist:VARARG
scanf			PROTO arg1:PTR BYTE, scanlist:VARARG
getchar			PROTO
srand			PROTO seed:DWORD
rand			PROTO 
time			PROTO timer:DWORD

main PROC
	invoke	time, 0
	invoke	srand, eax
	invoke	printf, ADDR s1

	mov		ecx, l
	mov		edi, offset arr
	mov		ebx, 21
	cld
@fillArr:
	push	ecx
	invoke	rand
	pop		ecx
	cdq
	div		ebx
	mov		eax, edx
	sub		eax, 10
	stosd
	push	ecx
	invoke	printf, ADDR s2, eax
	pop		ecx
	loop	@fillArr

	invoke	findNegativeCount, l, ADDR arr
	invoke	printf, ADDR s3, eax

	xor eax, eax

	invoke	findPositiveArithmeticMean, l, ADDR arr
	invoke	printf, ADDR s4, eax

	invoke	getchar
	xor		eax, eax
	ret
main ENDP

END main