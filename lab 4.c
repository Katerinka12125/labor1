#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void badinput(char *array)
{
	for (int i=0;i<strlen(array);i++)
	{
		if (array[i]>'9' || array[i]<'0' )
		{
			printf("bad input");
			exit(0);
		}
		for (int k=0;k<strlen(array);k++)
			{
				if ((array[k]==array[i]) && (k!=i))
				{
					printf("bad input");
					exit (0);
				}
			}
	}
}
static void swap(char *array, int i,int j)
{
	int temp=array[i];
	array[i]=array[j];
	array[j]=temp;
}
void permutation(char *array,int count)
{
	int x=count-1;
	while ((x>0) && (array[x-1]>=array[x]))
	x--;
	if (x==0)
		exit(0);
	int y = count - 1; 
	while (array[y] <= array[x - 1]) 
	y--; 
	swap(array, x - 1, y); 
	y = count - 1; 	
	while (x++ < y--) 
	swap(array, x, y); 
} 
int main() 
{ 
	char array[11] = { 0 }; 
	int count; 
	scanf("%s", array); 
	scanf("%d", &count); 
		badinput(array); 
	while (count)
	{ 
		permutation(array, strlen(array)); 
		printf("%s\n", array); 
	    count--; 
	} 
	return 0; 
}
