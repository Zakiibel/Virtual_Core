/*!
\file execute.c
\author BELMIR Zakaryae, YAZANE HASSAN
\version 1.0
\date 05/11/2021
\brief Virtual Core
*/

#include "functions.h"
#include "execute.h"

uint64_t op1; //used for CMP
uint64_t op2; //used for CMP

/*****EXECUTE***/
//int running = 1;
/* Evaluate the last decoded instruction */
int execute()
{
  switch (decoder[R_R6])
  {
    case OP_AND:
      if (decoder[R_R5] == 0)
      {
        // AND r1, r2, r3  r1 = r2 & r3
        printf("AND r%d, r%d, r%d\n",decoder[R_R9],decoder[R_R7],decoder[R_R8] );
        regs[decoder[R_R9]] = regs[decoder[R_R7]] & regs[decoder[R_R8]];
      }
      else{
        // AND r1, r2, iv   r1 = r2&iv
        printf("AND r%d, r%d, %d\n",decoder[R_R9],decoder[R_R7],decoder[R_R10]);
        regs[decoder[R_R9]] = regs[decoder[R_R7]] & decoder[R_R10];
      }
      break;

    case OP_ORR:
      if (decoder[R_R5] == 0)
      {
        // ORR r1, r2, r3  r1 = r2 | r3
        printf("ORR r%d, r%d, r%d\n",decoder[R_R9],decoder[R_R7],decoder[R_R8] );
        regs[decoder[R_R9]] = regs[decoder[R_R7]] | regs[decoder[R_R8]];
      }
      else{
        // ORR r1, r2, iv   r1 = r2 | iv
        printf("ORR r%d, r%d, %d\n",decoder[R_R9],decoder[R_R7],decoder[R_R10]);
        regs[decoder[R_R9]] = regs[decoder[R_R7]] | decoder[R_R10];
      }
      break;

    case OP_EOR:
      if (decoder[R_R5] == 0)
      {
        // EOR r1, r2, r3  r1 = r2 ^ r3
        printf("EOR r%d, r%d, r%d\n",decoder[R_R9],decoder[R_R7],decoder[R_R8] );
        regs[decoder[R_R9]] = regs[decoder[R_R7]] ^ regs[decoder[R_R8]];
      }
      else{
        // EOR r1, r2, iv   r1 = r2 ^ iv
        printf("ORR r%d, r%d, %d\n",decoder[R_R9],decoder[R_R7],decoder[R_R10]);
        regs[decoder[R_R9]] = regs[decoder[R_R7]] ^ decoder[R_R10];
      }
      break;

    case OP_ADD:
      if (decoder[R_R5] == 0)
      {
        // ADD r1, r2, r3  r1 = r2+r3
        printf("ADD r%d, r%d, r%d\n",decoder[R_R9],decoder[R_R7],decoder[R_R8] );
        regs[decoder[R_R9]] = regs[decoder[R_R7]] + regs[decoder[R_R8]];
      }
      else{
        // ADD r1, r2, iv   r1 = r2+iv
        printf("ADD r%d, r%d, %d\n",decoder[R_R9],decoder[R_R7],decoder[R_R10]);
        regs[decoder[R_R9]] = regs[decoder[R_R7]] + decoder[R_R10];
      }
      break;

    case OP_ADC:
      /*if (decoder[R_R5] == 0)
      {
        // ADC r1, r2, r3  r1 = r2+r3+carry
        printf("ADC r%d, r%d, r%d\n",decoder[R_R9],decoder[R_R7],decoder[R_R8] );
        regs[decoder[R_R9]] = regs[decoder[R_R7]] + regs[decoder[R_R8]] + carry;
      }
      else{
        // ADC r1, r2, iv   r1 = r2+iv+carry
        printf("ADC r%d, r%d, %d\n",decoder[R_R9],decoder[R_R7],decoder[R_R10]);
        regs[decoder[R_R9]] = regs[decoder[R_R7]] + decoder[R_R10] + carry;
      }*/
      break;

    case OP_CMP:
      if (decoder[R_R5]==0) {
        printf("CMP r%d, %d\n",decoder[R_R7],decoder[R_R8]);
        op1 = regs[decoder[R_R7]];
        op2 = regs[decoder[R_R8]];
        decode(fetch());
      }
      else {
        printf("CMP r%d, %d\n",decoder[R_R7],decoder[R_R10]);
        op1 = regs[decoder[R_R7]];
        op2 = decoder[R_R10];
        decode(fetch());
      }
      break;

    case OP_SUB:
      if (decoder[R_R5] == 0)
      {
        // SUB r1, r2, r3  r1 = r2 - r3
        printf("SUB r%d, r%d, r%d\n",decoder[R_R9],decoder[R_R7],decoder[R_R8] );
        regs[decoder[R_R9]] = regs[decoder[R_R7]] - regs[decoder[R_R8]];
      }
      else{
        // SUB r1, r2, iv   r1 = r2 - iv
        printf("SUB r%d, r%d, %d\n",decoder[R_R9],decoder[R_R7],decoder[R_R10]);
        regs[decoder[R_R9]] = regs[decoder[R_R7]] - decoder[R_R10];
      }
      break;

    case OP_SBC:
      /*if (decoder[R_R5] == 0)
      {
        // SBC r1, r2, r3  r1 = r2 - r3 + carry -1
        printf("SBC r%d, r%d, r%d\n",decoder[R_R9],decoder[R_R7],decoder[R_R8] );
        regs[decoder[R_R9]] = regs[decoder[R_R7]] - regs[decoder[R_R8]] + carry -1;
      }
      else{
        // SBC r1, r2, iv   r1 = r2 - iv +carry -1
        printf("SBC r%d, r%d, %d\n",decoder[R_R9],decoder[R_R7],decoder[R_R10]);
        regs[decoder[R_R9]] = regs[decoder[R_R7]] - decoder[R_R10] +carry -1;
      }*/
      break;

    case OP_MOV:
      if (decoder[R_R5] == 0)
      {
        // MOV r1, r2  R1: dest  && r2:OPe1
        printf("MOV r%d, r%d\n",decoder[R_R9],decoder[R_R7] );
        regs[decoder[R_R9]] = regs[decoder[R_R7]];
      }
      else{
        // MOV r1, iv  re1:dest
        printf("MOV r%d, %d\n",decoder[R_R9],decoder[R_R10]);
        regs[decoder[R_R9]] = decoder[R_R10];
      }
      break;

    case OP_LSH:
      if (decoder[R_R5] == 0)
      {
        // LSH r1, r2, r3  r1 = r2 << r3
        printf("LSH r%d, r%d, r%d\n",decoder[R_R9],decoder[R_R7],decoder[R_R8] );
        regs[decoder[R_R9]] = regs[decoder[R_R7]] << regs[decoder[R_R8]];
      }
      else{
        // LSH r1, r2, iv   r1 = r2 << iv
        printf("LSH r%d, r%d, %d\n",decoder[R_R9],decoder[R_R7],decoder[R_R10]);
        regs[decoder[R_R9]] = regs[decoder[R_R7]] << decoder[R_R10];
      }
      break;

    case OP_RSH:
      if (decoder[R_R5] == 0)
      {
        // RSH r1, r2, r3  r1 = r2 >> r3
        printf("RSH r%d, r%d, r%d\n",decoder[R_R9],decoder[R_R7],decoder[R_R8] );
        regs[decoder[R_R9]] = regs[decoder[R_R7]] >> regs[decoder[R_R8]];
      }
      else{
        // RSH r1, r2, iv   r1 = r2 >> iv
        printf("RSH r%d, r%d, %d\n",decoder[R_R9],decoder[R_R7],decoder[R_R10]);
        regs[decoder[R_R9]] = regs[decoder[R_R7]] >> decoder[R_R10];
      }
      break;

    case OP_HALT:
      /* Halt */
      printf("HALT\n");
      //running = 0;
      break;

  }
  return 0;
}
