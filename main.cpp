// *********************************************************
// Program: TC1L_Group01_main.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC1L
// Tutorial Class: TT1L
// Trimester: 2530
// Member_1: 252UC243XL | AISYAH BINTI AHMAD HAWARI | AISYAH.AHMAD.HAWARI1@student.mmu.edu.my | 01110691624
// Member_2: 252UC24216 | AMIRA SOFIA BINTI AZIZUL RAHMAN | AMIRA.SOFIA.AZIZUL1@student.mmu.edu.my | 01156786588
// Member_3: 252UC241RN | ELLY MAZLIN BINTI MOHD AZMIR | ELLY MAZLIN BINTI MOHD AZMIR | 012662 3767
// Member_4: 252UC242JW | YAP LI XUAN | yap.li.xuan1@student.mmu.edu.my | 0126371496
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

void content(string);


int main() {

    ifstream inputFile;
    ofstream outputFile;
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

    outputFile.open(sheetName);
    string text;
    cin >> text;

    outputFile << text;

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

    cout << "\nSheet structure created successfully.\n" <<endl;


    return 0;
}

