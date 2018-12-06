#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>
int main()
{
	int d[12], c[12], i, t, b1, b2, flag, nc, nd, kc, kd, ks;
	char st[50];
	char st2[50];
	ks = 0;
	t = scanf("%d %d", &b1, &b2);
	if (t != 2)
	{
		printf("bad input");
		return 0;
	}
	if (b1<2 || b1>16 || b2<2 || b2>16)
	{
		printf("bad input");
		return 0;
	}
	scanf("%s", st);
	if (st[0] == '-') flag = 1;
	else flag = 0;
	kc = 0;
	for (i = flag; i < strlen(st) && st[i] != '.'; i++)
	{
		if (st[i] >= 0x30 && st[i] <= 0x39)
			c[i - flag] = st[i] - 0x30;
		else
		if (st[i] >= 0x41 && st[i] <= 0x46)
			c[i - flag] = (st[i] - 0x41) + 10;
		else
		if (st[i] >= 0x61 && st[i] <= 0x66)
			c[i - flag] = (st[i] - 0x61) + 10;
		else
		{
			printf("bad input");
			return 0;
		}
		kc++;
		if (c[i - flag] > b1 || c[i - flag] < 0)
		{
			printf("bad input");
			return 0;
		}
	}
	kd = 0;
	for (i += 1; i < strlen(st); i++)
	{
		if (st[i] >= 0x30 && st[i] <= 0x39)
			d[kd] = st[i] - 0x30;
		else
		if (st[i] >= 0x41 && st[i] <= 0x46)
			d[kd] = (st[i] - 0x41) + 10;
		else
		if (st[i] >= 61 && st[i] <= 0x66)
			d[kd] = (st[i] - 0x61) + 10;
		else
		{
			printf("bad input");
			return 0;
		}
		if (d[kd] > b1 || d[kd] < 0)
		{
			printf("bad input");
			return 0;
		}
		kd++;
	}
	double num = 0;
	for (i = 0; i < kc; i++)
		num += c[i] * pow(b1, kc - i - 1);
	for (i = 0; i < kd; i++)
		num += d[i] * pow(b1, -(i + 1));
	long n = (long)num;
	for (i = 0; n != 0; i++)
	{
		c[i] = n % b2;
		n /= b2;
	}
	kc = i;
	double m = num - (long)num;
	for (i = 0; m != 0 && i < 12; i++)
	{
		d[i] = (int)(m*b2);
		m = m*b2 - (d[i]);
	}
	kd = i;
	if (flag == 1)
		st2[0] = '-';
	ks = flag;
	for (i = 0; i < kc; i++)
	{
		if (c[kc - i - 1] <= 9 && c[kc - i - 1] >= 0)
			st2[i + flag] = c[kc - i - 1] + 0x30;
		if (c[kc - i - 1] <= 15 && c[kc - i - 1] >= 10)
			st2[i + flag] = (c[kc - i - 1] - 10) + 0x41;
		ks++;
	}
	if (kd == 0)
	{
		for (i = 0; i<ks; i++)
			printf("%c", st2[i]);
		return 1;
	}
	if (kd>0)
	{
		st2[i + flag] = '.';
		ks++;
	}
	for (i = 0; i < kd; i++)
	{
		if (d[i] <= 9 && d[i] >= 0)
			st2[flag + kc + 1 + i] = d[i] + 0x30;
		if (d[i] <= 15 && d[i] >= 10)
			st2[flag + kc + 1 + i] = (d[i] - 10) + 0x41;
		ks++;
	}
	for (i = 0; i<ks; i++)
		printf("%c", st2[i]);
	return 1;
}
