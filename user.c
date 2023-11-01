#include "input.h"
extern int Npi;
/*
***************************************************************************************************
 Function to read the Test Pattern(.pattern files)
***************************************************************************************************/
int ReadPtrn(FILE *Ptr)
{
int len = 0;
char data[Mpt];
int i = 0;

for (i = 0 ;i < Mpi; i++){
	tstPrn[i]=(int *) malloc(Mpi * sizeof(int)); 
}

//int tstPrn[100][100] = {};
i = 0;
int j = 0;
while (fgets(data,sizeof(data),Ptr) != NULL){
	j=0;
	while (strcmp(&data[j],"\n")){
		tstPrn[i][j] = data[j] - '0';
		j++;
	}
	i++;
}
len = i;

//i = 0;
//j = 0;
//for (i = 0; i<20; i++){
//	for (j = 0; j<5; j++){
//		printf("%d",tstPrn[i][j]);
//	}
//	printf(" \n");
//}
i = 0;
for (i = 0; i < Mpi; i++){
        free(tstPrn[i]);
}
//free(tstPrn);

//printf("%d",resolveGate(1,1));
return len;
}
// end of readPattern
/***************************************************************************************************/


/*resolve a gate
***************************************************************************************************/
void logicSim(GATE *Node,int Tgat, int testPtrn[])
{
int i,j,k;
int testPattern[] = {1,0,1,1,1};
int currentInput = Npi;
//printf("current input\n, %d ",currentInput);
//
i=j=k=0;

for(i=0;i<=Tgat;i++){ 
  if(Node[i].Type!=0){
	resolveGate(Node,i,&currentInput,testPattern);
  

}
    //if(Node[i].Nfi==0){      j++; }
    //if(Node[i].Nfo==0){      k++; } }}
//*Npi=j; *Npo=k;
}

return;
}

void resolveGate (GATE *Node , int i , int *testInputPtr, int testPattern[]){
//int testPattern[] = {1,0,1,1,1};
int lenTstPtn = Npi;
int type = Node[i].Type;
int j = 0;
switch(type){
	case INPT :
		Node[i].Val = testPattern[lenTstPtn - *testInputPtr];
		*testInputPtr = *testInputPtr - 1;
		break;
	case FROM :
		//PrintList(Node[i].Fin);
		Node[i].Val = Node[i].Fin->Id;
		for(j=0;j<=Tgat;j++){ 
  			if(Node[j].Type!=0){
				if (Node[i].Fin->Id == j){
					Node[i].Val = Node[j].Val;
				}
			}
		}
		break;
	case NAND :
		for (j = 1; j <= Node[i].Nfi
	default :
		printf("Error \n");


}
}



