#include <stdio.h>

int main() {
    int number = 10;
    int *p = &number;
    printf("%p\n", *p);
    printf("%p\n", p);

    return 0;
}
