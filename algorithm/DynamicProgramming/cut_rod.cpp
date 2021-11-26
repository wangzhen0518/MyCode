#include <iostream>

#define MIN -10

void cut_rod(int* p, int* r, int* s, int n) {
    int max;
    r[0] = 0;
    s[0] = 0;
    for (int i = 1; i <= n; i++) {
        max = MIN;
        for (int k = 1; k <= i; k++) {
            if (max < p[k] + r[i - k]) {
                max = p[k] + r[i - k];
                s[i] = k;
            }
        }
        r[i] = max;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    // waste a[0]
    int* p = new int[n + 1];
    int* r = new int[n + 1];
    int* s = new int[n + 1];

    for (int i = 1; i <= n; i++)
        scanf("%d", &p[i]);
    cut_rod(p, r, s, n);
    printf("i");
    for (int i = 0; i <= n; i++)
        printf("%4d", i);
    printf("\nr");
    for (int i = 0; i <= n; i++)
        printf("%4d", r[i]);
    printf("\ns");
    for (int i = 0; i <= n; i++)
        printf("%4d", s[i]);
    printf("\nsequence");
    int i = n;
    while (i != 0) {
        printf("%3d ", s[i]);
        i = i - s[i];
    }
    printf("\n");
    delete[] s;
    delete[] r;
    delete[] p;
}