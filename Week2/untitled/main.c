#include <stdio.h>

float average(float num1, float num2, float num3) {
    return (num1 + num2 + num3) / 3;
}

double pi(int result) {
    double pi = 0.0;
    int i;
    for (i = 0; i < result; i++) {
        pi += ((i % 2) ? -1 : 1) * 4.0 / (2.0 * i + 1.0);
    }
    return pi;
}

int square_root(int num) {
    int i;
    for(i=0; i*i<=num; i++)
    {
        if(i*i==num)
            return i;
    }
    return -1;
}

int main() {
    int option;
    float num1, num2, num3;
    int precision, num;
    while (1) {
        printf("Type option:\n");
        printf("1: Average\n");
        printf("2: Calculate the nth iteration of the Gregory-Leibniz series\n");
        printf("3: Square root\n");
        printf("4: Exit\n");

        scanf("%d", &option);
        if (option == 1) {
            printf("Enter three numbers: ");
            scanf("%f %f %f", &num1, &num2, &num3);
            printf("The average of %f, %f, and %f is %f\n", num1, num2, num3, average(num1, num2, num3));
        }
        else if (option == 2) {
            printf("Enter the nth number: ");
            scanf("%d", &precision);
            printf("PI to precision %d is %f\n", precision, pi(precision));
        }
        else if (option == 3) {
            printf("Enter an integer: ");
            scanf("%d", &num);
            int result = square_root(num);
            printf("The square root of %d is %d\n", num, result);
        }
        else if (option == 4) {
            break;
        }
        else {
            printf("Invalid option.\n");
        }
    }
    return 0;
}

