#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void copy_file(const char *source, const char *destination) {
    int source_fd, dest_fd;
    ssize_t bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];

    // Open the source file in read-only mode
    source_fd = open(source, O_RDONLY);
    if (source_fd == -1) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // Open/create the destination file with write-only and create permissions
    dest_fd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (dest_fd == -1) {
        perror("Error opening/creating destination file");
        close(source_fd);
        exit(EXIT_FAILURE);
    }

    // Read from the source file and write to the destination file
    while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written == -1) {
            perror("Error writing to destination file");
            close(source_fd);
            close(dest_fd);
            exit(EXIT_FAILURE);
        }
    }

    if (bytes_read == -1) {
        perror("Error reading from source file");
    }

    // Close both source and destination files
    close(source_fd);
    close(dest_fd);

    printf("File copied successfully!\n");
}

int main() {
    char source_file[256], destination_file[256];

    // Get source and destination file names from the user
    printf("Enter the source file name: ");
    scanf("%s", source_file);
    printf("Enter the destination file name: ");
    scanf("%s", destination_file);

    // Call the function to copy the file
    copy_file(source_file, destination_file);

    return 0;
}
