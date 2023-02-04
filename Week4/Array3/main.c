#include <stdio.h>

struct User {    // Structure to store user information.
    char name[30];
    int num_relation;
    int relation[20];
};

struct User users[50];    // Array to store users.
int user_count = 0;    // Number of users, used to add new user.

char my_strcpy(char *dest, const char *src) {   // Function to copy strings, using in case 1.
    int i;
    for (i = 0; src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return *dest;
}

int my_strcmp(const char *s1, const char *s2) {   // Function to compare strings, using in case 1 and 2.
    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

void add_user(char* name) {    // Function to add user, using in case 1.
    my_strcpy(users[user_count].name, name);    // Copy name to users[user_count].name
    user_count++;
    if (user_count == 50) {
        printf("Error: Maximum number of users reached.\n");    // If user_count is 50, return error.
    }
}

int find_user(const char *name) {    // Function to find user, using in case 2 and 3.
    for (int i = 0; i < user_count; i++) {
        if (my_strcmp(users[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void add_relation(const char *name1, const char *name2) {
    int user1 = find_user(name1);
    int user2 = find_user(name2);

    if (user1 == -1 || user2 == -1) {    // If either user1 or user2 is not found, return error.
        printf("Error: One or both users not found.\n");
        return;
    }

    users[user1].relation[users[user1].num_relation++] = user2;    // Add relationship to user1
    users[user2].relation[users[user2].num_relation++] = user1;    // Add relationship to user2
}

void print_friends(const char *name) {    // Function to print friends, using in case 3.
    int user = find_user(name);

    if (user == -1) {    // If user is not found, return error.
        printf("Error: User not found.\n");
        return;
    }

    printf("%s's friends:\n", users[user].name);    // Print friends' names.
    for (int i = 0; i < users[user].num_relation; i++) {
        printf("%s\n", users[users[user].relation[i]].name);
    }
}

int main() {
    int choice;    // User's choice.
    char name1[30], name2[30];    // Names of users.

    while (1) {   // Infinite loop, until user enters 4.
        printf("1) Introduce new user\n");
        printf("2) Introduce social relationship\n");
        printf("3) Print friends' names of a given user\n");
        printf("4) Exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:    // Add user.
                printf("Enter user name: ");
                scanf("%s", name1);
                add_user(name1);
                printf("The user id is %d\n", user_count);
                break;
            case 2:    // Add relationship.
                printf("Enter first user name: ");
                scanf("%s", name1);
                printf("Enter second user name: ");
                scanf("%s", name2);

                if (my_strcmp(name1, name2) == 0) {    // If two names are the same, return error.
                    printf("You cannot be friends with yourself\n");
                    break;
                }
                else {
                    printf("Relationship added\n");
                    add_relation(name1, name2);
                }
                break;
            case 3:    // Print friends.
                printf("Enter user name: ");
                scanf("%s", name1);
                print_friends(name1);
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice, please re-enter\n");    // For invalid choice, return error.
        }
    }
}


