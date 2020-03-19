
#include <stdio.h>
#include "add.h"
#include "mul.h"
#include "sub.h"
#include "div.h"

int main(){

	int a,b,result,choice;
	printf("Enter two numbers\r\n");
	scanf("%d %d",&a,&b);
	printf("1.ADD 2.SUB 3.MUL 4.DIV 5.EXIT\r\n");
	printf("Enter your choice \r\n");
	scanf("%d",&choice);

	switch(choice){

		case 1:
			result=add(a,b);
			printf("Result of addition is %d\r\n",result);
			break;

		case 2:
			result=sub(a,b);
			printf("Result of addition is %d\r\n",result);
			break;

		case 3:
			result=mul(a,b);
			printf("Result of addition is %d\r\n",result);
			break;

		case 4:
			result=div(a,b);
			printf("Result of addition is %d\r\n",result);
			break;

		case 5:
			printf("exiting\r\n");
			break;


		default:
			printf("invalid choice and quitting\r\n");
			break;
	}
}
