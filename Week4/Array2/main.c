#include <stdio.h>
#include <string.h>

int my_strcmp(const char *s1, const char *s2) {
    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

char my_strcpy(char *dest, const char *src) {
    int i;
    for (i = 0; src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return *dest;
}

int main() {
    char s1[100] = "Hello";
    printf("s1_bef = %s \n", s1);
    char s2[100] = "Hello";
    char s3[100] = "Patrick";
    int result1 = my_strcmp(s1, s2);
    int result2 = my_strcpy(s1, s3);
    printf("s1_aft = %s \n", s1);
    if (result1 == 0) {
        printf("Two strings are equal\n");
    }
    else if (result1 < 0) {
        printf("First string less than the second\n");
    }
    else {
        printf("First string larger than the second\n");
    }
    return 0;
}

