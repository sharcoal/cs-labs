#include "lab8.h"

void insert(char* animal, int hour, int minute) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, animal);
    newNode->time[0] = hour;
    newNode->time[1] = minute;
    newNode->next = NULL;
    newNode->prev = NULL;

    // Insert in sorted order
    if (head == NULL) {
        head = tail = newNode;
        return;
    }

    Node* current = head;
    while (current != NULL && (current->time[0] < hour || 
           (current->time[0] == hour && current->time[1] < minute))) {
        current = current->next;
    }

    if (current == head) { // Insert at head
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    } else if (current == NULL) { // Insert at tail
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    } else { // Insert in middle
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
    }
}

void delete(char* animal) {
    Node* current = head;
    while (current != NULL) {
        if (strcmp(current->name, animal) == 0) {
            if (current == head) 
                head = current->next;
            if (current == tail) 
                tail = current->prev;
            if (current->next) 
                current->next->prev = current->prev;
            if (current->prev) 
                current->prev->next = current->next;
            free(current);
            break;
        }
        current = current->next;
    }
}

void change(char* animal, int new_hour, int new_minute) {
    Node* current = head;
    while (current != NULL) {
        if (strcmp(current->name, animal) == 0) {
            delete(animal);
            insert(animal, new_hour, new_minute);
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

void show_backwards(Node* node) {
    if (node == NULL) return;
    show_backwards(node->next);
    printf("%-15s %02d:%02d\n", node->name, node->time[0], node->time[1]);
}

void delete_all(Node* node) {
    if (node == NULL) return;
    delete_all(node->next);
    free(node);
}




