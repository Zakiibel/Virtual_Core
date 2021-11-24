/*!
\file fetch.c
\author BELMIR Zakaryae, YAZANE HASSAN
\version 1.0
\date 05/11/2021
\brief Virtual Core
*/

#include "functions.h"



/* Read instruction from binary file*/
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
