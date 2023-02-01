#include<stdio.h>

struct internet{
    char name[10];
    int identity;
    int relationship[10];
};

char my_strcpy(char *dest, const char *src) {
    int i;
    for (i = 0; src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return *dest;
}

int my_strcmp(const char *s1, const char *s2) {
    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

int main(){
    struct internet library[10];
    int option,overflow,i,j,k,youridentity,friendidentity;
    overflow=1;
    char newname[10];
    char yourname[10];
    char friendname[10];
    for (i=0;i<10;i++){//initialize the relationship array for all users
        for (j=0;j<10;j++){
            library[i].relationship[j]=-1;
        }
    }

    while(1){//big loop to make the programm keeps running
        printf("1) Introduce new user.\n2) Introduce social relationship.\n3) Print friends' names of a given user. \n4) Exit.\n");
        scanf("%d",&option);

        if (option==1){
            printf("Give me a user name\n");
            scanf("%s",newname);
            my_strcpy(library[overflow].name,newname);
            library[overflow].identity=overflow;
            printf("Your user identity is ");
            printf("%d\n",overflow);
            overflow++;//overflow makes the next name added to next position
        }

        if (option==2){
            printf("type in name 1\n");
            scanf("%s",yourname);
            printf("type in name 2\n");
            scanf("%s",friendname);

            for (i=0;i<10;i++){//browse your name by identity
                if (my_strcmp(yourname,library[i].name)==0){
                    youridentity=library[i].identity;
                    break;
                }
            }

            for (j=0;j<10;j++){//browse friend's name by identity
                if (my_strcmp(friendname,library[j].name)==0){
                    friendidentity=library[j].identity;
                    break;
                }
            }

            for (k=0;k<10;k++){//add relationship
                if (library[youridentity].relationship[k]==-1){
                    library[youridentity].relationship[k]=friendidentity;
                    break;
                }
            }
        }

        if (option==3){
            printf("type in your name\n");
            scanf("%s",yourname);
            for (i=0;i<10;i++){
                if (my_strcmp(yourname,library[i].name)==0){
                    youridentity=library[i].identity;
                    break;
                }
            }
            for (j=0;j<10;j++){//scan every relationship array to find the same value
                if (library[youridentity].relationship[j]!=-1){//not default value so not equal to -1
                    friendidentity=library[youridentity].relationship[j];
                    my_strcpy(newname,library[friendidentity].name);
                    printf("%s \n",newname);
                }
                else{
                    break;
                }
            }
        }
        if (option==4){
            return 0;
        }
    }
}
