#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include "WGraph.h"


int isNum(char *s){
	if(strspn(s, "0123456789")==strlen(s)){
		return 1;
	}
	else
		return 0;
}


int main(){
	int v,index,i,j;
	float out,pop[30][2],in;
	char a[20],b[20];
	//Edge e={1,2,100};
	Edge e;
	
	printf("Enter the number of vertices: ");
	scanf("%d",&v);
	Graph g=newGraph(v);
	while(1){
		printf("Enter an edge (from): ");
		scanf("%s",a);
		if (!isNum(a))
			break;
		printf("Enter an edge (to): ");
		scanf("%s",b);
		if (!isNum(b))
			break;
		e={atoi(a),atoi(b),1};
		insertEdge(g,e);	
	}
	printf("Done.\n");

//	showGraph(g);

	for(index=0;index<v;index++){
		out=0;
		in=0;
		for(j=0;j<v;j++){
			out+=adjacent(g,index,j);
	
		}
//		printf("%d :out= %d\n",index,out);
		for(i=0;i<v;i++){
			in+=adjacent(g,i,index);
	
		}
//		printf("%d :in= %d\n",index,in);
		out=(out==0)?0.5:out;
		pop[index][0]=index;
		pop[index][1]=in/out;
	} 
	
//	for(i=0;i<v;i++){
//		printf("%d",pop[i][1]);
//	}
	int max;
	float r[1][2];
	for(i=0;i<v;i++){
		for(j=i;j>0&&pop[j][1]>pop[j-1][1];j--){
			r[0][0]=pop[j][0];
			r[0][1]=pop[j][1];
			pop[j][0]=pop[j-1][0];
			pop[j][1]=pop[j-1][1];
			pop[j-1][0]=r[0][0];
			pop[j-1][1]=r[0][1];
		}	
//		printf("%d",index);
	}
	
	printf("Popularity ranking:\n");
	for(i=0;i<v;i++){
		if(i==v-1)
			printf("%d %.1f",(int)pop[i][0],pop[i][1]);
		else
			printf("%d %.1f\n",(int)pop[i][0],pop[i][1]);	
	}
	
	return 0;
}
