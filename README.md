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
