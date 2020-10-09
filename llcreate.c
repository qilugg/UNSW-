#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	int value;
	struct node *next; 
}node;

node* initList(){
	node *s=(node*)malloc(sizeof(node));
 	s->value=100;
	s->next=NULL;
	return s;
}

void insert(node *c,int data){
	node *s,*r;
	r=c; 
	s=(node*)malloc(sizeof(node));
	s->value=data;
	s->next=NULL;
	while(r->next!=NULL){
		r=r->next;
	}
	r->next=s;
}

void show(node *c){
	node *r=c;
	if (r->next!=NULL){
		printf("List is "); 
		r=c->next;
		while(r!=NULL){
			if(r->next==NULL){
				printf("%d",r->value);
			}
			else{
				printf("%d-->",r->value);
			}
			r=r->next;			
		}
	}
		
}

int isNum(char *s){
	//printf("%s",s);
	int i,n=strlen(s);
	for (i=0;i<n;i++){
		if(s[i]>'9'||s[i]<'0')
			return 0;
	}
	return 1;
}

int main(){
	node *p=initList();
	char a[20];	
	while(1){
		printf("Enter an integer: ");
		scanf("%s",a);
		if(isNum(a)){
			insert(p,atoi(a));
		}
		else
			break;
	}
	printf("Done. ");
	show(p);
	
	//printf("%d",p->value);
	return 0;
} 
