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
  char str[100] = { 0 }; 
  gets_s(str); 
  int j, k, t = strlen(pattern), len = strlen(str); 
  if ((len == 0) || (t == 0)) 
  exit(0); 
  if (len < t) 
  printf("%d ", t); 
  for (k = t; k <= len; ) 
 { 
   printf("%d ", k + i); 
   if (pattern[t - 1] == str[k - 1]) 
  { 
    for (j = t - 2; ( (j >= 0) && pattern[j] == str[k - t + j]); j--) 
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
     k += shift[str[k - 1] + 128]; 
  } 
 } 
 i += t; 
 pos(pattern, i); 
}  
int main(void) 
{ 
 char pattern[100]; 
 gets_s(pattern); 
 table(pattern); 
 pos(pattern, 0); 
 return 0; 
}
