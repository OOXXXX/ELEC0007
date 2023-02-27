#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person {
    char name[50];
    struct Person *next;
} Person;

Person *head = NULL;

void insertPerson(char name[]);
void removePerson(char name[]);
void introduceFriend(char name[], char friend[]);
void removeFriend(char name[], char friend[]);
void printFriends(char name[]);
void saveToFile(char filename[]);
void retrieveFromFile(char filename[]);

int main() {
    int choice;
    char name[50], friend[50], filename[100];

    while (1) {
        printf("\nMenu:\n");
        printf("1) Introduce user\n");
        printf("2) Introduce new resolution\n");
        printf("3) Remove user\n");
        printf("4) Print a given person's friends\n");
        printf("5) Save to file\n");
        printf("6) Retrieve data from file\n");
        printf("7) Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter name of person to introduce: ");
                scanf("%s", name);
                insertPerson(name);
                break;
            case 2:
                printf("Enter name of person to introduce resolution for: ");
                scanf("%s", name);
                printf("Enter new resolution: ");
                scanf("%s", friend);
                introduceFriend(name, friend);
                break;
            case 3:
                printf("Enter name of person to remove: ");
                scanf("%s", name);
                removePerson(name);
                break;
            case 4:
                printf("Enter name of person to print friends for: ");
                scanf("%s", name);
                printFriends(name);
                break;
            case 5:
                printf("Enter filename to save to: ");
                scanf("%s", filename);
                saveToFile(filename);
                break;
            case 6:
                printf("Enter filename to retrieve from: ");
                scanf("%s", filename);
                retrieveFromFile(filename);
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
}

void insertPerson(char name[]) {
    Person *newPerson = (Person*)malloc(sizeof(Person));
    strcpy(newPerson->name, name);
    newPerson->next = NULL;

    if (head == NULL || strcmp(name, head->name) < 0) {
        newPerson->next = head;
        head = newPerson;
    } else {
        Person *current = head;
        while (current->next != NULL && strcmp(name, current->next->name) > 0) {
            current = current->next;
        }
        newPerson->next = current->next;
        current->next = newPerson;
    }

    printf("Successfully introduced %s\n", name);
}

void removePerson(char name[]) {
    if (head == NULL) {
        printf("Error: List is empty.\n");
        return;
    }

    Person *current = head;
    Person *prev = NULL;
    while (current != NULL && strcmp(name, current->name) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("%s not found.\n", name);
    } else {
        if (prev == NULL) {
            head = current->next;
        } else {
            prev->next = current->next;
        }
        printf("Successfully removed %s\n", name);
        free(current);
    }
}

void introduceFriend(char name[], char friend[]) {
    Person *current = head;
    while (current != NULL && strcmp(name, current->name) != 0) {
        current = current->next;
    }

    if (current == NULL) {
        printf("%s not found.\n", name);
    } else {
        int numFriends = strlen(friend) + 1;
        if (current->next == NULL) {
            current->next = (Person*)malloc(sizeof(Person));
            strcpy(current->next->name, friend);
            current->next->next = NULL;
        } else {
            int i;
            for (i = 0; i < numFriends; i++) {
                current->next = (Person*)realloc(current->next, sizeof(Person) + (i+1)*sizeof(char));
                current->next->name[i] = friend[i];
            }
            current->next->next = NULL;
        }
        printf("Successfully introduced resolution for %s: %s\n", name, friend);
    }
}

void removeFriend(char name[], char friend[]) {
    // implementation omitted for brevity
}

void printFriends(char name[]) {
    Person *current = head;
    while (current != NULL && strcmp(name, current->name) != 0) {
        current = current->next;
    }

    if (current == NULL) {
        printf("%s not found.\n", name);
    } else {
        printf("%s's friends: ", name);
        if (current->next == NULL) {
            printf("None\n");
        } else {
            Person *friendList = current->next;
            while (friendList != NULL) {
                printf("%s ", friendList->name);
                friendList = friendList->next;
            }
            printf("\n");
        }
    }
}

void saveToFile(char filename[]) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file %s.\n", filename);
        return;
    }

    Person *current = head;
    while (current != NULL) {
        fprintf(fp, "%s", current->name);
        if (current->next != NULL) {
            fprintf(fp, ":");
            Person *friendList = current->next;
            while (friendList != NULL) {
                fprintf(fp, "%s", friendList->name);
                if (friendList->next != NULL) {
                    fprintf(fp, ",");
                }
                friendList = friendList->next;
            }
        }
        fprintf(fp, "\n");
        current = current->next;
    }

    fclose(fp);
    printf("Successfully saved to file %s\n", filename);
}

void retrieveFromFile(char filename[]) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file %s.\n", filename);
        return;
    }

    char line[150];
    while (fgets(line, 150, fp) != NULL) {
        char *token = strtok(line, ":");
        char name[50];
        strcpy(name, token);
        insertPerson(name);

        token = strtok(NULL, ":");
        if (token != NULL) {
            char *friendToken = strtok(token, ",");
            while (friendToken != NULL) {
                introduceFriend(name, friendToken);
                friendToken = strtok(NULL, ",");
            }
        }
    }

    fclose(fp);
    printf("Successfully retrieved data from file %s\n", filename);
}




