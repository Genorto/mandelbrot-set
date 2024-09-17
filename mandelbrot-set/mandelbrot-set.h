#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>
#include "point.h"

class MandelbrotSet {
public:
    MandelbrotSet();
    MandelbrotSet(const MandelbrotSet& other);
    MandelbrotSet operator=(const MandelbrotSet& other);
    MandelbrotSet(const MandelbrotSet&& other);
    MandelbrotSet operator=(const MandelbrotSet&& other);
    std::pair<Point, Point> AddFrame(Point p1, Point p2);
    void SetFrame(Point p1, Point p2);
    void Draw(sf::RenderWindow& window);

private:
    std::vector<std::vector<sf::Color>> grid_;
    Point p1_, p2_;
    void Swap(MandelbrotSet& other) {
        std::swap(grid_, other.grid_);
    }
    void Update();
};
