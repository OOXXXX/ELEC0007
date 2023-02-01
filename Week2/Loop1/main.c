#include <stdio.h>

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int k = n-i; k >= 1; k--) {
            printf(" ");
        }
        for (int s = 1; s <= 2*i-1; s++) {
            printf("*");
        }
        printf("\n");
    }
    for (int i = n-1; i >= 1; i--) {
        for (int k = 1; k <= n-i; k++) {
            printf(" ");
        }
        for (int s = 2*i-1; s >= 1; s--) {
            printf("*");
        }
        printf("\n");
    }
    return 0;
}



