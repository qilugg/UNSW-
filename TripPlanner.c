#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

struct Schedule{
	char time[5];
	int num_bus;
	int node_from;
};

struct Node{
	char node_name[32];
	int num_array;
	struct Schedule bus_schedule[20];
};

struct info{
	char time[5];
	int num;  // bus
	int order; // node
};

struct record{
	int node_num;
	int bus_num;
};


static int matrix[30][30];
static struct Node node[30];
static struct info node_stack[30];
int stack_top=-1;
static struct record record_[30];
int record_top=-1;
static struct info res[30];
int res_top=-1;


int string_int(char *name){
	int i;
	for( i=0;i<30;i++){
		if (!strcmp(node[i].node_name,name)){
			break;
		}		
	}
	return i;
}

struct info deepcopy(struct info node){
	struct info node_copy;
	strcpy(node_copy.time,node.time);
	node_copy.order=node.order;
	node_copy.num=node.num;
	return node_copy;
}
// compare time
int cmpTime(char *s1, char *s2){
	return atoi(s1)-atoi(s2)<=0;
}

//justify if the nth bus can go to num2 from num1 
int judge(int num1,int num,int num2){
	int i ,size=node[num2].num_array;
	for (i=0;i<size;i++){
		if (num==node[num2].bus_schedule[i].num_bus){
			if(node[num2].bus_schedule[i].node_from==num1){
				return 1;
			}
		}
			
	}
	
	return 0;
}

int num_index(int now,int num){
	int i;
	for(i=0;i<node[now].num_array;i++){
		if (num==node[now].bus_schedule[i].num_bus){
			return i;
		}				
	}
	
}
//judge if it is on record
int judge_record(int order,int num){
	int i;
	for (i=0;i<=record_top;i++){
		if (order==record_[i].node_num && num==record_[i].bus_num){
			
			return 1;
		}
				
	}

	return 0;
	
}

int transfer(int order){
	int i;
	for(i=0;i<node[order].num_array;i++){
	
		if (judge_record(order,node[order].bus_schedule[i].num_bus)==0){
			

	
				return node[order].bus_schedule[i].num_bus;			

	
		}
	}
	return -1;
}

						// num: number of bus
void DFS(int now,int des,int num,char *time,int numStop,int origin){
	
	if(cmpTime(node[now].bus_schedule[num_index(now,num)].time,time)){

		struct info stack_new;
		int index;
		stack_new.num=num;
		stack_new.order=now;
		strcpy(stack_new.time,node[now].bus_schedule[num_index(now,num)].time);
		node_stack[++stack_top]=deepcopy(stack_new);
		// push record
		record_[++record_top].bus_num=num;
		record_[record_top].node_num=now;
				
		//judge if arrive at destination
		if (now==des){
			
			if (res_top==-1){
				// copy path from stack to res 
				for( index=0;index<=stack_top;index++){
					res[index].num=node_stack[index].num;
					res[index].order=node_stack[index].order;
					strcpy(res[index].time,node_stack[index].time);	
				}
				res_top=stack_top;
//				stack_top--;
			}
			
			// update the path
			else{
				// leave later is better
				if(!cmpTime(node_stack[0].time,res[0].time)){
						for( index=0;index<=stack_top;index++){
							res[index].num=node_stack[index].num;
							res[index].order=node_stack[index].order;
							strcpy(res[index].time,node_stack[index].time);	
						}
						res_top=stack_top;
//						stack_top--;
				}
				else{
					// arrive earlier is better
					if (atoi(node_stack[0].time)==atoi(res[0].time) && cmpTime(node_stack[stack_top].time,res[res_top].time) ){
						for( index=0;index<=stack_top;index++){
							res[index].num=node_stack[index].num;
							res[index].order=node_stack[index].order;
							strcpy(res[index].time,node_stack[index].time);	
						}
						res_top=stack_top;
//						stack_top--;
					}		
				}
//				stack_top--;	
			}
			int order_before=node_stack[stack_top-1].order,num_before=node_stack[stack_top-1].num;
			stack_top-=2;
			DFS(order_before,des,num_before,time,numStop,origin);
		}
		// not arrive at destination
		else{
			//judge if DFS 
			now=node_stack[stack_top].order;
			num=node_stack[stack_top].num;
			for(int j=0;j<numStop;j++)
			{
				
				if(matrix[now][j]==1&&judge(now,num,j)&&(!judge_record(j,num)))
				{
					DFS(j,des,num,time,numStop,origin);
				}
			}
			//transfer bus
			
			if(origin!=now&&transfer(now)!=-1 ){
				int new_num=transfer(now);
				//pull stack
				while(1){
					if(node_stack[stack_top].num==node_stack[stack_top-1].num){
						break;	
					}
					else{
						stack_top--;	
					}
				}
//
				DFS(now,des,new_num,time,numStop,origin);
			}
			
			//pull stack
			else{
				
				if (stack_top<=0){	//end search
					
					return;
				} 	
				else{
					int _order_before=node_stack[stack_top-1].order,_num_before=node_stack[stack_top-1].num;
					stack_top-=2;
			
				
					DFS(_order_before,des,_num_before,time,numStop,origin);	
				}
			}
			
		}
		
	}
	
	//time is illegal
	else{
		record_[++record_top].bus_num=num;
		record_[record_top].node_num=now;
		
		int __order_before=node_stack[stack_top].order,__num_before=node_stack[stack_top].num;
		stack_top-=1;
		DFS(__order_before,des,__num_before,time,numStop,origin);
	}
	
}

void travel(char *from, char *to, char *time,int numStop){
	int i,num_node,des;
	des=string_int(to);
	num_node=string_int(from);


	for(i=0;i<node[num_node].num_array;i++){
		if(cmpTime(node[num_node].bus_schedule[i].time,time)){

	
			stack_top=-1;
			record_top=-1;
			DFS(num_node,des,node[num_node].bus_schedule[i].num_bus,time,numStop,num_node);
		
			
		}
		else{
			continue;
		}
		
	}
	
	

	if (res_top==-1){
		printf("No connection found.\n");
	}
	else{
		

		for(int j=0;j<=res_top;j++){
			if (j<res_top&&res[j].num!=res[j+1].num){
				printf("%s %s Change at %s\n",res[j].time,node[res[j].order].node_name,node[res[j].order].node_name);
			}
			else{
				printf("%s %s\n",res[j].time,node[res[j].order].node_name);
			}
		}
		
	}
	
	printf("\n");
}

int main(){	
	int i,j,numStop,numBus,numSingleStop,val,lastVal=-1;
	char nameStop[32],s1[5],s2[32],s3[32];
	
	printf("Enter the number of bus stops: ");
	scanf("%d",&numStop);
	for (i=0;i<numStop;i++){
		scanf("%s",nameStop);
		// node[i] record the information of stop 
		strcpy(node[i].node_name,nameStop);
		node[i].num_array=0;
	}
	
	printf("Enter the number of busses: ");
	scanf("%d",&numBus);
	for (i=0;i<numBus;i++){
		printf("Enter the number of stops: ");
		scanf("%d",&numSingleStop);
		lastVal=-1;
		for (j=0;j<numSingleStop;j++){
			scanf("%s",s1);
			scanf("%s",s2);
			//change node 
			val=string_int(s2);
			strcpy(node[val].bus_schedule[node[val].num_array].time,s1);
			node[val].bus_schedule[node[val].num_array].num_bus=i;
			
			//change Adjacency Matrix
			if (lastVal==-1){
				lastVal=val;
				// original node
				node[val].bus_schedule[node[val].num_array].node_from=-1;
			}
			else{
				node[val].bus_schedule[node[val].num_array].node_from=lastVal;
				matrix[lastVal][val]=1;
				lastVal=val;	
				
			}
			node[val].num_array++;
		}
	}
	printf("\n");	
	
                   	//inout and output
	while(1){
		printf("From: ");
		scanf("%s",s2);
		if (!strcmp(s2,"done")){
			printf("Thank you for using TripPlanner");
			break;
		}
		printf("To: ");
		scanf("%s",s3);
		printf("Arrive by ");
		scanf("%s",s1);
		printf("\n");
		res_top=-1;
		travel(s2,s3,s1,numStop);
	
	}
		
		
	
	return 0;
}
