section .data
var1 dd 255.0
section .text
bits 64
Default rel
global imgCvtGrayFloatToInt

imgCvtGrayFloatToInt:
	MOVSS xmm1, xmm0
	MOVSS xmm2, [var1]
	MULSS xmm1, xmm2
	CVTSS2SI RAX, xmm1
ret

