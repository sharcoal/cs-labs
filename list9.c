#include "lab9.h"

void insert(char* animal, int hour, int minute) {
    pthread_mutex_lock(&lock);

    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, animal);
    newNode->time[0] = hour;
    newNode->time[1] = minute;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (head == NULL) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    pthread_mutex_unlock(&lock);
}

void delete(char* animal) {
    pthread_mutex_lock(&lock);

    Node* current = head;
    while (current != NULL) {
        if (strcmp(current->name, animal) == 0) {
            if (current == head) head = current->next;
            if (current == tail) tail = current->prev;
            if (current->prev) current->prev->next = current->next;
            if (current->next) current->next->prev = current->prev;
            free(current);
            break;
        }
        current = current->next;
    }

    pthread_mutex_unlock(&lock);
}

void change(char* animal, int new_hour, int new_minute) {
    pthread_mutex_lock(&lock);

    Node* current = head;
    while (current != NULL) {
        if (strcmp(current->name, animal) == 0) {
            current->time[0] = new_hour;
            current->time[1] = new_minute;
            break;
        }
        current = current->next;
    }

    pthread_mutex_unlock(&lock);
}

void showall() {
    Node* current = head;
    while (current != NULL) {
        printf("%s %02d:%02d\n", current->name, current->time[0], current->time[1]);
        current = current->next;
    }
}

void show_backwards(Node* node) {
    if (node == NULL) return;
    show_backwards(node->next);
    printf("%s %02d:%02d\n", node->name, node->time[0], node->time[1]);
}

void delete_all(Node* node) {
    if (node == NULL) return;
    delete_all(node->next);
    free(node);
}
