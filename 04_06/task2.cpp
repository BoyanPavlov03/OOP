#include <iostream>
#include <fstream>

class Student {
    char *name;
    int age;

public:
    Student(const char *name = "\0", const int age = 0);
    Student(const Student& other);
    Student& operator=(const Student& other);

    friend std::ostream &operator<<(std::ostream &os, const Student &student);
    friend std::istream &operator>>(std::istream &is, Student &student);
};

Student::Student(const char *name, const int age)
: name(new char[strlen(name) + 1]), age(age) {
    strcpy(this->name, name);
}

Student::Student(const Student& other)
: name(new char[strlen(other.name) + 1]), age(other.age) {
    strcpy(this->name, other.name);
}

Student& Student::operator=(const Student& other) {
    if (&other != this) {
        delete[] name;

        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        age = other.age;
    }

    return *this;
}

std::ostream &operator<<(std::ostream &os, const Student &student) {
    size_t size_name = strlen(student.name) + 1;
    os.write((const char*)&size_name, sizeof(size_t));
    os.write(student.name, size_name);

    os.write((const char*)&student.age, sizeof(int));
    return os;
}

std::istream &operator>>(std::istream &is, Student &student) {
    size_t size;
    is.read((char*)&size, sizeof(size_t));
    delete[] student.name;
    std::cout << size << std::endl;
    student.name = new char[size];
    is.read(student.name, size);   
    is.read((char*)&student.age, sizeof(int));
    return is;
}

class University {
    char *name;
    Student* students;
    unsigned int studentsCount;

public: 
    University(const char* name = "\0", const Student* students = nullptr, unsigned int studentsCount = 0);
    University(const University& other);
    University& operator=(const University& other);

    friend std::ostream &operator<<(std::ostream &os, const University &uni);
    friend std::istream &operator>>(std::istream &is, University &uni);

    void add_student(const Student& student);
    void read_binary();
    void write_binary();
};

University::University(const char* name, const Student* students, unsigned int studentsCount)
: name(new char[strlen(name) + 1]), students(new Student[studentsCount]), studentsCount(studentsCount) {
    strcpy(this->name, name);
    for(int i = 0; i < studentsCount; i++) {
        this->students[i] = students[i];
    }
}

University::University(const University& other)
: name(new char[strlen(other.name) + 1]), 
  students(new Student[other.studentsCount]), 
  studentsCount(other.studentsCount) {
    strcpy(this->name, other.name);
    for(int i = 0; i < other.studentsCount; i++) {
        this->students[i] = other.students[i];
    }
}

University& University::operator=(const University& other) {
    if (&other != this) {
        delete[] students;
        delete[] name;

        name = new char[strlen(other.name) + 1];
        students = new Student[other.studentsCount];
        strcpy(this->name, other.name);
        for(int i = 0; i < other.studentsCount; i++) {
            this->students[i] = other.students[i];
        }
        this->studentsCount = other.studentsCount;
    }

    return *this;
}

std::ostream &operator<<(std::ostream &os, const University &uni) {
    os << "University name: " << uni.name << "\n"
       << "University students(" << uni.studentsCount << "):\n";

    for(int i = 0; i < uni.studentsCount; i++) {
        os << uni.students[i];
    }

    return os;
}

std::istream &operator>>(std::istream &is, University &uni) {
    char buffer[1024];

    std::cout << "Enter uni name: ";
    is.getline(uni.name, 1024);
    uni.name = new char[strlen(buffer) + 1];
    strcpy(uni.name, buffer);

    std::cout << "Enter students count: ";
    is >> uni.studentsCount;

    uni.students = new Student[uni.studentsCount];
    for(int i = 0; i < uni.studentsCount; i++) {
        is >> uni.students[i];
    }

    return is;
}

void University::add_student(const Student& student) {
    Student* newStudents = new Student[studentsCount + 1];
    for(int i = 0; i < studentsCount; i++) {
        newStudents[i] = students[i];
    }
    newStudents[studentsCount] = student;
    delete[] students;

    students = newStudents;
    studentsCount++;
}

void University::read_binary() {
    char filename[1024] = "binary_";
    strcat(filename, name);
    strcat(filename, ".dat");
    std::ifstream in(filename, std::ios::binary);

    if (!in) {
        std::cout << "Can't open file!\n";
    } else {

        size_t size_name;
        in.read((char*)&size_name, sizeof(size_t));
        delete[] name;
        name = new char[size_name];
        in.read(name, size_name);

        in.read((char*)&studentsCount, sizeof(unsigned int));
    
        delete[] students;
        students = new Student[studentsCount];
        for(int i = 0; i < studentsCount; i++) {
            in >> students[i];
        }
        
        in.close();
    }
}

void University::write_binary() {
    char filename[1024] = "binary_";
    strcat(filename, name);
    strcat(filename, ".dat");
    std::ofstream out(filename, std::ios::binary);

    if (!out) {
        std::cout << "Can't open file!\n";
    } else {
        size_t size_name = strlen(name) + 1;
        out.write((const char*)&size_name, sizeof(size_t));
        out.write(name, size_name);

        out.write((const char*)&studentsCount, sizeof(unsigned int));

        for(int i = 0; i < studentsCount; i++) {
            out << students[i];
        }
        
        out.close();
    }
}

int main() {
    University uni("SU");
    uni.add_student(Student("Gosho", 15));
    uni.add_student(Student("Pesho", 12));
    uni.write_binary();
    return 0;
}