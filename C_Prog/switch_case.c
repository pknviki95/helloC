#include<stdio.h>
int main(){
	char input[10];
	printf("enter the data\r\n");
	scanf("%s",input);
	switch(input[0]){
		case 49:
			printf("first choice\r\n");
			break;
		case 50:
			printf("second choice\r\n");
			break;
		case 51:
			printf("third choice\r\n");
			break;
		case 52:
			printf("fourth choice\r\n");
			break;
		default:
			printf("invalid choice\r\n");
	}
}
