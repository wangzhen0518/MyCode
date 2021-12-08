#include <iostream>

int cut_rod(int *value, int *r, int *s, int n) {
  r[1] = value[1];
  s[1] = 1;
  s[0] = 0;
  for (int i = 2; i <= n; i++) {
    int max = value[i];
    for (int j = 1; j <= i; j++)
      if (value[i - j] + r[j] > max) {
        max = value[i - j] + r[j];
        s[i] = j;
      }
    r[i] = max;
  }
  return r[n];
}

int main() {
  int n;
  scanf("%d", &n);
  int *value = new int[n + 1]{0};
  int *r = new int[n + 1]{0};
  int *s = new int[n + 1]{0};
  for (int i = 1; i < n + 1; i++) scanf("%d", &value[i]);

  cut_rod(value, r, s, n);

  printf("%4c", 'i');
  for (int i = 0; i <= n; i++) printf("%4d", i);
  printf("\n%4c", 'r');
  for (int i = 0; i <= n; i++) printf("%4d", r[i]);
  printf("\n%4c", 's');
  for (int i = 0; i <= n; i++) printf("%4d", s[i]);

  printf("\nmax value: ");
  int i = n;
  while (i != 0) {
    printf("%4d", i - s[i]);
    i = s[i];
  }
  printf("\n");
  delete[] s;
  delete[] r;
  delete[] value;
  return 0;
}