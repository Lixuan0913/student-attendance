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
string createAttendanceSheet();
void viewCSV(string);

int main() {
    ifstream inputFile;
    string sheetName;
    char choice;
    string sheet;
    char view;

    cout << " ===========================================" << endl;
    cout << "  STUDENT ATTENDANCE TRACKER - MILESTONE 1 " << endl;
    cout << " ===========================================" << endl << endl;

    sheetName = createAttendanceSheet();

    do{
    cout << "Do you want insert data?(y/n):\n";
    cin >> choice;

      if(choice == 'y' || choice == 'Y')
         insertData(sheetName);
      else if(choice == 'n' || choice == 'N'){
       // cout << "Goodbye!\n";
        break;
      }

      else
         cout << "Please enter either y or n\n";

    }while(true);

    do {
        /*string columnNames;
        string line;*/

        cout << "\nDo you want to view attendance sheet in csv mode?(y/n):" << endl;
        cin >> view;
        if (view == 'y' || view == 'Y')
        {
            viewCSV(sheetName);
            break;

        }
        else if (view == 'n' || view == 'N')
        {
            cout << "Goodbye!\n";
            break;
        }
        else
        {
            cout << "Please enter either y or n\n";
            cin.clear();
            cin.ignore();
        }


    } while(true);

    cout << "\n-------------------------------------------\n";
    cout << "End of Milestone 1 Output\n";
    cout << "-------------------------------------------\n";
    return 0;
}


string createAttendanceSheet() {
    ofstream outputFile;
    string sheetName;
    int numColumns;
    string columnNames[10];

    while (true) {
        cout << "Enter attendance sheet name: ";
        getline(cin, sheetName);

        // Check if file exists
        ifstream f(sheetName + ".csv");
        if (f.good()) {
            cout << "Error: The file \"" << sheetName << ".csv\" already exists. Please try another name.\n\n";
        }
        else {
            // File does not exist, safe to open a new file
            outputFile.open(sheetName + ".csv");
            break;
        }
    }

    cout << "Attendance sheet \"" << sheetName << "\" created successfully.\n\n";

    // Create number of columns
    do {
        cout << "Define number of columns (max 10): ";
        cin >> numColumns;

         if (cin.fail()) {
              cout << "Invalid input! Please enter a number only.\n\n";
              cin.clear();                // Clear error flag
              cin.ignore(1000,'\n');     // Remove invalid input from buffer
             continue;
        }

        else if (numColumns < 1 || numColumns > 10) {
            cout << "Please enter a number between 1 and 10.\n";
            continue;
        }

        break;

    } while (numColumns < 1 || numColumns > 10);

    cin.ignore(); // Clear buffer

    // Create column names
    for (int i = 0; i < numColumns; i++) {
        cout << "Enter column " << (i + 1) << " name: ";
        getline(cin, columnNames[i]);
    }

    // Input in text file
    for (int i = 0; i < numColumns; i++) {
        outputFile << columnNames[i];
        if (i < numColumns - 1) {
            outputFile << ",";
        }
    }
    outputFile << "\n";
    outputFile.close();

    cout << "\nSheet structure created successfully and saved to '" << sheetName << ".csv'.\n";

    //return back the sheetName to main
    return sheetName;
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

void viewCSV(string sheetName)
{
    ifstream inputFile;
    string columnNames;
    //string sheetName;
    string line;
    inputFile.open(sheetName + ".csv", ios::in);
    if (inputFile)
    {


    cout << "\n\n-------------------------------------------" << endl;
    cout << "View Attendance Sheet(CSV Mode)" << endl;
    cout << "-------------------------------------------\n" << endl;

    getline(inputFile,columnNames);
    cout << columnNames << endl;
        while (getline(inputFile,line))
        {
            cout << line << endl;
        }
    inputFile.close();
    cout << "End of file reading." << endl;
    }
    else
    {
       cout << "ERROR: Cannot open file." << endl;

    }
}
