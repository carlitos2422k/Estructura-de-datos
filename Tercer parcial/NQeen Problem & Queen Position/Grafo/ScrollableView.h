#pragma once 
#include <SFML/Graphics.hpp>

class ScrollableView {
private:
    sf::View view;
    sf::RenderWindow& window;
    float scrollSpeed;

public:
    ScrollableView(sf::RenderWindow& window, float scrollSpeed = 10.0f) 
        : window(window), scrollSpeed(scrollSpeed) {
        view = window.getDefaultView();
    }

    void handleScroll(float delta) {
        view.move(0, delta * scrollSpeed);
        window.setView(view);
    }

    void reset() {
        view = window.getDefaultView();
        window.setView(view);
    }
};