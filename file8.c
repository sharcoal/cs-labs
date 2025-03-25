#include "lab8.h"

void read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) 
        return;

    char name[MAX_NAME_LEN];
    int hour, minute;
    while (fscanf(file, "%s %d %d", name, &hour, &minute) == 3) {
        insert(name, hour, minute);
    }

    fclose(file);
}

void save_file(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) 
        return;

    Node* current = head;
    while (current != NULL) {
        fprintf(file, "%s %02d %02d\n", current->name, current->time[0], current->time[1]);
        current = current->next;
    }

    fclose(file);
}

