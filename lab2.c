#include <stdio.h>
#include <string.h>

#define MAX_ANIMALS 10
#define MAX_NAME_LEN 20

// Global variables
char animals[MAX_ANIMALS][MAX_NAME_LEN];
int times[MAX_ANIMALS][2]; // Columns: 0 = Hour, 1 = Minute
int counter = 0; // Number of animals in the list

// Function prototypes
void insert(char *animal, int hour, int minute);
void delete(char *animal);
void showall();

int main() {
    int command, hour, minute;
    char animal[MAX_NAME_LEN];

    while (1) {
        printf("\nChoose an option:\n");
        printf("1 Add an animal! enter format: <animal> <hour> <minute>\n");
        printf("2 Delete an entry! enter format: <animal>\n");
        printf("3 Show the list\n");
        printf("0 - Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &command);

        switch (command) {
            case 0: // Quit
                printf("Exiting the program. Goodbye!\n");
                return 0;

            case 1: // Insert an entry
                printf("Enter animal name, hour (0-23), and minute (0-59): ");
                scanf("%s %d %d", animal, &hour, &minute);
                if (hour >= 0 && hour < 24 && minute >= 0 && minute < 60) {
                    insert(animal, hour, minute);
                } else {
                    printf("Invalid time. Please enter hours (0-23) and minutes (0-59).\n");
                }
                break;

            case 2: // Delete an entry
                printf("Enter animal name to delete: ");
                scanf("%s", animal);
                delete(animal);
                break;

            case 3: // Show all entries
                showall();
                break;

            default: // Invalid choice
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
    return 0;
}

void insert(char *animal, int hour, int minute) {
    int i, j;

    // Check if the animal already exists
    for (i = 0; i < counter; i++) {
        if (strcmp(animals[i], animal) == 0) {
            printf("Animal already exists in the schedule.\n");
            return;
        }
    }

    // Check if there's space in the list
    if (counter >= MAX_ANIMALS) {
        printf("Cannot add more animals. Maximum capacity reached.\n");
        return;
    }

    // Find the correct position to insert based on time
    for (i = 0; i < counter; i++) {
        if (hour < times[i][0] || (hour == times[i][0] && minute < times[i][1])) {
            break;
        }
    }

    // Shift entries down to make space
    for (j = counter; j > i; j--) {
        strcpy(animals[j], animals[j - 1]);
        times[j][0] = times[j - 1][0];
        times[j][1] = times[j - 1][1];
    }

    // Insert the new animal and time
    strcpy(animals[i], animal);
    times[i][0] = hour;
    times[i][1] = minute;
    counter++;
    printf("Animal added successfully.\n");
}

void delete(char *animal) {
    int i, j;

    // Find the animal in the list
    for (i = 0; i < counter; i++) {
        if (strcmp(animals[i], animal) == 0) {
            // Shift entries up to fill the gap
            for (j = i; j < counter - 1; j++) {
                strcpy(animals[j], animals[j + 1]);
                times[j][0] = times[j + 1][0];
                times[j][1] = times[j + 1][1];
            }
            counter--;
            printf("Animal removed from the schedule.\n");
            return;
        }
    }

    printf("Animal not found in the schedule.\n");
}

void showall() {
    int i;

    if (counter == 0) {
        printf("The schedule is empty.\n");
        return;
    }

    printf("Animal          Time\n");
    printf("---------------------\n");
    for (i = 0; i < counter; i++) {
        printf("%-15s %02d:%02d\n", animals[i], times[i][0], times[i][1]);
    }
}
