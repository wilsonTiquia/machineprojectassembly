section .text
global daxpy_asm
daxpy_asm:
    ; Parameters are passed in registers: rcx, rdx, r8
    ; RCX CONTAINS N - SIZE OF ARRAY
    ; RDX CONTAINS ARRAY OF X
    ; R8 CONTAINS ARRAY OF Y
    ; R9 CONTAINS ARRAY OF Z
    ; XMM4 CONTAINS FLOAT A 
    
    
    
    ; SETUP STACK FRAME SINCE WE USE MORE THAN 4 PARAMETERS
    push rbp
    mov rbp, rsp
    add rbp, 16
    movsd xmm4, [rbp+32]
    
    
    MOV RAX, 0
    
    daxpy:
    
    
    cmp RAX, RCX
    ;go to end if the counter is equal or greater than the n
    jge end
    ; FIRST STEP
    ; (A * X[i])
    ; C float = single plrecision
    ; C double = double precision
    mulsd xmm4, [rdx + RAX * 8] ; 25 VALUE OF XMM4
    addsd xmm4, [R8 + RAX * 8] ; 30
    movsd [r9 + RAX * 8], xmm4

    ;incement the counter
    INC RAX
    movsd xmm4, [rbp+32]
    ;repeat the loop
    jmp daxpy

    end:
    ;return xmm0 to the C program
    
    pop rbp
    xor rax, rax
    ret