#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _bt {
  int val;
  int lcounter;
  int rcounter;
  struct _bt *left;
  struct _bt *right;
} binary_tree;

binary_tree *new_binary_tree(int val) {
  binary_tree *b = (binary_tree *)malloc(sizeof(binary_tree));
  b->lcounter = 0;
  b->rcounter = 0;
  b->left = NULL;
  b->right = NULL;
  b->val = val;
  return b;
}

binary_tree *balance(binary_tree *a) {
  if (!a) return a;
  if (abs(a->lcounter - a->rcounter) <= 1) return a;

  if (a->lcounter > a->rcounter) {
    binary_tree *b = a->left;  /* has to exist */
    binary_tree *c = b->right; /* has to exist */
    binary_tree *d = b->left;  /* may not exist */
    binary_tree *e = b->right; /* may not exist */

    a->left = e;
    a->lcounter = getnnodes(e);
    b->right = a;
    b->rcounter = getnnodes(a);
    b->lcounter = getnnodes(d);

    return b;
  } else {
    binary_tree *b = a->right; /* has to exist */
    binary_tree *c = b->left;  /* has to exist */
    binary_tree *d = b->right; /* may not exist */
    binary_tree *e = b->left;  /* may not exist */

    a->right = e;
    a->rcounter = getnnodes(e);
    b->left = a;
    b->lcounter = getnnodes(a);
    b->rcounter = getnnodes(d);

    return b;
  }
}

binary_tree *insert(binary_tree *b, int val) {
  if (val <= b->val) {
    if (b->left) {
      b->left = insert(b->left, val);
    } else
      b->left = new_binary_tree(val);
    b->lcounter++;
  } else {
    if (b->right) {
      b->right = insert(b->right, val);
    } else
      b->right = new_binary_tree(val);
    b->rcounter++;
  }
  return balance(b);
}

int getnnodes(binary_tree *b) {
  if (!b) return 0;
  return 1 + b->lcounter + b->rcounter;
}

int getnbigger(binary_tree *b, int val) {
  if (!b) return 0;

  if (val < b->val) {
    return (b->rcounter + 1 + getnbigger(b->left, val));
  }

  return getnbigger(b->right, val);
}

void clean(binary_tree *b) {
  if (b) {
    clean(b->left);
    clean(b->right);
    free(b);
  }
}
