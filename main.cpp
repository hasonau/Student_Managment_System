#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>

using namespace std;

class Student {
private:
    int rollNumber;
    string name;
    string fatherName;
    int age;

public:
    Student() {}

    void setRollNumber(int rollNumber) {
        this->rollNumber = rollNumber;
    }

    int getRollNumber() const {
        return rollNumber;
    }

    void setName(const string& name) {
        this->name = name;
    }

    string getName() const {
        return name;
    }

    void setFatherName(const string& fatherName) {
        this->fatherName = fatherName;
    }

    string getFatherName() const {
        return fatherName;
    }

    void setAge(int age) {
        this->age = age;
    }

    int getAge() const {
        return age;
    }

    void display() const {
        cout << "Roll Number: " << rollNumber << ", Name: " << name
             << ", Father's Name: " << fatherName << ", Age: " << age << endl;
    }
};

class StudentManager {
private:
    vector<Student> students;
    string studentFile = "students.txt";

public:
    StudentManager() {
        loadStudentsFromFile();
    }

    void addStudent(const Student& newStudent) {
        if (!isStudentExist(newStudent.getRollNumber())) {
            students.push_back(newStudent);
            saveStudentsToFile();
        } else {
            cout << "Student with this Roll Number already exists." << endl;
        }
    }

    bool isValidName(const string& name) const {
        for (char ch : name) {
            if (!isalpha(ch) && ch != ' ') {
                return false;
            }
        }
        return true;
    }

    void removeStudent(int rollNumber) {
        for (size_t i = 0; i < students.size(); ++i) {
            if (students[i].getRollNumber() == rollNumber) {
                students.erase(students.begin() + i);
                saveStudentsToFile();
                return;
            }
        }
        cout << "Student with this Roll Number does not exist." << endl;
    }

    void removeAllStudents() {
        students.clear();
        saveStudentsToFile();
        cout << "All student data removed." << endl;
    }

    void updateStudent(int rollNumber) {
        if (students.empty()) {
            cout << "No students found. The file is empty." << endl;
            return;
        }

        bool found = false;
        for (auto& student : students) {
            if (student.getRollNumber() == rollNumber) {
                string newName, newFatherName;
                int newAge;
                do {
                    cout << "Enter new name: ";
//                    cin.ignore(); // Clear input buffer
                    getline(cin, newName);
                    if (!isValidName(newName)) {
                        cout << "Invalid input for name. Please enter a valid name." << endl;
                    }
                } while (!isValidName(newName));

                do {
                    cout << "Enter new father's name: ";
                    getline(cin, newFatherName);
                    if (!isValidName(newFatherName)) {
                        cout << "Invalid input for father's name. Please enter a valid name." << endl;
                    }
                } while (!isValidName(newFatherName));

                int age;
                bool validAge = false;
                do {
                    cout << "Enter student Age: ";
                    cin >> ws; // Skip whitespace characters
                    if (!(cin >> age) || cin.peek() != '\n' || cin.fail() || cin.eof()) {
                        cout << "Invalid input for Age. Please enter an integer." << endl;
                        cin.clear(); // Clear error state
                        cin.ignore(10000, '\n'); // Ignore invalid input
                    } else {
                        validAge = true;
                    }
                } while (!validAge);


                student.setName(newName);
                student.setFatherName(newFatherName);
                student.setAge(age);
                saveStudentsToFile();
                cout << "Student with roll number " << rollNumber << " updated successfully." << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Student with roll number " << rollNumber << " does not exist." << endl;
        }
    }


    bool isStudentExist(int rollNumber) const {
        for (size_t i = 0; i < students.size(); ++i) {
            if (students[i].getRollNumber() == rollNumber) {
                return true;
            }
        }
        return false;
    }

    void displayAllStudents() const {
        if (students.empty()) {
            cout << "No students found. The file is empty." << endl;
            return;
        }
        cout << "All Students:" << endl;
        for (size_t i = 0; i < students.size(); ++i) {
            students[i].display();
        }
    }

private:
    void saveStudentsToFile() {
        ofstream file(studentFile);
        if (file.is_open()) {
            for (size_t i = 0; i < students.size(); ++i) {
                file << students[i].getRollNumber() << "," << students[i].getName() << ","
                     << students[i].getFatherName() << "," << students[i].getAge() << endl;
            }
            file.close();
        }
    }

    void loadStudentsFromFile() {
        ifstream file(studentFile);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                // Find positions of commas
                size_t pos1 = line.find(',');
                size_t pos2 = line.find(',', pos1 + 1);
                size_t pos3 = line.find(',', pos2 + 1);
                // Extract substrings between commas
                int rollNumber = stoi(line.substr(0, pos1));
                string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
                string fatherName = line.substr(pos2 + 1, pos3 - pos2 - 1);
                int age = stoi(line.substr(pos3 + 1));
                // Create a new Student object and add it to the vector
                Student student;
                student.setRollNumber(rollNumber);
                student.setName(name);
                student.setFatherName(fatherName);
                student.setAge(age);
                students.push_back(student);
            }
            file.close();
        }
    }


};

void displayMenu() {
    cout << "Menu:" << endl;
    cout << "1. Add Student" << endl;
    cout << "2. Remove one Student by Roll No." << endl;
    cout << "3. Update Student Record" << endl;
    cout << "4. Delete All Student Data" << endl;
    cout << "5. Display All Students" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    StudentManager studentManager;

    char choice;
    do {
        displayMenu();
        cin >> choice;
        switch (choice) {
            case '1': {
                Student newStudent;
                int rollNumber, age;
                string name, fatherName;
                bool validRollNumber = false;
                do {
                    cout << "Enter student Roll Number: ";
                    cin >> ws; // Skip whitespace characters
                    if (!(cin >> rollNumber) || cin.peek() != '\n' || cin.fail() || cin.eof()) {
                        cout << "Invalid input for Roll Number. Please enter an integer." << endl;
                        cin.clear(); // Clear error state
                        cin.ignore(10000, '\n'); // Ignore invalid input
                    } else if (studentManager.isStudentExist(rollNumber)) {
                        cout << "Student with this Roll Number already exists." << endl;
                    } else {
                        validRollNumber = true;
                    }
                } while (!validRollNumber);
                cin.ignore(10000, '\n');

                do {
//                    cin.ignore(10000, '\n');
                    cout << "Enter student name: ";
                    // Clear input buffer
                    getline(cin, name);
                    if (name.empty() || !studentManager.isValidName(name)) {
                        cout << "Invalid input for name. Please enter a valid name." << endl;
                    }
                } while (name.empty() || !studentManager.isValidName(name));

                do {
                    cout << "Enter father's name: ";
                    getline(cin, fatherName);
                    if (fatherName.empty() || !studentManager.isValidName(fatherName)) {
                        cout << "Invalid input for father's name. Please enter a valid name." << endl;
                    }
                } while (fatherName.empty() || !studentManager.isValidName(fatherName));

                bool validAge = false;
                do {
                    cout << "Enter student Age: ";
                    cin >> ws; // Skip whitespace characters
                    if (!(cin >> age) || cin.peek() != '\n' || cin.fail() || cin.eof()) {
                        cout << "Invalid input for Age. Please enter an integer." << endl;
                        cin.clear(); // Clear error state
                        cin.ignore(10000, '\n'); // Ignore invalid input
                    } else {
                        validAge = true;
                    }
                } while (!validAge);

                cin.ignore(10000, '\n');

                newStudent.setRollNumber(rollNumber);
                newStudent.setName(name);
                newStudent.setFatherName(fatherName);
                newStudent.setAge(age);
                studentManager.addStudent(newStudent);
                break;
            }


            case '2': {
                int rollNumber;
                cout << "Enter student Roll Number to remove: ";

                bool validRollNumber = false;
                do {
                    if (!(cin >> rollNumber)) {
                        cout << "Invalid input for Roll Number. Please enter an integer." << endl;
                        cin.clear(); // Clear error state
                        cin.ignore(10000, '\n'); // Ignore invalid input
                    } else {
                        validRollNumber = true;

                    }
                } while (!validRollNumber);
                studentManager.removeStudent(rollNumber);
                cout<<"The student with roll number "<<rollNumber<<" has been removed."<<endl;
                break;
            }
            case '3': {
                int rollNumber;
                cout << "Enter student roll number to update:";
                bool validRollNumber = false;
                do {
                    cin >> ws; // Skip whitespace characters
                    if (!(cin >> rollNumber) || cin.peek() != '\n' || cin.fail() || cin.eof()) {
                        cout << "Invalid input for Roll Number. Please enter an integer." << endl;
                        cin.clear(); // Clear error state
                        cin.ignore(10000, '\n'); // Ignore invalid input
                    } else {
                        validRollNumber = true;
                    }
                } while (!validRollNumber);
                cin.ignore(10000, '\n');
                studentManager.updateStudent(rollNumber);
                break;
            }
            case '4': {
                studentManager.removeAllStudents();
                break;
            }
            case '5': {
                studentManager.displayAllStudents();
                break;
            }
            case '6' : {
                cout << "Exiting program..." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
        }
    } while (choice != '6');

    return 0;
}
