#ifndef HEADER_FILE
#define HEADER_FILE

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
/***************************************************************************************************
Constant Declarations 
***************************************************************************************************/
// VARIOUS CONSTANTS
#define Mfnam      20		// Max number of characters in the input/output file name
#define Mlin      500		// Max number of characters in a single line in the input file
#define Mnod    15000 		// Max number of gates in a circuit/netlist
#define Mnam       25		// Max number of characters in the node name
#define Mtyp       10		// Max number of nodes/gates type 
#define Min         9		// Max number of fanin of a gate
#define Mout       16		// Max number of fanout of a gate
#define Mpi       235		// Max number of total primary inputs in a circuit/netlist
#define Mpo       140		// Max number of total primary outputs in a circuit/netlist
#define Mpt       100		// Max number of lines(inputpatterns) in .vec file
#define Mft       31		// Max number of lines(stuck at faults) in .fau file
// GATE TYPE CONSTANTS 
#define INPT 1			// Primary Input
#define FROM 2			// STEM BRANCH
#define BUFF 3			// BUFFER 
#define NOT  4			// INVERTER
#define AND  5			// AND 
#define NAND 6			// NAND 
#define OR   7			// OR 
#define NOR  8			// NOR 
#define XOR  9			// XOR 
#define XNOR 10			// XNOR 

#define XX 2
#define D 3
#define DB 4

//#define PODUM               //run PODUM ATPG
#define PODEMALL
//#define ONLYLOGICSIM      //to run the logic simulation and write the results to the outpur .res file
//#define DEBUG             //print the debug logs
//int testInputPtr;
int Npi,Npo,Tgat,Nptr;  
/***************************************************************************************************************************
Structure Declarations 
****************************************************************************************************************************/
//1.Stucture declaration for LIST
typedef struct LIST_type {
   int  Id;		   //Id for current element		
   struct LIST_type *Next; //Pointer to next element (if there is no element,it will be NULL)		
} LIST;
//2.Stucture declaration for GATE
typedef struct GATE_type
{
  char *Name;                            //Name of the gate
  int Type,Nfi,Nfo,Mark,Val;             //Type, No of fanins, No of fanouts, Marker,Value
  LIST *Fin,*Fot;                        //Fanin members, Fanout members 
} GATE;
int *tstPrn[Mpt];
LIST *D_front;

/***************************************************************************************************************************
Functions in declared in input.c
****************************************************************************************************************************/
/***************************************************************************************************************************
LIST Structure Functions
****************************************************************************************************************************/
void InsertEle(LIST **,int);
void DeleteEle(LIST **,int);
int FindEle(LIST *,int );
void PrintList(LIST *);
int CountList(LIST *);

void FreeList(LIST **);
/***************************************************************************************************************************
 GATE Structure Functions
****************************************************************************************************************************/
void InitiGat(GATE *,int);
void PrintGats(GATE *,int);
void CountPri(GATE *,int,int *,int *);
void ClearGat(GATE *,int);

/***************************************************************************************************************************
Functions for reading .isc file
****************************************************************************************************************************/
int AssignType(char *);
int ReadIsc(FILE *,GATE *);
int ReadPtrn(FILE *Isc);
void logicSim(GATE *Node,int Tgat, int testPtrn[], FILE *Ptr);
void resolveGate (GATE *Node , int i , int *testInputPtr, int testPattern[], int setInputs);


FILE *Isc,*Pat,*Res;  
/***************************************************************************************************************************
User Defined Functions in user.c
****************************************************************************************************************************/
/****************************************************************************************************************************/
#endif