#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #define OS_COMMAND "dir /B \"%s\""
#else
    #define OS_COMMAND "ls \"%s\""
#endif

void sortFileNamesAndFormats(const char* path);

int main() {
    char path[256];

    printf("Enter the directory path: ");
    fgets(path, sizeof(path), stdin);
    path[strcspn(path, "\n")] = '\0';  

    sortFileNamesAndFormats(path);

    return 0;
}

void sortFileNamesAndFormats(const char* path) {
    char command[512];
    sprintf(command, OS_COMMAND, path);

    FILE* pipe = popen(command, "r");
    if (!pipe) {
        perror("Error opening pipe");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    size_t count = 0;
    char* arr[100];  

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        arr[count] = strdup(buffer);
        count++;

        if (count >= sizeof(arr) / sizeof(arr[0])) {
            fprintf(stderr, "Too many files, array overflow\n");
            exit(EXIT_FAILURE);
        }
    }

    pclose(pipe);

    for (size_t i = 0; i < count; i++) {
        size_t lastDot = strcspn(arr[i], ".");
        if (lastDot != strlen(arr[i])) {
            arr[i][lastDot] = '\0';
        }
    }

    qsort(arr, count, sizeof(char*), strcmp);

    // Print sorted file names
    printf("Sorted file names and their formats:\n");
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", arr[i]);
    }


    FILE* outputFile = fopen("sorted_file_names.txt", "w");
    if (!outputFile) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < count; i++) {
        fprintf(outputFile, "%s\n", arr[i]);
        free(arr[i]); 
    }

    fclose(outputFile);
    printf("Sorted file names and their formats have been saved to: sorted_file_names.txt\n");
}

