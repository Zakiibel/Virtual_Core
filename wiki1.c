#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


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
unsigned prog[] = { 0x1064, 0x11C8, 0x2201, 0x0000 };

/***Registers****/
enum {
  r0 = 0,
  r1,
  r2,
  r3,
  R_COUNT
};
unsigned regs[R_COUNT];


/**********  instruction codes ***************
16-bits
1st digit instruction number
the last three for operands
12-15: instruction number
8-11: register number
0-7 : IV
*/
/** instruction number ***/
enum {
  halt = 0,
  loadi =1,
  add = 2
};

/**************** IMPLEMENTATION *******************
The first function will be run function
it does the following steps in a loop mode until the instruction Halt is called
Fetch : fetch the next instruction
Decode : decode the instruction into its constituent parts
Execute : execute the decode instruction
*/


/***FETCH****/
int pc = 0 ;// Program counter
int fetch()
{
  return prog[pc++];
}
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


/* display all registers as 4-digit hexadecimal words */
void showRegs()
{
  int i;
  printf( "regs = " );
  for( i=0; i<R_COUNT; i++ )
    printf( "%04X ", regs[ i ] );
  printf( "\n" );
}


/********* RUN  ********/
void run(int verbose)
{
  while (running)
  {
    if (verbose) {
      showRegs();
    }
    int instruction = fetch();
    decode(instruction);
    execute();
  }
}

/***************** MAIN ********************/
int main(int argc, char const *argv[])
{
  if (argc != 3) {
    printf("Number of args invalid\nTo run the program \nWith verbose mode :  %s code 1\nWithout verbose mode :  %s code 0\n",argv[0],argv[0]);
    printf("code is the binary file containing instructions\n");
    exit(0);
  }
  int verbose = atoi(argv[2]);
  run(verbose);
//  printf("%04X\n",prog[0] );
  return 0;
}
