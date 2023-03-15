#include <iostream>

class Point {
    double x;
    double y;
    double z;

public:
    Point(double x, double y, double z);
    friend std::ostream &operator<<(std::ostream &os, const Point &point);
};

Point::Point(double x, double y, double z) : x(x), y(y), z(z) {}

std::ostream &operator<<(std::ostream &os, const Point &point) {
    os << "X: " << point.x << "\n"
       << "Y: " << point.y << "\n"
       << "Z: " << point.z << "\n";
    return os;
}

class Cube {
    Point startPoint;
    double width;

public:
    Cube(Point startPoint, double width);
    double volume() const;
    friend std::ostream &operator<<(std::ostream &os, const Cube &cube);
};

Cube::Cube(Point startPoint, double width) : startPoint(startPoint), width(width) {}

double Cube::volume() const {
    return width * width * width;
}

std::ostream &operator<<(std::ostream &os, const Cube &cube) {
    os << "Start point: \n" << cube.startPoint << "\n"
       << "Side: " << cube.width << "\n"
       << "Volume: " << cube.volume() << "\n";
    return os;
}

class Cuboid {
    Point startPoint;
    double width;
    double height;
    double length;

public:
    Cuboid(Point startPoint, double width, double height, double length);
    double volume() const;
    friend std::ostream &operator<<(std::ostream &os, const Cuboid &cuboid);
};

Cuboid::Cuboid(Point startPoint, double width, double height, double length) 
    : startPoint(startPoint), width(width), height(height), length(length) {}

double Cuboid::volume() const {
    return width * height * length;
}

std::ostream &operator<<(std::ostream &os, const Cuboid &cuboid) {
    os << "Start point: \n" << cuboid.startPoint << "\n"
       << "Width: " << cuboid.width << "\n"
       << "Height: " << cuboid.height << "\n"
       << "Length: " << cuboid.length << "\n"
       << "Volume: " << cuboid.volume() << "\n";
    return os;
}

class Sphere {
    Point center;
    double radius;

public:
    Sphere(Point center, double radius);
    double volume() const;
    friend std::ostream &operator<<(std::ostream &os, const Sphere &circle);
};

Sphere::Sphere(Point center, double radius) : center(center), radius(radius) {}

double Sphere::volume() const {
    return (4/3)*(3.14 * radius * radius * radius);
}

std::ostream &operator<<(std::ostream &os, const Sphere &sphere) {
    os << "Center point: \n" << sphere.center << "\n"
       << "Radius: " << sphere.radius << "\n"
       << "Area: " << sphere.volume() << "\n";
    return os;
}

int main() {
    Point point(1, 2, 3);
    std::cout << point << std::endl;

    Cube cube(point, 5);
    std::cout << cube << std::endl;

    Cuboid cuboid(point, 5, 6, 7);
    std::cout << cuboid << std::endl;

    Sphere sphere(point, 5);
    std::cout << sphere << std::endl;

    return 0;
}