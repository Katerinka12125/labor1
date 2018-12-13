#define _USE_CRT_N0_WARNINGS 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#define MAXLINE 1000 
int shift[1000];
void table(const char pattern[MAXLINE])
{
	unsigned long long t = strlen(pattern), i;
	for (i = 0; i <= 1000; i++)
		shift[i] = t;
	for (i = 0; i < t - 1; i++)
		shift[pattern[i] + 128] = t - i - 1;
}
void pos(const char pattern[MAXLINE], int i)
{
	char str1[100] = { 0 };
	char str2[100] = { 0 };
	fgets(str1, sizeof(str1), stdin);
	fgets(str2, sizeof(str2), stdin);
	strcat(str1, str2);
	if (strlen(str1)>0)
		if ((str1[strlen(str1) - 1]) == '\n')
			str1[strlen(str1) - 1] = 0;
	int j, k, t = strlen(pattern), len = strlen(str1);
	if ((len == 0) || (t == 0))
		exit(0);
	if (len < t)
		printf("%d ", t);
	for (k = t; k <= len;)
	{
		printf("%d ", k + i);
		if (pattern[t - 1] == str1[k - 1])
		{
			for (j = t - 2; ((j >= 0) && pattern[j] == str1[k - t + j]); j--)
			{
				printf("%d ", k - t + j + 1 + i);
			}
			if (j < 0)
			{
				k += shift[pattern[t - 1] + 128];
			}
			else
			{
				printf("%d ", k - t + j + 1 + i);
				k += shift[pattern[t - 1] + 128];
			}
		}
		else
		{
			k += shift[str1[k - 1] + 128];
		}
	}
	i += t;
}
int main(void)
{
	char pattern[100];
	fgets(pattern, sizeof(pattern), stdin);
	if ((pattern[strlen(pattern) - 1]) == '\n')
		pattern[strlen(pattern) - 1] = 0;
	table(pattern);
	pos(pattern, 0);
	return 0;
}
