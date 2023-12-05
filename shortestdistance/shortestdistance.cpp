/**
 * @file shortestdistance.cpp
 * @author xuwithbean
 * @brief search for the shortest path in an undirected graph
 * @version 0.1
 * @date 2023-11-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/**
 * @brief includes
 * 
 */
#include<stdio.h>
#include<string.h>
/**
 * @brief definations
 * 
 */
#define MAX 40	
#define INFINITY 65535	
#define TRUE 1
#define FALSE 0
/**
 * @brief the structure will be used
 * 
 */
typedef struct
{
	char ves[13][MAX];
	int vexnum;
	int Edge[MAX][MAX];	
}MGraph;
typedef int PathMatrix[MAX][MAX];
typedef int ShortPathTable[MAX];
/**
 * @brief init the undigraph
 * 
 * @param G 
 */
void undigraph(MGraph& G)
{
	G.vexnum = 13;
	char ves[MAX][MAX]={"����","��ˮ˼Դ","�ڷ���","ͼ���","��ѧ��¥","�����","����","������","������4","������1","������3","������2","��Ǩ��"};
	for(int i=0;i<13;i++)
	{
		for(int j=0;j<=strlen(ves[i]);j++)
		{
			G.ves[i][j]=ves[i][j];
		}
	}
	for (int i = 0; i < G.vexnum; i++)
	{
		for (int j = 0; j < G.vexnum; j++)
		{
			G.Edge[i][j] = INFINITY;
		}
	}
	G.Edge[0][1] = 18;
	G.Edge[0][10] = 22;
	G.Edge[1][2] = 19;
	G.Edge[1][9] = 27;
	G.Edge[2][10] = 4;
	G.Edge[2][8] = 32;
	G.Edge[2][3] = 23;
	G.Edge[3][4] = 15;
	G.Edge[3][9] = 4;
	G.Edge[3][11] = 4;
	G.Edge[4][5] = 21;
	G.Edge[4][7] = 8;
	G.Edge[5][6] = 30;
	G.Edge[6][7] = 14;
	G.Edge[6][11] = 21;
	G.Edge[6][12] = 20;
	G.Edge[7][8] = 4;
	G.Edge[11][12] = 43;
	for (int i = 0; i < G.vexnum; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			G.Edge[i][j] = G.Edge[j][i];
		}
	}
}

/**
 * @brief the djikstra way to find the shortest path
 * 
 * @param G 
 * @param v0 
 * @param P 
 * @param D 
 */
void ShortestPath_DJI(MGraph G, int v0, PathMatrix& P, ShortPathTable& D)
{
	int final[MAX];
	int vj = 0;
	for (int i = 0; i < G.vexnum; i++)
	{
		final[i] = FALSE;
		D[i] = G.Edge[v0][i];
		for (int j = 0; j < G.vexnum; j++)
		{
			P[i][j] = FALSE;
		}
		if (D[i] < INFINITY)
		{
			P[i][v0] = TRUE;
			P[i][i] = TRUE;
		}
	}
	D[v0] = 0;
	final[v0] = TRUE;
	for (int i = 1; i < G.vexnum; i++)
	{
		int min = INFINITY;
		for (int j = 0; j < G.vexnum; j++)
		{
			if (!final[j])
			{
				if (D[j] < min)
				{
					vj = j;
					min = D[j];
				}
			}
		}
		final[vj] = TRUE;
		for (int k = 0; k < G.vexnum; k++)
		{
			if (!final[k] && (min + G.Edge[vj][k] < D[k]))
			{
				D[k] = min + G.Edge[vj][k];
				for (int j = 0; j < G.vexnum; j++)
				{
					P[k][j] = P[vj][j]; 
				}
				P[k][k] = TRUE;
			}
		}
	}
}
/**
 * @brief the main function
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, const char* argv[])
{
	if (argc != 3)
	{
		printf("ERROR_01");
		return FALSE;
	}
	int v1 = INFINITY;
	int v2 = INFINITY;
	MGraph Grapth;
	undigraph(Grapth);
	for (int i = 0; i < Grapth.vexnum; i++)
	{
		if (strcmp(Grapth.ves[i], argv[1]) == 0)
		{
			v1 = i;
		}
		if (strcmp(Grapth.ves[i], argv[2]) == 0)
		{
			v2 = i;
		}
	}
	if (v1 == INFINITY || v2 == INFINITY)
	{
		printf("ERROR_02");
		return FALSE;
	}
	PathMatrix Path_M;
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			Path_M[i][j] = 0;
		}
	}
	ShortPathTable D_ShortPath;
	for (int i = 0; i < MAX; i++) {
		D_ShortPath[i] = 0;
	}
	ShortestPath_DJI(Grapth, v1, Path_M, D_ShortPath);
	printf("%s", Grapth.ves[v1]);
	while (v1 != v2)
	{
		for (int i = 0; i < Grapth.vexnum; i++)
		{
			if (Path_M[v2][i] == TRUE && Grapth.Edge[v1][i] != INFINITY)
			{
				printf("->%s", Grapth.ves[i]);
				Grapth.Edge[v1][i] = Grapth.Edge[i][v1] = INFINITY;
				v1 = i;
				break;
			}
		}
	}
	printf("\n");
	printf("%d", D_ShortPath[v2]);
	return TRUE;
}