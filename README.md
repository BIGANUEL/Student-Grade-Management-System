[---

## **Student Grade Management System**

### **Description**
The Student Grade Management System is a C++ application designed to manage and evaluate student data effectively. It allows users to:
- Add students and their course details.
- Calculate and display GPA based on course grades.
- Rank students based on GPA.
- Identify students requiring extra help using GPA thresholds.
- Display detailed information for each student, including grades and performance.

---

### **Features**
1. **Student Management**:
   - Add student details such as ID, name, age, and gender.
   - Assign multiple courses to a student.
   - Input grades for assignments, quizzes, midterms, final exams, and projects.

2. **GPA Calculation**:
   - Automatically calculate GPA for students based on course grades.

3. **Ranking System**:
   - Rank students by GPA in descending order.
   - Display all courses for each student in the ranking table.

4. **Help Prioritization**:
   - Identify students needing extra help based on a GPA threshold.

5. **Detailed Reporting**:
   - Generate a tabular report showing student details, courses, grades, total scores, and overall GPA.

---

### **How to Run**
1. **Prerequisites**:
   - Install a C++ compiler (e.g., GCC, Clang).
   - Ensure a terminal or IDE for running the program.

2. **Compilation**:
   Compile the program using:
   ```bash
   g++ -o StudentManagementSystem main.cpp
   ```

3. **Execution**:
   Run the program using:
   ```bash
   ./StudentManagementSystem
   ```

---

### **Usage**
1. Follow the prompts to enter student details and grades.
2. Use menu options to:
   - Add students and courses.
   - View ranked students.
   - Identify students below a GPA threshold.
   - Generate detailed performance reports.

---

### **Example Outputs**

#### **Ranked Students**
```
---------------------------------------------------------------------------------------------
| Rank | ID   | Name                 | Age  | Gender | Course                 | GPA          |
---------------------------------------------------------------------------------------------
|    1 | 1234 | John Doe             |   20 | M      | Chemistry              | 3.80         |
|      |      |                      |      |        | Mathematics            |              |
|    2 | 1235 | Jane Smith           |   22 | F      | Biology                | 3.50         |
---------------------------------------------------------------------------------------------
```

#### **Detailed Performance Report**
```
---------------------------------------------------------------------------------------------------------------------------------------------------
| ID   | Name                 | Age  | Gender | Course                 | Assignment | Quiz       | Midterm    | Final Exam | Project    | Total     | Grade |
---------------------------------------------------------------------------------------------------------------------------------------------------
| 1234 | John Doe             |   20 | M      | Chemistry              |       10.00|       9.00 |      18.00 |      45.00 |      15.00 |     97.00 |   A   |
|      |                      |      |        | Mathematics            |        8.00|       7.00 |      16.00 |      40.00 |      10.00 |     81.00 |   B   |
---------------------------------------------------------------------------------------------------------------------------------------------------
```

---

### **Future Enhancements**
- Add functionality for exporting reports to files (e.g., CSV, PDF).
- Include graphical performance visualization.
- Implement a user-friendly GUI.

---

### **Contributors**
1. **Amanuel Wubishet …………………………….. ETS0133/15**
2.	**Betelhem Wondale……………………………….ETS0261/15**
3.	**Betelhem Petros………………………………….. ETS0258/15**
4.	**Betelhem Mengesha……………………………..ETS0257/15**
5.	**Abel Negatu ………………………………………...ETS0033/13**   

---
](https://github.com/BIGANUEL/Student-Grade-Management-System.git)
