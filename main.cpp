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


#include <iostream>
#include <string>
using namespace std;

int main() {
    string sheetName;
    int numColumns;
    string columnNames[10];

    cout << " ===========================================" << endl;
    cout << "  STUDENT ATTENDANCE TRACKER - MILESTONE 1 " << endl;
    cout << " ===========================================" << endl << endl;

    cout << "Enter attendance sheet name: ";
    getline(cin, sheetName);
    cout << "Attendance sheet \"" << sheetName << "\" created successfully.\n\n";

    // create number of columns
    do {
        cout << "Define number of columns (max 10): ";
        cin >> numColumns;

        if (numColumns < 1 || numColumns > 10) {
            cout << "Please enter a number between 1 and 10.\n";
        }
    } while (numColumns < 1 || numColumns > 10);

    cin.ignore(); // clear unwanted character

    //create column names
    for (int i = 0; i < numColumns; i++) {
        cout << "Enter column " << (i + 1) << " name: ";
        getline(cin, columnNames[i]);
    }

    cout << "\nSheet structure created successfully.\n";

    return 0;
}
