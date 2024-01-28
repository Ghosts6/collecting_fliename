![baner](https://github.com/Ghosts6/Local-website/blob/main/img/Baner.png)

# collecting_fliename
Collecting file data in specific path with help of c++ :
both program write with c++ and inclue library like iostream stirng vectore filesystem and some more,we have two differend def firs we have main for get path from user and run porgram and  sortFileNamesAndFormats too show result
# First program:
in this porgram we use some cmd command like dir with options: /s /b /a-d to print file data
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <cstdio>
using namespace std;
namespace fs = std::filesystem;

void sortFileNamesAndFormats(const string& path);

int main() {
    string path;
    cout << "Enter the directory path: ";
    getline(cin, path);
    sortFileNamesAndFormats(path);
    return 0;
}

void sortFileNamesAndFormats(const string& path) {
    vector<string> arr;
    string cmd = "dir \"" + path + "\" /s /b /a-d"; 
    FILE* pipe = _popen(cmd.c_str(), "r");
    if (!pipe) {
        cout << "Error: Unable to open pipe.\n";
        return;
    }
    char buffer[128];
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != nullptr) {
            string file(buffer);
            file.erase(remove(file.begin(), file.end(), '\n'), file.end());
            arr.push_back(file);
        }
    }

    _pclose(pipe);

    for (string& file : arr) {
        size_t lastDot = file.find_last_of(".");
        if (lastDot != string::npos) {
            file = file.substr(0, lastDot);
        }
    }

    sort(arr.begin(), arr.end());

    cout << "Sorted file names and their formats:\n";
    for (const string& file : arr) {
        cout << file << endl;
    }
}

```
# Second program:
unlike first one at this porgram we use somme method and loops to print file data and sort the data into the file which will be create in same path
```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

void sortFileNamesAndFormats(const string& path);

int main() {
    string path;

    cout << "Enter the directory path: ";
    getline(cin, path);

    sortFileNamesAndFormats(path);

    return 0;
}

void sortFileNamesAndFormats(const string& path) {
    vector<string> arr;


    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            string filename = entry.path().filename().string();
            arr.push_back(filename);
        }
    }

    for (string& file : arr) {
        size_t lastDot = file.find_last_of(".");
        if (lastDot != string::npos) {
            file = file.substr(0, lastDot);
        }
    }

    sort(arr.begin(), arr.end());

    cout << "Sorted file names and their formats:\n";
    for (const string& file : arr) {
        cout << file << endl;
    }

    string filePath = path + "/sorted_file_names.txt";
    ofstream outputFile(filePath);

    if (outputFile.is_open()) {
        for (const string& file : arr) {
            outputFile << file << endl;
        }
        outputFile.close();
        cout << "Sorted file names and their formats have been saved to: " << filePath << endl;
    } else {
        cout << "Unable to create the file." << endl;
    }
}
```

# Collect_filename_withc

this time we write same program but with different language and the only difference is this time program support differend os include win mac linux
```c
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

```
