#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char name[50];
    char **friends;
    int num_friends;
    struct node *next;
};
typedef struct node Node;

Node *head = NULL;

void introduce_user() {
    Node *temp, *prev, *aft;
    temp = (Node *)malloc(sizeof(Node));
    if (temp == NULL) {
        printf("Out of memory.\n");
        return;
    }
    printf("Enter name: ");
    scanf("%s", temp->name);
    temp->friends = (char **)malloc(10 * sizeof(char *));
    if (temp->friends == NULL) {
        printf("Out of memory.\n");
        free(temp);
        return;
    }
    temp->num_friends = 0;
    if (head == NULL || strcmp(head->name, temp->name) > 0) {
        temp->next = head;
        head = temp;
    } else {
        prev = head;
        aft = head->next;
        while (aft != NULL && strcmp(aft->name, temp->name) < 0) {
            prev = aft;
            aft = aft->next;
        }
        prev->next = temp;
        temp->next = aft;
    }
    printf("%s has been added to the list.\n", temp->name);
}

void introduce_resolution() {
    char name[50], friend_name[50];
    int i, num;
    Node *aft;
    printf("Enter name of user: ");
    scanf("%s", name);
    aft = head;
    while (aft != NULL && strcmp(aft->name, name) != 0) {
        aft = aft->next;
    }
    if (aft == NULL) {
        printf("%s not found in the list.\n", name);
        return;
    }
    printf("Enter number of friends: ");
    scanf("%d", &num);
    for (i = 0; i < num; i++) {
        printf("Enter name of friend %d: ", i + 1);
        scanf("%s", friend_name);
        aft->friends[i] = (char *)malloc((strlen(friend_name) + 1) * sizeof(char));
        if (aft->friends[i] == NULL) {
            printf("Out of memory.\n");
            return;
        }
        strcpy(aft->friends[i], friend_name);
    }
    aft->num_friends = num;
    printf("Resolution added for %s.\n", name);
}

void remove_user() {
    char name[50];
    Node *prev, *aft;
    printf("Enter name: ");
    scanf("%s", name);
    prev = NULL;
    aft = head;
    while (aft != NULL && strcmp(aft->name, name) != 0) {
        prev = aft;
        aft = aft->next;
    }
    if (aft == NULL) {
        printf("%s not found.\n", name);
        return;
    }
    if (prev == NULL) {
        head = aft->next;
    } else {
        prev->next = aft->next;
    }
    printf("%s has been removed.\n", name);
    free(aft->friends);
    free(aft);
}

void print_friends() {
    char name[50];
    int i;
    Node *aft;
    printf("Enter name: ");
    scanf("%s", name);
    aft = head;
    while (aft != NULL && strcmp(aft->name, name) != 0) {
        aft = aft->next;
    }
    if (aft == NULL) {
        printf("%s not found.\n", name);
        return;
    }
    printf("%s's friends: ", name);
    for (i = 0; i < aft->num_friends; i++) {
        printf("%s ", aft->friends[i]);
    }
    printf("\n");
}

void save_to_file() {
    char filename[50];
    FILE *fp;
    Node *aft;
    printf("Enter filename: ");
    scanf("%s", filename);
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    aft = head;
    while (aft != NULL) {
        fprintf(fp, "%s %d\n", aft->name, aft->num_friends);
        int i;
        for (i = 0; i < aft->num_friends; i++) {
            fprintf(fp, "%s ", aft->friends[i]);
        }
        fprintf(fp, "\n");
        aft = aft->next;
    }
    fclose(fp);
    printf("Data saved to file.\n");
}

void retrieve_from_file() {
    char filename[50], name[50], friend_name[50];
    int i, num_friends;
    FILE *fp;
    Node *temp, *prev, *aft;
    printf("Enter filename: ");
    scanf("%s", filename);
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    while (fscanf(fp, "%s %d", name, &num_friends) != EOF) {
        temp = (Node *)malloc(sizeof(Node));
        if (temp == NULL) {
            printf("Out of memory.\n");
            fclose(fp);
            return;
        }
        strcpy(temp->name, name);
        temp->friends = (char **)malloc(10 * sizeof(char *));
        if (temp->friends == NULL) {
            printf("Out of memory.\n");
            fclose(fp);
            free(temp);
            return;
        }
        for (i = 0; i < num_friends; i++) {
            fscanf(fp, "%s", friend_name);
            temp->friends[i] = (char *)malloc((strlen(friend_name) + 1) * sizeof(char));
            if (temp->friends[i] == NULL) {
                printf("Out of memory.\n");
                fclose(fp);
                free(temp->friends);
                int j;
                for (j = 0; j < i; j++) {
                    free(temp->friends[j]);
                }
                free(temp->friends);
                free(temp);
                return;
            }
            strcpy(temp->friends[i], friend_name);
        }
        temp->num_friends = num_friends;
        temp->next = NULL;
        prev = NULL;
        aft = head;
        while (aft != NULL && strcmp(aft->name, name) < 0) {
            prev = aft;
            aft = aft->next;
        }
        if (prev == NULL) {
            head = temp;
        } else {
            prev->next = temp;
        }
        temp->next = aft;
    }
    fclose(fp);
    printf("Data retrieved from file.\n");
}

int main() {
    int choice;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Introduce user\n");
        printf("2. Introduce new resolution\n");
        printf("3. Remove user\n");
        printf("4. Print a given person's friends\n");
        printf("5. Save to file\n");
        printf("6. Retrieve data from file\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                introduce_user();
                break;
            case 2:
                introduce_resolution();
                break;
            case 3:
                remove_user();
                break;
            case 4:
                print_friends();
                break;
            case 5:
                save_to_file();
                break;
            case 6:
                retrieve_from_file();
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

