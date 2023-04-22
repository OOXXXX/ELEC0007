#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for a user
struct User {
    char name[50];
    struct FriendNode *friends;
    struct User *next;
};
typedef struct User User;

typedef struct FriendNode {
    User *friend;
    struct FriendNode *next;
};
typedef struct FriendNode FriendNode;

// Linked list function prototypes
void insertUser(User **head, User *newUser);
void insertFriend(User *user, User *newFriend);
void removeUser(User **head, const char *name);
void printFriends(User *user);
void saveToFile(User *head, const char *filename);
void loadFromFile(User **head, const char *filename);

// Define the TreeNode struct
typedef struct TreeNode {
    User *user;
    struct TreeNode *left;
    struct TreeNode *right;
    int height;
    int balanceFactor;
} TreeNode;

//two functions to insert and remove a user from the tree
TreeNode *insertUserInTree(TreeNode *node, User *user);
TreeNode *removeUserFromTree(TreeNode *node, const char *name);

// Insert a new user into the linked list in alphabetical order
void insertUser(User **head, User *newUser) {
    User *current = *head;
    User *previous = NULL;

    while (current != NULL && strcmp(current->name, newUser->name) < 0) {
        previous = current;
        current = current->next;
    }
    // if the head node is null or the new user is smaller than the head node, insert the new user at the head
    if (previous == NULL) {
        newUser->next = *head;
        *head = newUser;
    } else {
        newUser->next = current;
        previous->next = newUser;
    }
}

// Print the friends of a given user
void printFriends(User *user) {
    printf("%s's friends:\n", user->name);
    FriendNode *currentFriend = user->friends;
    // when currentFriend is not null, print the name of the friend
    while (currentFriend != NULL) { 
        printf("%s\n", currentFriend->friend->name);
        currentFriend = currentFriend->next;
    }
}

void removeUser(User **head, const char *name) {
    if (head == NULL || *head == NULL) {
        return;
    }
    // If the head node is the one to be removed
    if (strcmp((*head)->name, name) == 0) {
        User *next = (*head)->next;
        free(*head);
        *head = next;
        return;
    }

    // Search for the node to be removed
    User *current = *head;
    while (current->next != NULL && strcmp(current->next->name, name) != 0) {
        current = current->next;
    }

    // If the node is found, remove it and update the links
    if (current->next != NULL) {
        User *node_to_remove = current->next;
        current->next = current->next->next;
        free(node_to_remove);
    }
}

// Save the linked list data to a file
void saveToFile(User *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error opening the file.\n");
        return;
    }
// Loop through the linked list and write the data to the file
    User *current = head;
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

// Find a user in the linked list
User *findUser(User *head, const char *name) {
    User *current = head;
    while (current != NULL) { // Loop through the list
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Load data from a file into a linked list
void loadFromFile(User **head, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening the file.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        strtok(line, "\n"); // Remove newline character
        User *newUser = (User *)malloc(sizeof(User));
        strcpy(newUser->name, line);
        newUser->friends = NULL;
        newUser->next = NULL;
        insertUser(head, newUser);

        fgets(line, sizeof(line), file);
        strtok(line, "\n"); // Remove newline character
        char *friendName = strtok(line, ",");
        while (friendName != NULL) {
            User *existingFriend = findUser(*head, friendName);
            if (existingFriend != NULL) {
                insertFriend(newUser, existingFriend);
            }
            friendName = strtok(NULL, ",");
        }
    }

    fclose(file);
}

// Insert a new user into the tree
void insertFriend(User *user, User *newFriend) {
    FriendNode *newFriendNode = (FriendNode *)malloc(sizeof(FriendNode));
    newFriendNode->friend = newFriend;
    newFriendNode->next = user->friends;
    user->friends = newFriendNode;
}

// Find a user in the tree
User *findUserInTree(TreeNode *node, const char *name) {
    if (node == NULL) {
        return NULL;
    }
    // compare the name with the name of the current node
    int comparison = strcmp(name, node->user->name);
    if (comparison == 0) {
        return node->user;
    } else if (comparison < 0) {
        return findUserInTree(node->left, name);
    } else {
        return findUserInTree(node->right, name);
    }
}

// Helper function for saveToFileTree
void saveToFileTreeHelper(TreeNode *node, FILE *file) {
    if (node == NULL) {
        return;
    }

    saveToFileTreeHelper(node->left, file);

    fprintf(file, "%s\n", node->user->name);
    FriendNode *currentFriend = node->user->friends;
    while (currentFriend != NULL) {
        fprintf(file, "%s,", currentFriend->friend->name);
        currentFriend = currentFriend->next;
    }
    fprintf(file, "\n");

    saveToFileTreeHelper(node->right, file);
}

// Save the tree data to a file
void saveToFileTree(TreeNode *root, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error opening the file.\n");
        return;
    }

    saveToFileTreeHelper(root, file);

    fclose(file);
}

// Load data from a file into a binary search tree
void loadFromFileTree(TreeNode **root, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening the file.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        strtok(line, "\n"); // Remove newline character
        User *newUser = (User *)malloc(sizeof(User));
        strcpy(newUser->name, line);
        newUser->friends = NULL;
        *root = insertUserInTree(*root, newUser);

        fgets(line, sizeof(line), file);
        strtok(line, "\n"); // Remove newline character
        char *friendName = strtok(line, ",");
        while (friendName != NULL) {
            User *existingFriend = findUserInTree(*root, friendName);
            if (existingFriend != NULL) {
                insertFriend(newUser, existingFriend);
            }
            friendName = strtok(NULL, ",");
        }
    }
    fclose(file);
}

// Function to find the max of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Update the height and balance factor of a node
void updateNodeHeightAndBalanceFactor(TreeNode *node) {
    int leftHeight = (node->left != NULL) ? node->left->height : -1;
    int rightHeight = (node->right != NULL) ? node->right->height : -1;
    node->height = 1 + max(leftHeight, rightHeight);
    node->balanceFactor = rightHeight - leftHeight;
}

// Right rotate
TreeNode *rotateRight(TreeNode *y) {
    TreeNode *x = y->left;
    TreeNode *T2 = x->right;
// Perform rotation
    x->right = y;
    y->left = T2;
// Update heights
    updateNodeHeightAndBalanceFactor(y);
    updateNodeHeightAndBalanceFactor(x);
    return x;
}

// Left rotate
TreeNode *rotateLeft(TreeNode *x) {
    TreeNode *y = x->right;
    TreeNode *T2 = y->left;
// Perform rotation
    y->left = x;
    x->right = T2;
// Update heights
    updateNodeHeightAndBalanceFactor(x);
    updateNodeHeightAndBalanceFactor(y);
    return y;
}

// Insert a new user into the tree
TreeNode *insertUserInTree(TreeNode *node, User *newUser) {
    if (node == NULL) {
        TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
        newNode->user = newUser;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->height = 0;
        newNode->balanceFactor = 0;
        return newNode;
    }
    // compare the name with the name of the current node
    int comparison = strcmp(newUser->name, node->user->name);
    if (comparison < 0) {
        node->left = insertUserInTree(node->left, newUser);
    } else if (comparison > 0) {
        node->right = insertUserInTree(node->right, newUser);
    }
    // Update the height and balance factor of the node
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

// Returns the node with the minimum value in the tree
TreeNode *findMinNode(TreeNode *node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

TreeNode *removeUserFromTreeHelper(TreeNode *node, const char *name) {
    if (node == NULL) {
        return NULL;
    }
    // if the name is less than the current node, go left
    int comparison = strcmp(name, node->user->name);
    if (comparison < 0) {
        node->left = removeUserFromTreeHelper(node->left, name);
    } else if (comparison > 0) {
        node->right = removeUserFromTreeHelper(node->right, name);
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
    // if the node has two children, find the minimum node in the right subtree
        TreeNode *temp = findMinNode(node->right);
        node->user = temp->user;
        node->right = removeUserFromTreeHelper(node->right, temp->user->name);
    }

    return node;
}

// returns the new root of the tree
TreeNode *removeUserFromTree(TreeNode *root, const char *name) {
    return removeUserFromTreeHelper(root, name);
}

void printTree_Help(TreeNode *node, int depth) { // depth is the number of spaces to print
    if (node == NULL) {
        return;
    }
    // print the left subtree
    printTree_Help(node->left, depth + 1);

    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("%s\n", node->user->name);
    // print the right subtree
    printTree_Help(node->right, depth + 1);
}

// Print the tree in order
void printTree(TreeNode *root) { 
    printTree_Help(root, 0); // start with depth 0
}

// Free the memory of the linked list of friends
void freeFriends(FriendNode *head) {
    FriendNode *current = head;
    while (current != NULL) {
        FriendNode *nextNode = current->next;
        free(current);
        current = nextNode;
    }
}

// Free the memory allocated for the linked list
void freeList(User *head) {
    User *current = head;
    while (current != NULL) {
        User *nextNode = current->next;
        freeFriends(current->name);
        free(current->name);
        free(current);
        current = nextNode;
    }
}

// Free the memory allocated for the tree
void freeTree(TreeNode *node) {
    if (node == NULL) {
        return;
    }
    freeTree(node->left);
    freeTree(node->right);
    freeFriends(node->user->friends);
    free(node->user);
    free(node);
}

// The main function
int main(int argc, char *argv[]) {
    int useTree = 0; // Default to using the linked list
    // Check argc and argv for the data structure choice
    if (argc > 1 && strcmp(argv[1], "---tree") == 0) {
        useTree = 1; // Use the tree data structure if the "---tree" argument is provided
    }
    // Initialize the data structure (linked list or tree)
    User *head = NULL; // For linked list
    TreeNode *root = NULL; // For tree
    // initialize the menu
    int choice;
    char name[50];
    char friendName[50];
    // Print the menu
    do {
        printf("\nMenu:\n");
        printf("1) Introduce user\n");
        printf("2) Introduce new relationship\n");
        printf("3) Remove user\n");
        printf("4) Print a given user's friends\n");
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
                User *newUser = (User *)malloc(sizeof(User));
                strcpy(newUser->name, name);
                newUser->friends = NULL;
                newUser->next = NULL;
                // If the data structure is a linked list, use the insertUser function
                if (!useTree) {
                    insertUser(&head, newUser);
                } else {
                    root = insertUserInTree(root, newUser);
                }
                break;

            case 2: // Introduce new relationship
                printf("Enter the user's name: ");
                scanf("%s", name);
                printf("Enter the friend's name: ");
                scanf("%s", friendName);
                // Find the user and friend
                User *user, *friend;
                if (!useTree) {
                    user = findUser(head, name);
                    friend = findUser(head, friendName);
                } else {
                    user = findUserInTree(root, name);
                    friend = findUserInTree(root, friendName);
                }

                if (user != NULL && friend != NULL) {
                    insertFriend(user, friend);
                    insertFriend(friend, user);
                } else {
                    printf("User or friend not found.\n");
                }
                break;

            case 3: // Remove user
                printf("Enter the user's name: ");
                scanf("%s", name);

                if (!useTree) {
                    removeUser(&head, name);
                } else {
                    root = removeUserFromTree(root, name);
                }
                break;

            case 4: // Print a given user's friends
                printf("Enter the user's name: ");
                scanf("%s", name);

                if (!useTree) {
                    user = findUser(head, name);
                } else {
                    user = findUserInTree(root, name);
                }

                if (user != NULL) {
                    printFriends(user);
                } else {
                    printf("User not found.\n");
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
        freeList(head); // Free the memory allocated for the linked list
    } else {
        freeTree(root); // Free the memory allocated for the tree
    }
    return 0;
}




