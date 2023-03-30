mcr m1
sub r1,r4
bne END
endmcr


MAIN: mov r3, LENGTH
LOOP: jmp r1
m1
jmp: dec K
prn #-5
bne LOOP(r4,r7)
m1
L1: inc r1
.entry hi
.entry good
.entry job
.extern bye
bne LOOP(K,STR)
END: stop
.string "abcdefg"
LENGTH: .data "1231"
.data "12"
