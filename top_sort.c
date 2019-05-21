#define _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h> 
#include <stdio.h> 

typedef struct rebro {
	int begin;
	int end;
} rebro_t;

enum color {
	COLOR_WHITE = 0,
	COLOR_GRAY = 1,
	COLOR_BLACK = 2
};

int process(int vert_num, int count_ver, int count_rebro, rebro_t * array, int *stack, int *kol, enum color *colors)
{
	// красим в серый
	if (colors[vert_num] == COLOR_GRAY)
	{
		return 1;
	}
	colors[vert_num] = COLOR_GRAY;

	// ид1м по всем детям и вызываем рекурсивно
	for (int i = 0; i < count_rebro; i++)
	{
		if (array[i].begin == vert_num && colors[array[i].end] != COLOR_BLACK)
		{
			int err = process(array[i].end, count_ver, count_rebro, array, stack, kol, colors);
			if (err == 1) {
				return 1;
			}
		}
	}

	// красим в чёрный и кладём в стек 
	colors[vert_num] = COLOR_BLACK;
	stack[*kol] = vert_num;
	(*kol)++;

	return 0;
}

int main()
{
	int count_ver;
	int count_rebro;
	rebro_t * array;
	int *stack;
	int kol;
	enum color * colors;
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
		if (colors[i] == COLOR_WHITE)
		{
			int err = process(i, count_ver, count_rebro, array, stack, &kol, colors);
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
