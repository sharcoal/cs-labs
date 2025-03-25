#include "lab9.h" 

Node* head = NULL;
Node* tail = NULL;
pthread_mutex_t lock;
pthread_t thread_id;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("missing arguments, use ./lab9 <text_file> <binary_file>\n");
        return 1;
    }

    pthread_mutex_init(&lock, NULL);
    read_file(argv[1]);

    if (pthread_create(&thread_id, NULL, auto_save_thread, argv[2]) != 0) {
        printf("error creating auto-save thread.\n");
        return 1;
    }

    int command, hour, minute;
    char animal[MAX_NAME_LEN];
    
    while (1) {
        printf("\nChoose an option:\n");
        printf("1 <animal> <hour> <minute> - Add an entry\n");
        printf("2 <animal> - Delete an entry\n");
        printf("3 - Show the list\n");
        printf("4 <animal> <hour> <minute> - Change feeding time\n");
        printf("5 - Show the list backwards\n");
        printf("6 - Show contents of the binary file\n");
        printf("0 - Save, delete all, and quit\n");
        printf("Enter your choice: ");
        scanf("%d", &command);

        switch (command) {
            case 0:
                pthread_cancel(thread_id);
                pthread_join(thread_id, NULL);
                save_file(argv[1]);
                delete_all(head);
                pthread_mutex_destroy(&lock);
                printf("Data saved. All nodes deleted. Exiting program.\n");
                return 0;

            case 1:
                printf("Enter animal name, hour (0-23), and minute (0-59): ");
                scanf("%s %d %d", animal, &hour, &minute);
                if (hour >= 0 && hour < 24 && minute >= 0 && minute < 60)
                    insert(animal, hour, minute);
                else 
                    printf("Invalid time. Please enter hours (0-23) and minutes (0-59).\n");
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

            case 5:
                printf("Displaying list in reverse order:\n");
                show_backwards(head);
                break;

            case 6:
                read_binary_file(argv[2]);
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}
