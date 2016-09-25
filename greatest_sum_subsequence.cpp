

#include <stdio.h>


void find_gss(int r, int n)
{
	
	int i=0, j=0, best_i=0, best_j=0, max=0;
	int acc=0;
	int val = 0;

	for(j=0; j<n; j++) {
		scanf("%d", &val);	
		acc += val;
		if (acc > max || (acc == max && (j-i > best_j - best_i) )) {
			max = acc;
			best_i = i;
			best_j = j;
		}	
		if (acc < 0) {
			i = j+1;
			acc = 0;
		}			
	}

	if (max > 0)
		printf("The nicest part of the route %d is between stops %d and %d\n",r, best_i, best_j);
	else
		printf("Route %d has no nice parts\n", r);
}



int main(void) {


	int b,r,n;
	scanf("%d", &b);
	for(r=1; r<=b; r++)
		{
		scanf("%d", &n);
		find_gss(r, n);
		}
}
