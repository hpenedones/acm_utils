#include <stdio.h>

int primes[80000]; /* enough to store primes up 1 million */
int nprimes;

void find_primes_smaller_than(int n) {
  primes[0] = 2;
  nprimes = 1;
  int i;
  for (i = 3; i <= n; i += 2) {
    int j;
    int isprime = 1;
    for (j = 0; primes[j] * primes[j] <= i; j++) {
      if (i % primes[j] == 0) {
        isprime = 0;
        break;
      }
    }
    if (isprime) {
      primes[nprimes++] = i;
    }
  }
}
