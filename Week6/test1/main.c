#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Person structure
typedef struct Person {
    char name[50];
    int age;
    char gender;
    char address[100];
    char friends[10][50];
    struct Person* next;
} Person;

Person* head = NULL;

// Insert a new person in the list
void insert(Person** head_ref, Person* new_person) {
    Person* current;
    // Find the appropriate position to insert the new person in alphabetical order
    if (*head_ref == NULL || strcmp((*head_ref)->name, new_person->name) > 0) {
        new_person->next = *head_ref;
        *head_ref = new_person;
    } else {
        current = *head_ref;
        while (current->next != NULL && strcmp(current->next->name, new_person->name) < 0) {
            current = current->next;
        }
        new_person->next = current->next;
        current->next = new_person;
    }
}

// Remove a person from the list
void remove_person(Person** head_ref, char* name) {
    Person* current = *head_ref;
    Person* prev = NULL;
    // Find the person to remove
    while (current != NULL && strcmp(current->name, name) != 0) {
        prev = current;
        current = current->next;
    }
    // If person was found, remove them from the list
    if (current != NULL) {
        if (prev == NULL) {
            *head_ref = current->next;
        } else {
            prev->next = current->next;
        }
        free(current);
    }
}

// Print a person's friends
void print_friends(Person* person) {
    printf("Friends of %s: ", person->name);
    for (int i = 0; i < 10; i++) {
        if (strcmp(person->friends[i], "") != 0) {
            printf("%s ", person->friends[i]);
        }
    }
    printf("\n");
}

// Save the list to a file
void save_to_file(Person* head) {
    FILE* fp;
    fp = fopen("persons.txt", "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    Person* current = head;
    // Write each person's data to the file
    while (current != NULL) {
        fprintf(fp, "%s %d %c %s ", current->name, current->age, current->gender, current->address);
        for (int i = 0; i < 10; i++) {
            fprintf(fp, "%s ", current->friends[i]);
        }
        fprintf(fp, "\n");
        current = current->next;
    }
    fclose(fp);
}

// Retrieve data from a file and insert it into the list
void retrieve_from_file(Person** head_ref) {
    FILE* fp;
    fp = fopen("persons.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    char line[300];
    while (fgets(line, sizeof(line), fp)) {
        Person* new_person = (Person*)malloc(sizeof(Person));
        sscanf(line, "%s %d %c %s", new_person->name, &new_person->age, &new_person->gender, new_person->address);
        for (int i = 0; i < 10; i++) {
            sscanf(line, "%*s %*d%*c %*s %s", new_person->friends[i]);
        }
        new_person->next = NULL;
        insert(head_ref, new_person);
    }
    fclose(fp);
}

// Main function
int main() {
    int choice;
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
        getchar(); // consume newline character
        switch (choice) {
            case 1: { // Introduce user
                Person* new_person = (Person*)malloc(sizeof(Person));
                printf("Enter name: ");
                fgets(new_person->name, sizeof(new_person->name), stdin);
                new_person->name[strcspn(new_person->name, "\n")] = 0; // remove newline character
                printf("Enter age: ");
                scanf("%d", &new_person->age);
                getchar(); // consume newline character
                printf("Enter gender (M/F): ");
                scanf("%c", &new_person->gender);
                getchar(); // consume newline character
                printf("Enter address: ");
                fgets(new_person->address, sizeof(new_person->address), stdin);
                new_person->address[strcspn(new_person->address, "\n")] = 0; // remove newline character
                for (int i = 0; i < 10; i++) {
                    printf("Enter friend %d's name (or press enter to skip): ", i+1);
                    fgets(new_person->friends[i], sizeof(new_person->friends[i]), stdin);
                    new_person->friends[i][strcspn(new_person->friends[i], "\n")] = 0; // remove newline character
                    if (strcmp(new_person->friends[i], "") == 0) {
                        break;
                    }
                }
                new_person->next = NULL;
                insert(&head, new_person);
                break;
            }
            case 2: { // Introduce new resolution
// TODO: Implement this option
                break;
            }
            case 3: { // Remove user
                char name[50];
                printf("Enter name of person to remove: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0; // remove newline character
                remove_person(&head, name);
                break;
            }
            case 4: { // Print a given person's friends
                char name[50];
                printf("Enter name of person to print friends of: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0; // remove newline character
                Person* current = head;
                while (current != NULL && strcmp(current->name, name) != 0) {
                    current = current->next;
                }
                if (current != NULL) {
                    print_friends(current);
                } else {
                    printf("Person not found.\n");
                }
                break;
            }
            case 5: { // Save to file
                save_to_file(head);
                break;
            }
            case 6: { // Retrieve data from file
                retrieve_from_file(&head);
                break;
            }
            case 7: { // Exit
                exit(0);
            }
            default: {
                printf("Invalid choice.\n");
                break;
            }
        }
    }
    return 0;
}

