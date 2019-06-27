#include <stdio.h>
int main(){
  int a = 3;
  float b = 2.3;
  a/b;
  a = a/b;
  b = 2+a;
  printf("%d\t%f",a,b);
}