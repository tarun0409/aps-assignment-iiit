#include<stdio.h>
#include<stdlib.h>
int main()
{
  FILE * fw;
  fw = fopen("data10.txt","w+");
  int n= 10;
  for(int i=0; i<n; i++)
  {
    int r = rand();
    fprintf(fw,"%d",r);
    if(i!=(n-1))
    {
      fprintf(fw," ");
    }
  }
  return 0;
}
