#define _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h> 
#include <stdio.h> 

typedef struct rebro {
	int begin;
	int end;
} rebro_t;

int count_ver;
int count_rebro;
rebro_t * array;
int *stack;
int kol;
int * colors;

int process(int vert_num)
{
	// красим в серый 
	if (colors[vert_num] == 1)
	{
		return 1;
	}
	colors[vert_num] = 1;

	// ид1м по всем детям и вызываем рекурсивно 
	for (int i = 0; i < count_rebro; i++)
	{
		if (array[i].begin == vert_num && colors[array[i].end] != 2)
		{

			int err = process(array[i].end);
			if (err == 1) {
				return 1;
			}
		}
	}

	// красим в чёрный и кладём в стек 
	colors[vert_num] = 2;
	stack[kol] = vert_num;
	kol++;

	return 0;
}

int main()
{
	scanf("%d\n", &count_ver);
	if (count_ver < 0 || count_ver>1000)
	{
		printf("bad number of vertices");
		return 0;
	}

	if (scanf("%d\n", &count_rebro) != 1) {
		printf("bad number of lines");
		return 0;
	}
	if (count_rebro<0 || count_rebro>((count_ver)*(count_ver + 1)) / 2)
	{
		printf("bad number of edges");
		return 0;
	}

	if (count_rebro > 0 && feof(stdin))
	{
		printf("bad number of lines");
		return 0;
	}

	array = malloc(sizeof(rebro_t)*count_rebro);

	for (int i = 0; i < count_rebro; ++i)
	{
		scanf("%d %d\n", &array[i].begin, &array[i].end);

		if (array[i].begin < 1 || array[i].begin > count_ver ||
			array[i].end < 1 || array[i].end > count_ver)
		{
			printf("bad vertex");
			free(array);
			return 0;
		}

		if (i < count_rebro - 1 && feof(stdin))
		{
			printf("bad number of lines");
			free(array);
			return 0;
		}
	}

	stack = malloc(sizeof(int)*count_ver);
	kol = 0;

	colors = calloc(sizeof(int), count_ver + 1);

	for (int i = 1; i <= count_ver; ++i)
	{
		if (colors[i] == 0)
		{
			int err = process(i);
			if (err == 1)
			{
				printf("impossible to sort");
				free(array);
				free(colors);
				free(stack);
				return 0;
			}
		}
	}

	for (int k = kol - 1; k >= 0; k--)
	{
		printf("%d ", stack[k]);
	}

	free(stack);
	free(array);
	free(colors);

	return 0;
}
