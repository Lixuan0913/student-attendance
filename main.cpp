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
#include <filesystem>
using namespace std;

void content(string);
void insertData(string);

int main() {
    ofstream outputFile;
    string sheetName;
    int numColumns;
    string columnNames[10];
    char choice;

    cout << " ===========================================" << endl;
    cout << "  STUDENT ATTENDANCE TRACKER - MILESTONE 1 " << endl;
    cout << " ===========================================" << endl << endl;

    while(true){
        cout << "Enter attendance sheet name: ";
        getline(cin, sheetName);

    // create text file
    outputFile.open(sheetName + ".csv");


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

    cout << "\nSheet structure created successfully and saved to '" << sheetName << ".csv'.\n";

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

// Function to insert a new row of attendance into a CSV file
void insertData(string sheetname){

   vector<string> columns; // Stores column names extracted from header
   string line;

   string filename = sheetname + ".csv";
   ifstream inputFile(filename);

    // Check if file exists / can be opened
   if (!inputFile) {
        cout << "Error opening file!" << endl;

    }

    // Read the first line of file (header)
    getline(inputFile,line);

    inputFile.close();

    //Put all header to an vector
    while(!line.empty()){
        // Seperate the value by checking comma
        int commaFound = line.find(",");

        string col = (commaFound!=1)? line.substr(0,commaFound) : line;

        //Push column name into array columns
        columns.push_back(col);

        // Remove the extracted column part from line
        line = (commaFound != -1) ? line.substr(commaFound + 1) : "";

    }


  cout << "\n-------------------------------------------\n";
   cout << "Insert New Attendance Row\n";
   cout << "-------------------------------------------\n";

   int size = columns.size(); // Number of columns
   string userInput[size];

   ofstream outputfile(filename, ios::app);  // Open file in append mode

   if(!outputfile)
      cout << "Error opening file for writing!\n";

   cin.ignore(); // Clear leftover newline from input buffer


   // Loop every columns
   for (int i = 0; i < size; i++) {
       while(true){

            // Condition for Status
            bool isStatus = (columns[i] == "STATUS" || columns[i] == "status" || columns[i] == "Status");

            // Check whether the current column is Status
            if(isStatus)
                cout << "Enter " << columns[i] << " (Present: 1, Absent: 0): ";

            else
              cout << "Enter " << columns[i] << ":";

            getline(cin, userInput[i]);

            // Validation for StudentID are digits
            if(i == 0){
               bool valid = true;
               // Check for every number
               for(char c : userInput[i]){
                    // Condition for non-digit number
                    if(!isdigit(c))
                       valid = false;
               }

              if(!valid){
                  // Print error statement and re-enter for the first value
                  cout << "Invalid INT value. Please enter a number.\n" << endl;
                  continue;
              }
            }

            //Validation for Status are digits
            if(isStatus){
                if(userInput[i]!= "0" && userInput[i]!= "1"){
                    cout << "Status only accept either 0(Absent) or 1(Present). Please re-enter" << endl;
                    continue;
                }
            }

        break; // Exit validation loop
    }
    //Insert value into file
    outputfile << userInput[i];
    if(i != size - 1) outputfile << ",";

   }

   outputfile << "\n"; // New row completed
   outputfile.close(); // Save file

 cout << "\nRow inserted successfully.\n";

}


