/*Department maintains student’s database. The file contains roll number, name, division and address.
Write a program to create a sequential file to store and maintain student data. It should allow the user
to add, delete information of student. Display information of particular student. If record of student
does not exist an appropriate message is displayed. If student record is found it should display the
student details.*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student {
    int rollNumber;
    string name;
    string division;
    string address;
};


void addStudent() {
    ofstream outFile("students.txt", ios::app); 
    if (!outFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    Student student;
    cout << "Enter Roll Number: ";
    cin >> student.rollNumber;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, student.name);
    cout << "Enter Division: ";
    getline(cin, student.division);
    cout << "Enter Address: ";
    getline(cin, student.address);

    outFile << student.rollNumber << " " << student.name << " " << student.division << " " << student.address << endl;
    outFile.close();

    cout << "Student record added successfully!" << endl;
}


void displayStudent() {
    ifstream inFile("students.txt");
    if (!inFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    int rollNumber;
    cout << "Enter Roll Number of student to display: ";
    cin >> rollNumber;

    Student student;
    bool found = false;

    while (inFile >> student.rollNumber) {
        inFile.ignore();
        getline(inFile, student.name, ' ');
        getline(inFile, student.division, ' ');
        getline(inFile, student.address);

        if (student.rollNumber == rollNumber) {
            cout << "Roll Number: " << student.rollNumber << endl;
            cout << "Name: " << student.name << endl;
            cout << "Division: " << student.division << endl;
            cout << "Address: " << student.address << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Student record not found." << endl;
    }

    inFile.close();
}


void deleteStudent() {
    ifstream inFile("students.txt");
    ofstream tempFile("temp.txt"); 

    if (!inFile || !tempFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    int rollNumber;
    cout << "Enter Roll Number of student to delete: ";
    cin >> rollNumber;

    Student student;
    bool found = false;

    while (inFile >> student.rollNumber) {
        inFile.ignore();
        getline(inFile, student.name, ' ');
        getline(inFile, student.division, ' ');
        getline(inFile, student.address);

        if (student.rollNumber == rollNumber) {
            found = true; 
        } else {
            
            tempFile << student.rollNumber << " " << student.name << " " << student.division << " " << student.address << endl;
        }
    }

    inFile.close();
    tempFile.close();

    remove("students.txt"); 
    rename("temp.txt", "students.txt"); 

    if (found) {
        cout << "Student record deleted successfully!" << endl;
    } else {
        cout << "Student record not found." << endl;
    }
}


int main() {
    int choice;
    do {
        cout << "\nStudent Database Management\n";
        cout << "1. Add Student\n";
        cout << "2. Display Student\n";
        cout << "3. Delete Student\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudent();
                break;
            case 3:
                deleteStudent();
                break;
            case 4:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 4);

    return 0;
}
