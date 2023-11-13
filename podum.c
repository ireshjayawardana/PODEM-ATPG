#include "podum.h"

GATE_VAL backTrack(GATE *Node, GATE_VAL gate);

void podum(GATE *Node, GATE_VAL fault){
	printf("testing fault on gate -  %d \n", fault.Id);
	printf("fault stuck at -  %d \n", fault.Val);
	//printf("fault stuck at -  %s \n", Node[fault.Id].Type);
    printf("running podum..\n");
	backTrack(Node,fault);
}

GATE_VAL backTrack(GATE *Node, GATE_VAL gate){
 int num_inversion = 0;
 while (Node[gate.Id].Type != INPT){
	int i = 0;
	for (i = 0; i < Node[gate.Id].Nfi ; i++){
		//printf("Name of the id assigned - %d \n", gate.Id);
		if (Node[Node[gate.Id].Fin->Id].Val == XX){
			gate.Id = Node[gate.Id].Fin->Id;
			printf("Name of the id assigned - %d \n", gate.Id);
		}
	}
	

 }	
 printf("Name of the input - %s \n", Node[gate.Id].Name);
 printf("Value of the input - %d", Node[gate.Id].Val);
 return gate;
}

int inputX(GATE *Node, int Id){

	// LIST *listPtr;
	// switch(Node[Id].Type){
	// case FROM :
	// 			Node[i].Val = Node[Node[i].Fin->Id].Val;
	// 	break;
	// case BUFF :
	// 		Node[i].Val = Node[Node[i].Fin->Id ].Val;
	// 	break;
	// case NOT:
	// 		Node[i].Val = NOTLUT[Node[Node[i].Fin->Id ].Val];
	// 	break;
	// case AND :
	// 	listPtr = Node[i].Fin;
	// 	while(listPtr!=NULL){
  	// 		tempGateVal1 = Node[listPtr->Id].Val;
	// 		if (gateInPro == 0){
	// 			tempGateVal2 = tempGateVal1;
	// 			gateInPro = 1;
	// 		}
	// 		else if(gateInPro == 1) {
	// 			Node[i].Val = ANDLUT[tempGateVal1][tempGateVal2];				
	// 			gateInPro = 2;
	// 		}
	// 		else {
	// 			Node[i].Val = ANDLUT[tempGateVal1][Node[i].Val];
	// 		}
  	// 		listPtr=listPtr->Next; 
	// 		}
	// 		break;
}

int forwardImp(GATE *Node, int Id, int Val){

}
int xPathCheck(GATE *Node, int Id, int Val){

}

int objective(GATE *Node, int Id, int Val){
 
int nextObj[] = {Id, Val}; 
int dFront[] = {};


}