/**
 * @file main.cpp
 * @author xuwithbean
 * @brief count math expression
 * @version 0.1
 * @date 2023-10-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
/**
 * @brief includes
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>//包含isdigit函数

/**
 * @brief defines
 * 
 */
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define OK 1
#define ERROR 0
#define op_len 11
#define order_number 2

/**
 * @brief some temp param
 * 
 */
int sign = 1, pos = 0;
char op[op_len] = { '+','-','*','/','(',')','\0','^','[',']' ,'.' };

/**
 * @brief define structs
 * 
 */
typedef struct 
{
	double* base;
	double* top;
	int stacksize;
}SqStack_OPND;
typedef struct 
{
	char* base;
	char* top;
	int stacksize;
}SqStack_OPTR;

/**
 * @brief initstacks
 * 
 * @param Stacks 
 * @return int 
 */
int InitStack_OPND(SqStack_OPND& Stacks) 
{
	Stacks.base = (double*)malloc(STACK_INIT_SIZE * sizeof(double));
	if (!Stacks.base) 
	{
		exit(OVERFLOW);
	}
	Stacks.top = Stacks.base;
	Stacks.stacksize = STACK_INIT_SIZE;
	return OK;
}
int InitStack_OPTR(SqStack_OPTR& Stacks) 
{
	Stacks.base = (char*)malloc(STACK_INIT_SIZE * sizeof(char));
	if (!Stacks.base) 
	{
		exit(OVERFLOW);
	}
	Stacks.top = Stacks.base;
	Stacks.stacksize = STACK_INIT_SIZE;
	return OK;
}
/**
 * @brief get into the stack
 * 
 * @param Stacks 
 * @param element 
 * @return int 
 */
int Push_OPND(SqStack_OPND& Stacks, double element) 
{
	if (Stacks.top - Stacks.base >= Stacks.stacksize) 
	{
		Stacks.base = (double*)realloc(Stacks.base, (Stacks.stacksize + STACKINCREMENT) * sizeof(double));
		if (!Stacks.base) exit(OVERFLOW);
		Stacks.top = Stacks.base + Stacks.stacksize;
		Stacks.stacksize += STACKINCREMENT;
	}
	*Stacks.top = element;
	Stacks.top++;
	return OK;
}
int Push_OPTR(SqStack_OPTR& Stacks, char element) 
{
	if (Stacks.top - Stacks.base >= Stacks.stacksize) 
	{
		Stacks.base = (char*)realloc(Stacks.base, (Stacks.stacksize + STACKINCREMENT) * sizeof(char));
		if (!Stacks.base) exit(OVERFLOW);
		Stacks.top = Stacks.base + Stacks.stacksize;
		Stacks.stacksize += STACKINCREMENT;
	}
	*Stacks.top = element;
	Stacks.top++;
	return OK;
}
/**
 * @brief get outo of the stack and get the value
 * 
 * @param Stacks 
 * @param element 
 * @return int 
 */
int Pop_OPND(SqStack_OPND& Stacks, double& element) 
{
	if (Stacks.top == Stacks.base)return 0;
	Stacks.top--;
	element = *Stacks.top;
	return OK;
}
int Pop_OPTR(SqStack_OPTR& Stacks, char& element) 
{
	if (Stacks.top == Stacks.base)return 0;
	Stacks.top--;
	element = *Stacks.top;
	return OK;
}
/**
 * @brief get the toppest param's value
 * 
 * @param Stacks 
 * @param element 
 * @return int 
 */
int GetTop_OPND(SqStack_OPND Stacks, double* element) 
{
	if (!element) exit(ERROR);
	if (Stacks.top == Stacks.base) return ERROR;
	*element = *(Stacks.top - 1);
	return OK;
}
int GetTop_OPTR(SqStack_OPTR Stacks, char* element) 
{
	if (!element) exit(ERROR);
	if (Stacks.top == Stacks.base) return ERROR;
	*element = *(Stacks.top - 1);
	return OK;
}
/**
 * @brief Brackets compare
 * 
 * @param String 
 * @return int 
 */
int Bracketfound(char* String) 
{
	if (!String) exit(ERROR);
	char a = '0', b = '0';
	int i = 0, time = 0;
	SqStack_OPTR optr;
	InitStack_OPTR(optr);
	for (i = 0; String[i] != '\0'; i++) 
	{
		a = String[i];
		if ((a == '(') || (a == '[')) Push_OPTR(optr, a);
		else if ((a == ')') || (a == ']')) {
			time = Pop_OPTR(optr, b);
			if ((time == 0) || (a == ')' && b != '(') || (a == ']' && b != '[')) 
			{
				return 0;
				break;
			}
		}
	}
	if (Pop_OPTR(optr, b) == 0) return OK;
	else return 0;
}
/**
 * @brief find the string put in is or not op
 * 
 * @param mychar 
 * @return int 
 */
int in(char mychar) 
{
	int i = 0;
	while (i < op_len) 
	{
		if (mychar == op[i]) return OK;
		i++;
	}
	return 0;
}
char OPTR[op_len] = { '+','-','*','/','(',')','\0','^','[',']' ,'.' };
/**
 * @brief compare the turns of the operater
 * 
 * @param optra the first operater
 * @param optrb the second operater
 * @return char 
 */
char Precede(char optra, char optrb)
{
	int i = 0, j = 0;
	char pre[][op_len] = 
	{
		{'>','>','<','<','<','>','>','<','<','>','<'},
		{'>','>','<','<','<','>','>','<','<','>','<'},
		{'>','>','>','>','<','>','>','<','<','>','<'},
		{'>','>','>','>','<','>','>','<','<','>','<'},
		{'<','<','<','<','<','=','0','<','0','0','<'},
		{'>','>','>','>','0','>','>','>','0','>','<'},
		{'<','<','<','<','<','0','=','<','<','0','<'},
		{'>','>','>','>','<','>','>','>','<','>','<'},
		{'<','<','<','<','<','0','0','<','<','=','<'},
		{'>','>','>','>','0','0','>','>','0','>','<'},
		{'>','>','>','>','0','>','>','>','0','>','0'},
	};
	switch (optra)
    {
	case '+':i = 0; break;
	case '-':i = 1; break;
	case '*':i = 2; break;
	case '/':i = 3; break;
	case '(':i = 4; break;
	case ')':i = 5; break;
	case '\0':i = 6; break;
	case '^':i = 7; break;
	case '[':i = 8; break;
	case ']':i = 9; break;
	case '.':i = 10; break;
	}
	switch (optrb) 
	{
	case '+':j = 0; break;
	case '-':j = 1; break;
	case '*':j = 2; break;
	case '/':j = 3; break;
	case '(':j = 4; break;
	case ')':j = 5; break;
	case '\0':j = 6; break;
	case '^':j = 7; break;
	case '[':j = 8; break;
	case ']':j = 9; break;
	case '.':j = 10; break;
	}
	return pre[i][j];
}

/**
 * @brief count the math expression
 * 
 * @param opnda the first number
 * @param theta the operator
 * @param opndb the second number
 * @return double 
 */
double Operate(double opnda, char theta, double opndb) 
{
	double i = opnda, j = opndb;
	double result = 0;
	switch (theta) 
	{
	case '+':result = i + j; break;
	case '-':result = i - j; break;
	case '*':result = i * j; break;
	case '/':if (j == 0) 
	{
		sign = 0; printf("ERROR_03"); break;
	}
		   else {
		result = i / j; break;
	}
	case '^':result = pow(i, j); break;
	}
	return result;
}
/**
 * @brief Get the Next object
 * 
 * @param node node is the num or the operator
 * @param String string is the string get in cmd
 * @return int 
 */
int getNext(double* node, char* String) 
{
	char c = '0';
	int num = 0, time = 0, len, pos_1;
	double multiple = 0.1;
	len = strlen(String);
	*node = 0;
	if (pos <= len) 
	{
		c = String[pos++];
		if (!isdigit(c)) 
		{
			if (in(c)) 
			{
				*node = c;
				return OK;
			}
			else 
			{
				sign = 0;
				printf("ERROR_02");
			}
		}
		do {//get nums int or double
			if (c >= '0' && c <= '9' && (time == 0)) 
			{
				*node = (*node) * 10 + (c - '0');
				pos_1 = pos;
				if (!in(c = String[pos_1++])) 
				{
					pos++;
				}
				//c = argv[pos_1++];
			}
			else if (c == '.' || num == 1) 
			{
				time++;
				if (time > 1 && c == '.') 
				{
					sign = 0;
					printf("ERROR_02");
					break;
				}
				else {
					if (num == 0) 
					{
						num = 1;
						c = String[++pos];
					}
					if (c >= '0' && c <= '9') 
					{
						*node = (*node) + (c - '0') * multiple;
						multiple = multiple / 10;
						c = String[++pos];
					}
				}
			}
		} 
		while (isdigit(c) || (c == '.'));
		ungetc(c, stdin);
	}
	return 0;
}
/**
 * @brief code on the book 
 * 
 * @param String 
 * @return double 
 */
double EvaluateExpression(char* String)
{
	int flag, flag_2 = 0;
	char x, theta;
	double a, b, c;
	SqStack_OPTR OPTR;//
	SqStack_OPND OPND;
	InitStack_OPTR(OPTR);
	Push_OPTR(OPTR, '\0');
	InitStack_OPND(OPND);
	flag = getNext(&c, String); 
	GetTop_OPTR(OPTR, &x);
	while ((c != '\0' || x != '\0') && sign != 0)
	{
		if (flag == 0)
		{
			Push_OPND(OPND, c);
			flag = getNext(&c, String);
		}
		else
		{
			GetTop_OPTR(OPTR, &x);
			switch (Precede(x, c))
			{
			case '<':Push_OPTR(OPTR, c); flag = getNext(&c, String); break;
			case '=':Pop_OPTR(OPTR, x); flag = getNext(&c, String); break;
			case '>':Pop_OPTR(OPTR, theta); Pop_OPND(OPND, b); flag_2 = Pop_OPND(OPND, a);
				if (!flag_2)
				{
					sign = 0;
					printf("ERROR_02");
					break;
				}
				; 
				Push_OPND(OPND, Operate(a, theta, b)); break;
			}
		}
		GetTop_OPTR(OPTR, &x);
	}
	GetTop_OPND(OPND, &c);
	return c;
}
/**
 * @brief main fuction
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char* argv[]) 
{
	double result = 0;
	if (argc != order_number) 
	{
		printf("ERROR_02");
		exit(OVERFLOW);
	}
	if (!Bracketfound(argv[1])) 
	{
		printf("ERROR_02");
		exit(OVERFLOW);
	}
	result = EvaluateExpression(argv[1]);
	if (sign) 
	{
		printf("%g", result);
	}
	return 0;
}
