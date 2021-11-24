#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>


#define TAILLE_MAX 40
#define MEMO_SIZE 256

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
int memo_idx = 0;  //indice de memoire

/***Registers****/
enum {
  r0 = 0,
  r1,
  r2,
  r3,
  R_COUNT
};
/*    Table des registres sur 64bits */
uint64_t regs[R_COUNT];


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
  return memory[pc++];
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
      memory[memo_idx] =b & 0xffff;
      memo_idx++;
    }
    fclose(fcode);
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
  if ((argc != 3) || ((atoi(argv[2])!=1) && (atoi(argv[2])!=0)))
  {
    printf("Number of args invalid\nTo run the program \nWith verbose mode :  %s code 1\nWithout verbose mode :  %s code 0\n",argv[0],argv[0]);
    printf("code is the binary file containing instructions\n");
    exit(0);
  }
  int verbose = atoi(argv[2]);
  read_file(argv[1]);
  run(verbose);
  return 0;
}
