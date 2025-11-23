; [MP2] x86-to-C interface
; "Project Specification: Grayscale Image Conversion
; "By: Pineda, Dencel Angelo D. & Punsalan, Emmanuel Gerald G. (LBYARCH-S19A)

section .data
    divisor: dq 255.0 ; constant division (integer-based pixel)

section .text
bits 64
default rel
global imgCvtGrayIntToDouble

; Function: imgCvtGrayIntToDouble
; Parameters:
; RCX - height
; RDX - width
; R8 - pointer to input array
; R9 - pointer to output array

imgCvtGrayIntToDouble:
    mov rax, rcx        ; moving height
    imul rax, rdx       ; height * width (total pixels)

    xor rcx, rcx        ; resetting loop counter

    movsd xmm1, qword [divisor] ; loading 255.0 to xmm1 with SIMD reg/ins
    
convert_loop:
    cmp rcx, rax        ; comparing counter to total pixels
    jge done            ; exit if >=
   
    movzx rdx, byte [r8 + rcx]  ; loading to input array with SIMD ins
    
    ; mapping int to double with SIMD reg/ins
    cvtsi2sd xmm0, rdx
    
    ; converting to grayscale (f/i; f = double float-based pixel value and i = integer-based pixel value)
    divsd xmm0, xmm1    ; result / 255.0 with SIMD reg/ins
    
    movsd qword [r9 + rcx*8], xmm0  ; storing result to output array with SIMD reg/ins
    
    inc rcx             ; increment counter
    jmp convert_loop    ; loop again
    
done:
    ret