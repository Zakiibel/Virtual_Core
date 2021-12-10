/*!
\file fetch.c
\author BELMIR Zakaryae, YAZANE HASSAN
\version 1.0
\date 05/11/2021
\brief Virtual Core
*/

#include "functions.h"
#include "fetch.h"


/***FETCH****/
int fetch()
{
  //regs[R_R13_MAR] = regs[R_R14_PC];
  //regs[R_R12_MDR] = memory[regs[R_R13_MAR]];
  switch (decoder[R_R4]) { //BCC
    case BCC_B:
      printf("B %d\n",decoder[R_R10]);
      regs[R_R14_PC]+=decoder[R_R10] -1;
      break;

    case BCC_BEQ:
    if (op1 == op2) {
      printf("BEQ %d\n",decoder[R_R10]);
      regs[R_R14_PC] +=  decoder[R_R10] -1;
    }
      break;

    case BCC_BNE:
      if (op1 != op2) {
        printf("BNE %d\n",decoder[R_R10]);
        regs[R_R14_PC] +=  decoder[R_R10] -1;
      }
      break;

    case BCC_BLE:
      if (op1 <= op2) {
        printf("BLE %d\n",decoder[R_R10]);
        regs[R_R14_PC] +=  decoder[R_R10] -1;
      }
      break;

    case BCC_BGE:
      if (op1 >= op2) {
        printf("BGE %d\n",decoder[R_R10]);
        regs[R_R14_PC] +=  decoder[R_R10] -1;
      }
      break;

    case BCC_BL:
      if (op1 < op2) {
        printf("BL %d\n",decoder[R_R10]);
        regs[R_R14_PC] +=  decoder[R_R10] - 1;
      }
      break;

    case BCC_BG:
      if (op1 > op2) {
        printf("BG %d\n",decoder[R_R10]);
        regs[R_R14_PC] +=  decoder[R_R10] - 1;
      }
      break;
  }
  if (verbose) {showRegs();}
  regs[R_R13_MAR] = regs[R_R14_PC];
  regs[R_R12_MDR] = memory[regs[R_R13_MAR]];
  regs[R_R14_PC]++;
  return regs[R_R12_MDR];
}
