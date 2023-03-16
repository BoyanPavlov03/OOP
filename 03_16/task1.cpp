#include <iostream>

class Book {
    char *name;
    char *author;
    int releaseYear;
    int price;

public:
    Book(const char* name = "", const char* author = "", const int releaseYear = 1970, const int price = 0);
    Book(const Book& other);
    ~Book();
    Book& operator=(const Book& other);
    char* getName() const;
    char* getAuthor() const;
    int getReleaseYear() const;
    int getPrice() const;
    void setName(char *name);
    void setAuthor(char *author);
    void setReleaseYear(int releaseYear);
    void setPrice(int price);
};

Book::Book(const char* name, const char* author, const int releaseYear, const int price) 
    : name(new char[strlen(name) + 1]), author(new char[strlen(author) + 1]),
    releaseYear(releaseYear), price(price) {
        strcpy(this->name, name);
        strcpy(this->author, author);
}

Book::Book(const Book& other) : name(new char[strlen(other.name) + 1]), author(new char[strlen(other.author) + 1]),
    releaseYear(other.releaseYear), price(other.price) {
    strcpy(name, other.name);
    strcpy(author, other.author);
}

Book& Book::operator=(const Book& other) {
    if (this != &other) {
        delete[] name;
        delete[] author;
        name = new char[strlen(other.name) + 1];
        author = new char[strlen(other.author) + 1];
        strcpy(name, other.name);
        strcpy(author, other.author);
        releaseYear = other.releaseYear;
        price = other.price;
    }
    return *this;
}

Book::~Book() {
    delete[] name;
    delete[] author;
}

class BookStore {
    char* name;
    Book* books;
    int bookCount;

public:
    BookStore(const char* name, const Book* books, const int bookCount);
    ~BookStore();
};

BookStore::BookStore(const char* name, const Book* books, const int bookCount)
    : name(new char[strlen(name) + 1]), books(new Book[bookCount]) {
    strcpy(this->name, name);
    for(int i = 0; i < bookCount; i++) {
        this->books[i] = books[i];
    }
}

BookStore::~BookStore() {
    delete[] name;
    delete[] books;
}

int main() {
    return 0;
}

