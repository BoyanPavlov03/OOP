#include <iostream>

class Point {
    double x;
    double y;

public:
    Point(double x, double y);
    int whichQuadrant();
    friend std::ostream &operator<<(std::ostream &os, const Point &point);
};

Point::Point(double x, double y) : x(x), y(y) {}

std::ostream &operator<<(std::ostream &os, const Point &point) {
    os << "X: " << point.x << "\n"
       << "Y: " << point.y << "\n";
    return os;
}

int Point::whichQuadrant() {
    if (x >= 0.0 && y >= 0.0) {
        return 1;
    } else if (x <= 0.0 && y >= 0.0) {
        return 2;
    } else if (x <= 0.0 && y <= 0.0) {
        return 3;
    } else {
        return 4;
    }
}

class Square {
    Point startPoint;
    double width;

public:
    Square(Point startPoint, double width);
    double area() const;
    friend std::ostream &operator<<(std::ostream &os, const Square &square);
};

Square::Square(Point startPoint, double width) : startPoint(startPoint), width(width) {}

double Square::area() const {
    return width * width;
}

std::ostream &operator<<(std::ostream &os, const Square &square) {
    os << "Start point: \n" << square.startPoint << "\n"
       << "Side: " << square.width << "\n"
       << "Area: " << square.area() << "\n";
    return os;
}

class Rectangle {
    Point startPoint;
    double width;
    double height;

public:
    Rectangle(Point startPoint, double width, double height);
    double area() const;
    friend std::ostream &operator<<(std::ostream &os, const Rectangle &rectangle);
};

Rectangle::Rectangle(Point startPoint, double width, double height) : startPoint(startPoint), width(width), height(height) {}

double Rectangle::area() const {
    return width * height;
}

std::ostream &operator<<(std::ostream &os, const Rectangle &rectangle) {
    os << "Start point: \n" << rectangle.startPoint << "\n"
       << "Width: " << rectangle.width << "\n"
       << "Height: " << rectangle.height << "\n"
       << "Area: " << rectangle.area() << "\n";
    return os;
}

class Circle {
    Point center;
    double radius;

public:
    Circle(Point center, double radius);
    double area() const;
    friend std::ostream &operator<<(std::ostream &os, const Circle &circle);
};

Circle::Circle(Point center, double radius) : center(center), radius(radius) {}

double Circle::area() const {
    return 3.14 * radius * radius;
}

std::ostream &operator<<(std::ostream &os, const Circle &circle) {
    os << "Center point: \n" << circle.center << "\n"
       << "Radius: " << circle.radius << "\n"
       << "Area: " << circle.area() << "\n";
    return os;
}

int main() {
    Point point(1.0, 2.0);
    Square square(point, 2.0);
    Rectangle rectangle(point, 2.0, 3.0);
    Circle circle(point, 2.0);

    std::cout << square << rectangle << circle;
    return 0;
}