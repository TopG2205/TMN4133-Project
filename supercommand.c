#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h> 

// Function to create or open a file
void create_open_file() {
    char filename[256];
    int fd;

    printf("Enter the file name to create/open (with path if needed): ");
    scanf("%s", filename);

    // Open the file (O_CREAT to create if it doesn't exist)
    fd = open(filename, O_CREAT | O_RDWR, 0644);
    if (fd == -1) {
        perror("Error opening/creating file");
    } else {
        printf("File '%s' successfully created/opened.\n", filename);
        close(fd);
    }
}

//Funtion to read and edit file 
void read_file() {
    char filename[256];
    char buffer[1024];
    char new_content[4096]; // Buffer for new file content during editing
    int fd, bytesRead;

    printf("Enter the file name to read (with path if needed): ");
    scanf("%s", filename);

    // Open the file in read-only mode
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return;
    }

    printf("\nContents of '%s':\n", filename);
    while ((bytesRead = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytesRead] = '\0'; // Null-terminate the string
        printf("%s", buffer);
    }

    if (bytesRead == -1) {
        perror("Error reading file");
    }

    close(fd);
    printf("\n--- End of File ---\n");

    // Offer to edit the file
    printf("\nDo you want to edit this file (overwrite its content)? (y/n): ");
    char choice;
    getchar(); // Clear the newline left by scanf
    scanf("%c", &choice);

    if (choice == 'y' || choice == 'Y') {
        // Open the file in write mode (overwrite existing content)
        fd = open(filename, O_WRONLY | O_TRUNC);
        if (fd == -1) {
            perror("Error opening file for editing");
            return;
        }

        printf("Enter the new content for the file (end with CTRL+D):\n");
        getchar(); // Clear the newline again
        fgets(new_content, sizeof(new_content), stdin);

        // Write the new content to the file
        if (write(fd, new_content, strlen(new_content)) == -1) {
            perror("Error writing to file");
        } else {
            printf("File '%s' successfully updated.\n", filename);
        }

        close(fd);
    } else {
        printf("File not edited.\n");
    }
}


//Funtion to write file 
void write_to_file() {
    char filename[256];
    char buffer[1024];
    int fd;

    printf("Enter the file name to write to (with path if needed): ");
    scanf("%s", filename);

    // Open the file in write-only mode (create if it doesn't exist)
    fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return;
    }

    printf("Enter the text to write into the file: ");
    getchar(); // Clear the newline character left by the previous input
    fgets(buffer, sizeof(buffer), stdin);

    // Write the text to the file
    if (write(fd, buffer, strlen(buffer)) == -1) {
        perror("Error writing to file");
    } else {
        printf("Text successfully written to '%s'.\n", filename);
    }

    close(fd);
}

//funtion to delete file 
void delete_file() {
    char filename[256];

    printf("Enter the file name to delete (with path if needed): ");
    scanf("%s", filename);

    // Attempt to delete the file
    if (remove(filename) == 0) {
        printf("File '%s' successfully deleted.\n", filename);
    } else {
        perror("Error deleting file");
    }
}

// File operations menu
void file_operations() {
    int choice;

    while (1) {
        // File operations submenu
        printf("\n--- File Operations Menu ---\n");
        printf("1. Create/Open File\n");
        printf("2. Read File\n");
	printf("3. Write to File\n");
        printf("4. Delete FIle\n");
	printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create_open_file();
                break;
            case 2:
                read_file();
                break;
            case 3:
		write_to_file();
		break;
	    case 4: 
		delete_file();
		break;
	    case 5:
		return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Placeholder for directory operations
void directory_operations() {
    printf("Directory operations selected.\n");
    // Placeholder for directory operations functionality
}

// Placeholder for keylogger operations
void keylogger_operations() {
    printf("Keylogger operations selected.\n");
    // Placeholder for keylogger functionality
}

// Main menu
int main() {
    int choice;

    while (1) {
        // Display the main menu
        printf("\n--- Super Command Menu ---\n");
        printf("1. File Operations\n");
        printf("2. Directory Operations\n");
        printf("3. Keylogger Operations\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Handle user input
        switch (choice) {
            case 1:
                file_operations();
                break;
            case 2:
                directory_operations();
                break;
            case 3:
                keylogger_operations();
                break;
            case 4:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
