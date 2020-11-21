#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
	
	
	int l,s,i,res;
	char str;
	l=atoi(argv[1]);
	s=atoi(argv[2]);
	

	srand(s);
	for(i=0;i<l;i++){
		res=rand()%26;
		str=97+res;
		printf("%c",str);
	}
	
	return 0;
}
