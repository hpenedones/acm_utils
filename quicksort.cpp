#include <iostream>

using namespace std;

void qsort(int v[], int start, int end) {
  int pivot = v[(start + end) / 2];
  int i = start, j = end;

  while (i <= j) {
    while (v[i] < pivot) i++;
    while (v[j] > pivot) j--;

    if (i <= j) {
      int tmp = v[i];
      v[i] = v[j];
      v[j] = tmp;
      i++;
      j--;
    }
  }

  if (start < j) qsort(v, start, j);
  if (i < end) qsort(v, i, end);
}

int main(int argc, const char *argv[]) {
  int n = 12;
  int set[] = {3, 1, 6, 7, 23, 72, 722, 61, 66, -1, 0, 333};

  qsort(set, 0, n - 1);

  for (int i = 0; i < n; i++) {
    cout << set[i] << endl;
  }

  return 0;
}
