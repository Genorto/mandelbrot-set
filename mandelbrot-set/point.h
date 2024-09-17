#pragma once

class Point {
public:
    Point() : x_(0), y_(0) {}
    Point(double x, double y) : x_(x), y_(y) {}
    double get_x() {
        return x_;
    }
    double get_y() {
        return y_;
    }

private:
    double x_, y_;
};
