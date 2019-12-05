#include <stdio.h> 
  
int x = 10; 
int z = 5; 
  
int main() 
{ 
  
    extern int y; // line 2 
    extern int z; 
    printf("%d %d %d", x, y, z); 
} 
  
int y = 2; 
