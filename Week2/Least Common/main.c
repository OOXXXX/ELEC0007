#include <stdio.h>

int main() {
    int a , b, temp, i;
    printf("Input a & b:");
    scanf("%d %d", &a, &b);
    if(a){
        temp = a;
        a = b;
        b = temp;
    }
    for(i=a; i>0; i++)
        if(i%a == 0 && i%b == 0)
        {
            printf("The lowest common multiple of %d and %d is: %d\n", a,b,i);
            break;
        }
    return 0;
}
