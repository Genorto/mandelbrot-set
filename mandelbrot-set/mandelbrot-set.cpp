#include "mandelbrot-set.h"
#include "complex-number.h"
#include "constants.h"
#include <iostream>

MandelbrotSet::MandelbrotSet() {
    grid_.assign(kWindowLength + 1, std::vector<sf::Color>(kWindowWidth + 1, sf::Color(0, 0, 0)));
    p1_ = Point(-2, 2);
    p2_ = Point(2, -2);
}

MandelbrotSet::MandelbrotSet(const MandelbrotSet& other) {
    grid_ = other.grid_;
    p1_ = other.p1_;
    p2_ = other.p2_;
}

MandelbrotSet MandelbrotSet::operator=(const MandelbrotSet& other) {
    MandelbrotSet buffer = other;
    Swap(buffer);
    return *this;
}

MandelbrotSet::MandelbrotSet(const MandelbrotSet&& other) {
    grid_ = std::move(other.grid_);
    p1_ = std::move(other.p1_);
    p2_ = std::move(other.p2_);
}

MandelbrotSet MandelbrotSet::operator=(const MandelbrotSet&& other) {
    MandelbrotSet buffer = other;
    Swap(buffer);
    return *this;
}

std::pair<Point, Point> MandelbrotSet::AddFrame(Point p1, Point p2) {
    double length = abs(p1_.get_x() - p2_.get_x());
    double width = abs(p1_.get_y() - p2_.get_y());
    double x1 = p1_.get_x();
    double y2 = p2_.get_y();
    p1_ = Point((p1.get_x() * length) / kWindowLength + x1, ((kWindowWidth - p1.get_y()) * width) / kWindowWidth + y2);
    p2_ = Point((p2.get_x() * length) / kWindowLength + x1, ((kWindowWidth - p2.get_y()) * width) / kWindowWidth + y2);
    Update();
    return { p1_, p2_ };
}

void MandelbrotSet::SetFrame(Point p1, Point p2) {
    p1_ = p1;
    p2_ = p2;
    Update();
}

void MandelbrotSet::Draw(sf::RenderWindow& window) {
    for (size_t x = 0; x <= kWindowLength; ++x) {
        for (size_t y = 0; y <= kWindowWidth; ++y) {
            sf::VertexArray point(sf::Points, 1);
            point[0].position = sf::Vector2f(x, y);
            point[0].color = grid_[x][y];
            window.draw(point);
        }
    }
}

/* updating all points */
void MandelbrotSet::Update() {
    double length = abs(p1_.get_x() - p2_.get_x());
    double width = abs(p1_.get_y() - p2_.get_y());
    for (int64_t x = 0; x <= kWindowLength; ++x) {
        for (int64_t y = 0; y <= kWindowWidth; ++y) {
            ComplexNumber z(0.0f, 0.0f);
            ComplexNumber c((x * length) / kWindowLength + p1_.get_x(), y * width / kWindowWidth + p2_.get_y());
            size_t n = 0;
            for (; n < 255; ++n) {
                if (z.get_length() >= 4) break;
                z = z * z + c;
            }
            if (n <= 122) grid_[x][y] = sf::Color(n / 2, n, n / 2);
            else if (n > 122) grid_[x][y] = sf::Color((255 - n) / 2, 255 - n, (255 - n) / 2);
        }
    }
}
