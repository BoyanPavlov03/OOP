#include <iostream>
#include <cstring>

enum Position {
    ASSISTANT,
    HEAD_ASSISTANT,
    DOCENT,
    PROFESSOR
};

class UniversityTeacher {
    char *name;
    Position position;
    double salary;
    double moneyEarnForDay;

public:
    UniversityTeacher();
    UniversityTeacher(const char *name, Position position, double salary, double moneyEarnForDay);
    ~UniversityTeacher();
    Position getPosition() const;
    void setPosition(Position position);
    double getSalary() const;
    void setSalary(double salary);
    UniversityTeacher& operator=(const UniversityTeacher& other);
    bool operator!=(const UniversityTeacher& other);
    bool operator==(const UniversityTeacher& other);
    friend std::ostream &operator<<(std::ostream &os, const UniversityTeacher &ut);
};

UniversityTeacher::UniversityTeacher() : name(), position(), salary(), moneyEarnForDay() {}

UniversityTeacher::UniversityTeacher(const char *name, Position position, double salary, double moneyEarnForDay)
    : name(new char[strlen(name) + 1]), position(position), salary(salary), moneyEarnForDay(moneyEarnForDay) {
    strcpy(this->name, name);
}

UniversityTeacher& UniversityTeacher::operator=(const UniversityTeacher& other) {
    if (this != &other) {
        delete[] name;
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        position = other.position;
        salary = other.salary;
        moneyEarnForDay = other.moneyEarnForDay;
    }
    return *this;
}

UniversityTeacher::~UniversityTeacher() {
    delete[] name;
}

Position UniversityTeacher::getPosition() const {
    return position;
}

void UniversityTeacher::setPosition(Position position) {
    this->position = position;
}

double UniversityTeacher::getSalary() const {
    return salary;
}

void UniversityTeacher::setSalary(double salary) {
    this->salary = salary;
}

bool UniversityTeacher::operator!=(const UniversityTeacher& other) {
    return strcmp(name, other.name) != 0;
}

bool UniversityTeacher::operator==(const UniversityTeacher& other) {
    return strcmp(name, other.name) == 0;
}

std::ostream &operator<<(std::ostream &os, const UniversityTeacher &ut) {
    os << "Name: " << ut.name << "\n"
       << "Position: " << ut.position << "\n"
       << "Salary: " << ut.salary << "\n"
       << "Money earned per day: " << ut.moneyEarnForDay << "\n";
    return os;
}

class University {
    UniversityTeacher *teachers;
    int teachersCount;

public:
    University();
    ~University();
    friend std::ostream &operator<<(std::ostream &os, const University &ut);
    void addNewTeacher(UniversityTeacher& teacher); 
    void fireTeacher(UniversityTeacher& teacher);
    void promoteTeacher(UniversityTeacher& teacher);
    void reduceSalary(Position position, double amount);
    void fireTeachers(Position position);
};

University::University() : teachers(), teachersCount(0) {}

University::~University() {
    delete[] teachers;
}

void University::addNewTeacher(UniversityTeacher& teacher) {
    UniversityTeacher *newTeachers = new UniversityTeacher[teachersCount + 1];
    for (int i = 0; i < teachersCount; i++) {
        newTeachers[i] = teachers[i];
    }
    newTeachers[teachersCount] = teacher;
    delete[] teachers;
    teachersCount++;
    teachers = newTeachers;
}

void University::fireTeacher(UniversityTeacher& teacher) {
    UniversityTeacher *newTeachers = new UniversityTeacher[teachersCount - 1];
    int index = 0;
    for (int i = 0; i < teachersCount; i++) {
        if (teachers[i] != teacher) {
            newTeachers[index] = teachers[i];
            index++;
        }
    }
    delete[] teachers;
    teachersCount--;
    teachers = newTeachers;
}

void University::promoteTeacher(UniversityTeacher& teacher) {
    for (int i = 0; i < teachersCount; i++) {
        if (teachers[i] == teacher) {
            teachers[i].setPosition((Position)(teachers[i].getPosition() + 1));
            teachers[i].setSalary(teachers[i].getSalary() + 100);
        }
    }
}

void University::reduceSalary(Position position, double amount) {
    for (int i = 0; i < teachersCount; i++) {
        if (teachers[i].getPosition() == position) {
            teachers[i].setSalary(teachers[i].getSalary() - amount);
        }
    }
}

void University::fireTeachers(Position position) {
    UniversityTeacher *newTeachers = new UniversityTeacher[teachersCount];
    int index = 0;
    for (int i = 0; i < teachersCount; i++) {
        if (teachers[i].getPosition() != position) {
            newTeachers[index] = teachers[i];
            index++;
        }
    }
    delete[] teachers;
    teachersCount = index;
    teachers = newTeachers;
}

std::ostream &operator<<(std::ostream &os, const University &u) {
    std::cout << "Teachers count: " << u.teachersCount << "\n";
    for (int i = 0; i < u.teachersCount; i++) {
        os << u.teachers[i] << "\n";
    }
    return os;
}

int main() {
    UniversityTeacher teacher1("Ivan Ivanov", Position::ASSISTANT, 1000, 100);
    UniversityTeacher teacher2("Petar Petrov", Position::HEAD_ASSISTANT, 2000, 200);
    UniversityTeacher teacher3("Georgi Georgiev", Position::DOCENT, 3000, 300);
    University university;
    university.addNewTeacher(teacher1);
    university.addNewTeacher(teacher2);
    university.addNewTeacher(teacher3);
    university.fireTeacher(teacher2);
    university.promoteTeacher(teacher1);
    university.reduceSalary(Position::DOCENT, 300);
    university.fireTeachers(Position::DOCENT);
    std::cout << university;
    return 0;
}
