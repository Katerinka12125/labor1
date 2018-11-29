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
  unsigned char line[1000]; 
  long husharray; 
  long hushline; 
  gets(str); 
  int m, n, i, k; 
  m = strlen(str); 
  for (i = 0; i < m; i++) 
  array[i] = str[i]; 
  memset (str,0,m); 
  while (fgets(line,sizeof(int),stdin))
    { 
      strcat(str, line); 
    } 
  n = strlen(str); 
  husharray = HashFunction(array, m); 
  hushline = HashFunction(str, m); 
  printf("%d ", husharray); 
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
                if (array[k - i] != str[k]) 
                break; 
              } 
          } 
      hushline = (hushline - (str[i] % 3)) / 3 + ((str[m + i] % 3)*pow1); 
       } 
    return 0; 
 }
