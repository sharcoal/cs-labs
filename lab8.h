#ifndef LAB8_H
#define LAB8_H

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

// Global variables
extern Node* head;
extern Node* tail;

// Function prototypes
void insert(char* animal, int hour, int minute);
void insert_tail(char* animal, int hour, int minute);
void delete(char* animal);
void showall();
void change(char* animal, int new_hour, int new_minute);
void read_file(const char* filename);
void save_file(const char* filename);
void show_backwards(Node* node);
void delete_all(Node* node);

#endif
