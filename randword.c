#include <stdio.h>
#include <stdlib.h>

int main(){
	
	
	int length,seed,i,res;
	char str;
	scanf("%d",&length);
	scanf("%d",&seed);
	

	srand(seed);
	for(i=0;i<length;i++){
		res=rand()%26;
		str=97+res;
		printf("%c",str);
	}
	
	return 0;
}
