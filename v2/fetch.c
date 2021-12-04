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
  regs[R_R13_MAR] = regs[R_R14_PC];
  regs[R_R12_MDR] = memory[regs[R_R13_MAR]];
  /*switch (1) { //BCC
    case 1:
      regs[R_R14_PC]++;
      break;
  }*/
  regs[R_R14_PC]++;
  return regs[R_R12_MDR];
}
