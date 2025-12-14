// *********************************************************
// Program: YOUR_FILENAME.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC1L
// Tutorial Class: TT4L
// Trimester: 2530
// Member_1: ID | NAME | EMAIL | PHONE
// Member_2: 252UC24216 | Amira Sofia Azizul | amira.sofia.azizul1@student.mmu.edu.my | 01156786588
// Member_3: ID | NAME | EMAIL | PHONE
// Member_4: ID | NAME | EMAIL | PHONE
// *********************************************************
// Task Distribution
// Member_1:
// Member_2:
// Member_3:
// Member_4:
// *********************************************************


#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main() {
    ifstream inputFile;
    ofstream outputFile;
    string sheetName;
    int numColumns;
    string columnNames[10];
    string studentData[100][10]; // StudentID, Name, Status will be stored here
    int studentCount = 0;
    int choice;

    cout << " ===========================================" << endl;
    cout << "  STUDENT ATTENDANCE TRACKER - MILESTONE 1 " << endl;
    cout << " ===========================================" << endl << endl;

    cout << "Enter attendance sheet name: ";
    getline(cin, sheetName);
    cout << "Attendance sheet \"" << sheetName << "\" created successfully.\n\n";

    // Create number of columns
    do {
        cout << "Define number of columns (max 10): ";
        cin >> numColumns;

        if (numColumns < 1 || numColumns > 10) {
            cout << "Please enter a number between 1 and 10.\n";
        }
    } while (numColumns < 1 || numColumns > 10);

    cin.ignore(); // Clear unwanted character

    // Create column names
    for (int i = 0; i < numColumns; i++) {
        cout << "Enter column " << (i + 1) << " name: ";
        getline(cin, columnNames[i]);
    }

    cout << "\nSheet structure created successfully.\n" << endl;

    // Now show the menu for additional operations
    do {
        cout << "\n===========================================\n";
        cout << "        ADDITIONAL FILE OPERATIONS\n";
        cout << "===========================================\n";
        cout << "1. Insert New Attendance Row\n";
        cout << "2. Display Current Sheet\n";
        cout << "3. Save Sheet to File\n";
        cout << "4. Load Sheet from File\n";
        cout << "5. Exit\n";
        cout << "===========================================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice) {
            case 1: { // Insert New Attendance Row
                if (studentCount >= 100) {
                    cout << "Maximum number of students reached!\n";
                    break;
                }

                cout << "-------------------------------------------\n";
                cout << "Insert New Attendance Row\n";
                cout << "-------------------------------------------\n";

                // Get data for each column
                for (int i = 0; i < numColumns; i++) {
                    cout << "Enter " << columnNames[i] << ": ";

                    // Special prompt for Status column
                    if (columnNames[i].find("Status") != string::npos ||
                        columnNames[i].find("status") != string::npos) {
                        cout << "(Present: 1, Absent: 0): ";
                    }

                    getline(cin, studentData[studentCount][i]);
                }

                studentCount++;
                cout << "Row inserted successfully.\n";
                break;
            }

            case 2: { // Display current sheet
                cout << "\n=== ATTENDANCE SHEET: " << sheetName << " ===\n";

                // Display column headers
                cout << "\n";
                for (int i = 0; i < numColumns; i++) {
                    cout << columnNames[i];
                    if (i < numColumns - 1) cout << "\t";
                }
                cout << endl;
                cout << "----------------------------------------------------------\n";

                // Display student data
                if (studentCount == 0) {
                    cout << "No attendance data available.\n";
                } else {
                    for (int i = 0; i < studentCount; i++) {
                        for (int j = 0; j < numColumns; j++) {
                            cout << studentData[i][j];
                            if (j < numColumns - 1) cout << "\t";
                        }
                        cout << endl;
                    }
                }
                cout << "\nTotal rows: " << studentCount << endl;
                break;
            }

            case 3: { // Save sheet to file
                string filename = sheetName + ".txt";
                outputFile.open(filename);

                if (!outputFile) {
                    cout << "Error creating file!\n";
                    break;
                }

                // Save sheet metadata
                outputFile << sheetName << endl;
                outputFile << numColumns << endl;

                // Save column names
                for (int i = 0; i < numColumns; i++) {
                    outputFile << columnNames[i] << endl;
                }

                // Save student count
                outputFile << studentCount << endl;

                // Save student data
                for (int i = 0; i < studentCount; i++) {
                    for (int j = 0; j < numColumns; j++) {
                        outputFile << studentData[i][j] << endl;
                    }
                }

                outputFile.close();
                cout << "\nSheet saved successfully to '" << filename << "'\n";
                break;
            }

            case 4: { // Load sheet from file
                cout << "\n=== LOAD SHEET FROM FILE ===\n";
                cout << "Enter sheet name to load: ";
                string loadName;
                getline(cin, loadName);

                string filename = loadName + ".txt";
                inputFile.open(filename);

                if (!inputFile) {
                    cout << "Error: File '" << filename << "' not found!\n";
                    break;
                }

                // Load sheet metadata
                getline(inputFile, sheetName);
                inputFile >> numColumns;
                inputFile.ignore(); // Clear newline character

                // Load column names
                for (int i = 0; i < numColumns; i++) {
                    getline(inputFile, columnNames[i]);
                }

                // Load student count
                inputFile >> studentCount;
                inputFile.ignore(); // Clear newline character

                // Load student data
                for (int i = 0; i < studentCount; i++) {
                    for (int j = 0; j < numColumns; j++) {
                        getline(inputFile, studentData[i][j]);
                    }
                }

                inputFile.close();

                // Show the loaded sheet info
                cout << "\n===========================================\n";
                cout << "  STUDENT ATTENDANCE TRACKER - MILESTONE 1\n";
                cout << "===========================================\n\n";
                cout << "Attendance sheet \"" << sheetName << "\" loaded successfully.\n";
                cout << "Number of columns: " << numColumns << endl;
                cout << "Number of rows: " << studentCount << endl;
                break;
            }

            case 5: // Exit
                cout << "\nExiting program. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}
