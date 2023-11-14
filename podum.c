#include "podum.h"

extern int NOTLUT [5] ;

GATE_VAL backTrack(GATE *Node, GATE_VAL gate);
int invertingGate(int type);
void forwardImp(GATE *Node ,GATE_VAL fault);
void initalDontCare (GATE *Node);
void ForwardTraversal(GATE *Node,int Tgat, GATE_VAL fault);

void podum(GATE *Node, GATE_VAL fault){
	printf("testing fault on gate -  %d \n", fault.Id);
	printf("fault stuck at -  %d \n", NOTLUT[fault.Val]);
    printf("running podum..\n");

	initalDontCare(Node);

	//check sucess , faulire and neutral
	GATE_VAL gate;
	gate = backTrack(Node,fault);
	forwardImp(Node,fault);
}

void initalDontCare (GATE *Node){
	int i = 0;
	for(i=0;i<=Tgat;i++){ 
  		if(Node[i].Type!=0){
			Node[i].Val = XX;
		}
	}
}
GATE_VAL backTrack(GATE *Node, GATE_VAL gate){
 int num_inversion = invertingGate(Node[gate.Id].Type);	// to get it self's type
 while (Node[gate.Id].Type != INPT){
	LIST *listPtr;
	listPtr = Node[gate.Id].Fin;
	while(listPtr!=NULL){
		if ((Node[listPtr->Id].Val == 6) || (Node[listPtr->Id].Val == XX)){ 	// uninitialized or don t care
			gate.Id = listPtr->Id;
			#ifdef DEBUG
				printf("Name of the id assigned - %d \n", gate.Id);
			#endif
			if (invertingGate(Node[gate.Id].Type)){
				num_inversion++;
			}
			break;
		}
		listPtr=listPtr->Next;
	}

 }	
 if (num_inversion % 2 != 0 ){
	Node[gate.Id].Val = NOTLUT[gate.Val];
 }
 else {
	Node[gate.Id].Val = gate.Val;					//assign the value to the PI
 }
#ifdef DEBUG
 	printf("Name of the input - %s \n", Node[gate.Id].Name);
 	printf("Value of the input - %d \n", Node[gate.Id].Val);
#endif
return gate;

}
/*
returns and int depending on the gate type
*/
int invertingGate(int type){	// 0 if non inveting else 1
	if ((type == NAND) || (type == NOR) || type == NOT){
		return 1;
	}
	else
		return 0;
}

void forwardImp(GATE *Node ,GATE_VAL fault){

	ForwardTraversal(Node,Tgat,fault);
	printf("val - %d", Node[fault.Id].Val);
}
int xPathCheck(GATE *Node, GATE_VAL gate){
	LIST *listPtr;
	listPtr = Node[gate.Id].Fot;
	while(listPtr!=NULL){
		printf("r");
	}
	listPtr=listPtr->Next;
}

int objective(GATE *Node, GATE_VAL gate){
 
//int nextObj[] = {Id, Val}; 
//int dFront[] = {};


}


/*tropological travesal
***************************************************************************************************/
void ForwardTraversal(GATE *Node,int Tgat, GATE_VAL fault)
{

	
int *Dfront;
Dfront = (int*)malloc(100* sizeof(int)); //see the size for dfront

int i,j,k;
int testPattern[] = {0,0,0,0,0};
int currentInput = Npi;
//printf("current input\n, %d ",currentInput);
//
i=j=k=0;
int output [Npo];
for(i=0;i<=Tgat;i++){ 
  	if(Node[i].Type!=0){
		if (i == fault.Id){
				//activate the fault
			if (fault.Val){
				Node[fault.Id].Val = DB; //STUCK AT 1
				printf("val - %d", Node[fault.Id].Val);
			}
			else {
				Node[fault.Id].Val = D; //STUCK AT 0
				printf("sa0");
			}
		}
		else {
			resolveGate(Node,i,&currentInput,testPattern, 0);
		}
		//get d front
		if ((Node[i].Val == D) || (Node[i].Val == DB)){
			Dfront[j] = i;
			j++;
		}

		
		if (Node[i].Nfo == 0){
				//check fault propergated to output
				//update podum state success
      #ifdef DEBUG
				  printf("%d",Node[i].Val);
      #endif
       // fprintf(Ptr, "%d",Node[i].Val);
			}
	}
	free(Dfront);
}
#ifdef DEBUG
  printf("\n");
#endif
//fprintf(Ptr, "\n");
return;
}