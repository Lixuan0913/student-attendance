// *********************************************************
// Program: TC1L_Group01_main.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC1L
// Tutorial Class: TT1L
// Trimester: 2530
// Member_1: 252UC243XL | AISYAH BINTI AHMAD HAWARI | AISYAH.AHMAD.HAWARI1@student.mmu.edu.my | 01110691624
// Member_2: 252UC24216 | AMIRA SOFIA BINTI AZIZUL RAHMAN | AMIRA.SOFIA.AZIZUL1@student.mmu.edu.my | 01156786588
// Member_3: 252UC241RN | ELLY MAZLIN BINTI MOHD AZMIR | ELLY MAZLIN BINTI MOHD AZMIR | 0126623767
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
    ifstream fileCheck;
    string sheetName = "";
    string choice;

    // MENU LOOP
    do {
        cout << "===========================================" << endl;
        cout << "  STUDENT ATTENDANCE TRACKER - MILESTONE 1 " << endl;
        cout << "===========================================" << endl << endl;
        cout << "1. Create Attendance Sheet" << endl;
        cout << "2. Insert Attendance Data" << endl;
        cout << "3. View Attendance Sheet (CSV)" << endl;
        cout << "4. Exit" << endl;
        cout << "===========================================" << endl << endl;
        cout << "Enter your choice: " << endl;

        getline(cin, choice);

        // CREATE ATTENDANCE SHEET
        if (choice == "1") {
            sheetName = createAttendanceSheet();
        }

        // INSERT ATTENDANCE DATA
        else if (choice == "2"){
             cout << "Enter the attendance sheet name to open (e.g., attendance):\n";
             getline(cin, sheetName);

             // Parse filename and csv together
             string FileName = sheetName + ".csv";

             // Try open the file
             fileCheck.open(FileName,ios::in);

             // If file exist then open file or ask them go to create file
             if (fileCheck.is_open()) {
                 fileCheck.close(); // Close the file
                 insertData(FileName); // Pass file name to insertData

             } else {
               cout << "\n File does not exist. PLEASE CREATE ATTENDANCE SHEET FIRST!! \n" << endl; // Statement if file does not exist
               fileCheck.clear();// Clear fileCheck
             }
        }

        // VIEW ATTENDANCE SHEET (CSV)
        else if (choice == "3"){
             cout << "Enter the attendance sheet name to open (e.g., attendance):\n";
             getline(cin, sheetName);

             // Parse filename and csv together
             string FileName = sheetName + ".csv";

             // Try open the file
             fileCheck.open(FileName,ios::in);

             // If file exist then open file or ask them go to create file
             if (fileCheck.is_open()) {
                 fileCheck.close(); // Close the file
                 viewCSV(FileName); // Pass file name to insertData

             } else {
               cout << "\n File does not exist. PLEASE CREATE ATTENDANCE SHEET FIRST!! \n" << endl; // Statement if file does not exist
               fileCheck.clear();// Clear fileCheck
             }
        }

        // EXIT
        else if (choice == "4"){
             cout << "\n Goodbye!\n" << endl;
        }

        // DEFAULT INVALID (NUMBER OTHER THAN 1-4)
        else {
             cout << "\n Invalid choice. Please enter a number (1-4) \n" << endl;
        }

    } while (choice != "4");
        cout << "===========================================" << endl;
        cout << "End of Milestone 1 Output" << endl;
        cout << "===========================================" << endl;

        return 0;
}


string createAttendanceSheet() {
    ofstream outputFile;
    string sheetName;
    int numColumns;
    string columnNames[10];
    string columnTypes[10];

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

    //Create column names
    for (int i = 0; i < numColumns; i++) {
        cout << "\nColumn " << (i + 1) << ":\n";

        cout << "  Enter column name: ";
        getline(cin, columnNames[i]);

        // Get column data type
        cout << "  Choose data type for '" << columnNames[i] << "':\n";
        cout << "  1. Text\n";
        cout << "  2. Integer\n";
        cout << "  Enter choice (1 or 2): ";

        string typeChoice;
        getline(cin, typeChoice);

        //Store data type
        if (typeChoice == "1") {
            columnTypes[i] = "TEXT";
        } else if (typeChoice == "2") {
            columnTypes[i] = "INTEGER";
        } else {
            cout << "  Invalid choice! Defaulting to Text.\n";
            columnTypes[i] = "TEXT";
        }

        cout << "  Column '" << columnNames[i] << "' set to " << columnTypes[i] << " type.\n";
    }

    // Input in text file and column names
    for (int i = 0; i < numColumns; i++) {
        outputFile << columnNames[i];
        if (i < numColumns - 1) {
            outputFile << ",";
        }
    }
    outputFile << "\n";

    for (int i = 0; i < numColumns; i++) {
        outputFile << columnTypes[i];
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

//Function to insert a new row of attendance into a CSV file
void insertData(string fileName){

    vector<string> columns; // Stores column names extracted from header
    vector<string> columnTypes; //Stores column data types
    string line;

    ifstream inputFile(fileName);

    // Check if file exists / can be opened
    if (!inputFile) {
        cout << "Error opening file!" << endl;
    }

    //Read the first line of the file(header)
    getline(inputFile, line);
    string headerLine = line; // Save header

    //Read the second line (column types)
    getline(inputFile, line);
    string typeLine = line; // Save types line

    inputFile.close();

    //Parse column names from header line
    string header = headerLine;
    while(!header.empty()){
        int commaFound = header.find(",");
        string col = (commaFound != -1) ? header.substr(0, commaFound) : header;
        columns.push_back(col);
        header = (commaFound != -1) ? header.substr(commaFound + 1) : "";
    }

    //Parse column types from type line
    string types = typeLine;
    while(!types.empty()){
        int commaFound = types.find(",");
        string type = (commaFound != -1) ? types.substr(0, commaFound) : types;
        columnTypes.push_back(type);
        types = (commaFound != -1) ? types.substr(commaFound + 1) : "";
    }

    cout << "\n-------------------------------------------\n";
    cout << "Insert New Attendance Row\n";
    cout << "-------------------------------------------\n";

    int size = columns.size(); // Number of columns
    string userInput[size];

    ofstream outputfile(fileName, ios::app);  // Open file in append mode

    if(!outputfile)
        cout << "Error opening file for writing!\n";

    // Loop every columns
    for (int i = 0; i < size; i++) {
        while(true){
            // Condition for Status
            bool isStatus = (columns[i] == "STATUS" || columns[i] == "status" || columns[i] == "Status");

            //Check column type
            bool isIntegerType = (columnTypes[i] == "INTEGER");

            // Check whether the current column is Status and display prompt based on type
            if(isStatus)
                cout << "Enter " << columns[i] << " (Present: 1, Absent: 0): ";
            else if(isIntegerType)
                cout << "Enter " << columns[i] << " (Integer): ";
            else
                cout << "Enter " << columns[i] << " (Text): ";

            getline(cin, userInput[i]);

            //Validation based on data type
            if(isIntegerType){
                bool valid = true;
                for(char c : userInput[i]){
                    if(!isdigit(c) && c != '-') {
                        valid = false;
                        break;
                    }
                }

                //Check for valid integer format
                if(!userInput[i].empty() && userInput[i] != "-"){
                    // Check if it's a valid integer
                    for(size_t j = 0; j < userInput[i].length(); j++){
                        if(j == 0 && userInput[i][j] == '-') continue; // Allow minus sign at start
                        if(!isdigit(userInput[i][j])) {
                            valid = false;
                            break;
                        }
                    }
                } else {
                    valid = false;
                }

                if(!valid){
                    // Print error statement and re-enter for the first value
                    cout << "Invalid input. Please enter an integer value.\n";
                    continue;
                }
            }

            // Validation for StudentID (first column)
            if(i == 0 && !isIntegerType){
                // Only apply if not already validated as integer type
                bool valid = true;
                for(char c : userInput[i]){
                    if(!isdigit(c))
                        valid = false;
                }
                if(!valid){
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

void viewCSV(string fileName)
{
    ifstream inputFile;
    string columnNames;
    string line;
    inputFile.open(fileName, ios::in);
    if (inputFile)
    {
        cout << "\n\n-------------------------------------------" << endl;
        cout << "View Attendance Sheet(CSV Mode)" << endl;
        cout << "-------------------------------------------\n" << endl;

        getline(inputFile, columnNames);
        cout << "COLUMNS: " << columnNames << endl;

        getline(inputFile, line);

        cout << "DATA:\n";
        while (getline(inputFile, line))
        {
            cout << line << endl;
        }

        cout << "\n";
        inputFile.close();
    }
    else
    {
        cout << "ERROR: Cannot open file." << endl;
    }
}
