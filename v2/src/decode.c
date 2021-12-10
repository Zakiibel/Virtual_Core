/*!
\file decode.C
\author BELMIR Zakaryae, YAZANE HASSAN
\version 1.0
\date 05/11/2021
\brief Virtual Core
*/
#include "functions.h"
#include "decode.h"

char decoder[16];


/*****DECODE****/
void decode(int instr)
{
  /*  [
  32 bits of instructions;
  31-28 : 4bits for BCC;
  ;27-25 : 3bits always 0;
  24 : 1 bit IV Flag;
  23-20 : 4bits for Opcode;
  19-16 : 4 bits for ope1;
  15-12: 4 bits for ope2;
  11-8 : 4bits for dest register;
  7-0 : 8 bits for IV]*/
  //decoder[R_R3] = (instr & 0x4000000) >> 27;   //BCC
  decoder[R_R4] = (instr & 0xF0000000) >> 28;   //BCC
  decoder[R_R5] = (instr & 0x1000000) >> 24;    //FLAG
  decoder[R_R6] = (instr & 0xF00000) >> 20;     //OPCODE
  decoder[R_R7] = (instr & 0xF0000) >> 16;      //OPE1
  decoder[R_R8] = (instr & 0xF000) >> 12;        //OPE2
  decoder[R_R9] = (instr & 0xF00) >> 8;          //DEST
  decoder[R_R10] = (instr & 0xFF);               //IV
}
