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

void insert_node(Node **head, Node *new_node) {
    Node *prev = NULL;
    Node *aft = *head;
    while (aft != NULL && strcmp(aft->name, new_node->name) < 0) {
        prev = aft;
        aft = aft->next;
    }
    if (prev == NULL) {
        new_node->next = *head;
        *head = new_node;
    } else {
        prev->next = new_node;
        new_node->next = aft;
    }
}

void remove_node(Node **head, char *name) {
    Node *prev = NULL;
    Node *aft = *head;
    while (aft != NULL && strcmp(aft->name, name) != 0) {
        prev = aft;
        aft = aft->next;
    }
    if (aft == NULL) {
        printf("User not found.\n");
        return;
    }
    if (prev == NULL) {
        *head = aft->next;
    } else {
        prev->next = aft->next;
    }
    int i;
    for (i = 0; i < aft->num_friends; i++) {
        free(aft->friends[i]);
    }
    free(aft->friends);
    free(aft);
}

void introduce_user() {
    char name[50];
    printf("Enter name of user: ");
    scanf("%s", name);
    Node *new_node = (Node *) malloc(sizeof(Node));
    strcpy(new_node->name, name);
    new_node->num_friends = 0;
    new_node->friends = NULL;
    new_node->next = NULL;
    insert_node(&head, new_node);
    printf("%s has been added to the list.\n", new_node->name);
}

void introduce_resolution() {
    char name[50];
    printf("Enter name of user: ");
    scanf("%s", name);
    Node *temp = head;
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("User not found.\n");
        return;
    }
    int num_friends;
    printf("Enter number of friends: ");
    scanf("%d", &num_friends);
    temp->num_friends = num_friends;
    temp->friends = (char **) malloc(num_friends * sizeof(char *));
    int i;
    for (i = 0; i < num_friends; i++) {
        temp->friends[i] = (char *) malloc(50 * sizeof(char));
        printf("Enter name of friend %d: ", i + 1);
        scanf("%s", temp->friends[i]);
    }
    printf("Resolution added successfully.\n");
}

void remove_user() {
    char name[50];
    printf("Enter name of user: ");
    scanf("%s", name);
    remove_node(&head, name);
    printf("%s has been removed.\n", name);
}

void print_friends() {
    char name[50];
    printf("Enter name of user: ");
    scanf("%s", name);
    Node *temp = head;
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("User not found.\n");
        return;
    }
    printf("Friends of %s:\n", name);
    int i;
    for (i = 0; i < temp->num_friends; i++) {
        printf("%s", temp->friends[i]);
        if (i != temp->num_friends - 1) {
            printf(", ");
        }
    }
}

void save_to_file() {
    char filename[50];
    printf("Enter filename to save data: ");
    scanf("%s", filename);
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    Node *temp = head;
    while (temp != NULL) {
        fprintf(file, "%s %d", temp->name, temp->num_friends);
        int i;
        for (i = 0; i < temp->num_friends; i++) {
            fprintf(file, " %s", temp->friends[i]);
        }
        fprintf(file, "\n");
        temp = temp->next;
    }
    fclose(file);
    printf("Data saved successfully.\n");
}

void retrieve_from_file() {
    char filename[50];
    printf("Enter filename to retrieve data: ");
    scanf("%s", filename);
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    char name[50];
    int num_friends;
    while (fscanf(file, "%s %d", name, &num_friends) != EOF) {
        Node *new_node = (Node *) malloc(sizeof(Node));
        strcpy(new_node->name, name);
        new_node->num_friends = num_friends;
        new_node->friends = (char **) malloc(num_friends * sizeof(char *));
        int i;
        for (i = 0; i < num_friends; i++) {
            new_node->friends[i] = (char *) malloc(50 * sizeof(char));
            fscanf(file, " %s", new_node->friends[i]);
        }
        new_node->next = NULL;
        insert_node(&head, new_node);
    }
    fclose(file);
    printf("Data retrieved successfully.\n");
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

