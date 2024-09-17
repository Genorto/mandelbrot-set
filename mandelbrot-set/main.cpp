#include "mandelbrot-set.h"
#include "constants.h"
#include <vector>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(kWindowLength, kWindowWidth), "Mandelbrot Set", sf::Style::Close);
    Point new_p1, new_p2;
    std::vector<std::pair<Point, Point>> history;
    size_t pos = 0;
    bool choosing = false;
    MandelbrotSet fractal;
    history.push_back(fractal.AddFrame(Point(0, 0), Point(kWindowLength, kWindowWidth)));

    /* selection area settings */
    sf::RectangleShape selection_area;
    selection_area.setOutlineColor(sf::Color(66, 133, 180));
    selection_area.setOutlineThickness(1);
    selection_area.setFillColor(sf::Color(66, 133, 180, 100));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (!choosing) {
                        new_p1 = Point(event.mouseButton.x, kWindowWidth - event.mouseButton.y);
                        choosing = true;
                    } else {
                        new_p2 = Point(event.mouseButton.x, kWindowWidth - event.mouseButton.y);
                        /* adding new frame */
                        Point temp_p1(std::min(new_p1.get_x(), new_p2.get_x()), std::min(new_p1.get_y(), new_p2.get_y())),
                            temp_p2(std::max(new_p1.get_x(), new_p2.get_x()), std::max(new_p1.get_y(), new_p2.get_y()));
                        history.erase(history.begin() + pos + 1, history.end());
                        history.push_back(fractal.AddFrame(temp_p1, temp_p2));
                        ++pos;
                        choosing = false;
                    }
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.scancode == sf::Keyboard::Scan::Left) {
                    choosing = false;
                    if (pos > 0) {
                        --pos;
                        fractal.SetFrame(history[pos].first, history[pos].second);
                    }
                } else if (event.key.scancode == sf::Keyboard::Scan::Right) {
                    choosing = false;
                    if (pos < history.size() - 1) {
                        ++pos;
                        fractal.SetFrame(history[pos].first, history[pos].second);
                    }
                } else if (event.key.scancode == sf::Keyboard::Scan::Escape) {
                    choosing = false;
                }
            }
        }

        window.clear(sf::Color::White);
        fractal.Draw(window);
        if (choosing) {
            /* drawing selection area */
            Point temp = Point(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            selection_area.setPosition(std::min(new_p1.get_x(), temp.get_x()), std::min(kWindowWidth - new_p1.get_y(), temp.get_y()));
            double length = abs(new_p1.get_x() - temp.get_x());
            double width = abs(kWindowWidth - new_p1.get_y() - temp.get_y());
            selection_area.setSize(sf::Vector2f(length, width));
            window.draw(selection_area);
        }
        window.display();
    }

    return 0;
}
