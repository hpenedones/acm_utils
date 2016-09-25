#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


/* assumes that v is sorted */
int binsearch(int * v, int n, int val)
{

  int i=-1, j=n-1, h;

  while(i +1< j) {
        h = i + (j-i)/2;
        if (v[h] >= val)
                j = h;
        else
                i = h;       
  }

  if (v[j] == val)
        return j;        
  return -1;
}


int cmp(const void * a, const void * b) {
     return (*(int*)a) > (*(int*)b);
}


int main(int argc, char * argv[]) {
        
  /*      srand(time(NULL)); */ 

        int size = 20;
        int v[size];

        int i;
        for(i=0;i<size;i++) {
            v[i] = rand() % 100;
        }

        qsort(v, size, sizeof(int), cmp); 

        int index = binsearch(v, size, atoi(argv[1]));

        for(i=0;i<size;i++) {
            char c = i==index ? '-' : ' ';
            printf("%c %d %d\n",c, i,  v[i]);
        }




        return 0;
}
