#include "input.h"
extern int Npi;
/*
***************************************************************************************************
 LookUp tables for the gates
***************************************************************************************************/
// ....................0 1 X D !D 
int ANDLUT [5][5] = { 	{0, 0, 0, 0, 0},
						{0, 1 , XX, D, DB},
						{0, XX, XX, XX, XX},
						{0, D, XX, D, 0},
						{0, DB, XX, 0 ,DB}
						};
						
int ORLUT [5][5] = {	{0, 1, XX, D, DB},
						{1, 1, 1, 1, 1},
						{XX, 1, XX, XX, XX},
						{D ,1, XX, D, 1},
						{DB, 1, XX ,1,DB}
						};
						
int NOTLUT [5] = { 1, 0 , XX , DB ,D };
/*
***************************************************************************************************
 Function to read the Test Pattern(.pattern files)
***************************************************************************************************/
int ReadPtrn(FILE *Ptr)
{
int len = 0;
char data[Mpi];
int i = 0;

for (i = 0 ;i < Mpt; i++){
	tstPrn[i]=(int *) malloc(Mpi * sizeof(int)); 
}

i = 0;
int j = 0;

while (fgets(data,sizeof(data),Ptr) != NULL){
	j=0;
	while (strcmp(&data[j],"\n")){
		tstPrn[i][j] = data[j] - '0';
		j++;
  if (j > Npi){
  break;
	}
}
	i++;
	if (i > 99) {
		break;				//to only read 100 patterns
	}
}
len = i;
// i = 0;
// for (i = 0; i < Mpi; i++){
//         free(tstPrn[i]);
// }

return len;
}
// end of readPattern
/***************************************************************************************************/


/*logic sim for a test pattern input
***************************************************************************************************/
void logicSim(GATE *Node,int Tgat, int testPtrn[], FILE *Ptr)
{
int i,j,k;
int testPattern[] = {1,1,1,1,0};
int currentInput = Npi;
//printf("current input\n, %d ",currentInput);
//
i=j=k=0;
int output [Npo];
for(i=0;i<=Tgat;i++){ 
  	if(Node[i].Type!=0){
		resolveGate(Node,i,&currentInput,testPtrn,1);
			if (Node[i].Nfo == 0){
      #ifdef DEBUG
				  printf("%d",Node[i].Val);
      #endif
        fprintf(Ptr, "%d",Node[i].Val);
			}
	}
}
#ifdef DEBUG
  printf("\n");
#endif
fprintf(Ptr, "\n");
return;
}



void resolveGate (GATE *Node , int i , int *testInputPtr, int testPattern[], int setInputs){
//int testPattern[] = {1,0,1,1,1};
int lenTstPtn = Npi;
int type = Node[i].Type;
int j,k = 0;
int tempGateVal1 = 0;
int tempGateVal2 = 0;
int gateInPro	= 0;
LIST *listPtr;
switch(type){
	case INPT :
		if (setInputs){
		Node[i].Val = testPattern[lenTstPtn - *testInputPtr];
		*testInputPtr = *testInputPtr - 1;
		}
		break;
	case FROM :
				Node[i].Val = Node[Node[i].Fin->Id].Val;
		break;
	case BUFF :
			Node[i].Val = Node[Node[i].Fin->Id ].Val;
		break;
	case NOT:
			Node[i].Val = NOTLUT[Node[Node[i].Fin->Id ].Val];
		break;
	case AND :
		listPtr = Node[i].Fin;
		while(listPtr!=NULL){
  			tempGateVal1 = Node[listPtr->Id].Val;
			if (gateInPro == 0){
				tempGateVal2 = tempGateVal1;
				gateInPro = 1;
			}
			else if(gateInPro == 1) {
				Node[i].Val = ANDLUT[tempGateVal1][tempGateVal2];				
				gateInPro = 2;
			}
			else {
				Node[i].Val = ANDLUT[tempGateVal1][Node[i].Val];
			}
  			listPtr=listPtr->Next; 
			}
			break;
	case OR :
		listPtr = Node[i].Fin;
		while(listPtr!=NULL){
  			tempGateVal1 = Node[listPtr->Id].Val;
			if (gateInPro == 0){
				tempGateVal2 = tempGateVal1;
				gateInPro = 1;
			}
			else if(gateInPro == 1) {
				Node[i].Val = ORLUT[tempGateVal1][tempGateVal2];
				gateInPro = 2;
			}
			else {
				Node[i].Val = ORLUT[tempGateVal1][Node[i].Val];
			}
  			listPtr=listPtr->Next; 
			}
			break;
	case NAND :
		listPtr = Node[i].Fin;
		while(listPtr!=NULL){
  			tempGateVal1 = Node[listPtr->Id].Val;
			if (gateInPro == 0){
				tempGateVal2 = tempGateVal1;
				gateInPro = 1;
			}
			else if(gateInPro == 1) {
				Node[i].Val = ANDLUT[tempGateVal1][tempGateVal2];
				gateInPro = 2;
			}
			else {
				Node[i].Val = ANDLUT[tempGateVal1][Node[i].Val];
			}
  			listPtr=listPtr->Next; 
			}
      Node[i].Val = NOTLUT[Node[i].Val];
			break;
	case NOR :
		listPtr = Node[i].Fin;
		while(listPtr!=NULL){
  			tempGateVal1 = Node[listPtr->Id].Val;
			if (gateInPro == 0){
				tempGateVal2 = tempGateVal1;
				gateInPro = 1;
			}
			else if(gateInPro == 1) {
				Node[i].Val = ORLUT[tempGateVal1][tempGateVal2];
				gateInPro = 2;
			}
			else {
				Node[i].Val = ORLUT[tempGateVal1][Node[i].Val];
			}
  			listPtr=listPtr->Next; 
			}
      Node[i].Val = NOTLUT[Node[i].Val];
			break;
	default :
		printf("ERROR");
		break;


}
}


