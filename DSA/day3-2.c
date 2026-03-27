#include<stdio.h>
#include<stdlib.h>
typedef struct{
	char data;
	int line;
}stack;
int push(stack s[],int *t,char d,int l){
	if(*t==99)
		return 0;
	*t=*t+1;
	s[*t].data=d;
	s[*t].line=l;
	return 1;
}
int pop(stack s[],int *t,stack *d){
	if(*t==-1)
		return 0;
	*d=s[*t];
	*t=*t-1;
	return 1;
}
char topele(stack s[],int t){
	return s[t].data;
}
int isEmpty(int t){
	return t==-1?1:0;
}
int main(int argc,char *argv[]){
	char x;
	stack st[100],y;
	int top=-1;
	int line=1;
	int flag1=0,flag2=0;
	if(argc!=2){
		printf("Enter File name in parameter\n");
		return -1;
	}
	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("File could not be opened!\n");
		return -1;
	}
	while((x=fgetc(fin))!=EOF){
		if(x==39) flag1++;
		if(x==34) flag1++;
		if(flag1>=2) flag1=0;
		if(flag2>=2) flag2=0;
		if(x=='\n'||x=='\r')
			line++;
		if((x=='('||x=='{'||x=='[')&&flag1==0&&flag2==0)
			push(st,&top,x,line);
		else if(x==')'&&flag1==0&&flag2==0){
			pop(st,&top,&y);
			if(y.data!='('){
				printf("Parenthesis %c missed at line no %d\n",y.data,y.line);
				return 0;
			}
		}
		else if(x=='}'&&flag1==0&&flag2==0){
			pop(st,&top,&y);
			if(y.data!='{'){
				printf("Parenthesis %c missed at line no %d\n",y.data,y.line);
				return 0;
			}
		}
		else if(x==']'&&flag1==0&&flag2==0){
			pop(st,&top,&y);
			if(y.data!='['){
				printf("Parenthesis %c missed at line no %d\n",y.data,y.line);
				return 0;
			}
		}	
	}
	if(isEmpty(top))
		printf("Parenthesis checking successful. No Error\n");
	else
		printf("Parenthesis mismatch found\n");
	return 0;
}