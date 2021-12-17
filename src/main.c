/*!
\file main.c
\author BELMIR Zakaryae, YAZANE HASSAN
\version 1.0
\date 05/11/2021
\brief Virtual Core
*/



#include "functions.h"


int verbose;




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


/*Memoire de taille 64bits*/
uint64_t memory[MEMO_SIZE] ;

/*    Table des registres sur 64bits*/
uint64_t regs[R_COUNT];

/***************** MAIN ********************/
int main(int argc, char const *argv[])
{
  if ((argc != 4) || ((atoi(argv[3])!=1) && (atoi(argv[3])!=0)))
  {
    printf("invalid Number of args\n");
    printf("To run the program \n");
    printf("With verbose mode :  %s bin/code sources/regState 1\n",argv[0]);
    printf("Without verbose mode :  %s sources/code sources/regState 0\n",argv[0]);
    printf("code is the binary file containing instructions\n");
    printf("regState is the  file containing initial state of registers\n");
    exit(0);
  }
  verbose = atoi(argv[3]);
  init_regs(argv[2]);
  //showRegs();

  read_file(argv[1]);
  showMemory();

  run(verbose);
  return 0;
}
