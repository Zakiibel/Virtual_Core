/*!
\file functions.h
\author BELMIR Zakaryae, YAZANE HASSAN
\version 1.0
\date 05/11/2021
\brief Virtual Core
*/

#ifndef PROJET_FUNCTIONS_H
#define PROJET_MFUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>


#define TAILLE_MAX 40
#define MEMO_SIZE 512
#define MEMSIZ 10



/*Memoire de taille 64bits */
extern uint64_t memory[MEMO_SIZE] ;
//extern int running;
extern int verbose;
/***Registers****/
enum //enumeration I have no idea about this , Yes I do
{
  R_R0 = 0,
  R_R1,
  R_R2,
  R_R3,
  R_R4,
  R_R5,
  R_R6,
  R_R7,
  R_R8,
  R_R9,
  R_R10,
  R_R11,
  R_R12_MDR,
  R_R13_MAR,
  R_R14_PC,
  R_R15_IR,
  R_COUNT
};


/*    Table des registres sur 64bits */
extern uint64_t regs[R_COUNT];

/* decode instr */
extern int decoder[16];

/** instruction number ***/
enum  /* OPCPDE */
{
  OP_AND = 0x0,     //dest = ope1 and ope2
  OP_ORR = 0x1,     //dest = ope1 or ope2
  OP_EOR = 0x2,     //dest = ope1 xor ope2
  OP_ADD = 0x3,     //dest = ope1 + ope2
  OP_ADC = 0x4,     //dest = ope1 + ope2 + carry
  OP_CMP = 0x5,     //Comparison
  OP_SUB = 0x6,     //dest = ope1 - ope2
  OP_SBC = 0x7,     //dest = ope1 - ope2 + carry -1
  OP_MOV = 0x8,     //dest = ope2
  OP_LSH = 0x9,     //dest = ope1 << ope2
  OP_RSH = 0xa,     //dest = ope1 >> ope2
  OP_HALT= 0xb      //end the program
};

enum  /* BCC */
{
  BCC_B   = 0x8,      //Unconditional branch
  BCC_BEQ = 0x9,      //Branch if equal              ope1 =  ope2
  BCC_BNE = 0xa,      //Branch if not equal          ope1 != ope2
  BCC_BLE = 0xb,      //Branch if lower or equal     ope1 <= ope2
  BCC_BGE = 0xc,      //Branch if greater or equal   ope1 >= ope2
  BCC_BL  = 0xd,      //Branch if lower              ope1 <  ope2
  BCC_BG  = 0xe       //Branch if greater            ope1 >  ope2
};



void read_file(char const * file);
void init_regs(char const * file);
void showRegs();
void showMemory();
void run();

#endif //PROJET_FUNCTIONS_H
