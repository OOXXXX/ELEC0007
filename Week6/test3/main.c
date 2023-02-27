#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char name[50];
    char **friends;
    int num_friends;
    struct node *next;
} Node;

Node *head = NULL;

void introduce_user();
void introduce_resolution();
void remove_user();
void print_friends();
void save_to_file();
void retrieve_from_file();


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

void introduce_user() {
    Node *temp, *prev, *cur;
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
        cur = head->next;
        while (cur != NULL && strcmp(cur->name, temp->name) < 0) {
            prev = cur;
            cur = cur->next;
        }
        prev->next = temp;
        temp->next = cur;
    }
    printf("%s has been added to the list.\n", temp->name);
}

void introduce_resolution() {
    char name[50], friend_name[50];
    int i, num;
    Node *cur;
    printf("Enter name of user: ");
    scanf("%s", name);
    cur = head;
    while (cur != NULL && strcmp(cur->name, name) != 0) {
        cur = cur->next;
    }
    if (cur == NULL) {
        printf("%s not found in the list.\n", name);
        return;
    }
    printf("Enter number of friends: ");
    scanf("%d", &num);
    for (i = 0; i < num; i++) {
        printf("Enter name of friend %d: ", i + 1);
        scanf("%s", friend_name);
        cur->friends[i] = (char *)malloc((strlen(friend_name) + 1) * sizeof(char));
        if (cur->friends[i] == NULL) {
            printf("Out of memory.\n");
            return;
        }
        strcpy(cur->friends[i], friend_name);
    }
    cur->num_friends = num;
    printf("Resolution added for %s.\n", name);
}

void remove_user() {
    char name[50];
    Node *prev, *cur;
    printf("Enter name: ");
    scanf("%s", name);
    prev = NULL;
    cur = head;
    while (cur != NULL && strcmp(cur->name, name) != 0) {
        prev = cur;
        cur = cur->next;
    }
    if (cur == NULL) {
        printf("%s not found in the list.\n", name);
        return;
    }
    if (prev == NULL) {
        head = cur->next;
    } else {
        prev->next = cur->next;
    }
    printf("%s has been removed from the list.\n", name);
    free(cur->friends);
    free(cur);
}

void print_friends() {
    char name[50];
    int i;
    Node *cur;
    printf("Enter name: ");
    scanf("%s", name);
    cur = head;
    while (cur != NULL && strcmp(cur->name, name) != 0) {
        cur = cur->next;
    }
    if (cur == NULL) {
        printf("%s not found in the list.\n", name);
        return;
    }
    printf("%s's friends: ", name);
    for (i = 0; i < cur->num_friends; i++) {
        printf("%s ", cur->friends[i]);
    }
    printf("\n");
}

void save_to_file() {
    char filename[50];
    FILE *fp;
    Node *cur;
    printf("Enter filename: ");
    scanf("%s", filename);
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    cur = head;
    while (cur != NULL) {
        fprintf(fp, "%s %d\n", cur->name, cur->num_friends);
        int i;
        for (i = 0; i < cur->num_friends; i++) {
            fprintf(fp, "%s ", cur->friends[i]);
        }
        fprintf(fp, "\n");
        cur = cur->next;
    }
    fclose(fp);
    printf("Data saved to file.\n");
}

void retrieve_from_file() {
    char filename[50], name[50], friend_name[50];
    int i, num_friends;
    FILE *fp;
    Node *temp, *prev, *cur;
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
        cur = head;
        while (cur != NULL && strcmp(cur->name, name) < 0) {
            prev = cur;
            cur = cur->next;
        }
        if (prev == NULL) {
            head = temp;
        } else {
            prev->next = temp;
        }
        temp->next = cur;
    }
    fclose(fp);
    printf("Data retrieved from file.\n");
}

