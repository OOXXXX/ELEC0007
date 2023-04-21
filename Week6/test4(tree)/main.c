#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for a person
struct person {
    char name[50];
    struct person *next;
    int num_friends;
    char **friends;
};

// Function prototypes
void insert_person(struct person **head, char name[]);
void remove_person(struct person **head, char name[]);
void insert_friend(struct person **head, char name[], char friend_name[]);
void print_friends(struct person *head, char name[]);
void save_to_file(struct person *head);
void retrieve_from_file(struct person **head);
void print_menu();
void free_person(struct person *p);

// Global variables
struct person *head = NULL;

int main(int argc, char *argv[]) {
    // Check if user wants to use binary trees
    int use_trees = 0;
    if (argc > 1 && strcmp(argv[1], "-t") == 0) {
        use_trees = 1;
    }

    // Load data from file
    retrieve_from_file(&head);

    // Display menu
    int choice;
    char name[50], friend_name[50];
    do {
        print_menu();
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("Enter name: ");
                scanf("%s", name);
                insert_person(&head, name);
                break;
            case 2:
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter friend's name: ");
                scanf("%s", friend_name);
                insert_friend(&head, name, friend_name);
                break;
            case 3:
                printf("Enter name: ");
                scanf("%s", name);
                remove_person(&head, name);
                break;
            case 4:
                printf("Enter name: ");
                scanf("%s", name);
                print_friends(head, name);
                break;
            case 5:
                save_to_file(head);
                break;
            case 6:
                retrieve_from_file(&head);
                break;
            case 7:
                // Free memory for all persons before exit
                while (head != NULL) {
                    struct person *p = head;
                    head = head->next;
                    free_person(p);
                }
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 7);

    return 0;
}

// Insert a person in alphabetical order by name
void insert_person(struct person **head, char name[]) {
    struct person *new_person = (struct person *) malloc(sizeof(struct person));
    strcpy(new_person->name, name);
    new_person->num_friends = 0;
    new_person->friends = NULL;

    // If the list is empty or new person is less than the first person
    if (*head == NULL || strcmp((*head)->name, name) > 0) {
        new_person->next = *head;
        *head = new_person;
    }
    else {
        // Traverse the list to find the correct position for the new person
        struct person *current = *head;
        while (current->next != NULL && strcmp(current->next->name, name) < 0) {
            current = current->next;
        }
        new_person->next = current->next;
        current->next = new_person;
    }

    printf("Person %s introduced.\n", name);
}

// Remove a person and their friendships from the list
void remove_person(struct person **head, char name[]) {
    // Find the person to remove
    struct person *current = *head;
    struct person *prev = NULL;
    while (current != NULL && strcmp(current->name, name) != 0) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Person %s not found.\n", name);
        return;
    }

// Remove the person from the list
    if (prev == NULL) {
        *head = current->next;
    }
    else {
        prev->next = current->next;
    }

    printf("Person %s removed.\n", name);

// Free memory for the person and their friendships
    free_person(current);
}

// Insert a friendship between two people
void insert_friend(struct person **head, char name[], char friend_name[]) {
// Find the persons
    struct person *p1 = NULL, *p2 = NULL;
    struct person *current = *head;
    while (current != NULL && (p1 == NULL || p2 == NULL)) {
        if (strcmp(current->name, name) == 0) {
            p1 = current;
        }
        if (strcmp(current->name, friend_name) == 0) {
            p2 = current;
        }
        current = current->next;
    }
    // If one of the persons was not found, return
    if (p1 == NULL) {
        printf("Person %s not found.\n", name);
        return;
    }
    if (p2 == NULL) {
        printf("Person %s not found.\n", friend_name);
        return;
    }

// Check if they are already friends
    for (int i = 0; i < p1->num_friends; i++) {
        if (strcmp(p1->friends[i], friend_name) == 0) {
            printf("%s and %s are already friends.\n", name, friend_name);
            return;
        }
    }

// Add friendship to both persons
    p1->num_friends++;
    p1->friends = (char **) realloc(p1->friends, sizeof(char *) * p1->num_friends);
    p1->friends[p1->num_friends - 1] = (char *) malloc(sizeof(char) * 50);
    strcpy(p1->friends[p1->num_friends - 1], friend_name);

    p2->num_friends++;
    p2->friends = (char **) realloc(p2->friends, sizeof(char *) * p2->num_friends);
    p2->friends[p2->num_friends - 1] = (char *) malloc(sizeof(char) * 50);
    strcpy(p2->friends[p2->num_friends - 1], name);

    printf("%s and %s are now friends.\n", name, friend_name);
}

// Print the list of friends for a given person
void print_friends(struct person *head, char name[]) {
// Find the person
    struct person *current = head;
    while (current != NULL && strcmp(current->name, name) != 0) {
        current = current->next;
    }
    if (current == NULL) {
        printf("Person %s not found.\n", name);
        return;
    }

// Print their friends
    printf("Friends of %s: ", name);
    for (int i = 0; i < current->num_friends; i++) {
        printf("%s ", current->friends[i]);
    }
    printf("\n");
}

// Save the list of persons and their friendships to a file
void save_to_file(struct person *head){
    FILE *fp = fopen("social_network.txt", "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }// Write each person and their friends to file
    struct person *current = head;
    while (current != NULL) {
        fprintf(fp, "%s %d", current->name, current->num_friends);
        for (int i = 0; i < current->num_friends; i++) {
            fprintf(fp, " %s", current->friends[i]);
        }
        fprintf(fp, "\n");
        current = current->next;
    }

    fclose(fp);
    printf("Data saved to file.\n");
}

// Load the list of persons and their friendships from a file
void retrieve_from_file(struct person **head) {
// Free memory for all persons currently in the list
    while (*head != NULL) {
        struct person *p = *head;
        *head = (*head)->next;
        free_person(p);
    }FILE *fp = fopen("social_network.txt", "r");
    if (fp == NULL) {
        printf("No previous data found.\n");
        return;
    }

// Read each person and their friends from file and insert into list
    char name[50], friend_name[50];
    int num_friends;
    while (fscanf(fp, "%s %d", name, &num_friends) != EOF) {
        insert_person(head, name);
        for (int i = 0; i < num_friends; i++) {
            fscanf(fp, "%s", friend_name);
            insert_friend(head, name, friend_name);
        }
    }

    fclose(fp);
    printf("Data retrieved from file.\n");
}

// Print the menu options for the user
void print_menu() {
    printf("\nSocial Network Application\n");
    printf("1. Introduce user\n");
    printf("2. Introduce new relationship\n");
    printf("3. Remove user\n");
    printf("4. Print a given person's friends\n");
    printf("5. Save to file\n");
    printf("6. Retrieve data from file\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

// Free memory for a person and their friendships
void free_person(struct person *p) {
    for (int i = 0; i < p->num_friends; i++) {
        free(p->friends[i]);
    }
    free(p->friends);
    free(p);
}
