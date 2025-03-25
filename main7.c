#include "lab7.h"

Node* head = NULL;
Node* tail = NULL;

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("The name of the file is missing!\n");
        return 1;
    }

    // Read existing data from file
    read_file(argv[1]);

    int command, hour, minute;
    char animal[MAX_NAME_LEN];

    while (1) {
        printf("\nChoose an option:\n");
        printf("1 <animal> <hour> <minute> - Add an entry\n");
        printf("2 <animal> - Delete an entry\n");
        printf("3 - Show the list\n");
        printf("4 <animal> <hour> <minute> - Change feeding time\n");
        printf("0 - Save and Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &command);

        switch (command) {
            case 0:
                save_file(argv[1]);
                printf("Data saved. Exiting the program.\n");
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
