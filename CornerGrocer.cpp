// CornerGrocer.cpp
// Corner Grocer Project
// Author: Jonathan Streetman
// Date: Oct 16 2025
// Purpose: Read day's purchases from CS210_Project_Three_Input_File.txt,
//          produce frequency counts, write a backup frequency.dat, and
//          provide a menu for the user to query and display results.

// Required headers
// I have the coolest instructor :D
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm> // transform
#include <cctype>    // tolower
#include <limits>    // numeric_limits

using std::cin;
using std::cout;
using std::endl;
using std::string;

/*
  ItemTracker class
  - Keeps frequency counts of items (case-insensitive keys).
  - Stores first-seen original capitalization to print nice names.
*/
class ItemTracker {
public:
    // Constructor: reads input file, builds map, and writes backup file.
    ItemTracker(const string &inputFileName, const string &backupFileName) {
        bool ok = readInputFile(inputFileName);
        if (!ok) {
            throw std::runtime_error("Failed to open input file: " + inputFileName);
        }
        writeBackupFile(backupFileName);
    }

    // Returns frequency of a given item (case-insensitive).
    int getFrequency(const string &item) const {
        string key = normalize(item);
        auto it = frequency.find(key);
        return (it == frequency.end()) ? 0 : it->second;
    }

    // Prints all items with counts (alphabetical by normalized key).
    void printAllFrequencies() const {
        if (frequency.empty()) {
            cout << "No items recorded." << endl;
            return;
        }
        cout << "Item\tCount" << endl;
        cout << "----------------" << endl;
        for (const auto &p : frequency) {
            const string &key = p.first;
            const int count = p.second;
            const string &displayName = originalName.at(key);
            cout << displayName << "\t" << count << endl;
        }
    }

    // Prints a histogram (item followed by count of '*').
    void printHistogram() const {
        if (frequency.empty()) {
            cout << "No items recorded." << endl;
            return;
        }
        for (const auto &p : frequency) {
            const string &key = p.first;
            const int count = p.second;
            const string &displayName = originalName.at(key);
            cout << displayName << " ";
            for (int i = 0; i < count; ++i) cout << "*";
            cout << endl;
        }
    }

private:
    std::map<string,int> frequency;        // normalized -> count
    std::map<string,string> originalName;  // normalized -> first-seen original capitalization

    // Normalize to lowercase (helper)
    static string normalize(const string &s) {
        string out = s;
        std::transform(out.begin(), out.end(), out.begin(),
                       [](unsigned char c){ return std::tolower(c); });
        return out;
    }

    // Read input file and populate maps. Returns false if file can't be opened.
    bool readInputFile(const string &inputFileName) {
        std::ifstream inFile(inputFileName);
        if (!inFile.is_open()) return false;

        string line;
        while (std::getline(inFile, line)) {
            // Trim whitespace from both ends (simple)
            const auto ltrim = [](string &str) {
                while (!str.empty() && std::isspace((unsigned char)str.front())) str.erase(str.begin());
            };
            const auto rtrim = [](string &str) {
                while (!str.empty() && std::isspace((unsigned char)str.back())) str.pop_back();
            };
            ltrim(line);
            rtrim(line);

            if (line.empty()) continue; // skip blank lines

            string key = normalize(line);
            if (frequency.find(key) == frequency.end()) {
                // first time we see this item
                frequency[key] = 1;
                originalName[key] = line; // store original capitalization
            } else {
                frequency[key] += 1;
            }
        }
        inFile.close();
        return true;
    }

    // Write backup file frequency.dat with item and count pairs (alphabetical)
    void writeBackupFile(const string &backupFileName) const {
        std::ofstream outFile(backupFileName);
        if (!outFile.is_open()) {
            // If backup cannot be written, we report to stdout but continue.
            cout << "Warning: could not create backup file '" << backupFileName << "'." << endl;
            return;
        }
        for (const auto &p : frequency) {
            const string &key = p.first;
            const int count = p.second;
            const string &displayName = originalName.at(key);
            outFile << displayName << " " << count << "\n";
        }
        outFile.close();
    }
}; // end class ItemTracker

// Helper: read integer menu choice with validation
int readMenuChoice() {
    int choice;
    while (true) {
        cout << "\nEnter choice (1-4): ";
        if (cin >> choice) {
            if (choice >= 1 && choice <= 4) {
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear rest of line
                return choice;
            }
        } else {
            // clear bad input
            cin.clear();
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
    }
}

// Helper: read a non-empty line from user (for searching item)
string readNonEmptyLine(const string &prompt) {
    string input;
    while (true) {
        cout << prompt;
        std::getline(cin, input);
        // Trim simple whitespace
        auto ltrim = [](string &s){ while (!s.empty() && std::isspace((unsigned char)s.front())) s.erase(s.begin()); };
        auto rtrim = [](string &s){ while (!s.empty() && std::isspace((unsigned char)s.back())) s.pop_back(); };
        ltrim(input);
        rtrim(input);
        if (!input.empty()) return input;
        cout << "Input cannot be empty. Please try again." << endl;
    }
}

int main() {
    const string inputFileName = "CS210_Project_Three_Input_File.txt";
    const string backupFileName = "frequency.dat";

    cout << "Corner Grocer Item-Tracking Program\n";
    cout << "-----------------------------------\n";

    ItemTracker *tracker = nullptr;
    try {
        // Construct tracker; this will read input file and immediately write backup file.
        tracker = new ItemTracker(inputFileName, backupFileName);
        cout << "Backup '" << backupFileName << "' created successfully (or already overwritten)." << endl;
    } catch (const std::exception &e) {
        cout << "Error initializing ItemTracker: " << e.what() << endl;
        cout << "Make sure '" << inputFileName << "' exists in the program's working directory." << endl;
        return 1;
    }

    bool running = true;
    while (running) {
        cout << "\nMenu Options:\n";
        cout << "1. Search for an item frequency (enter item name)\n";
        cout << "2. Print the frequency of all items\n";
        cout << "3. Print histogram of item frequencies\n";
        cout << "4. Exit program\n";

        int choice = readMenuChoice();

        switch (choice) {
            case 1: {
                string item = readNonEmptyLine("Enter the item (word) to search for: ");
                int freq = tracker->getFrequency(item);
                cout << "'" << item << "' appears " << freq << (freq == 1 ? " time." : " times.") << endl;
                break;
            }
            case 2:
                cout << "\nAll items with frequencies:\n";
                tracker->printAllFrequencies();
                break;
            case 3:
                cout << "\nHistogram (item followed by asterisks):\n";
                tracker->printHistogram();
                break;
            case 4:
                cout << "Exiting program. Goodbye!" << endl;
                running = false;
                break;
            default:
                // Shouldn't happen due to validation
                cout << "Unexpected choice." << endl;
        }
    }

    delete tracker;
    return 0;
}
