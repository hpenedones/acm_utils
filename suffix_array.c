#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 100001
#define LOG2_MAXLEN 18

typedef struct _triple {
  int a, b, p;
} triple;

int suffix_array[LOG2_MAXLEN][MAXLEN];
triple L[MAXLEN];

int cmp_int(int a, int b) {
  if (a == b) return 0;
  return (a < b ? -1 : 1);
}

int cmp(const void *m, const void *n) {
  triple *M = (triple *)m;
  triple *N = (triple *)n;
  if (M->a == N->a) {
    return cmp_int(M->b, N->b);
  }
  return cmp_int(M->a, N->a);
}

void construct_suffix_array(const char *text, int len, int depth) {
  int i;
  for (i = 0; i < len; i++) {
    assert(isalpha(text[i]) && islower(text[i]));
    suffix_array[0][i] = text[i] - ' ' + 1;
  }
  int k, cnt;
  for (cnt = 1, k = 1; k <= depth; k++, cnt *= 2) {
    for (i = 0; i < len; i++) {
      L[i].a = suffix_array[k - 1][i];
      L[i].b = (i + cnt < len) ? suffix_array[k - 1][i + cnt] : -1;
      L[i].p = i;
    }
    qsort(L, len, sizeof(triple), cmp);
    for (i = 0; i < len; i++) {
      if (i > 0 && cmp(&L[i - 1], &L[i]) == 0)
        suffix_array[k][L[i].p] = suffix_array[k][L[i - 1].p];
      else
        suffix_array[k][L[i].p] = i;
    }
  }
}

void print_suffix_array(const char *text, int len, int depth, int show_string) {
  int i;
  int ptrs[len];
  for (i = 0; i < len; i++) {
    ptrs[suffix_array[depth][i]] = i;
  }
  for (i = 0; i < len; i++) {
    if (show_string)
      printf("%d %s\n", ptrs[i], &text[ptrs[i]]);
    else
      printf("%d\n", ptrs[i]);
  }
}

void debug_suffix_array(const char *text, int len, int depth) {
  int i;
  for (i = 0; i < len; i++) {
    printf("%d %d\n", i, suffix_array[depth][i]);
  }
}

int longest_common_prefix(int x, int y, int len, int depth) {
  int k, ret = 0;
  if (x == y) return len - x;
  for (k = depth; k >= 0 && x < len && y < len; k--) {
    if (suffix_array[k][x] == suffix_array[k][y])
      x += (1 << k), y += (1 << k), ret += (1 << k);
  }

  return ret;
}

int main(int argc, const char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <lowercase-string-without-spaces>\n", argv[0]);
    return 1;
  }
  const char *text = argv[1];
  int len = strlen(text);
  int depth = ceil(log(len) / log(2));

  construct_suffix_array(text, len, depth);
  int j;
  for (j = 0; j <= depth; j++) {
    debug_suffix_array(text, len, j);
    puts("----------------------------");
  }

  int a, b;
  while (scanf("%d%d\n", &a, &b) == 2) {
    printf("lcp = %d\n", longest_common_prefix(a, b, len, depth));
  }

  return 0;
}
