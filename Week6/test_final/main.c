#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person {
    char name[50];
    struct FriendNode *friends;
    struct Person *next;
} Person;

typedef struct FriendNode {
    Person *friend;
    struct FriendNode *next;
} FriendNode;

void insertPerson(Person **head, Person *newPerson);
void insertFriend(Person *person, Person *newFriend);
void removePerson(Person **head, const char *name);
void printFriends(Person *person);
void saveToFile(Person *head, const char *filename);
void loadFromFile(Person **head, const char *filename);

typedef struct TreeNode {
    Person *person;
    struct TreeNode *left;
    struct TreeNode *right;
    int height;
    int balanceFactor;
} TreeNode;

TreeNode *insertPersonInTree(TreeNode *node, Person *person);
TreeNode *removePersonFromTree(TreeNode *node, const char *name);

// Insert a new person into the linked list in alphabetical order
void insertPerson(Person **head, Person *newPerson) {
    Person *current = *head;
    Person *previous = NULL;

    while (current != NULL && strcmp(current->name, newPerson->name) < 0) {
        previous = current;
        current = current->next;
    }

    if (previous == NULL) {
        newPerson->next = *head;
        *head = newPerson;
    } else {
        newPerson->next = current;
        previous->next = newPerson;
    }
}

// Print the friends of a given person
void printFriends(Person *person) {
    printf("%s's friends:\n", person->name);
    FriendNode *currentFriend = person->friends;
    while (currentFriend != NULL) {
        printf("%s\n", currentFriend->friend->name);
        currentFriend = currentFriend->next;
    }
}

void removePerson(Person **head, const char *name) {
    if (head == NULL || *head == NULL) {
        return;
    }

    // If the head node is the one to be removed
    if (strcmp((*head)->name, name) == 0) {
        Person *next = (*head)->next;
        free(*head);
        *head = next;
        return;
    }

    // Search for the node to be removed
    Person *current = *head;
    while (current->next != NULL && strcmp(current->next->name, name) != 0) {
        current = current->next;
    }

    // If the node is found, remove it and update the links
    if (current->next != NULL) {
        Person *node_to_remove = current->next;
        current->next = current->next->next;
        free(node_to_remove);
    }
}

// Save the linked list data to a file
void saveToFile(Person *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error opening the file.\n");
        return;
    }

    Person *current = head;
    while (current != NULL) {
        fprintf(file, "%s\n", current->name);
        FriendNode *currentFriend = current->friends;
        while (currentFriend != NULL) {
            fprintf(file, "%s,", currentFriend->friend->name);
            currentFriend = currentFriend->next;
        }
        fprintf(file, "\n");
        current = current->next;
    }

    fclose(file);
}

Person *findPerson(Person *head, const char *name) {
    Person *current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Load data from a file into a linked list
void loadFromFile(Person **head, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening the file.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        strtok(line, "\n"); // Remove newline character
        Person *newPerson = (Person *)malloc(sizeof(Person));
        strcpy(newPerson->name, line);
        newPerson->friends = NULL;
        newPerson->next = NULL;
        insertPerson(head, newPerson);

        fgets(line, sizeof(line), file);
        strtok(line, "\n"); // Remove newline character
        char *friendName = strtok(line, ",");
        while (friendName != NULL) {
            Person *existingFriend = findPerson(*head, friendName);
            if (existingFriend != NULL) {
                insertFriend(newPerson, existingFriend);
            }
            friendName = strtok(NULL, ",");
        }
    }

    fclose(file);
}

void insertFriend(Person *person, Person *newFriend) {
    FriendNode *newFriendNode = (FriendNode *)malloc(sizeof(FriendNode));
    newFriendNode->friend = newFriend;
    newFriendNode->next = person->friends;
    person->friends = newFriendNode;
}

Person *findPersonInList(Person *head, const char *name) {
    Person *current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}


Person *findPersonInTree(TreeNode *node, const char *name) {
    if (node == NULL) {
        return NULL;
    }

    int comparison = strcmp(name, node->person->name);
    if (comparison == 0) {
        return node->person;
    } else if (comparison < 0) {
        return findPersonInTree(node->left, name);
    } else {
        return findPersonInTree(node->right, name);
    }
}

void saveToFileTreeHelper(TreeNode *node, FILE *file) {
    if (node == NULL) {
        return;
    }

    saveToFileTreeHelper(node->left, file);

    fprintf(file, "%s\n", node->person->name);
    FriendNode *currentFriend = node->person->friends;
    while (currentFriend != NULL) {
        fprintf(file, "%s,", currentFriend->friend->name);
        currentFriend = currentFriend->next;
    }
    fprintf(file, "\n");

    saveToFileTreeHelper(node->right, file);
}

void saveToFileTree(TreeNode *root, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error opening the file.\n");
        return;
    }

    saveToFileTreeHelper(root, file);

    fclose(file);
}

void loadFromFileTree(TreeNode **root, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening the file.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        strtok(line, "\n"); // Remove newline character
        Person *newPerson = (Person *)malloc(sizeof(Person));
        strcpy(newPerson->name, line);
        newPerson->friends = NULL;
        *root = insertPersonInTree(*root, newPerson);

        fgets(line, sizeof(line), file);
        strtok(line, "\n"); // Remove newline character
        char *friendName = strtok(line, ",");
        while (friendName != NULL) {
            Person *existingFriend = findPersonInTree(*root, friendName);
            if (existingFriend != NULL) {
                insertFriend(newPerson, existingFriend);
            }
            friendName = strtok(NULL, ",");
        }
    }
    fclose(file);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

void updateNodeHeightAndBalanceFactor(TreeNode *node) {
    int leftHeight = (node->left != NULL) ? node->left->height : -1;
    int rightHeight = (node->right != NULL) ? node->right->height : -1;
    node->height = 1 + max(leftHeight, rightHeight);
    node->balanceFactor = rightHeight - leftHeight;
}

TreeNode *rotateRight(TreeNode *y) {
    TreeNode *x = y->left;
    TreeNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    updateNodeHeightAndBalanceFactor(y);
    updateNodeHeightAndBalanceFactor(x);

    return x;
}

TreeNode *rotateLeft(TreeNode *x) {
    TreeNode *y = x->right;
    TreeNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    updateNodeHeightAndBalanceFactor(x);
    updateNodeHeightAndBalanceFactor(y);

    return y;
}

TreeNode *insertPersonInTree(TreeNode *node, Person *newPerson) {
    if (node == NULL) {
        TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
        newNode->person = newPerson;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->height = 0;
        newNode->balanceFactor = 0;
        return newNode;
    }

    int comparison = strcmp(newPerson->name, node->person->name);
    if (comparison < 0) {
        node->left = insertPersonInTree(node->left, newPerson);
    } else if (comparison > 0) {
        node->right = insertPersonInTree(node->right, newPerson);
    }

    updateNodeHeightAndBalanceFactor(node);

    // Perform rotations to balance the tree
    if (node->balanceFactor > 1) {
        if (node->right->balanceFactor < 0) {
            node->right = rotateRight(node->right);
        }
        node = rotateLeft(node);
    } else if (node->balanceFactor < -1) {
        if (node->left->balanceFactor > 0) {
            node->left = rotateLeft(node->left);
        }
        node = rotateRight(node);
    }

    return node;
}


TreeNode *findMinNode(TreeNode *node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

TreeNode *removePersonFromTreeHelper(TreeNode *node, const char *name) {
    if (node == NULL) {
        return NULL;
    }

    int comparison = strcmp(name, node->person->name);
    if (comparison < 0) {
        node->left = removePersonFromTreeHelper(node->left, name);
    } else if (comparison > 0) {
        node->right = removePersonFromTreeHelper(node->right, name);
    } else {
        if (node->left == NULL) {
            TreeNode *temp = node->right;
            free(node);
            return temp;
        } else if (node->right == NULL) {
            TreeNode *temp = node->left;
            free(node);
            return temp;
        }

        TreeNode *temp = findMinNode(node->right);
        node->person = temp->person;
        node->right = removePersonFromTreeHelper(node->right, temp->person->name);
    }

    return node;
}

TreeNode *removePersonFromTree(TreeNode *root, const char *name) {
    return removePersonFromTreeHelper(root, name);
}

void printTreeHelper(TreeNode *node, int depth) {
    if (node == NULL) {
        return;
    }

    printTreeHelper(node->left, depth + 1);

    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("%s\n", node->person->name);

    printTreeHelper(node->right, depth + 1);
}

void printTree(TreeNode *root) {
    printTreeHelper(root, 0);
}

void freeFriends(FriendNode *head) {
    FriendNode *current = head;
    while (current != NULL) {
        FriendNode *nextNode = current->next;
        free(current);
        current = nextNode;
    }
}

void freeTree(TreeNode *node) {
    if (node == NULL) {
        return;
    }
    freeTree(node->left);
    freeTree(node->right);
    freeFriends(node->person->friends);
    free(node->person);
    free(node);
}

void freeList(Person *head) {
    Person *current = head;
    while (current != NULL) {
        Person *nextNode = current->next;
        freeFriends(current->name);
        free(current->name);
        free(current);
        current = nextNode;
    }
}

int main(int argc, char *argv[]) {
    int useTree = 0; // Default to using the linked list
    // Check argc and argv for the data structure choice
    if (argc > 1 && strcmp(argv[1], "--tree") == 0) {
        useTree = 1; // Use the tree data structure if the "--tree" argument is provided
    }
    // Initialize the data structure (linked list or tree)
    Person *head = NULL; // For linked list
    TreeNode *root = NULL; // For tree

    int choice;
    char name[50];
    char friendName[50];

    do {
        printf("\nMenu:\n");
        printf("1) Introduce user\n");
        printf("2) Introduce new relationship\n");
        printf("3) Remove user\n");
        printf("4) Print a given person's friends\n");
        printf("5) Save to file\n");
        printf("6) Retrieve data from file\n");
        printf("7) Exit\n");
        printf("8) Print tree(to check binary tree)\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Introduce user
                printf("Enter the user's name: ");
                scanf("%s", name);
                Person *newPerson = (Person *)malloc(sizeof(Person));
                strcpy(newPerson->name, name);
                newPerson->friends = NULL;
                newPerson->next = NULL;

                if (!useTree) {
                    insertPerson(&head, newPerson);
                } else {
                    root = insertPersonInTree(root, newPerson);
                }
                break;

            case 2: // Introduce new relationship
                printf("Enter the person's name: ");
                scanf("%s", name);
                printf("Enter the friend's name: ");
                scanf("%s", friendName);

                Person *person, *friend;
                if (!useTree) {
                    person = findPerson(head, name);
                    friend = findPerson(head, friendName);
                } else {
                    person = findPersonInTree(root, name);
                    friend = findPersonInTree(root, friendName);
                }

                if (person != NULL && friend != NULL) {
                    insertFriend(person, friend);
                    insertFriend(friend, person);
                } else {
                    printf("Person or friend not found.\n");
                }
                break;

            case 3: // Remove user
                printf("Enter the user's name: ");
                scanf("%s", name);

                if (!useTree) {
                    removePerson(&head, name);
                } else {
                    root = removePersonFromTree(root, name);
                }
                break;

            case 4: // Print a given person's friends
                printf("Enter the person's name: ");
                scanf("%s", name);

                if (!useTree) {
                    person = findPerson(head, name);
                } else {
                    person = findPersonInTree(root, name);
                }

                if (person != NULL) {
                    printFriends(person);
                } else {
                    printf("Person not found.\n");
                }
                break;

            case 5: // Save to file
                printf("Enter the file name: ");
                scanf("%s", name);
                if (!useTree) {
                    saveToFile(head, name);
                } else {
                    // Implement saveToFileTree for the tree data structure
                    saveToFileTree(root, name);
                }
                break;

            case 6: // Retrieve data from file
                printf("Enter the file name: ");
                scanf("%s", name);
                if (!useTree) {
                    loadFromFile(&head, name);
                } else {
                    // Implement loadFromFileTree for the tree data structure
                    loadFromFileTree(&root, name);
                }
                break;

            case 7: // Exit
                printf("Exiting...\n");
                break;

            case 8: // Print the tree (new option)
                if (useTree) {
                    printTree(root);
                } else {
                    printf("This option is available only when using the tree data structure.\n");
                }
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    }
    while (choice != 7); // Update the exit condition
    if (!useTree) {
        freeList(head);
    } else {
        freeTree(root);
    }
    return 0;
}




