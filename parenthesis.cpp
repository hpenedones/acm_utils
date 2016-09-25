
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;


void print_parenthesis(string curr_str, int left, int right, int maxp)
{

	if (left == maxp && right == maxp) {
		cout << curr_str << endl;
		return;
	}

	if (left < maxp) {
		print_parenthesis(curr_str + "(", left+1, right, maxp);
	}
	if (right < left) {
		print_parenthesis(curr_str + ")", left, right+1, maxp);
	}
	
}



int main(int argc, char ** argv)
{
	int n = atoi(argv[1]);
	
	print_parenthesis("", 0, 0, n);


}
