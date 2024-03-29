#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class FileManager {
public:
    void createFile(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Unable to create file");
        }
        cout << "File '" << filename << "' created successfully.\n";
    }

    void writeFile(const string& filename, const string& data) {
        ofstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Unable to open file for writing");
        }
        file << data;
        cout << "Data written to file '" << filename << "' successfully.\n";
    }

    void displayFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Unable to open file for reading");
        }
        string line;
        cout << "Contents of file '" << filename << "':\n";
        while (getline(file, line)) {
            cout << line << '\n';
        }
    }

    void copyFile(const string& sourceFilename, const string& destFilename) {
        ifstream sourceFile(sourceFilename);
        if (!sourceFile.is_open()) {
            throw runtime_error("Unable to open source file for copying");
        }

        ofstream destFile(destFilename);
        if (!destFile.is_open()) {
            throw runtime_error("Unable to open destination file for copying");
        }

        destFile << sourceFile.rdbuf();

        cout << "Contents of file '" << sourceFilename << "' copied to '" << destFilename << "' successfully.\n";
    }

    void deleteFile(const string& filename) {
        if (remove(filename.c_str()) != 0) {
            throw runtime_error("Error deleting file");
        }
        cout << "File '" << filename << "' deleted successfully.\n";
    }

    void renameFile(const string& oldFilename, const string& newFilename) {
        if (rename(oldFilename.c_str(), newFilename.c_str()) != 0) {
            throw runtime_error("Error renaming file");
        }
        cout << "File '" << oldFilename << "' renamed to '" << newFilename << "' successfully.\n";
    }
};

int main() {
    FileManager fileManager;
    int choice;
    string filename, data, sourceFilename, destFilename;

    do {
        cout << "\nMenu:\n"
            << "1. Create File\n"
            << "2. Write to File\n"
            << "3. Display File\n"
            << "4. Copy File\n"
            << "5. Delete File\n"
            << "6. Rename File\n"
            << "7. Exit\n"
            << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter filename to create: ";
            cin >> filename;
            try {
                fileManager.createFile(filename);
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << '\n';
            }
            break;
        case 2:
            cout << "Enter filename to write: ";
            cin >> filename;
            cin.ignore();
            cout << "Enter data to write: ";
            getline(cin, data);
            try {
                fileManager.writeFile(filename, data);
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << '\n';
            }
            break;
        case 3:
            cout << "Enter filename to display: ";
            cin >> filename;
            try {
                fileManager.displayFile(filename);
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << '\n';
            }
            break;
        case 4:
            cout << "Enter source filename: ";
            cin >> sourceFilename;
            cout << "Enter destination filename: ";
            cin >> destFilename;
            try {
                fileManager.copyFile(sourceFilename, destFilename);
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << '\n';
            }
            break;
        case 5:
            cout << "Enter filename to delete: ";
            cin >> filename;
            try {
                fileManager.deleteFile(filename);
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << '\n';
            }
            break;
        case 6:
            cout << "Enter old filename: ";
            cin >> filename;
            cout << "Enter new filename: ";
            cin >> data;
            try {
                fileManager.renameFile(filename, data);
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << '\n';
            }
            break;
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 7.\n";
        }
    } while (choice != 7);
}