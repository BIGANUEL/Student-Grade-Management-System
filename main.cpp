#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// Structure to represent a grade node
struct GradeNode {
    float grade;
    GradeNode* next;
};

//Structure that represents a Course node
struct CourseNode{
    string courseName;
    GradeNode* grades; 
    float total;
    int creditHours;
    string letterGrade;
    CourseNode* next;
};

// Structure to represent a student
struct Student {
    int id;
    string name;
    int age;
    string gender;
    CourseNode* courses;
    float gpa;
    Student* next;
};

struct GradeHistoryNode {
    GradeNode* grades; 
    GradeHistoryNode* next;
};

struct StudentQueueNode {
    Student* student;
    StudentQueueNode* next;
};

class GradeHistoryStack{
    private:
    GradeHistoryNode* top;

    // Function to deep copy a grade list
    GradeNode* copyGradeList(GradeNode* original){
        if (!original){
            return nullptr;
        }
        GradeNode* newHead = new GradeNode{original->grade, nullptr};
        GradeNode* currentNew = newHead;
        GradeNode* currentOriginal = original->next;

        while(currentOriginal){
            currentNew->next = new GradeNode{currentOriginal->grade,nullptr};
            currentNew = currentNew->next;
            currentOriginal = currentOriginal->next;
        }

        return newHead;
    }
    // Function to delete a grade list
    void deleteGradeList(GradeNode* gradeHead){
        while (gradeHead){
            GradeNode* temp = gradeHead;
            gradeHead = gradeHead->next;
            delete temp;
        }
    }

 public:
    GradeHistoryStack() : top(nullptr){}

    void push(GradeNode* grades){
        GradeHistoryNode* newNode = new GradeHistoryNode{copyGradeList(grades), top};
        top = newNode;
    }

    GradeNode* pop() {
        if(!top) {
            cout<< "No previous grades to restore.\n";
            return nullptr;
        }
        GradeNode* grades = top->grades;
        GradeHistoryNode* temp = top;
        top = top->next;
        delete temp;
        return grades;
    }

    bool isEmpty(){
        return top == nullptr;
    }
    
    ~GradeHistoryStack(){
        while(top){
            deleteGradeList(top->grades);
            GradeHistoryNode* temp = top;
            top = top->next;
            delete temp;
        }
    }
};


class StudentQueue {
    private:
        StudentQueueNode* front;
        StudentQueueNode* rear;

    public:
        StudentQueue() : front(nullptr), rear(nullptr) {}

        void enqueue(Student* student) {
            StudentQueueNode* newNode = new StudentQueueNode{student, nullptr};
            if (!front) {
                front = rear = newNode;
            } else {
                rear->next = newNode;
                rear = newNode;
            }
        }

        Student* dequeue() {
            if (!front) {
                return nullptr;
            }
            StudentQueueNode* temp = front;
            front = front->next;
            if (!front) rear = nullptr;
            Student* student = temp->student;
            delete temp;
            return student;
        }

        bool isEmpty() {
            return front == nullptr;
        }

        ~StudentQueue() {
            while (front) {
                StudentQueueNode* temp = front;
                front = front->next;
                delete temp;
            }
        }
    };



// Student Management System class
class StudentManagementSystem {
private:
    Student* head;

    // Function to validate and return an integer input
    int validateIntegerInput() {
        int input;
        while (!(cin >> input)) {
            cout << "Invalid input! Please enter a valid integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return input;
    }

    // Function to validate and return a string input
    string validateStringInput() {
        string input;
        if (cin.peek() == '\n') { 
            cin.ignore();         
        }
        getline(cin, input);     
        return input;
    }


    // Function to find a student by ID
    Student* findStudent(int id) {
        Student* current = head;
        while (current != nullptr) {
            if (current->id == id) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    

    // Function to add grades to a student
    void addGrade(GradeNode*& gradeHead, float grade) {
        GradeNode* newNode = new GradeNode{grade, nullptr};
        if (!gradeHead) {
            gradeHead = newNode;
        } else {
            GradeNode* current = gradeHead;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // Function to calculate GPA
    float calculateSum(GradeNode* grades) {
        float sum = 0;
        while (grades) {
            sum += grades->grade;
            grades = grades->next;
        }
        return sum;
    }

    // Function to delete all grades for a student
    void deleteGrades(GradeNode*& gradeHead) {
        while (gradeHead) {
            GradeNode* temp = gradeHead;
            gradeHead = gradeHead->next;
            delete temp;
        }
    }

    string letterGrade(float total) {
        if (total > 90) {
            return "A";      
        }else if (total >= 80) {
            return "B";
        } else if (total >= 70) {
            return "C";
        } else if (total >= 60) {
            return "D";
        } else {
            return "F";
        }
    }

    float calculateGPA(CourseNode* courses) {
        if (!courses) return 0.0; 

        float totalGradePoints = 0.0;
        int totalCreditHours = 0;

        CourseNode* currentCourse = courses;
        while (currentCourse) {
            
            float gradePoint = 0.0;
            if (currentCourse->letterGrade == "A") {
                gradePoint = 4.0;
            } else if (currentCourse->letterGrade == "B") {
                gradePoint = 3.0;
            } else if (currentCourse->letterGrade == "C") {
                gradePoint = 2.0;
            } else if (currentCourse->letterGrade == "D") {
                gradePoint = 1.0;
            } else if (currentCourse->letterGrade == "F") {
                gradePoint = 0.0;
            }

            totalGradePoints += gradePoint * currentCourse->creditHours;
            totalCreditHours += currentCourse->creditHours;

            currentCourse = currentCourse->next;
        }

        return totalCreditHours > 0 ? totalGradePoints / totalCreditHours : 0.0;
    }

    

public:
    StudentManagementSystem() : head(nullptr) {}

    // Function to add a new student
    void addStudent() {
        Student* newStudent = new Student;

        cout << "Enter Student ID: ";
        newStudent->id = validateIntegerInput();

        if (findStudent(newStudent->id)) {
            cout << "Student ID already exists. Try again.\n";
            delete newStudent;
            return;
        }

        cout << "Enter Name: ";
        newStudent->name = validateStringInput();

        cout << "Enter Age: ";
        newStudent->age = validateIntegerInput();

        cout << "Enter Gender (M/F): ";
        newStudent->gender = validateStringInput();

        cout << "Enter Course: ";
        newStudent->courses = nullptr;
        
        

        char moreCourses;
        do{
            CourseNode* course = new CourseNode;

            cout<< "Enter Course Name: ";
            course->courseName = validateStringInput();

            cout << "Enter Credit Hours: ";
            course->creditHours = validateIntegerInput();

            course->grades = nullptr;
            course->next = nullptr;

            const string gradeTypes[] = {"Assignment(10%)", "Quiz(5%)", "Midterm(20%)", "Final Exam(50%)", "Project(15%)"};
            const int numGrades = 5;

            cout << "Enter grades for the following components in "<< course->courseName << ":\n";
            for (int i=0 ; i < numGrades; ++i){
                float grade;
                cout << gradeTypes[i] << ": ";
                grade = validateIntegerInput();
                addGrade(course->grades, grade);
            }

        course->total = calculateSum(course->grades);
        course->letterGrade = letterGrade(course->total);

        if (!newStudent->courses) {
            newStudent->courses = course;
        }
        
        else{
            CourseNode* temp = newStudent->courses;

            while (temp->next) {
                temp = temp->next;
            }

            temp->next = course;
        }
        

        cout << "Do you want to add another course for this student (y/n): ";
        cin >> moreCourses;
        }while( moreCourses == 'y' || moreCourses == 'Y');

       
        newStudent->gpa = calculateGPA(newStudent->courses);

        newStudent->next = nullptr;

        if (!head) {
            head = newStudent;
        } else {
            Student* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newStudent;
        }

        cout << "Student added successfully with all courses!\n";
        cout << "GPA for " << newStudent->name << " is: " << fixed << setprecision(2) << newStudent->gpa << endl;
    }

    // function to add a course for exisiting student
    void addCourseForStudent() {
        cout << "Enter Student ID to add a course: ";
        int id = validateIntegerInput();

        Student* student = findStudent(id);
        if (!student) {
            cout << "Student not found!\n";
            return;
        }

        CourseNode* newCourse = new CourseNode;

        cout << "Enter Course Name: ";
        newCourse->courseName = validateStringInput();

        cout << "Enter Credit Hours: ";
        newCourse->creditHours = validateIntegerInput();

        newCourse->grades = nullptr; 
        newCourse->next = nullptr; 

        const string gradeTypes[] = {"Assignment(10%)", "Quiz(5%)", "Midterm(20%)", "Final Exam(50%)", "Project(15%)"};
        const int numGrades = 5;

        cout << "Enter grades for the following components in " << newCourse->courseName << ":\n";
        for (int i = 0; i < numGrades; ++i) {
            float grade;
            cout << gradeTypes[i] << ": ";
            grade = validateIntegerInput();
            addGrade(newCourse->grades, grade);
        }

        newCourse->total = calculateSum(newCourse->grades);
        newCourse->letterGrade = letterGrade(newCourse->total);

        if (!student->courses) {
            student->courses = newCourse;
        } else {
            CourseNode* temp = student->courses;
            while (temp->next) {
                temp = temp->next; 
            }
            temp->next = newCourse; 
        }

        cout << "Course added successfully for student " << student->name << "!\n";
    }

    // Function to display all students
   void displayStudents() {
        if (!head) {
            cout << "No students to display!\n";
            return;
        }

        const string gradeTypes[] = {"Assignment", "Quiz", "Midterm", "Final Exam", "Project"};
        const int numGrades = 5;

        
        cout << "---------------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "| ID   | Name                 | Age  | Gender | Course                 | Assignment | Quiz       | Midterm    | Final Exam | Project    | Total     | Grade |\n";
        cout << "---------------------------------------------------------------------------------------------------------------------------------------------------\n";

        Student* current = head;
        while (current) {
            CourseNode* course = current->courses;
            bool isFirstCourse = true;

            while (course) {
                if (isFirstCourse) {
                    
                    cout << "| " << setw(5) << current->id
                        << " | " << setw(20) << current->name
                        << " | " << setw(4) << current->age
                        << " | " << setw(6) << current->gender;
                    isFirstCourse = false; 
                } else {
                    
                    cout << "| " << setw(5) << " "
                        << " | " << setw(20) << " "
                        << " | " << setw(4) << " "
                        << " | " << setw(6) << " ";
                }

                cout << " | " << setw(20) << course->courseName << " | ";

                GradeNode* gradeCurrent = course->grades;
                int gradeIndex = 0;

                while (gradeCurrent && gradeIndex < numGrades) {
                    cout << setw(10) << fixed << setprecision(2) << gradeCurrent->grade << " | ";
                    gradeCurrent = gradeCurrent->next;
                    gradeIndex++;
                }

                while (gradeIndex < numGrades) {
                    cout << setw(10) << "N/A" << " | ";
                    gradeIndex++;
                }

                cout << setw(10) << fixed << setprecision(2) << course->total << " | "
                    << setw(8) << course->letterGrade << " |\n";

                course = course->next;
            }

        if (!current->courses) {
            cout << "| " << setw(5) << current->id
                 << " | " << setw(20) << current->name
                 << " | " << setw(4) << current->age
                 << " | " << setw(6) << current->gender
                 << " | " << setw(20) << "No courses"
                 << " | " << setw(10) << "N/A"
                 << " | " << setw(10) << "N/A"
                 << " | " << setw(10) << "N/A"
                 << " | " << setw(10) << "N/A"
                 << " | " << setw(10) << "N/A"
                 << " | " << setw(10) << "N/A"
                 << " | " << setw(8) << "N/A"
                 << " |\n";
    }

        cout << "---------------------------------------------------------------------------------------------------------------------------------------------------\n";
        current = current->next;
    }
}
  // Function to edit grades of a student
    void editGrades(GradeHistoryStack& historyStack) {
        cout << "Enter Student ID to edit grades: ";
        int id = validateIntegerInput();

        Student* student = findStudent(id);
        if (!student) {
            cout << "Student not found!\n";
            return;
        }

        if(!student->courses) {
            cout << "This student has no courses.\n";
            return;
        }

        cout << "Courses for " << student->name << ":\n";
        CourseNode* course = student->courses;
        int courseIndex = 1;

        while (course) {
            cout << courseIndex++ << ". " << course->courseName << " (Total: " << fixed << setprecision(2) << course->total << ")\n";
            course = course->next;
        }

        cout << "Enter the number of the course to edit grades: ";
        int selectedCourse;
        cin >> selectedCourse;

        course = student->courses;
        courseIndex = 1;

        while (course && courseIndex < selectedCourse) {
            course = course->next;
            courseIndex++;
        }

        if(!course) {
            cout << "Invalid course selection.\n";
            return;
        }
        
        historyStack.push(course->grades);

        deleteGrades(course->grades);

        cout << "Enter grades for the following components in " << course->courseName << ":\n";
        const string gradeTypes[] = {"Assignment(10%)", "Quiz(5%)", "Midterm(20%)", "Final Exam(50%)", "Project(15%)"};
        const int numGrades = 5;

        for (int i = 0; i < numGrades; ++i) {
            float grade;
            cout << gradeTypes[i] << ": ";
            grade = validateIntegerInput();
            addGrade(course->grades, grade);
        }
        course->total = calculateSum(course->grades);
        course->letterGrade = letterGrade(course->total);
        
        cout << "Grades updated successfully for " << course->courseName << "! You can undo this action.\n";
    }


    // Function to undo the last grade Update
    void undoLastGradeUpdate(GradeHistoryStack& historyStack){
        cout << "Enter Student ID to undo last grade update: ";
        int id = validateIntegerInput();

        Student* student = findStudent(id);
        if(!student){
            cout << "Student not found!\n";
            return;
        }


        if (!student->courses) {
        cout << "This student has no courses.\n";
        return;
        }

        cout << "Courses for " << student->name << ":\n";
        CourseNode* course = student->courses;
        int courseIndex = 1;

        while (course) {
            cout << courseIndex++ << ". " << course->courseName << " (Total: " << fixed << setprecision(2) << course->total << ")\n";
            course = course->next;
        }

        cout << "Enter the number of the course to undo the last grade update: ";
        int selectedCourse;
        cin >> selectedCourse;

        course = student->courses;
        courseIndex = 1;

        while (course && courseIndex < selectedCourse) {
            course = course->next;
            courseIndex++;
        }

        if (!course || courseIndex != selectedCourse) {
            cout << "Invalid course selection.\n";
            return;
        }

        GradeNode* previousGrades = historyStack.pop();

        if (previousGrades) {
            deleteGrades(course->grades);
            course->grades = previousGrades;
            course->total = calculateSum(course->grades);
            course->letterGrade = letterGrade(course->total);
            cout << "Last grade update undone successfully for " << course->courseName << ".\n";
        }
        else{
            cout << "No previous grades to undo.\n";
        }
    }

    // Function to prioritize Students
   void prioritizeStudentsForHelp(float threshold) {
        StudentQueue queue;
        Student* student = head;

        while (student) {
            float studentGPA = calculateGPA(student->courses);

            if (studentGPA < threshold) {
                queue.enqueue(student);
            }

            student = student->next;
        }

        if (queue.isEmpty()) {
            cout << "No students meet the criteria.\n";
            return;
        }

        cout << "Students prioritized for extra help (GPA below threshold):\n";
        cout << "---------------------------------------------------------\n";
        cout << "| ID   | Name                 | Age  | Gender | GPA    |\n";
        cout << "---------------------------------------------------------\n";

        while (!queue.isEmpty()) {
            Student* student = queue.dequeue();

            cout << "| " << setw(4) << student->id
                << " | " << setw(20) << student->name
                << " | " << setw(4) << student->age
                << " | " << setw(6) << student->gender
                << " | " << setw(5) << fixed << setprecision(2) << calculateGPA(student->courses)
                << " |\n";
        }
        cout << "---------------------------------------------------------\n";
    }
    //Function to rank students by GPA
    void rankAndDisplayStudents() {
        if (!head || !head->next) {
            cout << "Not enough students to rank.\n";
            return;
        }

        Student* current = head;
        while (current) {
            current->gpa = calculateGPA(current->courses);
            current = current->next;
        }

        bool swapped;
        do {
            swapped = false;
            Student* prev = nullptr;
            current = head;

            while (current && current->next) {
                if (current->gpa < current->next->gpa) {
                    if (!prev) {
                        head = current->next;
                    } else {
                        prev->next = current->next;
                    }
                    Student* temp = current->next->next;
                    current->next->next = current;
                    current->next = temp;

                    swapped = true;
                }

                prev = current;
                current = current->next;
            }
        } while (swapped);

        cout << "---------------------------------------------------------------------------------------------\n";
        cout << "| Rank | ID   | Name                 | Age  | Gender | Course                 | GPA          |\n";
        cout << "---------------------------------------------------------------------------------------------\n";

        int rank = 1;
        current = head;
        while (current) {
            string courseName = (current->courses) ? current->courses->courseName : "No Course";
            cout << "| " << setw(4) << rank++ 
                << "  | " << setw(4) << current->id
                << " | " << setw(20) << current->name
                << " | " << setw(4) << current->age
                << " | " << setw(6) << current->gender
                << " | " << setw(20) << courseName
                << " | " << setw(4) << fixed << setprecision(2) << current->gpa
                << " |\n";

            CourseNode* course = current->courses->next; 
            while (course) {
                cout << "|       |      |                      |      |        | " << setw(20) << course->courseName << " |\n";
                course = course->next;
            }

            cout << "---------------------------------------------------------------------------------------------\n";
            
            current = current->next;
        }
    }
    //Function to delete a student
    void deleteStudent() {
    cout << "Enter Student ID to delete: ";
    int id = validateIntegerInput();

    Student* current = head;
    Student* prev = nullptr;

    while (current && current->id != id) {
        prev = current;
        current = current->next;
    }

    if (!current) {
        cout << "Student not found!\n";
        return;
    }

    if (!prev) {
        head = current->next; 
    } else {
        prev->next = current->next;
    }
    CourseNode* courseCurrent = current->courses;
    while (courseCurrent) {
        CourseNode* temp = courseCurrent;
        courseCurrent = courseCurrent->next;
        delete temp;
    }
    delete current;
    cout << "Student deleted successfully!\n";
}

// Destructor to clean up all memory
~StudentManagementSystem() {
    while (head) {
        Student* temp = head;
        head = head->next;

        CourseNode* courseCurrent = temp->courses;
        while (courseCurrent) {
            CourseNode* courseTemp = courseCurrent;
            courseCurrent = courseCurrent->next;
            delete courseTemp; 
        }

        delete temp;
    }
}
};

int main() {
    StudentManagementSystem sms;
    GradeHistoryStack historyStack;
    int choice;
    float threshold;

    do {
        cout << "\n\n\n\n";
        cout << "                                          ***************************************" << endl;
        cout << "                                          ************* WELCOME TO STUDENT GRADE MANAGEMENT SYSTEM *************" << endl;
        cout << "                                          ***************************************" << endl;
        cout << "                                          *  1. Add Student                         *" << endl;
        cout << "                                          *  2. Display Students                    *" << endl;
        cout << "                                          *  3. Edit Grades                         *" << endl;
        cout << "                                          *  4. Rank Students                       *" << endl;
        cout << "                                          *  5. Delete Student                      *" << endl;
        cout << "                                          *  6. Undo Last Grade Update              *" << endl;
        cout << "                                          *  7. Prioritize Students for Extra Help  *" << endl;
        cout << "                                          *  8. Add Course for Existing Student     *" << endl;
        cout << "                                          ***************************************" << endl;
        cout << "                                          Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            sms.addStudent();
            break;

        case 2:
            sms.displayStudents();
            break;

        case 3:
            sms.editGrades(historyStack);
            break;

        case 4:
            sms.rankAndDisplayStudents();
            break;

        case 5:
            sms.deleteStudent();
            break;
        case 6:
            sms.undoLastGradeUpdate(historyStack);
            break;
        case 7:
            cout << "Enter GPA threshold: ";
            cin >> threshold;
            sms.prioritizeStudentsForHelp(threshold);
            break;
        case 8:
            sms.addCourseForStudent();
            break;

        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while(choice != 9);

 
  return 0;
}
