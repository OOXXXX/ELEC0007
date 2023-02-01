#include <stdio.h>

struct User {
    char name[30];
    int id;
    int friends[20];
    int friends_count;
};

struct User users[50];
int user_count = 0;

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

void add_user(char* name) {
    my_strcpy(users[user_count].name, name);
    users[user_count].id = user_count;
    users[user_count].friends_count = 0;
    user_count++;
}

void add_relation(char* name1, char* name2) {
    int i, j, user1_number, user2_number;
    for (i = 0; i < user_count; i++) {
        if (my_strcmp(users[i].name, name1) == 0) {
            user1_number = i;
            break;
        }
    }
    for (j = 0; j < user_count; j++) {
        if (my_strcmp(users[j].name, name2) == 0) {
            user2_number = j;
            break;
        }
    }
    users[user1_number].friends[users[user1_number].friends_count] = user2_number;
    users[user1_number].friends_count++;
    users[user2_number].friends[users[user2_number].friends_count] = user1_number;
    users[user2_number].friends_count++;
}

void print_friends(char* name) {
    int i, j, user_number;
    for (i = 0; i < user_count; i++) {
        if (my_strcmp(users[i].name, name) == 0) {
            user_number = i;
            break;
        }
    }
    printf("%s's friends: \n", name);
    for (j = 0; j < users[user_number].friends_count; j++) {
        printf("%s\n", users[users[user_number].friends[j]].name);
    }
}

int main() {
    int choice;
    char name1[30], name2[30];

    while (1) {
        printf("1) Introduce new user\n");
        printf("2) Introduce social relationship\n");
        printf("3) Print friends' names\n");
        printf("4) Exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter user name: ");
                scanf("%s", name1);
                add_user(name1);
                printf("The user id is %d\n", user_count);
                break;
            case 2:
                printf("Enter first user name: ");
                scanf("%s", name1);
                printf("Enter second user name: ");
                scanf("%s", name2);

                if (my_strcmp(name1, name2) == 0) {
                    printf("You cannot be friends with yourself\n");
                    break;
                }
                else {
                    printf("Relationship added\n");
                    add_relation(name1, name2);
                }
                break;
            case 3:
                printf("Enter user name: ");
                scanf("%s", name1);
                print_friends(name1);
                break;
            case 4:
                return 0;
        }
    }
}
