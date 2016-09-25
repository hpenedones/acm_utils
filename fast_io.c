#include <stdio.h>
#include <string.h>

/* assumes that the next token is indeed an integer (possibly negative)
 however there might be whitespace before (even tolerates some trash...) */
int read_int(int * n) {

	int sign =1, acc=0;
	char c = getchar();
	if (c == EOF) return 0;	

	while ( c!='-' && !(c >= '0' && c <= '9'))
		{
		c = getchar();
		if (c == EOF) return 0;	
		}

	if (c == '-') {
		sign=-1;
		c = getchar(); /* assumes that after the minus sign, we will find a digit */
		if (c == EOF) return 0;	
	}

	while (c >= '0' && c <= '9') {
		acc = acc * 10 + (c-'0');
		c = getchar();
	}

	if (acc >= 0)
	 {
		*n = sign*acc;
		return 1;
	}
	return 0;
}
 /* assumes that the next token is a strictly positive integer ( n > 0 )
 however there might be whitespace before (even tolerates some trash...) */
int read_pos_int(int * n) {

	*n=0;
	char c;

	do {
		c = getchar();
		if (c == EOF) return 0;	
	
	} while ( c < '0' || c > '9');
		

	while (c >= '0' && c <= '9') {
		*n = *n * 10 + (c-'0');
		c = getchar();
	}

	
	return 1;
}
    

void print_pos_int(int n) {

	if (n == 0)
		return;

	print_pos_int(n/10);
	putchar('0' + n%10);

}



