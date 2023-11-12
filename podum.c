#include "podum.h"
#include "input.h"

void podum(){
    printf("running podum..\n");
}



GATE_VAL backTrack(GATE *Node, GATE_VAL gate){
 int i = gate.Id;
 int num_inversion = 0;
 while (Node[i].Type != INPT){
	printf("");
 }	
 for (i = gate.Id ; i > 0 ; i--){
	if(Node[i].Type!=0){
		int type = Node[i].Type;
		switch(type){
			case INPT :
				return gate;
			default :
				printf("ERROR"); 
	}
 }
}
}

int forwardImp(GATE *Node, int Id, int Val){

}
int xPathCheck(GATE *Node, int Id, int Val){

}

int objective(GATE *Node, int Id, int Val){
 
int nextObj[] = {Id, Val}; 
int dFront[] = {};


}