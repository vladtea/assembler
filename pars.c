// Opcode table
enum Opcode {
   /*first group of instructions getting 2 operans*/
    mov = 0b0000,/*0*/
    cmp = 0b0001,/*1*/
    add = 0b0010,/*2*/
    sub = 0b0011,/*3*/
    lea = 0b0110,/*6*/
    /*second group of instructions that needs only one operand, have only dec operand 4 - 5 always zero*/
    not = 0b0100,/*4*/
    clr = 0b0101,/*5*/
    inc = 0b0111,/*7*/
    dec = 0b1000,/*8*/
    jmp = 0b1001,/*9*/
    bne = 0b1010,/*10*/
    red = 0b1011,/*11*/
    prn = 0b1100,/*12*/
    jsr = 0b1101,/*13*/
    /*third group of instructions*/
    rts = 0b1110,/*14*/
    stop = 0b1111/*15*/
};