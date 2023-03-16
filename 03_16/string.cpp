#include <iostream>

class MyString {
    char *arr;
    int capacity;

public:
    MyString(const char* arr = "");
    ~MyString();
    MyString(const MyString& other);
    MyString& operator=(const MyString& other);
    int size() const;
    int getCapacity() const;
    char* c_str() const;
    char at(unsigned index) const;
    void push_back(char c);
    void pop_back();
    int find(char c, unsigned startPos = 0);
    bool empty();
    MyString substr(unsigned pos = 0, unsigned n = 0);
    void append(const MyString& str);
    void append(const char* str);
    friend std::ostream &operator<<(std::ostream &os, const MyString &str);
};

MyString::MyString(const char* arr) : arr(new char[strlen(arr) + 1]) {
    strcpy(this->arr, arr);
    capacity = strlen(arr) + 1;
}

MyString::~MyString() {
    delete[] arr;
}

MyString::MyString(const MyString& other) : arr(new char[strlen(other.arr) + 1]) {
    strcpy(this->arr, other.arr);
    if (capacity < other.capacity) {
        capacity = other.capacity;
    }
}

MyString& MyString::operator=(const  MyString& other) {
    if (this != &other) {
        delete[] arr;
        arr = new char[strlen(other.arr) + 1];
        strcpy(arr, other.arr);
        if (capacity < other.capacity) {
            capacity = other.capacity;
        }
    }
    return *this;
}

std::ostream &operator<<(std::ostream &os, const MyString &str) {
    os << str.arr << "\n";
    return os;
}

int MyString::size() const {
    return strlen(arr);
}

int MyString::getCapacity() const {
    return capacity;
}

char* MyString::c_str() const {
    return arr;
}

char MyString::at(unsigned index) const {
    return arr[index];
}

void MyString::push_back(char c) {
    if (capacity == strlen(arr) + 1) {
        char *temp = new char[capacity + 1];
        strcpy(temp, arr);
        delete[] arr;
        arr = temp;
        capacity ++;
    }
    arr[strlen(arr)] = c;
    arr[strlen(arr) + 1] = '\0';
}

void MyString::pop_back() {
    arr[strlen(arr) - 1] = '\0';
}

int MyString::find(char c, unsigned startPos) {
    int size = this->size();
    for(int i = startPos; i < size; i++) {
        if (arr[i] == c) {
            return i;
        }
    }
    return -1;
}

bool MyString::empty() {
    return this->size() == 0;
}

MyString MyString::substr(unsigned pos, unsigned n) {
    int size = this->size();
    MyString substr;
    for(int i = pos; i < pos + n && i < size; i++) {
        substr.push_back(arr[i]);
    }
    return substr;
}

void MyString::append(const MyString& str) {
    int size = str.size();
    for(int i = 0; i < size; i++) {
        this->push_back(str.at(i));
    }
}

void MyString::append(const char* str) {
    int size = strlen(str);
    for(int i = 0; i < size; i++) {
        this->push_back(str[i]);
    }
}

int main() {
    MyString str1("We think in generalities, ");
    std::cout << str1;
    MyString str2("but we live in details.");
    str1.append(str2);
    std::cout << str1;
}