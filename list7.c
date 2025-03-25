#include "lab7.h"

void insert(char* animal, int hour, int minute) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, animal);
    newNode->time[0] = hour;
    newNode->time[1] = minute;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (head == NULL) {
        head = tail = newNode;
        return;
    }

    Node* current = head;
    while (current != NULL && (current->time[0] < hour || 
           (current->time[0] == hour && current->time[1] < minute))) {
        current = current->next;
    }

    if (current == head) {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    } else if (current == NULL) {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    } else {
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
    }
}

void insert_tail(char* animal, int hour, int minute) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, animal);
    newNode->time[0] = hour;
    newNode->time[1] = minute;
    newNode->next = NULL;
    newNode->prev = tail;

    if (tail == NULL) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

void delete(char* animal) {
    Node* current = head;

    while (current != NULL) {
        if (strcmp(current->name, animal) == 0) {
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
            free(current);
            return;
        }
        current = current->next;
    }
}

void showall() {
    Node* current = head;
    while (current != NULL) {
        printf("%-15s %02d:%02d\n", current->name, current->time[0], current->time[1]);
        current = current->next;
    }
}

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