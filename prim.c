#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h> 
#include <stdio.h> 

typedef struct rebro {
	int begin;
	int end;
	int length;
} rebro_t;
int cmp(const void *a, const void *b)
{
	return ((rebro_t*)a)->length - ((rebro_t*)b)->length;
}

int process(int count_rebro, int count_ver, rebro_t * all_rebro, int * visited_vertices, rebro_t *rebro_answer)
{
	int count_rebro_already_added = 0;
	while (count_rebro_already_added != count_ver - 1)
	{
		int min_rebro = -1;
		for (int i = 0; i < count_rebro; i++)
		{
			int visited_begin = visited_vertices[all_rebro[i].begin];
			int visited_end = visited_vertices[all_rebro[i].end];
			if ((visited_begin == 0 && visited_end != 0) || (visited_begin != 0 && visited_end == 0))
			{
				min_rebro = i;
				break;
			}
		}
		if (min_rebro == -1)
			return 1;
		rebro_answer[count_rebro_already_added] = all_rebro[min_rebro];
		count_rebro_already_added++;
		visited_vertices[all_rebro[min_rebro].begin] = 1;
		visited_vertices[all_rebro[min_rebro].end] = 1;
	}

	return 0;
}

int main()
{

	int count_ver;
	int * visited_vertices;
	int count_rebro;
	rebro_t * all_rebro;
	rebro_t *rebro_answer;
	scanf("%d\n", &count_ver);
	if (count_ver < 0 || count_ver>5000)
	{
		printf("bad number of vertices");
		return 0;
	}
	else if (count_ver == 0)
	{
		printf("no spanning tree");
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

	all_rebro = malloc(sizeof(rebro_t)*count_rebro);
	rebro_answer = malloc(sizeof(rebro_t)*count_ver);
	visited_vertices = calloc(sizeof(int), (count_ver + 1));

	for (int i = 0; i < count_rebro; ++i)
	{
		scanf("%d %d %d\n", &all_rebro[i].begin, &all_rebro[i].end, &all_rebro[i].length);

		if (all_rebro[i].begin < 1 || all_rebro[i].begin > count_ver ||
			all_rebro[i].end < 1 || all_rebro[i].end > count_ver)
		{
			printf("bad vertex");
			free(all_rebro);
			free(visited_vertices);
			free(rebro_answer);
			return 0;
		}

		if (i < count_rebro - 1 && feof(stdin))
		{
			printf("bad number of lines");
			free(all_rebro);
			free(visited_vertices);
			free(rebro_answer);
			return 0;
		}
		if (all_rebro[i].length < 0)
		{
			printf("bad length");
			free(all_rebro);
			free(visited_vertices);
			free(rebro_answer);
			return 0;
		}
	}

	qsort(all_rebro, count_rebro, sizeof(rebro_t), &cmp);

	visited_vertices[1] = 1;

	if (process(count_rebro, count_ver, all_rebro, visited_vertices, rebro_answer) == 1)
	{
		printf("no spanning tree");
	}
	else
		for (int i = 0; i < count_ver - 1; i++)
			printf("%d %d\n", rebro_answer[i].begin, rebro_answer[i].end);

	free(all_rebro);
	free(visited_vertices);
	free(rebro_answer);

	return 0;
}
