#include <stdio.h>
#include <string.h>

struct socialnetwork
{
    char name[10];
    int uuid;
    int relation[10];
} library[10];

int main() {
    struct socialnetwork library[10];//asscessing a position of memory
    char relation[10];
    int option;
    int input2;
    char name1[10];
    char name2[10];
    int uuid1;
    int uuid2;
    char input1[10];
    input2 = 3;
    int i, j, k;
    memset(library, -1, 10);
    memset(relation, -1, 10);


    for (i = 0; i <= 10; i++) {
        for (j = 0; j <= 10; j++) {
            library[i].relation[j] = -1;
        }
    }

    strcpy(library[1].name, "john");
    strcpy(library[1].name, "mike");
    library[1].uuid = 1;
    library[1].relation[0] = 2;
    library[2].uuid = 2;
    library[2].relation[0] = 1;
    while (1) {
        printf("1.Introduce new user.\n2.Introduce social relationship.\n3.Print friends' names of a given user.\n4.exit.\n");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("what is your name\n");
                scanf("%s", input1);

                strcpy(library[input2].name, input1);
                library[input2].uuid = input2;
                printf("uuid is %d\n", input2);
                input2++;
                break;
            case 2:
                printf("give me two names\n");
                scanf("%s%s", name1, name2);
                for (i = 0; i <= 20; i++) {

                    if (strcmp(name1, library[i].name) == 0) {
                        library[i].uuid = uuid1;
                        break;
                    }
                }
                for (j = 0; j <= 20; j++) {

                    if (strcmp(name2, library[j].name) == 0) {
                        library[j].uuid = uuid2;
                        break;
                    }
                }
                for (k = 0; k <= 20; k++) {           //add your friend's id to your relationship
                    if (library[uuid1].relation[k] == -1) {
                        library[uuid2].relation[k] = uuid2;
                        break;
                    }
                }
                break;
            case 3:
                printf("What is your name?\n");
                scanf("%s", name1);
                for (i = 0; i <= 20; i++) {
                    if (strcmp(name1, library[i].name) == 0) {
                        library[i].uuid = uuid1;
                        break;
                    }
                }
                printf("your friends are:\n");
                for (j = 0; j <= 20; j++) {
                    if (library[uuid1].relation[j] != -1) {
                        printf("%s\n", library[library[uuid1].relation[j]].name);
                    }
                }
                break;
            case 4:
                return 0;
        }
    }
}
