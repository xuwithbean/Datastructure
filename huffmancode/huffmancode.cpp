/**
 * @file main.cpp
 * @author Jiaxu Xiao
 * @brief huffman code and decode 
 * @version 0.1
 * @date 2023-11-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/**
 * @brief includes
 * 
 */
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/**
 * @brief definations
 * 
 */
#define MINLEN             20
#define OVERFLOW           -1

/**
 * @brief define the type of huffmantree and huffmancode
 * 
 */
typedef struct 
{
	char ch;
	int weight;
	int parent, lchild, rchild;
}HTNode, * HuffmanTree;
typedef char** HuffmanCode;

/**
 * @brief get the weight of the code in a string
 * 
 * @param huffmantree 
 * @param str 
 * @param weight 
 * @return int 
 */
int StrWeight(HuffmanTree& huffmantree, char* str, int* weight) 
{
	if (!str) exit(-1);
	if (!weight) exit(-1);
	int len = strlen(str);
	int i, j, count = 1, flag = 1, chnum = 1;
	for (i = 0; i < len; i++)
	{
		for (j = 0; j < len - i - 1; j++) 
		{
			if (str[j] > str[j + 1]) 
			{
				char temp;
				temp = str[j + 1];
				str[j + 1] = str[j];
				str[j] = temp;
			}
		}
	}
	for (i = 1; i < len; i++) 
	{
		if (str[i] != str[i - 1])
		{
			count++;
		}
	}
	weight = (int*)realloc(weight, count * sizeof(int));
	if (!weight)
	{
		exit(OVERFLOW);
	}
	weight[count] = '\0';
	huffmantree = (HuffmanTree)malloc(2 * count * sizeof(HTNode));
	if (!huffmantree)
	{
		exit(OVERFLOW);
	}
	for (i = 0; i < len; i++) 
	{
		if (str[i] == str[i + 1])
		{
			flag++;
		}
		if (str[i] != str[i + 1]) 
		{
			*weight++ = flag;
			flag = 1;
			huffmantree[chnum++].ch = str[i];
		}
	}
	return count;
}

/**
 * @brief find the min1 and min2 at loc
 * 
 * @param huffmantree 
 * @param loc 
 * @param min1 
 * @param min2 
 */
void Select(HuffmanTree& huffmantree, int loc, int& min1, int& min2) 
{
	int min_weight1=0;
	int i = 0;
	for (i = 1; i <= loc; i++) 
	{
		if (huffmantree[i].parent == 0) 
		{
			min1 = i;
			min_weight1 = huffmantree[i].weight;
			break;
		}
	}
	int min_weight2=0;
	for (i = 1; i <= loc; i++) 
	{   
		if (huffmantree[i].parent == 0) 
		{
			if (i == min1)
			{
				continue;
			}
			else if (huffmantree[i].weight > huffmantree[min1].weight) 
			{
				min2 = i;
				min_weight2 = huffmantree[i].weight;
			}
			else if (huffmantree[i].weight == huffmantree[min1].weight) 
			{
				min2 = i;
				min_weight2 = huffmantree[i].weight;
				break;
			}
		}
	}
	for (i = 1; i <= loc; i++) 
	{
		if (huffmantree[i].parent == 0) 
		{
			if (huffmantree[i].weight < huffmantree[min1].weight) 
			{ 
				min_weight2 = min_weight1;
				min2 = min1;
				min_weight1 = huffmantree[i].weight;
				min1 = i;
			}
			else if (huffmantree[i].weight < huffmantree[min2].weight && i != min1)
			{
				min_weight2 = huffmantree[i].weight;
				min2 = i;
			}
			else if (huffmantree[i].weight == huffmantree[min1].weight) 
			{
				if (huffmantree[min1].ch > huffmantree[i].ch) 
				{
					min1 = i;
				}
			}
			else if (huffmantree[i].weight == huffmantree[min2].weight) 
			{
				if (huffmantree[min2].ch > huffmantree[i].ch) 
				{
					min2 = i;
				}
			}
		}
	}
}

/**
 * @brief function to code huffmantree
 * 
 * @param huffmantree 
 * @param huffmancode 
 * @param weight 
 * @param num 
 */
void HuffmanCoding(HuffmanTree& huffmantree, HuffmanCode& huffmancode, int* weight, int num) 
{
	if (!weight) exit(-1);
	if (num <= 1) return;
	int i, m;
	int min1 = 0, min2 = 0; 
	int start, temc, temp;
	m = 2 * num - 1;
	for (i = 1; i <= num; ++i) 
	{
		huffmantree[i].weight = weight[i - 1];
		huffmantree[i].parent = 0;
		huffmantree[i].lchild = 0;
		huffmantree[i].rchild = 0;
	}
	for (; i <= m; ++i) 
	{
		huffmantree[i].ch = '~';
		huffmantree[i].weight = 0;
		huffmantree[i].parent = 0;
		huffmantree[i].lchild = 0;
		huffmantree[i].rchild = 0;
	}
	for (i = num + 1; i <= m; i++) 
	{
		Select(huffmantree, i - 1, min1, min2);
		huffmantree[min1].parent = i; huffmantree[min2].parent = i;
		huffmantree[i].lchild = min1; huffmantree[i].rchild = min2;
		huffmantree[i].weight = huffmantree[min1].weight + huffmantree[min2].weight;
	}
	huffmancode = (HuffmanCode)malloc((num + 1) * sizeof(char*));
	if (!huffmancode)
	{
		exit(OVERFLOW);
	}
	char* code;
	code = NULL;
	code = (char*)malloc(num * sizeof(char));
	if (!code)
	{
		exit(OVERFLOW);
	}
	code[num - 1] = '\0';
	for (i = 1; i <= num; ++i) 
	{       
		start = num - 1;          
		for (temc = i, temp = huffmantree[i].parent; temp != 0; temc = temp, temp = huffmantree[temp].parent) 
		{
			if (temc == huffmantree[temp].lchild)
			{
				code[--start] = '0';
			}
			else
			{
				code[--start] = '1';
			}
		}
		huffmancode[i] = (char*)malloc(num * sizeof(char));
		if (!huffmancode[i])
		{
			exit(OVERFLOW);
		}
		strcpy(huffmancode[i], &code[start]);  
	}
	free(code);
}

/**
 * @brief function to decode huffmantree
 * 
 * @param huffmancode 
 * @param str2 
 * @param num 
 */
void HuffmanDecoding(HuffmanTree huffmancode, char* str2, int num) 
{
	int m = 2 * num - 1;
	int i = 0;
	while (str2[i] && m) {
		if (str2[i] != '0' && str2[i] != '1') 
		{
			printf("ERROR_03");
			return;
		}
		if (str2[i] == '0')
		{
			m = huffmancode[m].lchild;
		}
		if (str2[i] == '1')
		{
			m = huffmancode[m].rchild;
		}
		i++;
		if (huffmancode[m].lchild == 0 && huffmancode[m].rchild == 0) 
		{
			printf("%c", huffmancode[m].ch);
			m = 2 * num - 1;
		}
	}
	if (huffmancode[m].lchild != 0 && m != 2 * num - 1) 
	{ 
		printf("ERROR_03");
	}
}

/**
 * @brief detect if the string is all the same
 * 
 * @param str 
 * @param num 
 * @return int 
 */
int same(char* str, int num) 
{
	int i, flag;
	for (i = 0, flag = 1; i < num - 1; i++) 
	{
		if (str[i] == str[i + 1])
		{
			flag++;
		}
	}
	if (flag == num)
	{
		return 1;
	}
	return 0;
}

/**
 * @brief the main function of huffmancoding and huffmandecoding
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char* argv[]) 
{
	if (argc != 3) 
    {
		printf("ERROR_01");
		return 0;
	}
	int length1 = strlen(argv[1]);
	if (length1 < MINLEN) 
    {
		printf("ERROR_02");
		return 0;
	}
	if (same(argv[1], length1)) 
    {
		printf("ERROR_02");
		return 0;
	}
	HuffmanTree HT = {};
	HuffmanCode HC = {};
	int i = 0, j = 0;
	int node_len=0;
	char* strargv1 = NULL; 
	char* q=NULL;
	q = argv[1];
	strargv1 = (char*)malloc(length1 * sizeof(char));
	if (!strargv1)
	{
        exit(OVERFLOW);
    }
	while (q[i]) 
    {
		strargv1[i] = q[i];
		i++;
	}
	int* weight=NULL;
	weight = (int*)malloc(length1 * sizeof(int));
	if (!weight)
	{
		exit(OVERFLOW);
	}
	node_len = StrWeight(HT, argv[1], weight);
	HuffmanCoding(HT, HC, weight, node_len);
	int m = 2 * node_len - 1; 
	i = 0;
	while (argv[2][i] && m) 
    {
		if (argv[2][i] == '0')
        {
            m = HT[m].lchild;
        }
		if (argv[2][i] == '1')
        {
            m = HT[m].rchild;
        }
		i++;
		if (HT[m].lchild == 0 && HT[m].rchild == 0)
		{
            m = 2 * node_len - 1;
        }
	}
	if (HT[m].lchild != 0 && m != 2 * node_len - 1) 
    {
		printf("ERROR_03");
		return 0;
	}
	/**
	 * @brief print the code after huffmancoding
	 * 
	 */
	for (i = 0; i < length1; i++) 
    {
		for (j = 1; j <= node_len; j++) 
        {
			if (strargv1[i] == HT[j].ch)
			{
                printf("%s", HC[j]);
            }
		}
	}
	printf(" ");
	HuffmanDecoding(HT, argv[2], node_len);
	free(strargv1);
	free(HT);
	free(HC);
	return 0;
}