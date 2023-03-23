mcr m1
sub r1,r4
bne END
endmcr


MAIN: mov r3, LENGTH
LOOP: jmp L1(#-1,r6)
m1
jmp: dec K
prn #-5
bne LOOP(r4,r7)
m1
L1: inc K

bne LOOP(K,STR)
END: stop
STR: .string "abcdef"
LENGTH: .data
K: .data 22