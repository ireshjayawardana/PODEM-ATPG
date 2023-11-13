#include "podum.h"

extern int NOTLUT [5] ;

GATE_VAL backTrack(GATE *Node, GATE_VAL gate);
int invertingGate(int type);

void podum(GATE *Node, GATE_VAL fault){
	printf("testing fault on gate -  %d \n", fault.Id);
	printf("fault stuck at -  %d \n", fault.Val);
    printf("running podum..\n");
	backTrack(Node,fault);
}

GATE_VAL backTrack(GATE *Node, GATE_VAL gate){
 int num_inversion = invertingGate(Node[gate.Id].Type);	// to get it self's type
 while (Node[gate.Id].Type != INPT){
	LIST *listPtr;
	listPtr = Node[gate.Id].Fin;;
	while(listPtr!=NULL){
		if ((Node[listPtr->Id].Val == 6) | (Node[listPtr->Id].Val == XX)){ 	// uninitialized or don t care
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
	Node[gate.Id].Val = gate.Val;
 }
#ifdef DEBUG
 	printf("Name of the input - %s \n", Node[gate.Id].Name);
 	printf("Value of the input - %d \n", Node[gate.Id].Val);
#endif
return gate;

}

int invertingGate(int type){	// 0 if non inveting else 1
	if ((type == NAND) | (type == NOR)){
		return 1;
	}
	else
		return 0;
}

int forwardImp(GATE *Node, int Id, int Val){

}
int xPathCheck(GATE *Node, int Id, int Val){

}

int objective(GATE *Node, int Id, int Val){
 
int nextObj[] = {Id, Val}; 
int dFront[] = {};


}