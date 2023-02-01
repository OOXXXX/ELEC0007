#include <stdio.h>
#include <string.h>

int my_strcpy(char *t, const char *s) {
    char *temp;
    temp=t;
    while(*s!='\0')
    {
        *t=*s;
        s++;
        t++;
    }
    *t='\0';
    return temp;
}

int my_strcmp(const char *s1, const char *s2) {
    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

int main()
{
    int result;
    char string1[1024] = "Patrick"; // Src
    char string2[1024] = "Tony";  // Dest
    printf("str1 = %s \n", string1);
    printf("str2 = %s \n", string2);

    result = my_strcmp(string1, string2);
    if (result == 0){
        printf("The two strings are identical\n");
    }
    else{
        printf("The two strings are not identical\n");
    }

    my_strcpy(string1, string2);

    printf("str1_aft = %s \n", string1); // String1 after my_strcpy
    printf("str2_aft = %s \n", string2); // String2 after my_strcpy

    result = my_strcmp(string1, string2);
    if (result == 0){
        printf("The two strings are identical\n");
    }
    else{
        printf("The two strings are not identical\n");
    }

    return 0;
}
