#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

// GroceryTracker class handles all item frequency operations
class GroceryTracker {
public:
    // Loads items from the input file and counts frequencies
    bool LoadInputFile(const string& fileName) {
        ifstream inFile(fileName);
        if (!inFile.is_open()) {
            cerr << "Error: Could not open input file." << endl;
            return false;
        }

        string item;
        while (inFile >> item) {
            itemFrequency[item]++;   // Count each item
        }

        inFile.close();
        return true;
    }

    // Writes frequency.dat backup file at program start
    bool WriteBackupFile(const string& fileName) const {
        ofstream outFile(fileName);
        if (!outFile.is_open()) {
            cerr << "Error: Could not create backup file." << endl;
            return false;
        }

        for (const auto& pair : itemFrequency) {
            outFile << pair.first << " " << pair.second << endl;
        }

        outFile.close();
        return true;
    }

    // Returns frequency of a specific item
    int GetFrequency(const string& item) const {
        auto it = itemFrequency.find(item);
        if (it != itemFrequency.end()) {
            return it->second;
        }
        return 0;
    }

    // Prints all items and their frequencies
    void PrintAllFrequencies() const {
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    // Prints histogram using asterisks
    void PrintHistogram() const {
        for (const auto& pair : itemFrequency) {
            cout << setw(12) << left << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }

private:
    map<string, int> itemFrequency;  // Stores item ? frequency
};

// Prints the user menu
void PrintMenu() {
    cout << endl;
    cout << "========== Corner Grocer Menu ==========" << endl;
    cout << "1. Look up frequency of a specific item" << endl;
    cout << "2. Print frequency of all items" << endl;
    cout << "3. Print histogram of all items" << endl;
    cout << "4. Exit program" << endl;
    cout << "========================================" << endl;
    cout << "Enter your choice: ";
}

int main() {
    GroceryTracker tracker;

    // Load input file
    if (!tracker.LoadInputFile("CS210_Project_Three_Input_File.txt")) {
        return 1;
    }

    // Create backup file automatically
    tracker.WriteBackupFile("frequency.dat");

    bool running = true;
    int choice;

    while (running) {
        PrintMenu();

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a number 1–4." << endl;
            continue;
        }

        cout << endl;

        switch (choice) {
        case 1: {
            string item;
            cout << "Enter item name: ";
            cin >> item;
            cout << item << " " << tracker.GetFrequency(item) << endl;
            break;
        }
        case 2:
            tracker.PrintAllFrequencies();
            break;

        case 3:
            tracker.PrintHistogram();
            break;

        case 4:
            cout << "Exiting program. Goodbye!" << endl;
            running = false;
            break;

        default:
            cout << "Invalid choice. Enter 1–4." << endl;
        }
    }

    return 0;
}
