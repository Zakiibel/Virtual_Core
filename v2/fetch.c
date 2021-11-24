/*!
\file fetch.c
\author BELMIR Zakaryae, YAZANE HASSAN
\version 1.0
\date 05/11/2021
\brief Virtual Core
*/

#include "fetch.h"


/***FETCH****/
int pc = 0 ;// Program counter
int fetch()
{
  return memory[pc++];
}
