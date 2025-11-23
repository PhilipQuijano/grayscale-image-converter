section .data
    const_255 dd 255.0      ; Constant 255.0 for multiplication

section .text
    bits 64                 ; Specify 64-bit mode
    default rel             ; Use RIP-relative addressing for position independence
    global imgCvtGryFltArrEntries

; Function: imgCvtGryFltArrEntries
; Purpose: Convert float pixel array to uint8_t integer array
; 
; Windows x86-64 Calling Convention:
; Parameters (as per lecture):
;   RCX = float* float_array (1st parameter - input)
;   RDX = uint8_t* integer_array (2nd parameter - output)  
;   R8  = int total_pixels (3rd parameter - count)
;
; Return: void (no return value)
;
; Conversion formula: integer_pixel = float_pixel * 255.0
; Uses SIMD scalar floating-point instructions (XMM registers)

imgCvtGryFltArrEntries:
    ; No need to save non-volatile registers if we don't use them
    ; RCX, RDX, R8 are volatile (caller-saved) - we can use them freely
    
    ; Load constant 255.0 into XMM1 (we'll reuse this for all conversions)
    movss xmm1, dword [rel const_255]
    
    ; Initialize loop counter
    xor r9, r9              ; r9 = 0 (index counter, r9 is volatile so safe to use)

.convert_loop:
    ; Check if we've processed all pixels
    cmp r9, r8              ; compare counter with total_pixels
    jge .done               ; if r9 >= r8, exit loop
    
    ; Load float pixel value from float_array[r9]
    ; Each float is 4 bytes, so offset = r9 * 4
    movss xmm0, dword [rcx + r9*4]    ; xmm0 = float_array[r9] (SIMD scalar load)
    
    ; Multiply by 255.0: xmm0 = xmm0 * 255.0 (SIMD scalar floating-point instruction)
    mulss xmm0, xmm1                   ; xmm0 *= xmm1 (255.0)
    
    ; Convert float to integer with rounding (SIMD to integer conversion)
    cvtss2si eax, xmm0                 ; eax = (int)round(xmm0)
    
    ; Clamp value to [0, 255] range
    ; Check if negative
    test eax, eax
    jns .check_upper_bound             ; if eax >= 0, check upper bound
    xor eax, eax                       ; else eax = 0 (clamp to 0)
    jmp .store_result
    
.check_upper_bound:
    ; Check if greater than 255
    cmp eax, 255
    jle .store_result                  ; if eax <= 255, store it
    mov eax, 255                       ; else eax = 255 (clamp to 255)
    
.store_result:
    ; Store uint8_t value to integer_array[r9]
    ; Each uint8_t is 1 byte, so offset = r9 * 1
    mov byte [rdx + r9], al            ; integer_array[r9] = al (lower 8 bits of eax)
    
    ; Increment counter and continue loop
    inc r9
    jmp .convert_loop

.done:
    ; No registers to restore (we only used volatile registers)
    ret