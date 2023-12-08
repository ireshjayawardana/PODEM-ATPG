#include "podum.h"
#include <time.h>
 
#define TIMEOUT_VALUE 0.2
//#define PRINTTOTERMINAL
#define PRINTTOFILE
extern int NOTLUT [5] ;
//					INPUT FROM BUFF NOT AND NAND OR NOR XOR XNOR
int NONCTRLLUT [10]= { 1, 1,1,1,0,1,0,1,1,1 };

extern FILE *Res;
FILE *Ptr;

int loopCount = 0;
int faultActivated = 0;
GATE_VAL backTrack(GATE *Node, GATE_VAL gate);
int invertingGate(int type);
state forwardImp(GATE *Node ,GATE_VAL fault, GATE_VAL PI);
void initalDontCare (GATE *Node);
state ForwardTraversal(GATE *Node,int Tgat, GATE_VAL fault, GATE_VAL PI);
void printPI(GATE *Node);
state podumRecursion(GATE *Node, GATE_VAL fault);
state faultAtPO(GATE *Node);
int isDfront(GATE *Node,int id);
GATE_VAL getObjective(GATE *Node, GATE_VAL gate);

//#define PDEBUG
time_t startTime ;

int masked = 0;
int timeout = 0;
double start_time;
/*iterates the podem algo throughout the circuit*/
void podemall(GATE *Node){
	Ptr = Res;
	int i = 0;
	for (i = 0; i < Tgat+1 ; i++){
		if (Node[i].Type != 0){
			GATE_VAL fault;
			fault.Id = i;
			fault.Val = 0;
			#ifdef PRINTTOTERMINAL
				printf("%d / 0 -> ", i );
			#endif
			#ifdef PRINTTOFILE
				fprintf(Ptr, "%d / 0 -> ", i);
			#endif
			podum(Node,fault);
			fault.Val = 1;
			#ifdef PRINTTOTERMINAL
				printf("%d / 1 -> ", i );
			#endif
			#ifdef PRINTTOFILE
				fprintf(Ptr, "%d / 1 -> ", i);
			#endif
			podum(Node,fault);
		}
	}
	float totFaults = 2 * Tgat;
	float cov = (((float)totFaults - ((float)masked + (float)timeout))/ (float)totFaults) * 100.0 ;
	
	printf("Coverage %.6f \n" , cov);
	fprintf(Ptr, "Coverage %.6f \n" , cov);
	float timeoutp = timeout;
	printf("Timeouts %f \n" , timeoutp);
	fprintf(Ptr, "Timeouts %f \n" , timeoutp);
	float faliuresp = masked;
	printf("Failures %f \n" , faliuresp);
	fprintf(Ptr, "Failures %f \n" , faliuresp);
}
/*Handles the fault injection to recursion and its final return states*/
void podum(GATE *Node, GATE_VAL fault){
	start_time = (double)clock()/CLOCKS_PER_SEC;
	#ifdef PDEBUG
		printf("testing fault on gate -  %d \n", fault.Id);
		printf("fault stuck at -  %d \n", fault.Val);
		printf("running podum..\n");
	#endif
	faultActivated = 0;
	fault.Val = NOTLUT[fault.Val]; 		//TO GO WITH SA CONVENTION
	initalDontCare(Node);
	FreeList(&D_front);
	#ifdef PDEBUG
		printf("init complete..\n");
	#endif
	state result = podumRecursion(Node,fault);
	if (result == sucess){
			#ifdef PRINTTOFILE
				fprintf(Ptr, "SUCCESS \n");
			#endif
			printPI(Node);

	}
	else if (result == fail){
		masked++;
			#ifdef PRINTTOFILE
				fprintf(Ptr, "FAILURE \n");
			#endif
			//exit(0);
		#ifdef PDEBUG
			printf("The fault at gate  -  %d \n", fault.Id);
			printf("fault stuck at -  %d \n",fault.Val);
			printf("is untestable..\n");
		#endif
	}
	else if (result == timeout_){
		#ifdef PDEBUG
			printf("timeout \n");
		#endif
		#ifdef PRINTTOFILE
			fprintf(Ptr, "TIMEOUT \n");
		#endif
		timeout++;
	}
	
}
/*print out GATE_VAL type as gate id and its value*/
void printGate(GATE_VAL gate){
		printf(" gate - %d \n", gate.Id);
		printf(" gate value- %d \n", gate.Val);
}
/*This is the podem resursion that will recursively activate the fault and propergate it*/
state podumRecursion(GATE *Node, GATE_VAL fault){

	double clock_end = (double)clock()/CLOCKS_PER_SEC;
	double duration = (double)(clock_end - start_time);
	state resultPodum;

	#ifdef PDEBUG
		printf("podum top \n");
	#endif
	if (duration > TIMEOUT_VALUE){
		return timeout_;
	}

	GATE_VAL gate = getObjective(Node,fault);
	#ifdef PDEBUG
		printGate(gate);
		printf("get objective \n");
	#endif
	if (gate.Id == 0){
		return fail;
	}
	GATE_VAL PIgate = backTrack(Node,gate);

	state stateLogic = forwardImp(Node ,fault,PIgate);		//as backtrace sets the value to PI
	
	#ifdef PDEBUG
		printf("logic sim - 1 \n");
	#endif
	if (stateLogic == sucess){
		return sucess;
	}
	if (stateLogic != fail){
		resultPodum = podumRecursion(Node,fault);
	}
	if (resultPodum == sucess){
		return sucess;
	}
	#ifdef PDEBUG
		printf("trying with inverted fault val \n");
	#endif
	PIgate.Val = NOTLUT[PIgate.Val];
	stateLogic = forwardImp(Node,fault,PIgate);
	#ifdef PDEBUG
		printf("logic sim - 2 \n");
	#endif
	if (stateLogic == sucess){
		return sucess;
	}
	else if (stateLogic != fail){
		resultPodum = podumRecursion(Node,fault);
	}
	if (resultPodum == sucess){
		return sucess;
	}
	PIgate.Val = XX;
	stateLogic = forwardImp(Node,fault,PIgate);
	#ifdef PDEBUG
		printf("logic sim - 3\n");
	#endif
	if (stateLogic == sucess){
		return sucess;;
	}
	else if (stateLogic == fail){
		return fail;
	}
return fail;
}
/*checks if the D or DB is at the primary outputs*/
state faultAtPO(GATE *Node){
	int i = 0;
	for(i=0;i<=Tgat;i++){ 
		if(Node[i].Nfo==0){
			if ((Node[i].Val == D) || (Node[i].Val == DB)){
				return sucess;
			} 
	}
	return neutral;
	}
	printf("\n");
}
/*printout the values of the primary inputs*/
void printPI(GATE *Node){
	int i = 0;
	for(i=0;i<=Tgat;i++){ 
		if(Node[i].Type==INPT){
			if (Node[i].Val == XX){
				#ifdef PRINTTOTERMINAL
					printf("X");
				#endif
			}
			else if (Node[i].Val == D){
				#ifdef PRINTTOTERMINAL
					printf("%d",1);
				#endif
			}
			else if (Node[i].Val == DB){
				#ifdef PRINTTOTERMINAL
					printf("%d",0);
				#endif
			}
			else{
				#ifdef PRINTTOTERMINAL
					printf("%d",Node[i].Val);
				#endif
			}
		}
	}
	#ifdef PRINTTOTERMINAL
		printf("\n");
	#endif
}
/*set all the gate values to XX*/
void initalDontCare (GATE *Node){
	int i = 0;
	for(i=0;i<=Tgat;i++){ 
  		if(Node[i].Type!=0){
			Node[i].Val = XX;
		}
	}
}
/*podem backtracking*/
GATE_VAL backTrack(GATE *Node, GATE_VAL gate){
 int num_inversion = invertingGate(Node[gate.Id].Type);	// to get it self's type
 while (Node[gate.Id].Type != INPT){
	//printf("print gate id %d %d %d %d %d \n", gate.Id , Node[gate.Id].Val, Node[gate.Id].Fin->Id ,Node[Node[gate.Id].Fin->Id].Val , Node[gate.Id].Type);
	//if ((gate.Id == 483) && (Node[gate.Id].Val == 1)) exit(0);
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
		//printf("point 2 \n");
		listPtr=listPtr->Next;
	}

 }	
 if (num_inversion % 2 != 0 ){
	gate.Val = NOTLUT[gate.Val];
 }
 else {
	gate.Val = gate.Val;					//get the value of the PI
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

state forwardImp(GATE *Node ,GATE_VAL fault, GATE_VAL PI){
	state state;
	state = ForwardTraversal(Node,Tgat,fault,PI);
	//printf("val - %d \n", Node[fault.Id].Val);
	return state;
}
int xPathCheck(GATE *Node, GATE_VAL gate){
	LIST *listPtr;
	listPtr = Node[gate.Id].Fot;
	while(listPtr!=NULL){
		printf("r");
	}
	listPtr=listPtr->Next;
}

GATE_VAL getObjective(GATE *Node, GATE_VAL gate){
 //fault not exsited
 if ((Node[gate.Id].Val != gate.Val ) && (faultActivated == 0)){
	faultActivated = 0; 		//only run once
	return gate;
	
 }
 //if the fault has already been activated
 else {
	//LIST *listPtr;
	//listPtr = D_front;
	
	int d = 0;
	int g = 0;
	int v = 0;
	while(D_front!=NULL){
		d = D_front->Id;
		LIST *listPtr2;
		listPtr2 = Node[d].Fin;
		while(listPtr2!=NULL){
			if (Node[listPtr2->Id].Val == XX){
				g = listPtr2->Id;	
				//printf("d front gate %d type %d \n", g , Node[g].Type);
	
				if ((Node[d].Type == INPT) || (Node[d].Type == FROM) || (Node[d].Type == BUFF)){
					v = gate.Val;
				}
				else if ((Node[d].Type == AND) || (Node[d].Type == NAND)){
					v = 1;
				}
				else if ((Node[d].Type == OR) || (Node[d].Type == NOR)){
					v = 0;
				}
				else if ((Node[d].Type == NOT) || (Node[d].Type == XOR) || (Node[d].Type == XNOR)){
					v = NOTLUT[gate.Val];
				}
				break;
			}
			listPtr2 = listPtr2->Next;
		}
		D_front = D_front->Next;
		if (g != 0){
			gate.Id = g;
			gate.Val = v;
			//DeleteEle(&D_front,g);	//delete the gate we took
			return gate;
			break;
		}

		//printGate(gate);
		return gate;
 		}
	
	}
}

/*tropological travesal
***************************************************************************************************/
state ForwardTraversal(GATE *Node,int Tgat, GATE_VAL fault, GATE_VAL PI)
{
//printf("logic sim \n");
Node[PI.Id].Val = PI.Val;
int i,j,k;
int testPattern[] = {0,0,0,0,0};
int currentInput = Npi;
//printf("current input\n, %d ",currentInput);
//
FreeList(&D_front);
i=j=k=0;
int output [Npo];
//set the PI
Node[PI.Id].Val = PI.Val;
for(i=0;i<=Tgat;i++){ 
  	if(Node[i].Type!=0){
		// printf(" i - %d \n", i);
		resolveGate(Node,i,&currentInput,testPattern, 0);
		if (i == fault.Id){
			#ifdef PDEBUG
				printf("at fault - %d\n",Node[i].Val);
			#endif
			if (Node[i].Val == fault.Val){
				if (fault.Val == 1){
					Node[i].Val = DB; //STUCK AT 1
					//printf("set val\n");
				}
				else{
					Node[i].Val = D; //STUCK AT 0
				}
				#ifdef PDEBUG
					printf("fault activated val - %d \n",Node[i].Val);
				#endif
				//printf("val - %d", Node[i].Val);
				faultActivated = 1; 
			}
			else if (Node[i].Val == NOTLUT[fault.Val]){
				#ifdef PDEBUG
					printf("fault masked \n");
				#endif
				faultActivated = 0;
				return fail;
			} 
			else if ((Node[i].Val == XX) ){
				#ifdef PDEBUG
					printf("fault masked \n");
				#endif
				faultActivated = 0;
				return neutral;
			}
		}

		if (isDfront(Node,i)){
			InsertEle(&D_front,i);
				// D_front->Id = i;
				//D_front = D_front->Next;
			}

		if (Node[i].Nfo == 0){
			if ((Node[i].Val == D)||(Node[i].Val == DB)){
				return sucess;
			}
		}
	}

}
if (((Node[fault.Id].Val == D) || (Node[fault.Id].Val == DB)) && (D_front==NULL)){
	#ifdef PDEBUG
		printf("d front empty \n");
	#endif
	//masked++;
	//exit(0);
	return fail;		//fault masked
}
return neutral;
#ifdef DEBUG
  printf("\n");
#endif
//fprintf(Ptr, "\n");

}
/*returns if a gate is suitable for a dfrontier*/
int isDfront(GATE *Node,int id){
		if (Node[id].Val !=  XX){
			return 0;
		}
		LIST *listPtr = Node[id].Fin;
		int D_front_detected = 0;
		int X_detected = 0;
		while(listPtr!=NULL){
			if ((Node[listPtr->Id].Val == D) || (Node[listPtr->Id].Val == DB)){
				D_front_detected = 1;
			}
			else if (Node[listPtr->Id].Val == XX){
				X_detected = 1;
			}
			listPtr=listPtr->Next; 
		}
		if ((D_front_detected) && (X_detected)){
			return 1;
		}
		else {
			return 0;
		}
}