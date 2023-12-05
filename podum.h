/***************************************************************************************************
C Header Files
***************************************************************************************************/
#include <stdlib.h>           //standard library definitions
#include <stdio.h>            //standard buffered input/output 
#include <ctype.h>            //character types
#include <string.h>           //string operations 
#include <strings.h>          //string operations
#include <math.h>             //mathematical declarations
#include <time.h>             //time types 
#include <complex.h>          //complex arithmetic
#include <assert.h>           //verify program assertion
#include <limits.h>           //implementation-dependent constants 
#include "input.h"


//3.Structure to declaration for gate & value
typedef struct GATE_VAL_type
{
  int Id;
  int Val;
}GATE_VAL;

typedef enum PODUM_State_type
{
  sucess = 1,
  fail = 0,
  neutral = 2
}state;

void podum(GATE *Node, GATE_VAL gate);
void podemall(GATE *Node);