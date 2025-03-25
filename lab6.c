#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 20

// Struct for linked list node
typedef struct Node {
    char name[MAX_NAME_LEN];
    int time[2];  // time[0] = hour, time[1] = minute
    struct Node* next;
    struct Node* prev;
} Node;

// Global head and tail pointers
Node* head = NULL;
Node* tail = NULL;

// Function prototypes
void insert(char* animal, int hour, int minute);
void delete(char* animal);
void showall();
void change(char* animal, int new_hour, int new_minute);

int main() {
    int command, hour, minute;
    char animal[MAX_NAME_LEN];

    while (1) {
        printf("\nChoose an option:\n");
        printf("1 <animal> <hour> <minute> - Add an entry\n");
        printf("2 <animal> - Delete an entry\n");
        printf("3 - Show the list\n");
        printf("4 <animal> <hour> <minute> - Change feeding time\n");
        printf("0 - Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &command);

        switch (command) {
            case 0:
                printf("Exiting the program. Goodbye!\n");
                return 0;

            case 1:
                printf("Enter animal name, hour (0-23), and minute (0-59): ");
                scanf("%s %d %d", animal, &hour, &minute);
                if (hour >= 0 && hour < 24 && minute >= 0 && minute < 60) {
                    insert(animal, hour, minute);
                } else {
                    printf("Invalid time. Please enter hours (0-23) and minutes (0-59).\n");
                }
                break;

            case 2:
                printf("Enter animal name to delete: ");
                scanf("%s", animal);
                delete(animal);
                break;

            case 3:
                showall();
                break;

            case 4:
                printf("Enter animal name, new hour (0-23), and new minute (0-59): ");
                scanf("%s %d %d", animal, &hour, &minute);
                if (hour >= 0 && hour < 24 && minute >= 0 && minute < 60) {
                    change(animal, hour, minute);
                } else {
                    printf("Invalid time. Please enter hours (0-23) and minutes (0-59).\n");
                }
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}

// Insert function (sorted order)
void insert(char* animal, int hour, int minute) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // allocate memory
    strcpy(newNode->name, animal); // storing
    newNode->time[0] = hour;
    newNode->time[1] = minute;
    newNode->next = NULL;
    newNode->prev = NULL;

    // If list is empty, insert at head
    if (head == NULL) {
        head = tail = newNode;
        return;
    }

    Node* current = head;
    while (current != NULL && (current->time[0] < hour || 
           (current->time[0] == hour && current->time[1] < minute))) {
        current = current->next;
    }

    if (current == head) { // insert at the beginning
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    } else if (current == NULL) { // insert at the end
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    } else { // insert in the middle
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
    }
}

// Delete function
void delete(char* animal) {
    Node* current = head;

    while (current != NULL) {
        if (strcmp(current->name, animal) == 0) {
            if (current == head) { // deleting head
                head = current->next;
                if (head) head->prev = NULL;
            } else if (current == tail) { // deleting tail
                tail = current->prev;
                tail->next = NULL;
            } else { // deleting in middle
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            free(current);
            printf("Animal removed from the schedule.\n");
            return;
        }
        current = current->next;
    }
    printf("Animal not found in the schedule.\n");
}

// Change function (remove and reinsert)
void change(char* animal, int new_hour, int new_minute) {
    Node* current = head;
    Node* temp = NULL;

    // Find and remove the node
    while (current != NULL) {
        if (strcmp(current->name, animal) == 0) {
            temp = current;
            if (current == head) {
                head = current->next;
                if (head) head->prev = NULL;
            } else if (current == tail) {
                tail = current->prev;
                tail->next = NULL;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            break;
        }
        current = current->next;
    }

    if (temp == NULL) {
        printf("Animal not found in the schedule.\n");
        return;
    }

    temp->time[0] = new_hour;
    temp->time[1] = new_minute;
    temp->next = temp->prev = NULL;
    insert(temp->name, temp->time[0], temp->time[1]);
    free(temp);
    printf("Feeding time updated successfully.\n");
}

// Show function
void showall() {
    if (head == NULL) {
        printf("The schedule is empty.\n");
        return;
    }

    printf("Animal          Time\n");
    printf("---------------------\n");
    Node* current = head;
    while (current != NULL) {
        printf("%-15s %02d:%02d\n", current->name, current->time[0], current->time[1]);
        current = current->next;
    }
}
