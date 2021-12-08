#include <stdio.h>

void quick_sort(int a[], int l, int r) {
    if (l < r) {
        int i, j, x;

        i = l;
        j = r;
        x = a[i];
        while (i < j) {
            while (i < j && a[j] > x)
                j--; // 从右向左找第一个小于x的数
            if (i < j)
                a[i++] = a[j];
            while (i < j && a[i] < x)
                i++; // 从左向右找第一个大于x的数
            if (i < j)
                a[j--] = a[i];
        }
        a[i] = x;
        quick_sort(a, l, i - 1);
        quick_sort(a, i + 1, r);
    }
}

int main() {
    int i;
    int len;
    printf("set length of array:");
    scanf("%d", &len);
    int a[len];
    for (int j = 0; j < len; ++j) {
        printf("a[%d]:", j);
        scanf("%d", &a[j]);
    }
    //输出sort前的数组
    printf("before sort:");
    for (i = 0; i < len; i++)
        printf("%d ", a[i]);
    printf("\n");

    quick_sort(a, 0, len - 1);
    //输出sort后的数组
    printf("after  sort:");
    for (i = 0; i < len; i++)
        printf("%d ", a[i]);
    printf("\n");
}