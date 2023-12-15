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
