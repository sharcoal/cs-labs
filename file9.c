#include "lab9.h"

void* auto_save_thread(void* arg) {
    char* filename = (char*)arg;

    while (1) {
        sleep(15);

        pthread_mutex_lock(&lock);
        save_binary_file(filename);
        pthread_mutex_unlock(&lock);

        printf("Auto-save complete.\n");
    }

    pthread_exit(NULL);
}

void save_binary_file(const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) return;

    Node* current = head;
    while (current != NULL) {
        fwrite(current, sizeof(Node), 1, file);
        current = current->next;
    }

    fclose(file);
}

void read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return;

    char name[MAX_NAME_LEN];
    int hour, minute;
    while (fscanf(file, "%s %d %d", name, &hour, &minute) == 3) {
        insert(name, hour, minute);
    }

    fclose(file);
}

void save_file(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) return;

    Node* current = head;
    while (current != NULL) {
        fprintf(file, "%s %02d %02d\n", current->name, current->time[0], current->time[1]);
        current = current->next;
    }

    fclose(file);
}

void read_binary_file(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Cannot open binary file.\n");
        return;
    }

    Node temp;
    while (fread(&temp, sizeof(Node), 1, file)) {
        printf("%-15s %02d:%02d\n", temp.name, temp.time[0], temp.time[1]);
    }

    fclose(file);
}
