#include <iostream>

class IntArr {
    int *arr;
    unsigned int length;

public:
    IntArr(const int* arr, unsigned int length);
    IntArr(const IntArr& other);
    ~IntArr();
    IntArr& operator=(const IntArr& other);

    int& operator[](int index);
    void push_back(int newElement);
    bool contains(int element);
    bool isEmpty();
    int size();
};

IntArr::IntArr(const int* arr, unsigned int length) : arr(new int[length]), length(length) {
    for(int i = 0; i < length; i++) {
        this->arr[i] = arr[i];
    }
}

IntArr::IntArr(const IntArr& other) : arr(new int[other.length]), length(other.length) {
    for(int i = 0; i < other.length; i++) {
        this->arr[i] = arr[i];
    }
}

IntArr::~IntArr() {
    delete[] arr;
}

IntArr& IntArr::operator=(const IntArr& other) {
    if (&other != this) {
        delete[] arr;
        arr = new int[other.length];
        length = other.length;
        for(int i = 0; i < other.length; i++) {
            this->arr[i] = arr[i];
        }
    }
    return *this;
}

void IntArr::push_back(int newElement) {
    int *temp = new int[length + 1];
    for (int i = 0; i < length; i++) {
        temp[i] = arr[i];
    }
    temp[length] = newElement;
    delete[] arr;
    arr = temp;
}

bool IntArr::contains(int element) {
    for(int i = 0; i < length; i++) {
        if (arr[i] == element) {
            return true;
        }
    }
    return false;
}

bool IntArr::isEmpty() {
    return length == 0;
}

int IntArr::size() {
    return length;
}

int& IntArr::operator[](int index) {
    return arr[index];
}

int main() {
    int normal_arr[] = {1,2,3,4};
    IntArr int_arr(normal_arr, 4);

    std::cout << int_arr[2];
    return 0;
}