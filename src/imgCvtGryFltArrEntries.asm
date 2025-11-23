section .data
    const_255 dd 255.0      ; Constant 255.0 for multiplication

section .text
    bits 64                 ; Specify 64-bit mode
    default rel             ; Use RIP-relative addressing for position independence
    global imgCvtGryFltArrEntries

imgCvtGryFltArrEntries:
    ; Load constant 255.0 into XMM1 (for all conversions)
    movss xmm1, dword [rel const_255]
    
    ; Initialize loop counter
    xor r9, r9              ; r9 = 0 (index counter, r9 is volatile so safe to use)

.convert_loop:
    cmp r9, r8              
    jge .done             
    movss xmm0, dword [rcx + r9*4]    ; xmm0 = float_array[r9] (SIMD scalar load)

    mulss xmm0, xmm1                   ; xmm0 *= xmm1 (255.0)
    
    cvtss2si eax, xmm0                 ; eax = (int)round(xmm0)
    
    test eax, eax
    jns .check_upper_bound             ; if eax >= 0, check upper bound
    xor eax, eax                       ; else eax = 0 (clamp to 0)
    jmp .store_result
    
.check_upper_bound:
    cmp eax, 255
    jle .store_result                  ; if eax <= 255, store it
    mov eax, 255                       ; else eax = 255 (clamp to 255)
    
.store_result:
    mov byte [rdx + r9], al            ; integer_array[r9] = al (lower 8 bits of eax)
    
    inc r9
    jmp .convert_loop

.done:
    ret