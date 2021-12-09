/*!
\file fetch.c
\author BELMIR Zakaryae, YAZANE HASSAN
\version 1.0
\date 05/11/2021
\brief Virtual Core
*/

#include "functions.h"
#include "fetch.h"
#include "decode.h"
#include "execute.h"

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
      uint64_t b=1;
      for (int i = 0; i < strlen(ligne)-1; i++)
      {
        b=b<<1;
        if (ligne[i]=='1') {b++;}
      }
      memory[decoder[R_R3]] =b & 0xffffffff;
      //printf("%016lx\n",b&0xffffffff );
      decoder[R_R3]++;
    }
    fclose(fcode);
    decoder[R_R3] = 0;
  }
  else
  {
    // On affiche un message d'erreur si on veut
    printf("Impossible d'ouvrir le fichier memory");
      exit(0);
  }
}


/* Read instruction from binary file*/
void init_regs(char const * file)
{
  int j=0;
  FILE* fregState = NULL;
  fregState = fopen(file, "r");
  char ligne[TAILLE_MAX] = "";
  if (fregState != NULL)
  {
    while (fgets(ligne, TAILLE_MAX, fregState) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
    {
      uint64_t a= 1;
      for (int i = 5; i < strlen(ligne)-1; i++)
      {
        a=a<<4;
        //printf("%016X\n",a);
        switch (ligne[i]) {
          case 49: a++;  break;
          case 50: a+=2; break;
          case 51: a+=3; break;
          case 52: a+=4; break;
          case 53: a+=5; break;
          case 54: a+=6; break;
          case 55: a+=7; break;
          case 56: a+=8; break;
          case 57: a+=9; break;
          case 97: a+=10;break;
          case 98: a+=11;break;
          case 99: a+=12;break;
          case 100:a+=13;break;
          case 101:a+=14;break;
          case 102:a+=15;break;
        }
      }
      regs[j] = a & 0xffffffffffffffff;
      j++;
    }
    fclose(fregState);
  }
  else
  {
    // On affiche un message d'erreur si on veut
    printf("Registers File can not be opened");
      exit(0);
  }
}



/* display all registers as 4-digit hexadecimal words */
void showRegs()
{
  int i;
  printf("***** Registers *******\n");
  for( i=0; i<R_COUNT; i++ )
    printf( "R%d = 0x%016lX\n",i, regs[ i ] );
}

/* display memory as 16-digit in hexadecimal */
void showMemory()
{
  int i;
  printf( "******** Memory ********\n" );
  for( i=0; i<MEMSIZ; i++ )  //nmbre de ligne dans le fichier code
    printf( "0x%016lX\n", memory[ i ] );
}



/********* RUN  ********/
void run(int verbose)
{
  while (decoder[R_R6] != 11)
  {
    if (verbose) {showRegs();}
    regs[R_R15_IR] = fetch();
    decode(regs[R_R15_IR]);
    execute();

  }
}
