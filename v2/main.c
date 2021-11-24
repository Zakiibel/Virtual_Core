/*!
\file main.c
\author BELMIR Zakaryae, YAZANE HASSAN
\version 1.0
\date 05/11/2021
\brief Virtual Core
*/



#include "functions.h"
#include "fetch.h"
#include "decode.h"
#include "execute.h"




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
