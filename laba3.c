#define CRT_SECURE_NO_WARNINGS 
#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
long HashFunction(unsigned char *str, int m) 
{ 
long hush = 0; 
long t = 1; 
int i; 
for (i = 0; i < m; i++) 
{ 
hush += (str[i] % 3)*t; 
t *= 3; 
} 
return hush; 
} 
int main() 
{ 
unsigned char array[19]; 
unsigned char str[1000]; 
unsigned char line1[1000]; 
unsigned char line2[1000]; 
long husharray; 
long hushline; 
gets(str); 
int m, n, i, k; 
m = strlen(str);  
fgets(line1,sizeof(line1),stdin);
if (fgets(line2,sizeof(line2), stdin))
	strcat(line1, line2); 
if (strlen(line1)>0)
	if (line1[strlen(line1) - 1] == '\n')
		line1[strlen(line1) - 1] = 0;
n = strlen(line1); 
husharray = HashFunction(str, m); 
hushline = HashFunction(line1, m); 
printf("%ld ", husharray); 
long pow1 = 1; 
for (i = 1; i < m; i++) 
pow1 *= 3; 
for (i = 0; i< n - m + 1; i++) 
{ 
if (husharray == hushline) 
{ 
for (k = i; k<i + m; k++) 
{ 
printf("%d ", k + 1); 
if (str[k - i] != line1[k]) 
break; 
} 
} 
hushline = (hushline - (line1[i] % 3)) / 3 + ((line1[m + i] % 3)*pow1); 
} 
return 0; 
}
