#include <stdio.h>
#include <string.h>

#define MAX_ANIMALS 10
#define MAX_NAME_LEN 20
#define MAX_PLACE_LEN 20

// Union to store either cage coordinates or a place name
typedef union {
    int cage[2];       // Coordinates if location == 0
    char place[MAX_PLACE_LEN]; // Place name if location == 1
} LocationInfo;

// Struct to store an animal's feeding schedule
typedef struct {
    char name[MAX_NAME_LEN];
    int time[2];  // time[0] = hour, time[1] = minute
    int location; // 0 = cage coordinates, 1 = place
    LocationInfo info; // Union storing additional location data
} Animal;

// Global variables
Animal zoo[MAX_ANIMALS]; // Array of structs
int counter = 0; // Number of animals in the list

// Function prototypes
void insert(char *animal, int hour, int minute, int location, char *extra);
void delete(char *animal);
void showall();
void change(char *animal, int new_hour, int new_minute);

int main() {
    int command, hour, minute, location;
    char animal[MAX_NAME_LEN], extra[MAX_PLACE_LEN];

    while (1) {
        printf("\nChoose an option:\n");
        printf("1 <animal> <hour> <minute> <0 or 1> <cage coordinates or place> - Add an entry\n");
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
                printf("Enter animal name, hour (0-23), minute (0-59), location (0=cage, 1=place), and extra info: ");
                scanf("%s %d %d %d", animal, &hour, &minute, &location);

                if (location == 0) { // Cage coordinates
                    int x, y;
                    scanf("%d %d", &x, &y);
                    sprintf(extra, "%d %d", x, y);
                } else if (location == 1) { // Place name
                    scanf("%s", extra);
                } else {
                    printf("Invalid location type. Use 0 for cage or 1 for place.\n");
                    break;
                }

                if (hour >= 0 && hour < 24 && minute >= 0 && minute < 60) {
                    insert(animal, hour, minute, location, extra);
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
    return 0;
}

// Insert function
void insert(char *animal, int hour, int minute, int location, char *extra) {
    int i, j;

    // Check if the animal already exists
    for (i = 0; i < counter; i++) {
        if (strcmp(zoo[i].name, animal) == 0) {
            printf("Animal already exists in the schedule.\n");
            return;
        }
    }

    // Check if there's space in the list
    if (counter >= MAX_ANIMALS) {
        printf("Cannot add more animals. Maximum capacity reached.\n");
        return;
    }

    // Find the correct position based on time
    for (i = 0; i < counter; i++) {
        if (hour < zoo[i].time[0] || (hour == zoo[i].time[0] && minute < zoo[i].time[1])) {
            break;
        }
    }

    // Shift entries down to make space
    for (j = counter; j > i; j--) {
        zoo[j] = zoo[j - 1];
    }

    // Insert the new animal
    strcpy(zoo[i].name, animal);
    zoo[i].time[0] = hour;
    zoo[i].time[1] = minute;
    zoo[i].location = location;

    if (location == 0) {
        sscanf(extra, "%d %d", &zoo[i].info.cage[0], &zoo[i].info.cage[1]);
    } else {
        strcpy(zoo[i].info.place, extra);
    }

    counter++;
    printf("Animal added successfully.\n");
}

// Delete function
void delete(char *animal) {
    int i, j;

    // Find the animal in the list
    for (i = 0; i < counter; i++) {
        if (strcmp(zoo[i].name, animal) == 0) {
            // Shift entries up to fill the gap
            for (j = i; j < counter - 1; j++) {
                zoo[j] = zoo[j + 1];
            }
            counter--;
            printf("Animal removed from the schedule.\n");
            return;
        }
    }

    printf("Animal not found in the schedule.\n");
}

// Show function using pointers
void showall() {
    if (counter == 0) {
        printf("The schedule is empty.\n");
        return;
    }

    Animal *ptr = zoo; // Pointer to the start of the array

    printf("Animal          Time    Location\n");
    printf("------------------------------------\n");
    for (int i = 0; i < counter; i++, ptr++) {
        printf("%-15s %02d:%02d ", ptr->name, ptr->time[0], ptr->time[1]);

        if (ptr->location == 0) {
            printf("cage: %d,%d\n", ptr->info.cage[0], ptr->info.cage[1]);
        } else {
            printf("%s\n", ptr->info.place);
        }
    }
}

// Change function (remains the same)
void change(char *animal, int new_hour, int new_minute) {
    int i;

    // Search for the animal
    for (i = 0; i < counter; i++) {
        if (strcmp(zoo[i].name, animal) == 0) {
            zoo[i].time[0] = new_hour;
            zoo[i].time[1] = new_minute;
            printf("Feeding time for %s updated successfully.\n", animal);
            return;
        }
    }

    printf("Animal not found in the schedule.\n");
}   


