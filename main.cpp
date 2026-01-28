// *********************************************************
// Program: TC1L_Group01_main.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC1L
// Tutorial Class: TT1L
// Trimester: 2530
// Member_1: 252UC243XL | AISYAH BINTI AHMAD HAWARI | AISYAH.AHMAD.HAWARI1@student.mmu.edu.my | 01110691624
// Member_2: 252UC24216 | AMIRA SOFIA BINTI AZIZUL RAHMAN | AMIRA.SOFIA.AZIZUL1@student.mmu.edu.my | 01156786588
// Member_3: 252UC241RN | ELLY MAZLIN BINTI MOHD AZMIR | elly.mazlin.mohd1@student.mmu.edu.my| 0126623767
// Member_4: 252UC242JW | YAP LI XUAN | yap.li.xuan1@student.mmu.edu.my | 0126371496
// *********************************************************
// Task Distribution
// Member_1: viewCSV
// Member_2: createAttendanceSheet
// Member_3: flowchart and menu
// Member_4: insertData
// *********************************************************

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
using namespace std;
namespace fs = filesystem;

void content(string);
void insertData(string);
string createAttendanceSheet(string &);
void viewCSV(string);
void deleteRow(string);

int main() {
    ifstream file;
    ofstream fileCreate;
    string choice, termName,sheetName,txt_file,currentLine,fileName;

    cout << "===========================================\n";
    cout << "   STUDENT ATTENDANCE TRACKER - MILESTONE 2  \n";
    cout << "===========================================\n\n";

    cout << "Create School Term (Database)\n";
    cout << "-------------------------------------------\n";

    cout << "Enter term name: ";
    getline(cin,termName);

    file.open(termName);
    if (!file.is_open()) {
        fileCreate.open(termName);
        if (!fileCreate.is_open()) {
            cout << "Failed to create file!\n";
            return 1;
        }
        fileCreate.close();
    }
    cout << "Database/" + termName + "\created and loaded";

    bool isEmpty = true;
    cout << "Reading attendance data from file...\n";
    while (getline(file, currentLine)) {
        isEmpty = false;
        cout << "Successfully loaded: "+ currentLine << endl;
    }
    file.close();

    if (isEmpty) {
        cout << "There is no CSV file in the term.\n";
    }
    else {
        cout << "Which file would you like to open?\n";
        getline(cin, sheetName);
        fileName = sheetName + "_" + termName + ".csv";
        viewCSV(fileName);
    }

    cout << "---------------------------------\n\n";


    do {
        cout << "===========================================" << endl;
        cout << "  MENU " << endl;
        cout << "===========================================" << endl << endl;
        cout << "1. Create Attendance Sheet" << endl;
        cout << "2. Insert Attendance Data" << endl;
        cout << "3. View Attendance Sheet (CSV)" << endl;
        cout << "5. Delete Attendance Row"<< endl;
        cout << "6. Exit" << endl;
        cout << "===========================================" << endl << endl;
        cout << "Enter your choice: " << endl;

        getline(cin, choice);

        // CREATE ATTENDANCE SHEET
        if (choice == "1") {
            sheetName = createAttendanceSheet(termName);
        }

        // INSERT ATTENDANCE DATA AND VIEW ATTENDANCE SHEET
        else if (choice == "2" || choice == "3" || choice == "5"){
             cout << "Enter the attendance sheet name to open (e.g., attendance):\n";
             getline(cin, sheetName);

             // Parse filename and csv together
             string FileName = sheetName + "_" + termName + ".csv";

             // Try open the file
             file.open(FileName,ios::in);

             // If file exist then open file or ask them go to create file
             if (file.is_open()) {
                 if (choice == "2")
                    insertData(FileName);

                 else if (choice == "3")
                 // VIEW ATTENDANCE SHEET (CSV)
                    viewCSV(FileName);

                 else if (choice == "5")
                 //Delete row from attendance sheet
                    deleteRow(FileName);


            } else {
                cout << "\n File does not exist. PLEASE CREATE ATTENDANCE SHEET FIRST!! \n" << endl;
            }
        }

        // EXIT
        else if (choice == "6"){
             cout << "\n Goodbye!\n" << endl;
        }

        // DEFAULT INVALID (NUMBER OTHER THAN 1-4)
        else {
             cout << "\n Invalid choice. Please enter a number (1-4) \n" << endl;
        }

    } while (choice != "6");
        cout << "===========================================" << endl;
        cout << "End of Milestone 2 Output" << endl;
        cout << "===========================================" << endl;
        return 0;
}


string createAttendanceSheet(string &termName) {
    ofstream outputFile;
    string sheetName;
    int numColumns;
    string columnNames[10];
    string columnTypes[10];

    while (true) {
        cout << "Enter attendance sheet name: ";
        getline(cin, sheetName);

        string filepath = sheetName + "_" + termName + ".csv";
        // Check if file exists
        ifstream f(filepath);
        if (f.good()) {
            cout << "Error: The file \"" << sheetName << ".csv\" already exists. Please try another name.\n\n";
        }
        else {
            // File does not exist, safe to open a new file
            outputFile.open(filepath);
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

        cout << "Enter column " <<  (i+1) << " name: ";
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
    outputFile << "\n";//Next line if loop finished


    outputFile.close(); // Close the file

    cout << "\nSheet structure created successfully and saved to '" << sheetName << ".csv'.\n"; // Indicate create attendance sheet successfully


    outputFile.open(termName, ios::app);
    if (outputFile.is_open()) {
        outputFile << sheetName << ".csv\n";
        outputFile.close(); // Close it again when done
    } else {
        cout << "Error: Could not update the term text file.\n";
    }

    //return back the sheetName to main
    return sheetName;
}

//Function to insert a new row of attendance into a CSV file
void insertData(string fileName){

    vector<string> columns; // Stores column names extracted from header
    vector<string> columnTypes; //Stores column data types
    string line;

    ifstream inputFile(fileName);

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
        string col = (commaFound != -1) ? header.substr(0, commaFound) : header;//remove comma
        columns.push_back(col);//push into vector columns
        header = (commaFound != -1) ? header.substr(commaFound + 1) : "";
    }

    //Parse column types from type line
    string types = typeLine;
    while(!types.empty()){
        int commaFound = types.find(",");
        string type = (commaFound != -1) ? types.substr(0, commaFound) : types;//remove comma
        columnTypes.push_back(type);//push into vector columnType
        types = (commaFound != -1) ? types.substr(commaFound + 1) : "";
    }

    cout << "\n-------------------------------------------\n";
    cout << "Insert New Attendance Row\n";
    cout << "-------------------------------------------\n";

    int size = columns.size(); // Number of columns
    string userInput[size];

    ofstream outputfile(fileName, ios::app);  // Open file in append mode

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

            //Validation for status
            if(isStatus){
                if(userInput[i] != "0" && userInput[i] != "1"){
                    cout << "Status only accepts either 0 (Absent) or 1 (Present). Please re-enter.\n" << endl;
                    continue; // Restart while loop for this column
                }
            }
            //Validation for INTEGER types (e.g., Student ID)
            else if(isIntegerType){
                bool valid = true;

                if(userInput[i].empty()){
                    valid = false;
                } else {
                    // Check if every character is a digit (no minus sign allowed)
                    for(char c : userInput[i]){
                        if(!isdigit(c)) {
                            valid = false;
                            break;
                        }
                    }
                }

                if(!valid){
                    cout << "Invalid INT value. Please enter an integer value." << endl;
                    continue; // Restart while loop for this column
                }
            }
            //Validation for TEXT types (e.g., Student Name)
            else {
                if(userInput[i].empty()){
                    cout << "Input cannot be empty. Please enter text.\n" << endl;
                    continue;
                }
                // If it's text and not empty, it is accepted automatically
            }

        //Insert value into file
         outputfile << userInput[i];
        if (i != size - 1) outputfile << ",";

        break; // ONLY exits while(true)
    }
}
    outputfile << "\n"; // New row completed
    outputfile.close(); // Save file

   cout << "\nRow inserted successfully.\n"; // Indicate insert row successfully
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
        cout << "Current Attendance Sheet" << endl;
        cout << "-------------------------------------------\n" << endl;

        getline(inputFile, columnNames);
        cout << columnNames << endl;

        getline(inputFile, line);

        while (getline(inputFile, line)) //Loop through every line
        {
            cout << line << endl;
        }

        cout << "\n"; // Go to next line
        inputFile.close();//Close inputfilee
    }
    else
    {
        cout << "ERROR: Cannot open file." << endl;
    }
}

void deleteRow(string fileName)
{
    ifstream inputFile(fileName);
    vector<string> allLines;
    string line;

    while (getline(inputFile, line))//Read all lines from file
    {
        allLines.push_back(line);
    }
    inputFile.close();

    if (allLines.size() <= 2)//Not including title row and data type row
    {
        cout << "\nNo data rows to delete.\n" << endl;
        return;
    }

    string studentIDToDelete; //Ask for student id to delete
    cout << "\nEnter StudentID to delete: ";
    getline(cin, studentIDToDelete);

    int rowIndexToDelete = -1;

    for (int i = 2; i < allLines.size(); i++)//Search for student id
    {
        string currentRow = allLines[i];
        vector<string> rowData;

        string tempRow = currentRow;//Split current row by commas
        while(!tempRow.empty())
        {
            int commaPos = tempRow.find(",");
            string value = (commaPos != -1) ? tempRow.substr(0, commaPos) : tempRow;

            while (!value.empty() && value[0] == ' ')//Delete unwanted space in front
            {
                value = value.substr(1);
            }
            while (!value.empty() && value[value.length()-1] == ' ')//Delete unwanted space at back
            {
                value = value.substr(0, value.length()-1);
            }

            rowData.push_back(value);
            tempRow = (commaPos != -1) ? tempRow.substr(commaPos + 1) : "";
        }

        bool found = false;//Check if student id exists
        for (int j = 0; j < rowData.size(); j++)
        {
            if (rowData[j] == studentIDToDelete)
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            rowIndexToDelete = i;
            break;
        }
    }

    if (rowIndexToDelete == -1)//If student id not found
    {
        cout << "\nStudent ID '" << studentIDToDelete << "' not found.\n" << endl;
        return;
    }

    allLines.erase(allLines.begin() + rowIndexToDelete);//Delete row containing student id
    ofstream outputFile(fileName);//Write all remaining rows back to file
    for (int i = 0; i < allLines.size(); i++)
    {
        outputFile << allLines[i];
        if (i < allLines.size() -1)
        {
            outputFile << "\n";
        }
    }
    outputFile.close();
    cout << "\nRow deleted succesfully." << endl;
    cout << "\nUpdated Sheet:" << endl;
    viewCSV(fileName);//Display updated sheet

}

