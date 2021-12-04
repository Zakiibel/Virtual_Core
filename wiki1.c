#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>


#define TAILLE_MAX 40
#define MEMO_SIZE 512
#define MEMSIZ 4


/**************** INTRODUCTION *****************
A c PROGRAM to create a virtual cpu with the simplest architecture

WHY C :
It's a very simple language that allows the writing of concise programs.
It's a low level language with some high-level features. This makes it a good choice for creating a VM.

a set of 4 register r0-r3
a program script of commands
a excution unit to run the program
*/

/************** ADRESSING MODE ***************
registers : begin with r :            r0, r1, r2, r3
Immediat values IV  begin with # :    #20, #250
Memory addresses begin with @ :       @1505, @250
*/

/*Memoire de taille 64bits */
uint64_t memory[MEMO_SIZE] ;
//int memo_idx = 0;  //indice de memoire

/***Registers****/
/*enum {
  r0 = 0,
  r1,
  r2,
  r3,
  R_COUNT
};*/
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
uint64_t regs[R_COUNT];


/**********  instruction codes ***************

/* Instructoin Set 32bits */
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
/** instruction number
enum {
  halt = 0,
  loadi =1,
  add = 2
};*/
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



/**************** IMPLEMENTATION *******************
The first function will be run function
it does the following steps in a loop mode until the instruction Halt is called
Fetch : fetch the next instruction
Decode : decode the instruction into its constituent parts
Execute : execute the decode instruction
*/


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
/*****DECODE****/
//int instrNum = 0;
//operands
/* Initializing the registers */
//int reg1 = 0;
//int reg2 = 0;
//int reg3 = 0;
//int immv = 0;
int decode(int instr)
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
  regs[R_R4] = (instr & 0xF0000000) >> 28;   //BCC
  regs[R_R5] = (instr & 0x1000000) >> 24;    //FLAG
  regs[R_R6] = (instr & 0xF00000) >> 20;     //OPCODE
  regs[R_R7] = (instr & 0xF0000) >> 16;      //OPE1
  regs[R_R8] = (instr & 0xF000) >> 12;        //OPE2
  regs[R_R9] = (instr & 0xF00) >> 8;          //DEST
  regs[R_R10] = (instr & 0xFF);               //IV
}
/*****EXECUTE***/
int running = 1;
/* Evaluate the last decoded instruction */
int execute()
{
  switch (regs[R_R6])
  {
    case OP_HALT:
      /* Halt */
      printf("HALT\n");
      running = 0;
      break;
    case OP_MOV:
      if (regs[R_R5] == 0)
      {
        // MOV r1, r2  R1: dest  && r2:OPe1
        printf("MOV r%d, r%d\n",regs[R_R9],regs[R_R7] );
        regs[regs[R_R9]] = regs[regs[R_R7]];
      }
      else{
        // MOV r1, iv  re1:dest
        printf("MOV r%d, %d\n",regs[R_R9],regs[R_R10]);
        regs[regs[R_R9]] = regs[R_R10];
      }
      break;
    case OP_ADD:
      if (regs[R_R5] == 0)
      {
        // ADD r1, r2, r3  r1 = r2+r3
        printf("ADD r%d, r%d, r%d\n",regs[R_R9],regs[R_R7],regs[R_R8] );
        regs[regs[R_R9]] = regs[regs[R_R7]] + regs[regs[R_R8]];
      }
      else{
        // ADD r1, r2, iv   r1 = r2+iv
        printf("MOV r%d, r%d, %d\n",regs[R_R9],regs[R_R7],regs[R_R10]);
        regs[regs[R_R9]] = regs[regs[R_R7]] + regs[R_R10];
      }
      break;
  }
}
/* REad instruction from binary file*/
void read_file(char const * file)
{
  FILE* fcode = NULL;
  fcode = fopen(file, "r");
  char ligne[TAILLE_MAX] = "";
  if (fcode != NULL)
  {
    while (fgets(ligne, TAILLE_MAX, fcode) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
    {
      int b=1;
      for (int i = 0; i < strlen(ligne)-1; i++)
      {
        b=b<<1;
        if (ligne[i]=='1') {b++;}
      }
      memory[regs[R_R3]] =b & 0xffffffff;
      regs[R_R3]++;
    }
    fclose(fcode);
    regs[R_R3] = 0;
  }
  else
  {
    // On affiche un message d'erreur si on veut
    printf("Impossible d'ouvrir le fichier test.txt");
      exit(0);
  }
}

/* display all registers as 4-digit hexadecimal words */
void showRegs()
{
  int i;
  printf( "regs = " );
  for( i=0; i<R_COUNT; i++ )
    printf( "%08X ", regs[ i ] );
  printf( "\n" );
}
void showMemory()
{
  int i;
  printf( "Memory =\n" );
  for( i=0; i<MEMSIZ; i++ )  //nmbre de ligne dans le fichier code
    printf( "%016X\n", memory[ i ] );
}

/********* RUN  ********/
void run(int verbose)
{
  while (running)
  {
    if (verbose) {showRegs();}
    regs[R_R15_IR] = fetch();
    decode(regs[R_R15_IR]);
    execute();

  }
}

/***************** MAIN ********************/
int main(int argc, char const *argv[])
{
  if ((argc != 3) || ((atoi(argv[2])!=1) && (atoi(argv[2])!=0)))
  {
    printf("Number of args invalid\nTo run the program \nWith verbose mode :  %s code 1\nWithout verbose mode :  %s code 0\n",argv[0],argv[0]);
    printf("code is the binary file containing instructions\n");
    exit(0);
  }
  int verbose = atoi(argv[2]);
  //showRegs();
  //printf("************************************\n");
  read_file(argv[1]);
  showMemory();
  printf("************************************\n");
  run(verbose);
  return 0;
}
