#include <iostream>

enum Grade {
    F = 2,
    D,
    C,
    B,
    A
};

enum Subject {
    MATH,
    PHYSICS,
    SET_THEORY,
    PROGRAMMING
};

struct GradeForSubject {
    Subject subject;
    Grade grade;
};

struct GradeBook {
    char *name;
    char *faculty_number;
    int grades_count;
    GradeForSubject *grades;
};

void addGradeForSubject(GradeBook *grade_book, Subject subject, Grade grade) {
    for(int i = 0; i < grade_book->grades_count; i++) {
        if(grade_book->grades[i].subject == subject) {
            grade_book->grades[i].grade = grade;
            return;
        }
    }
    grade_book->grades[grade_book->grades_count].subject = subject;
    grade_book->grades[grade_book->grades_count].grade = grade;
    grade_book->grades_count++;
}

void sortGrades(GradeBook *grade_book) {
    for(int i = 0; i < grade_book->grades_count; i++) {
        for(int j = i + 1; j < grade_book->grades_count; j++) {
            if(grade_book->grades[i].grade > grade_book->grades[j].grade) {
                GradeForSubject temp = grade_book->grades[i];
                grade_book->grades[i] = grade_book->grades[j];
                grade_book->grades[j] = temp;
            }
        }
    }
}

double averageGrade(GradeBook *grade_book, bool aditionalCheck = false) {
    double sum = 0;
    int countF = 0;
    for(int i = 0; i < grade_book->grades_count; i++) {
        if (aditionalCheck) {
            sum += grade_book->grades[i].grade;
            continue;
        }
        if (grade_book->grades[i].grade != F) {
            sum += grade_book->grades[i].grade;
        } else {
            countF++;
        }
    }
    return sum / (grade_book->grades_count - countF);
}

void print(GradeBook *grade_book) {
    std::cout << "Name: " << grade_book->name << std::endl;
    std::cout << "Faculty number: " << grade_book->faculty_number << std::endl;
    std::cout << "Grades: " << std::endl;
    for(int i = 0; i < grade_book->grades_count; i++) {
        std::cout << grade_book->grades[i].subject << " " << grade_book->grades[i].grade << std::endl;
    }
}

bool canAdvance(GradeBook *grade_book) {
    int countF = 0;
    for(int i = 0; i < grade_book->grades_count; i++) {
        if (grade_book->grades[i].grade == F) {
            countF++;
        }
    }
    if (countF > 4) {
        return false;
    }
    if (countF == 4) {
        return averageGrade(grade_book) >= 4;
    }
    return true;
}

bool willGetScholarship(GradeBook *grade_book) {
    if (!canAdvance(grade_book)) {
        return false;
    }
    return averageGrade(grade_book) >= 5;
}

int main() {
    GradeBook *grade_book = new GradeBook();
    grade_book->name = "Ivan";
    grade_book->faculty_number = "123456";
    grade_book->grades_count = 0;
    grade_book->grades = new GradeForSubject[3];
    addGradeForSubject(grade_book, MATH, A);
    addGradeForSubject(grade_book, PHYSICS, B);
    addGradeForSubject(grade_book, PROGRAMMING, A);
    addGradeForSubject(grade_book, SET_THEORY, C);
    sortGrades(grade_book);
    std::cout << "Will pass: " << std::boolalpha << canAdvance(grade_book) << std::endl;
    std::cout << "Will get scholarship: " << std::boolalpha << willGetScholarship(grade_book) << std::endl;
    delete grade_book->name;
    delete grade_book->faculty_number;
    delete[] grade_book->grades;
    delete grade_book;
}