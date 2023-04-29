#pragma once

class Person {
protected:
    char* name;
    unsigned int age;
public:
    explicit Person(const char *name = "\0", unsigned int age = 0);
    Person(const Person &other);
};