#include <iostream>

class Room {
    double area;
    char description[30];

public:
    Room(double area = 0, const char description[] = "\0");
    Room(const Room& other);
    Room& operator=(const Room& other);

    void setArea(double area);
    void setDescription(const char description[]);
    char* getDescription();
    double getArea();

    friend std::ostream &operator<<(std::ostream &os, const Room &room);
    friend std::istream &operator>>(std::istream &is, Room &room);
};

Room::Room(double area = 0, const char description[] = "\0")
: area(area), description() {
    strcpy(this->description, description);
}

Room::Room(const Room& other)
: area(area), description() {
    strcpy(this->description, description);
}

Room& Room::operator=(const Room& other) {
    if (&other != this) {
        strcpy(description, other.description);
        area = other.area;
    }

    return *this;
}

void Room::setArea(double area) {
    this->area = area;
}

void Room::setDescription(const char description[]) {
    strcpy(this->description, description);
}

double Room::getArea() {
    return area;
}

char* Room::getDescription() {
    return description;
}

std::ostream &operator<<(std::ostream &os, const Room &room) {
    os << "Room: \nArea: " << room.area << "\n"
       << "Description: " << room.description << "\n";
    return os;
}

std::istream &operator>>(std::istream &is, Room &room) {
    std::cout << "Enter area: ";
    is >> room.area;
    std::cout << "Enter description: ";
    is.getline(room.description, 30);
    return is;
}

class Apartment {
    Room* rooms;
    unsigned int roomCount;

public: 
    Apartment(Room* rooms, unsigned int roomCount = 0);
    Apartment(const Apartment& other);
    Apartment& operator=(const Apartment& other);

    void setRooms(Room* rooms);
    Room* getRooms();
    unsigned int getRoomCount();

    friend std::ostream &operator<<(std::ostream &os, const Apartment &room);
    friend std::istream &operator>>(std::istream &is, Apartment &room);

    double totalArea() const;
    Room* operator[](char description[]);

    bool operator>(const Apartment& other) const;
    bool operator>=(const Apartment& other) const;
    bool operator==(const Apartment& other) const;
    bool operator<=(const Apartment& other) const;
    bool operator<(const Apartment& other) const;
};

Apartment::Apartment(Room* rooms, unsigned int roomCount)
: rooms(new Room[roomCount]), roomCount(roomCount) {
    this->rooms = rooms;
}

Apartment::Apartment(const Apartment& other)
: rooms(new Room[other.roomCount]), roomCount(other.roomCount) {
    this->rooms = other.rooms;
}

Apartment& Apartment::operator=(const Apartment& other) {
    if (&other != this) {
        delete[] rooms;
        this->rooms = other.rooms;
        this->roomCount = other.roomCount;
    }

    return *this;
}

void Apartment::setRooms(Room* rooms) {
    delete[] this->rooms;
    this->rooms = rooms;
}

Room* Apartment::getRooms() {
    return rooms;
}

unsigned int Apartment::getRoomCount() {
    return roomCount;
}

std::ostream &operator<<(std::ostream &os, const Apartment &ap) {
    os << "Rooms(" << ap.roomCount << "):\n";
    for(int i = 0; i < ap.roomCount; i++) {
        os << ap.rooms[i];
    }

    return os;
}

std::istream &operator>>(std::istream &is, Apartment &ap) {
    std::cout << "Enter rooms amount: ";
    is >> ap.roomCount;
    std::cout << "Enter rooms: ";
    for(int i = 0; i < ap.roomCount; i++) {
        is >> ap.rooms[i];
    }

    return is;
}

double Apartment::totalArea() const {
    double sum = 0.0;
    for(int i = 0; i < roomCount; i++) {
        sum += rooms[i].getArea();
    } 
    return sum;
}

Room* Apartment::operator[](char description[]) {
    for(int i = 0; i < roomCount; i++) {
        if (strcmp(rooms[i].getDescription(), description) == 0) {
            return &rooms[i];
        }
    }
    return nullptr;
}

bool Apartment::operator>(const Apartment& other) const {
    return this->totalArea() > other.totalArea();
}

bool Apartment::operator<(const Apartment& other) const {
    return this->totalArea() < other.totalArea();
}

bool Apartment::operator==(const Apartment& other) const {
    return this->totalArea() == other.totalArea();
}

bool Apartment::operator>=(const Apartment& other) const {
    return this->totalArea() >= other.totalArea();
}

bool Apartment::operator<=(const Apartment& other) const {
    return this->totalArea() <= other.totalArea();
}

int main() {
    return 0;
}