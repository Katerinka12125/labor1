#include <stdlib.h> 
#include <stdio.h> 

typedef struct rebro {
	int begin;
	int end;
	int length;
} rebro_t;

int count_ver;
int count_rebro;
rebro_t * all_rebro;

int * ver_colors;
int visited_ver_count;
rebro_t *rebro_answer;
int count_rebro_already_added = 0;

int cmp(rebro_t *a, rebro_t *b)
{
	return a->length - b->length;
}

int process()
{
	for (int i = 0; i < count_rebro; i++)
	{
		if (all_rebro[i].begin == all_rebro[i].end)
		{
			continue;
		}

		if (ver_colors[all_rebro[i].begin] != ver_colors[all_rebro[i].end] || ver_colors[all_rebro[i].end] == 0 || ver_colors[all_rebro[i].begin] == 0)
		{
			rebro_answer[count_rebro_already_added] = all_rebro[i];
			count_rebro_already_added++;

			if (count_rebro_already_added == count_ver - 1) return 0;

			if (ver_colors[all_rebro[i].begin] == 0 && ver_colors[all_rebro[i].end] != 0)
			{
				ver_colors[all_rebro[i].begin] = ver_colors[all_rebro[i].end];
			}
			else if (ver_colors[all_rebro[i].begin] != 0 && ver_colors[all_rebro[i].end] == 0)
			{
				ver_colors[all_rebro[i].end] = ver_colors[all_rebro[i].begin];
			}
			else if (ver_colors[all_rebro[i].begin] == 0 && ver_colors[all_rebro[i].end] == 0)
			{
				ver_colors[all_rebro[i].begin] = i+1;
				ver_colors[all_rebro[i].end] = i+1;
			}
			else
			{
				int old_color = ver_colors[all_rebro[i].begin];
				int new_color = ver_colors[all_rebro[i].end];
				for (int k = 0; k < count_ver; k++)
				{
					if (ver_colors[k] == old_color)
					{
						ver_colors[k] = new_color;
					}
				}
			}
		}
	}

	return 1;
}

int main()
{
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
	else if (count_ver == 1)
	{
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
	ver_colors = calloc(sizeof(int), (count_ver + 1));

	for (int i = 0; i < count_rebro; ++i)
	{
		scanf("%d %d %d\n", &all_rebro[i].begin, &all_rebro[i].end, &all_rebro[i].length);

		if (all_rebro[i].begin < 1 || all_rebro[i].begin > count_ver ||
			all_rebro[i].end < 1 || all_rebro[i].end > count_ver)
		{
			printf("bad vertex");
			free(all_rebro);
			free(ver_colors);
			free(rebro_answer);
			return 0;
		}

		if (i < count_rebro - 1 && feof(stdin))
		{
			printf("bad number of lines");
			free(all_rebro);
			free(ver_colors);
			free(rebro_answer);
			return 0;
		}
		if (all_rebro[i].length < 0)
		{
			printf("bad length");
			free(all_rebro);
			free(ver_colors);
			free(rebro_answer);
			return 0;
		}
	}

	qsort(all_rebro, count_rebro, sizeof(rebro_t), cmp);

	if (process() == 1)
	{
		printf("no spanning tree");
	}
	else
		for (int i = 0; i < count_ver - 1; i++)
			printf("%d %d\n", rebro_answer[i].begin, rebro_answer[i].end);

	free(all_rebro);
	free(ver_colors);
	free(rebro_answer);

	return 0;
}
