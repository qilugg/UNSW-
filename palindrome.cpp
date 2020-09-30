#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isPalindrome(char a[],int len){
	int j=len-1,i=0;
	while(i<j){
		if (a[i]!=a[j])
			return 0;
		i++;
		j--;
	}
	return 1;
}


int main(){
	char a[50];
	int i,n;
	
	printf("Enter a word:");
	gets(a);
	n=strlen(a);
	i=isPalindrome(a,n);	
	if(i=1)
		printf("yes");
	else
		printf("no");
	
	return 0;
} 
