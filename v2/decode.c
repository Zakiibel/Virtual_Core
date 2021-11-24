/*!
\file decode.C
\author BELMIR Zakaryae, YAZANE HASSAN
\version 1.0
\date 05/11/2021
\brief Virtual Core
*/

#include "decode.h"



/*****DECODE****/
int instrNum = 0;
//operands
/* Initializing the registers */
int reg1 = 0;
int reg2 = 0;
int reg3 = 0;
int immv = 0;
int decode(int instr)
{
  instrNum = (instr & 0xF000) >> 12;
  reg1 = (instr & 0xF00) >> 8;
  reg2 = (instr & 0xF0) >> 4;
  reg3 = (instr & 0xF);
  immv = (instr & 0xFF);
}
