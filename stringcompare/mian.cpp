/**
 * @file mian.cpp
 * @author xuwithbean
 * @brief the way of KMP_match to match two strings
 * @version 0.1
 * @date 2023-10-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/**
 * @brief  includes
 * 
 */
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "malloc.h"

/**
 * @brief defines
 * 
 */
#define OK 1
#define Error -1
#define OVERFLOW -2
#define NUMOFARGC 3

/**
 * @brief define structures HString and NString
 * 
 */
typedef struct 
{
	char* ch;
	int length;
}HString;
typedef struct 
{
	int* num;
	int length;
}NString;

/**
 * @brief Initlize the HString and the NString
 * 
 * @param Hstr
 */
void InitHString(HString& Hstr)
{
    Hstr.ch={};
    Hstr.length=0;
}

/**
 * @brief initilize the Hstr and copy the information of string to it 
 * 
 * @param Tstr 
 * @param chars 
 * @return int 
 */
int StrAssign(HString& Hstr, char* chars) 
{
	if (!chars) 
    {
        return Error;
    }
	if (Hstr.ch) 
    {
        free(Hstr.ch);
    }
	int i=0,j=0;
	char* c;
	for (i = 0, c = chars; *c; ++i, ++c)
    {
        if (!i) 
        {
            Hstr.ch = NULL; 
            Hstr.length = 0;
        }
        else 
        {
            if (!(Hstr.ch = (char*)malloc(i * sizeof(char))))
            {
                exit(OVERFLOW);
            }
            for (j = 0; j < i; j++) 
            {
                Hstr.ch[j] = chars[j];
            }
            Hstr.length = i;
        }
    }
	return OK;
}

/**
 * @brief compare the master string and the slaver string
 * 
 * @param Sstr 
 * @param Tstr 
 * @return int 
 */
char StringCompare(HString Hstr1, HString Hstr2) 
{
	int i=0;
	for (i = 0; i < Hstr1.length && i < Hstr2.length; ++i) 
    {
		if((Hstr1.ch[i]>Hstr2.ch[i])||(Hstr1.ch[i]=Hstr2.ch[i]&&i==(Hstr2.length-1)&&Hstr1.length>Hstr2.length)) 
        {
            return '>';
        }
        else if(Hstr1.ch[i]<Hstr2.ch[i]||(Hstr1.ch[i]=Hstr2.ch[i]&&i==(Hstr1.length-1)&&Hstr1.length<Hstr2.length)) 
        {
            return '<';
        }
        else if(i==(Hstr1.length-1)&&Hstr1.length==Hstr2.length)
        {
            return '=';
        }
	}
}

/**
 * @brief let the hstring to be a null string
 * 
 * @param Hstr 
 * @return int 
 */
int ClearHString(HString& Hstr) {
	if (Hstr.ch) 
    {
		free(Hstr.ch);
		Hstr.ch = NULL;
	}
	Hstr.length = 0;
	return OK;
}

/**
 * @brief let the nstring to be a null string 
 * 
 * @param Nstr 
 * @return int 
 */
int ClearNString(NString & Nstr)
{
    if (Nstr.num) 
    {
        free(Nstr.num);
        Nstr.num = NULL;
	}
	Nstr.length = 0;
	return OK;
}

/**
 * @brief initlize the next string of Hstr
 * 
 * @param Hstr 
 * @param Nstr 
 * @return int 
 */
int InitNext(HString Hstr, NString &Nstr) 
{
	int i = 1;
	int j = 0;
	Nstr.length = Hstr.length+1;
	if (!(Nstr.num = (int*)malloc(Nstr.length * sizeof(int))))
	{
        exit(OVERFLOW);
    }
	Nstr.num[1]=0;
	while (i < Hstr.length)
    {
		if (j == 0 || Hstr.ch[i] == Hstr.ch[j]) 
        {
			++i;
			++j;
            if(Hstr.ch[i]!=Hstr.ch[j])
            {
                Nstr.num[i]=j;
            }
            else
            {
                Nstr.num[i]=Nstr.num[j];
            }
		}
		else
        {
			j = Nstr.num[j];
        }
	}
	return OK;
}

/**
 * @brief ways to match the two string of KMP
 * 
 * @param Hstr1 
 * @param Hstr2 
 * @return int 
 */
int Index_KMP(HString Hstr1, HString Hstr2) 
{
	NString Next;
	InitNext(Hstr2, Next);
	int i = 1;
	int j = 1;
	while (i <= Hstr1.length && j <= Hstr2.length) 
    {
		if (j == 0 || Hstr1.ch[i-1] == Hstr2.ch[j-1]) 
        { 
            ++i; 
            ++j; 
        }
		else j = Next.num[j];
	}
	ClearNString(Next);
	if (j > Hstr2.length) 
    {
        return i - Hstr2.length;
    }
	else 
    {
        return -1;
    }
}

/**
 * @brief the main function of KMP_match to run
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc,char *argv[])
{
	if (argc != NUMOFARGC) 
    {
		printf("ERROR_01");
		return -1;
	}
	HString MasterStr,SlaverStr;
    InitHString(MasterStr);
    InitHString(SlaverStr);
	StrAssign(MasterStr, argv[1]);
	StrAssign(SlaverStr, argv[2]);
	printf("%d", Index_KMP(MasterStr, SlaverStr));
	ClearHString(MasterStr);
	ClearHString(SlaverStr);
    return 0;
}