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
#include <vector>
#include <limits>
using namespace std;

void content(string);
void insertData(string);

int main() {
    ifstream inputFile;
    ofstream outputFile;
    string sheetName;
    int numColumns;
    string columnNames[10];
    char choice;

    cout << " ===========================================" << endl;
    cout << "  STUDENT ATTENDANCE TRACKER - MILESTONE 1 " << endl;
    cout << " ===========================================" << endl << endl;

    cout << "Enter attendance sheet name: ";
    getline(cin, sheetName);

    // create text file
    outputFile.open(sheetName + ".txt");

    cout << "Attendance sheet \"" << sheetName << "\" created successfully.\n\n";

    // create number of columns
    do {
        cout << "Define number of columns (max 10): ";
        cin >> numColumns;

        if (numColumns < 1 || numColumns > 10) {
            cout << "Please enter a number between 1 and 10.\n";
        }
    } while (numColumns < 1 || numColumns > 10);

    cin.ignore();

    //create column names
    for (int i = 0; i < numColumns; i++) {
        cout << "Enter column " << (i + 1) << " name: ";
        getline(cin, columnNames[i]);
    }

    //input in text file


    for (int i = 0; i < numColumns; i++) {
        outputFile << columnNames[i];
        if (i < numColumns - 1) {
            outputFile << ",";
        }
    }
    outputFile << "\n";

    outputFile.close();

    cout << "\nSheet structure created successfully and saved to '" << sheetName << ".txt'.\n";

    do{
    cout << "Do you want insert data?(y/n):\n";
    cin >> choice;

      if(choice == 'y' || choice == 'Y')
         insertData(sheetName);
      else if(choice == 'n' || choice == 'N'){
        cout << "Goodbye!\n";
        break;
      }

      else
         cout << "Please enter either y or n\n";

    }while(true);


    return 0;
}

void insertData(string sheetname){
   vector<string> columns;
   string line;

   string filename = sheetname + ".txt";
   ifstream inputFile(filename);

   if (!inputFile) {
        cout << "Error opening file!" << endl;

    }

    getline(inputFile, line);
    inputFile.close();

    //Put all header to an vector
    while(!line.empty()){
        // Seperate the value by checking comma
        int commaFound = line.find(",");
        //
        string col = (commaFound!=1)? line.substr(0,commaFound) : line;

        while (!col.empty() && col[0] == ' ') col.erase(0, 1);
        while (!col.empty() && col[col.size()-1] == ' ') col.pop_back();

        columns.push_back(col);

        line = (commaFound != -1) ? line.substr(commaFound + 1) : "";

    }


   cout << "\n-------------------------------------------\n";
   cout << "Insert New Attendance Row\n";
   cout << "-------------------------------------------\n";

   int size = columns.size();
   string userInput[size];

   ofstream outputfile(filename, ios::app);

   if(!outputfile) cout << "Error opening file for writing!\n";

   cin.ignore();


   for (int i = 0; i < size; i++) {
       while(true){

            if(columns[i] == "STATUS" || columns[i] == "status" || columns[i] == "Status")
                cout << "Enter " << columns[i] << " (Present: 1, Absent: 0): ";

            else
              cout << "Enter " << columns[i] << ":";

            getline(cin, userInput[i]);

            // Check if StudentID are digits
            if(i == 0){
               bool valid = true;
               for(char c : userInput[i]){
                    if(!isdigit(c))
                       valid = false;
               }

            if(!valid){
                cout << "Invalid INT value. Please enter a number." << endl;
                continue;
            }

            }

        break;
    }
    //Insert value into file
    outputfile << userInput[i];
    if(i != size - 1) outputfile << ",";

   }
   outputfile << "\n";
   outputfile.close();

 cout << "\nRow inserted successfully.\n";
    /*for(int i = 0; i < size; i++)
        cout << columns[i] << ": " << userInput[i] << endl;* for debug use/
}

