/*!
\file execute.c
\author BELMIR Zakaryae, YAZANE HASSAN
\version 1.0
\date 05/11/2021
\brief Virtual Core
*/

#include "execute.h"



/*****EXECUTE***/
int running = 1;
/* Evaluate the last decoded instruction */
int execute()
{
  switch (instrNum)
  {
    case halt:
      /* Halt */
      printf("halt\n");
      running = 0;
      break;
    case loadi:
      /* Loadi */
      printf("loadi r%d #%d\n",reg1,immv);
      regs[reg1] = immv;
      break;
    case add:
      /* Add */
      printf("add r%d r%d r%d\n",reg1,reg2,reg3 );
      regs[reg1] = regs[reg2] + regs[reg3];
      break;
  }
}
